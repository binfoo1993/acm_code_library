struct ac_automaton
{
    int ch[maxn][26], val[maxn];
    int f[maxn], last[maxn], sz;
    
    void init()
    {
        sz = 1; memset(ch, 0, sizeof(ch));
        memset(val, 0, sizeof(val)); memset(f, 0, sizeof(f));
        memset(last, 0, sizeof(last));
    }
    
    void insert(char * s, int v)
    {
        int u = 0;
        for(int i = 0; s[i]; ++i)
        {
            int c = tran[s[i]];
            if(!ch[u][c])
            {
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }
    
    void getfail()
    {
        queue<int> q; f[0] = 0;
        for(int c = 0; c < 26; ++c)
        {
            int u = ch[0][c];
            if(u) { f[u] = 0; q.push(u); last[u] = 0; }
            else ch[0][c] = 0;
        }
        while(!q.empty())
        {
            int r = q.front(); q.pop();
            for(int c = 0; c < 26; ++c)
            {
                int u = ch[r][c];
                if(u)
                {
                    q.push(u);
                    f[u] = ch[f[r]][c];
                    last[u] = val[f[u]] ? f[u] : last[f[u]];
                }
                else ch[r][c] = ch[f[r]][c];
            }
        }
    }
}a;
