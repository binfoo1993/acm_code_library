// segment tree for scanning line
int num[maxn];

struct seg_tree
{
    int l[5 * maxn], r[5 * maxn];
    int c[5 * maxn];
    int ans[5 * maxn];
    
    void build(int pos, int le, int ri)
    {
        l[pos] = le; r[pos] = ri;
        c[pos] = 0;
        ans[pos] = num[ri] - num[le];
        if(ri - le > 1)
        {
            int mid = (le + ri) / 2;
            build(ls(pos), le, mid);
            build(rs(pos), mid, ri);
        }
    }
    
    void update(int pos)
    {
        if(c[pos] > 0) ans[pos] = 0;
        else if(r[pos] - l[pos] == 1) ans[pos] = num[r[pos]] - num[l[pos]];
        else ans[pos] = ans[ls(pos)] + ans[rs(pos)];
    }
    
    void add(int pos, int le, int ri, int flag)
    {
        if(le <= l[pos] && ri >= r[pos])
        {
            if(flag) c[pos]++;
            else c[pos]--;
        }
        else
        {
            int mid = (l[pos] + r[pos]) / 2;
            if(ri > mid) add(rs(pos), le, ri, flag);
            if(le < mid) add(ls(pos), le, ri, flag);
        }
        update(pos);
    }
    
}tree;
