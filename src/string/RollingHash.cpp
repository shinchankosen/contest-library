struct RollingHash {
    static const int base1 = 1007, base2 = 2009;
    static const int mod1 = 1000000007, mod2 = 1000000009;
    int n;
    std::vector<long long> hash1, hash2, power1, power2;
    std::vector<long long> hash1_, hash2_, power1_, power2_;

    void rev_init(std::string S) {
        std::reverse(S.begin(), S.end());
        hash1_.assign(n+1, 0);
        hash2_.assign(n+1, 0);
        power1_.assign(n+1, 1);
        power2_.assign(n+1, 1);
        for (int i = 0; i < n; ++i) {
            hash1_[i+1] = (hash1_[i] * base1 + S[i]) % mod1;
            hash2_[i+1] = (hash2_[i] * base2 + S[i]) % mod2;
            power1_[i+1] = (power1_[i] * base1) % mod1;
            power2_[i+1] = (power2_[i] * base2) % mod2;
        }
    }
 
    // construct
    RollingHash(const std::string &S, int rev = 0) {
        n = (int)S.size();
        hash1.assign(n+1, 0);
        hash2.assign(n+1, 0);
        power1.assign(n+1, 1);
        power2.assign(n+1, 1);
        for (int i = 0; i < n; ++i) {
            hash1[i+1] = (hash1[i] * base1 + S[i]) % mod1;
            hash2[i+1] = (hash2[i] * base2 + S[i]) % mod2;
            power1[i+1] = (power1[i] * base1) % mod1;
            power2[i+1] = (power2[i] * base2) % mod2;
        }
        if(rev) rev_init(S);
    }
    
    // get hash of S[left:right)
    inline std::pair<long long, long long> get(int l, int r) const {
        long long res1 = hash1[r] - hash1[l] * power1[r-l] % mod1;
        if (res1 < 0) res1 += mod1;
        long long res2 = hash2[r] - hash2[l] * power2[r-l] % mod2;
        if (res2 < 0) res2 += mod2;
        return {res1, res2};
    }

    inline std::pair<long long, long long> get_rev(int l, int r) const {
        long long res1 = hash1_[r] - hash1_[l] * power1_[r-l] % mod1;
        if (res1 < 0) res1 += mod1;
        long long res2 = hash2_[r] - hash2_[l] * power2_[r-l] % mod2;
        if (res2 < 0) res2 += mod2;
        return {res1, res2};
    }

    // [l, r) is palindrome
    inline bool is_palindrome(int l, int r) const {
        int l_rev = n - r;
        int r_rev = n - l;
        return get(l, r) == get_rev(l_rev, r_rev);
    }
 
    // get lcp of S[a:) and T[b:)
    inline int getLCP(int a, int b) const {
        int len = std::min((int)hash1.size()-a, (int)hash1.size()-b);
        int low = -1, high = len;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid) != get(b, b+mid)) high = mid;
            else low = mid;
        }
        return low;
    }
};
