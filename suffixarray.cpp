struct suffixarray
{
    int len;
    int sa[maxn], t[maxn], t2[maxn], c[maxn];
    int rank[maxn], height[maxn];
    int rmq[maxn][50];
    
    void build_sa(int * s, int n, int m)
    {
        int i, * x = t, * y = t2, * t;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) c[x[i] = s[i]]++;
        for(i = 1; i < m; ++i) c[i] += c[i - 1];
        for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for(i = n - k; i < n; ++i) y[p++] = i;
            for(i = 0; i < n; ++i) if(sa[i] >= k) y[p++] = sa[i] - k;
            for(i = 0; i < m; ++i) c[i] = 0;
            for(i = 0; i < n; ++i) c[x[y[i]]]++;
            for(i = 1; i < m; ++i) c[i] += c[i - 1];
            for(i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            t = x; x = y; y = t; p = 1;
            x[sa[0]] = 0;
            for(i = 1; i < n; ++i)
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            if(p >= n) break;
            m = p;
        }
    }

    void get_heigth(int * s, int n)
    {
        int i, j, k = 0;
        for(i = 1; i <= n; ++i) rank[sa[i]] = i;
        for(i = 0; i < n; ++i)
        {
            if(k) k--;
            j = sa[rank[i] - 1];
            while(s[i + k] == s[j + k]) k++;
            height[rank[i]] = k;
        }
    }

    void rmq_init()
    {
        for(int i = 1; i <= len; ++i) rmq[i][0] = height[i];
        for(int j = 1; (1 << j) <= len; ++j)
            for(int i = 1; i + j - 1 <= len; ++i)
                rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
    }

    int get_lcp(int a, int b)
    {
        int k = 0, l = min(rank[a], rank[b]) + 1, r = max(rank[a], rank[b]);
        while(((1 << (k + 1)) <= r - l + 1)) k++;
        return min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
    }
    
    void init(int * s, int n)
    {
        this->len = n;
        s[n] = 0;
        build_sa(s, n + 1, 30);
        get_heigth(s, n);
        rmq_init();
    }
}s;
