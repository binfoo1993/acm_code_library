struct diff_seq
{
	lng cof[100];
	lng inv[100];
	int order;

	void init()
	{
		// initialization: order and cof array.
		for(int i = 1; i <= order; ++i)
		{
			inv[i] = inverse(i, mod); // find inverse of i when module mod
			for(int j = order; j >= i; --j) cof[j] -= cof[j - 1];
		}
	}

	lng calc(lng n)
	{
		lng res = 0;
		for(int i = order; i > 0; --i)
		{
			res += cof[i]; res %= mod;
			res *= (n - i + 1); res %= mod; 
			res *= inv[i]; res %= mod;
		}
		res += cof[0]; res %= mod;
		if(res < 0) res += mod;
		return res;
	}
}diff;