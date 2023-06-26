// verified in : https://techful-programming.com/user/skill/problem/coding/12549
// base : https://tubo28.me/compprog/algorithm/avl_tree/

#include <bits/stdc++.h>

#define be(v) (v).begin(),(v).end()
#define pb(q) push_back(q)
#define rep(i, n) for(int i=0;i<n;i++)
#define all(i, v) for(auto& i : v)
typedef long long ll;
using namespace std;
const ll mod=1000000007, INF=(1LL<<60);
#define doublecout(a) cout<<fixed<<setprecision(10)<<a<<endl;

using key_type = int;

enum { L, R };
struct avl_node {
    ll num;
    key_type key;
    std::array<avl_node *, 2> ch;
    int size;
    int height;
    ll sum;
    
    static avl_node *const nil;

    avl_node() : avl_node(0, key_type()) {}
    avl_node(ll nn, key_type key) : avl_node(nn, key, nil, nil, 1, 1, nn) {}
    avl_node(ll nn, const key_type key, avl_node *left, avl_node *right, int size, int height, ll sum)
        : num(nn), key(key), ch({{left, right}}), size(size), height(height), sum(sum) {}
};

avl_node *const avl_node::nil = new avl_node(0, key_type(), nullptr, nullptr, 0, 0, 0);
avl_node *const nil = avl_node::nil;
namespace init_nil {
int _ = (nil->ch = {{nil, nil}}, 0);
}

using np = avl_node *;
using cnp = const avl_node *;

np update(np n) {
    n->size = n->ch[L]->size + 1 + n->ch[R]->size;
    n->sum = n->ch[L]->sum + n->num + n->ch[R]->sum;
    n->height = std::max(n->ch[L]->height, n->ch[R]->height) + 1;
    return n;
}

template <int dir>
np rotate(np n) {
    assert(n->ch[!dir] != nil);
    np root = n->ch[!dir];
    n->ch[!dir] = root->ch[dir];
    root->ch[dir] = n;
    update(n);
    update(root);
    return root;
}

int balance_factor(np n) {
    assert(n != nil);
    return n->ch[R]->height - n->ch[L]->height;
}

np balance(np n) {
    assert(abs(balance_factor(n)) <= 2);
    if (balance_factor(n) == +2) {
        if (balance_factor(n->ch[R]) < 0) n->ch[R] = rotate<R>(n->ch[R]);
        return rotate<L>(n);
    } else if (balance_factor(n) == -2) {
        if (balance_factor(n->ch[L]) > 0) n->ch[L] = rotate<L>(n->ch[L]);
        return rotate<R>(n);
    } else {
        return n;
    }
}

np insert_at(np n, int k, key_type x) {
    assert(0 <= k && k <= n->size);
    if (n == nil) return new avl_node(0, x);
    int sl = n->ch[L]->size;
    if (k <= sl)
        n->ch[L] = insert_at(n->ch[L], k, x);
    else
        n->ch[R] = insert_at(n->ch[R], k - sl - 1, x);
    return balance(update(n));
}

template <int dir>
std::pair<np, np> remove_most(np n) {
    assert(n != nil);
    if (n->ch[dir] != nil) {
        np most;
        std::tie(n->ch[dir], most) = remove_most<dir>(n->ch[dir]);
        return {balance(update(n)), most};
    } else {
        np res = n->ch[!dir];
        n->ch[!dir] = nil;
        return {res, update(n)};
    }
}

std::pair<np, key_type> remove_at(np n, int k) {
    assert(n != nil);
    int sl = n->ch[L]->size;
    if (k < sl) {
        key_type most;
        std::tie(n->ch[L], most) = remove_at(n->ch[L], k);
        return {balance(update(n)), most};
    }
    if (k == sl) {
        if (n->ch[R] == nil) {
            return {n->ch[L], n->key};
        } else {
            np most;
            std::tie(n->ch[R], most) = remove_most<L>(n->ch[R]);
            most->ch = n->ch;
            // delete n;
            return {balance(update(most)), n->key};
        }
    } else {
        key_type most;
        std::tie(n->ch[R], most) = remove_at(n->ch[R], k - sl - 1);
        return {balance(update(n)), most};
    }
}

