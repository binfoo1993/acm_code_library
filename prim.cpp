struct edge
{
    int from, to, dist;
};

struct heapnode
{
    int u, d;
    bool operator < (const heapnode & rhs) const
    {
        return d > rhs.d;
    }
};

struct prim
{
    int n, m;
    vector<edge> edges;
    vector<int> g[maxn];
    int d[maxn], p[maxn];
    bool done[maxn];
    
    void init(int n)
    {
        this->n = n;
        for(int i = 1; i <= n; ++i) g[i].clear(); // start at 1
        edges.clear();
        memset(d, 0x3f, sizeof(d)); memset(done, 0, sizeof(done));
    } 
    
    void addedge(int from, int to, int dist)
    {
        edges.push_back((edge){from, to, dist});
        m = edges.size();
        g[from].push_back(m - 1);
    }
    
    int solve()
    {
        priority_queue<heapnode> qu;
        d[1] = 0;
        qu.push((heapnode){1, 0});
        int ans = 0;
        while(!qu.empty())
        {
            int u = qu.front().u; qu.pop();
            if(done[u]) continue;
            done[u] = true;
            ans += d[u];
            for(int i = 0; i < g[u].size(); ++i)
            {
                edge & e = edges[g[u][i]]
                if(!done[e.to] && d[e.to] > e.dist)
                {
                    d[e.to] = e.dist;
                    p[e.to] = u;
                    qu.push((heapnode){e.to, d[e.to});
                }
            }
        }
        return ans;
    }
};