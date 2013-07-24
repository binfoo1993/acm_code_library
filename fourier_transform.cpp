struct fft
{
    int len, id;
    int sp[maxn];
    pair<double, double> p[3][maxn], tmp[maxn];
    
    void init(int l, int * s)
    {
        this->len = l;
        for(int i = 0; i < len; ++i)
            sp[i] = s[i];
    }
    
    void fill(int m, int d, int c)
    {
        if(m == len) p[c][d] = tmp[id++];
        else
        {
            fill(m << 1, d, c);
            fill(m << 1, d + m, c);
        }
    }
    
    void calc(double oper, int c)
    {
        for(int d = 0; (1 << d) < len; ++d)
        {
            int m = (1 << d);
            double x = pi / m * oper;
            double i0 = sin(x), r0 = cos(x);
            for(int k = 0; k < len; k += (m << 1))
            {
                double i = 0, r = 1;
                for(int j = 0; j < m; ++j)
                {
                    double tr = r * p[c][k + j + m].first - i * p[c][k + j + m].second;
                    double ti = r * p[c][k + j + m].second + i * p[c][k + j + m].first;
                    p[c][k + j + m].first = p[c][k + j].first - tr;
                    p[c][k + j + m].second = p[c][k + j].second - ti;
                    p[c][k + j].first += tr;
                    p[c][k + j].second += ti;
                    double tmpi = i;
                    i = i * r0 + r * i0; r = r * r0 - tmpi * i0;
                }
            }
        }
    }
    
    void multi()
    {
        for(int i = 0; i < len; ++i)
        {
            tmp[i].first = sp[i];
            tmp[i].second = 0.0;
        }
        id = 0; fill(1, 0, 0); calc(1.0, 0);
        id = 0; fill(1, 0, 1); calc(1.0, 1);
        for(int i = 0; i < len; ++i)
        {
            tmp[i].first = p[0][i].first * p[1][i].first - p[0][i].second * p[1][i].second;
            tmp[i].second = p[0][i].first * p[1][i].second + p[0][i].second * p[1][i].first;
        }
        id = 0; fill(1, 0, 2); calc(-1.0, 2);
        for(int i = 0; i < len; ++i) p[2][i].first /= len;
    }
    
}f;