np merge_with_root(np l, np root, np r) {
    if (abs(l->height - r->height) <= 1) {
        root->ch = {{l, r}};
        return update(root);
    } else if (l->height > r->height) {
        l->ch[R] = merge_with_root(l->ch[R], root, r);
        return balance(update(l));
    } else {
        r->ch[L] = merge_with_root(l, root, r->ch[L]);
        return balance(update(r));
    }
}

np merge(np l, np r) {
    if (l == nil) return r;
    if (r == nil) return l;
    np m;
    if (l->height > r->height)
        std::tie(r, m) = remove_most<L>(r);
    else
        std::tie(l, m) = remove_most<R>(l);
    return merge_with_root(l, m, r);
}

std::pair<np, np> split_at(np n, int k) {
    assert(0 <= k && k <= n->size);
    if (n == nil) return {nil, nil};
    int sl = n->ch[L]->size;
    np l = n->ch[L];
    np r = n->ch[R];
    n->ch[L] = n->ch[R] = nil;
    np nl, nr;
    if (k < sl) {
        std::tie(nl, nr) = split_at(l, k);
        return {nl, merge_with_root(nr, n, r)};
    } else if (k == sl) {
        update(n);
        return {l, merge(n, r)};
    } else {
        std::tie(nl, nr) = split_at(r, k - sl - 1);
        return {merge_with_root(l, n, nl), nr};
    }
}

void update_at(np n, int k, key_type x) {
    assert(0 <= k && k < n->size);
    int sl = n->ch[L]->size;
    if (k < sl)
        update_at(n->ch[L], k, x);
    else if (k == sl)
        n->key = x;
    else
        update_at(n->ch[R], k - sl - 1, x);
    update(n);
}

np lower_bound(np n, key_type x) {
    if (n == nil) return nil;
    if (x <= n->key) {
        np res = lower_bound(n->ch[L], x);
        return res != nil ? res : n;
    } else {
        return lower_bound(n->ch[R], x);
    }
}

template <typename Iterator, typename Iterator1>
np build(Iterator left, Iterator right, Iterator1 left1, Iterator1 right1) {
    int n = right - left;
    Iterator mid = left + n / 2;
    Iterator1 mid1 = left1 + n / 2;
    if (n == 0) return nil;
    np l = build(left, mid, left1, mid1);
    np r = build(mid + 1, right, mid1 + 1, right1);
    np m = new avl_node(*mid, *mid1);
    m->ch = {{l, r}};
    return update(m);
}



int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false); 
    ll n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    map<char, int> mp;
    mp['A'] = 0;
    mp['C'] = 1;
    mp['G'] = 2;
    mp['T'] = 3;

    vector<vector<ll>> cnt(4, vector<ll> (n, 0));
    vector<vector<int>> ord(4, vector<int> (n, 0));
    rep(i, n) {
        cnt[mp[s[i]]][i] ++;
        rep(j, 4) ord[j][i] = j * n + i;
    }

    vector<np> root(4);
    rep(i, 4) root[i] = build(be(cnt[i]), be(ord[i]));

    // 前からa個、後ろからb個
    auto split3 = [&](np r, int a, int b) -> tuple<np, np, np>{
        auto [le, mr] = split_at(r, a);
        auto [mid, ri] = split_at(mr, n - a - b);
        return {le, mid, ri};
    };
    auto merge3 = [&](np a, np b, np c) {
        return merge(merge(a, b), c);
    };

    int key_id = n * 4;
    rep(i, q) {
        ll t, a, b;
        char c;
        cin >> t;
        if(t == 1) {
            cin >> a >> b;
            rep(j, 4) {
                auto [x, y, z] = split3(root[j], b, a);
                root[j] = merge3(x, z, y);
            }
        } else if(t == 2) {
            cin >> a >> c;
            ll idx = mp[c];
            rep(j, 4) {
                auto [x, y, z] = split3(root[j], a, 1);
                vector<ll> tmp(1, 0), tt(1, key_id++);
                if(idx == j) tmp[0] = 1;
                auto tmpr = build(be(tmp), be(tt));
                root[j] = merge3(x, tmpr, y);
            }
        } else {
            cin >> a >> b >> c;
            a--;
            ll idx = mp[c];
            auto [x, y, z] = split3(root[idx], a, n - b);
            cout << y->sum << endl;
            root[idx] = merge3(x, y, z);
        }
    }
    return 0; 
}
