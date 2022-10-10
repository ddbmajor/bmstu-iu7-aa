int damereu_rec_cache(char *s1, int l1, char *s2, int l2)
{
    int **cache = malloc((l1 + 1) * sizeof(int*));
    for (int i = 0; i < l1 + 1; i++)
    {
        cache[i] = malloc((l2 + 1) * sizeof(int));
    }
    for (int i = 0; i < l1 + 1; i++)
    {
        for (int j = 0; j < l2 + 1; j++)
        {
            cache[i][j] = -1;
        }
    }
    return do_rec(s1, l1, s2, l2, cache, l1 + 1, l2 + 1);
}

int do_rec(char *s1, int l1, char *s2, int l2, int **cache, 
            int m, int n)
{
    if (cache[l1][l2] != -1)
        return cache[l1][l2];
    if (l1 == 0)
        return l2;
    if (l2 == 0)
        return l1;
    char ch1 = s1[l1 - 1];
    char ch2 = s2[l2 - 1];
    if (l1 > 1 && l2 > 1)
    {
        char pch1 = s1[l1 - 2];
        char pch2 = s2[l2 - 2];
        if (ch1 == pch2 && ch2 == pch1)
        {
            int dist = min4(do_rec(s1, l1 - 1, s2, l2, 
                                    cache, m, n) + 1,
                            do_rec(s1, l1, s2, l2 - 1, 
                                    cache, m, n) + 1,
                            do_rec(s1, l1 - 1, s2, l2 - 1, 
                                    cache, m, n) 
                            + (ch1 == ch2 ? 0 : 1),
                            do_rec(s1, l1 - 2, s2, l2 - 2, 
                                    cache, m, n) + 1);
            cache[l1][l2] = dist;
            return dist;
        }
        else
        {
            int dist = min3(do_rec(s1, l1 - 1, s2, l2, 
                                    cache, m, n) + 1,
                            do_rec(s1, l1, s2, l2 - 1, 
                                    cache, m, n) + 1,
                            do_rec(s1, l1 - 1, s2, l2 - 1, 
                                    cache, m, n) 
                            + (ch1 == ch2 ? 0 : 1));
            cache[l1][l2] = dist;
            return dist;
        }
    }
    else
    {
        int dist = min3(do_rec(s1, l1 - 1, s2, l2, 
                                cache, m, n) + 1,
                        do_rec(s1, l1, s2, l2 - 1, 
                                cache, m, n) + 1,
                        do_rec(s1, l1 - 1, s2, l2 - 1, 
                                cache, m, n) 
                        + (ch1 == ch2 ? 0 : 1));
        cache[l1][l2] = dist;
        return dist;
    }
}