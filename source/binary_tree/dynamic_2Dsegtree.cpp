template <class S, S (*op)(S, S), S (*e)()> class dynamic_segtree {
public:
    dynamic_segtree(size_t n) : n(n), root(nullptr) {}
    
    dynamic_segtree(dynamic_segtree&&) = default;
    dynamic_segtree& operator=(dynamic_segtree&&) = default;

    void set(size_t p, S x) {
        assert(p < n);
        set(root, 0, n, p, x);
    }

    S get(size_t p) const {
        assert(p < n);
        return get(root, 0, n, p);
    }

    S prod(size_t l, size_t r) const {
        assert(l <= r && r <= n);
        return prod(root, 0, n, l, r);
    }

    S all_prod() const { return root ? root->product : e(); }

    void reset(size_t l, size_t r) {
        assert(l <= r && r <= n);
        return reset(root, 0, n, l, r);
    }

private:
    struct node;
    using node_ptr = std::unique_ptr<node>;

    struct node {
        size_t index;
        S value, product;
        node_ptr left, right;

        node(size_t index, S value)
            : index(index), value(value), product(value),
              left(nullptr), right(nullptr) {}

        void update() {
            product = op(op(left ? left->product : e(), value),
                         right ? right->product : e());
        }
    };

    const size_t n;
    node_ptr root;

    void set(node_ptr& t, size_t a, size_t b, size_t p, S x) const {
        if (!t) {
            t = std::make_unique<node>(p, x);
            return;
        }
        if (t->index == p) {
            t->value = x;
            t->update();
            return;
        }
        size_t c = (a + b) >> 1;
        if (p < c) {
            if (t->index < p) std::swap(t->index, p), std::swap(t->value, x);
            set(t->left, a, c, p, x);
        } else {
            if (p < t->index) std::swap(p, t->index), std::swap(x, t->value);
            set(t->right, c, b, p, x);
        }
        t->update();
    }

    S get(const node_ptr& t, size_t a, size_t b, size_t p) const {
        if (!t) return e();
        if (t->index == p) return t->value;
        size_t c = (a + b) >> 1;
        if (p < c) return get(t->left, a, c, p);
        else return get(t->right, c, b, p);
    }

    S prod(const node_ptr& t, size_t a, size_t b, size_t l, size_t r) const {
        if (!t || b <= l || r <= a) return e();
        if (l <= a && b <= r) return t->product;
        size_t c = (a + b) >> 1;
        S result = prod(t->left, a, c, l, r);
        if (l <= t->index && t->index < r) result = op(result, t->value);
        return op(result, prod(t->right, c, b, l, r));
    }

    void reset(node_ptr& t, size_t a, size_t b, size_t l, size_t r) const {
        if (!t || b <= l || r <= a) return;
        if (l <= a && b <= r) {
            t.reset();
            return;
        }
        size_t c = (a + b) >> 1;
        reset(t->left, a, c, l, r);
        reset(t->right, c, b, l, r);
        t->update();
    }
};

template <class S, S (*op)(S, S), S (*e)()> class segtree_2d {
private:
    int n; 
    size_t m; 
    std::vector<dynamic_segtree<S, op, e>> tree;

public:
    segtree_2d(int n, size_t m) : n(n), m(m) {
        tree.reserve(2 * n);
        for (int i = 0; i < 2 * n; ++i) {
            tree.emplace_back(m);
        }
    }

    void set(int x, size_t y, S val) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < m);
        x += n;
        tree[x].set(y, val);
        while (x > 1) {
            x >>= 1;
            S left_val = tree[2 * x].get(y);
            S right_val = tree[2 * x + 1].get(y);
            tree[x].set(y, op(left_val, right_val));
        }
    }

    S get(int x, size_t y) const {
        assert(0 <= x && x < n);
        assert(0 <= y && y < m);
        return tree[x + n].get(y);
    }

    S prod(int l_x, int r_x, size_t l_y, size_t r_y) const {
        assert(0 <= l_x && l_x <= r_x && r_x <= n);
        assert(0 <= l_y && l_y <= r_y && r_y <= m);
        S sml = e(), smr = e();
        l_x += n;
        r_x += n;

        while (l_x < r_x) {
            if (l_x & 1) sml = op(sml, tree[l_x++].prod(l_y, r_y));
            if (r_x & 1) smr = op(tree[--r_x].prod(l_y, r_y), smr);
            l_x >>= 1;
            r_x >>= 1;
        }
        return op(sml, smr);
    }
};

using S = pair<int, int>;
S op(S a, S b) {
    return S{min(a.first, b.first), max(a.second, b.second)};
}
S e() {
    return S{inf, -inf};
}