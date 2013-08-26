struct edge
{
    int from, to, dist;
};

struct heapnode
{
    int d, u;
    bool operator < (const heapnode & rhs) const
    {
        return d > rhs.d;
    }
};

struct dijkstra
{
    int n, m;
    vector<edge> edges;
    vector<int> g[maxn];
    bool done[maxn];
    int d[maxn], p[maxn];
    
    void init(int n)
    {
        this->n = n;
        for(int i = 0; i < n; ++i) g[i].clear();
        edges.clear();
    }
    
    void addedge(int from, int to, int dist)
    {
        edges.push_back((edge){from, to, dist});
        m = edges.size();
        g[from].push_back(m - 1);
    }
    
    void solve(int s)
    {
        priority_queue<heapnode> Q;
        memset(d, 0x3f, sizeof(d));
        d[s] = 0;
        memset(done, 0, sizeof(done));
        Q.push((heapnode){0, s});
        while(!Q.empty())
        {
            heapnode x = Q.top(); Q.pop();
            int u = x.u;
            if(done[u]) continue;
            done[u] = true;
            for(int i = 0; i < g[u].size(); ++i)
            {
                edge & e = edges[g[u][i]];
                if(!done[e.to] && d[e.to] > d[u] + e.dist)
                {
                    d[e.to] = d[u] + e.dist;
                    p[e.to] = g[u][i];
                    Q.push((heapnode){d[e.to], e.to});
                }
            }
        }
    }
    
}d;
