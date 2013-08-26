struct edge
{
    int from, to, dist;
};

struct bellmanford
{
    int n, m;
    vector<edge> edges;
    vector<int> g[maxn];
    bool inq[maxn];
    int d[maxn];
    int p[maxn];
    int cnt[maxn];
    
    void init(int n)
    {
        this->n = n;
        for(int i = 1; i <= n; ++i) g[i].clear();
        edges.clear();
    }
    
    void addedge(int from, int to, double dist)
    {
        edges.push_back((edge){from, to, dist});
        m = edges.size();
        g[from].push_back(m - 1);
    }
    
    bool negativecycle()
    {
        queue<int> qu;
        memset(inq, 0, sizeof(inq));
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= n; ++i) { d[i] = 0; inq[i] = true; qu.push(i); }
        d[1] = 0;
        while(!qu.empty())
        {
            int u = qu.front(); qu.pop();
            inq[u] = false;
            for(int i = 0; i < g[u].size(); ++i)
            {
                edge & e = edges[g[u][i]];
                if(d[e.to] > d[u] + e.dist)
                {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = g[u][i];
                    if(!inq[e.to])
                    {
                        qu.push(e.to); inq[e.to] = true;
                        if(++cnt[e.to] >= n) return true;
                    }
                }
            }
        }
        return false;
    }
}b;
