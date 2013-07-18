struct partition_tree
{
	int n;
	int sorted[maxn];
	int val[30][maxn], sum[30][maxn];
	
	void init(int n, int * num)
	{
		this->n = n;
		for(int i = 1; i <= n; ++i) sorted[i] = val[0][i] = num[i];
		sort(sorted + 1, sorted + n + 1);
		build(0, 1, n);
	}
	
	void build(int pos, int l, int r)
	{
		if(l == r) return;
		int mid = (l + r) / 2, ln = 1, tmp = mid - 1;
		while(sorted[tmp] == sorted[mid]) ln++, tmp--;
		for(int i = l, j = l, k = mid + 1; i <= r; ++i)
		{
			sum[pos][i] = (i == l) ? 0 : sum[pos][i - 1];
			if(val[pos][i] < sorted[mid]) val[pos + 1][j++] = val[pos][i], sum[pos][i]++;
			else if(val[pos][i] > sorted[mid]) val[pos + 1][k++] = val[pos][i];
			else
			{
				if(ln > 0) val[pos + 1][j++] = val[pos][i], ln--, sum[pos][i]++;
				else val[pos + 1][k++] = val[pos][i];
			}
		}
		build(pos + 1, l, mid); build(pos + 1, mid + 1, r);
	}
	
	int query(int a, int b, int k, int l, int r, int pos)
	{
		if(l == r) return val[pos][a];
		int ln = (l == a) ? 0 : sum[pos][a - 1], rn = sum[pos][b], mid = (l + r) / 2;
		if(rn - ln >= k) 
			return query(l + ln, l + rn - 1, k, l, mid, pos + 1);
		else 
		{
			int n1 = a - l - ln, n2 = b - l + 1 - rn;
			return query(mid + 1 + n1, mid + n2, k - rn + ln, mid + 1, r, pos + 1);
		}
	}
}t;