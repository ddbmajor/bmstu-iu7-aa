int damereu_rec(char *s1, int l1, char *s2, int l2)
{
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
            return min4(damereu_rec(s1, l1 - 1, s2, l2) + 1,
                        damereu_rec(s1, l1, s2, l2 - 1) + 1,
                        damereu_rec(s1, l1 - 1, s2, l2 - 1) 
                        + (ch1 == ch2 ? 0 : 1),
                        damereu_rec(s1, l1 - 2, s2, l2 - 2) 
                        + 1);
        }
        else
        {
            return min3(damereu_rec(s1, l1 - 1, s2, l2) + 1,
                        damereu_rec(s1, l1, s2, l2 - 1) + 1,
                        damereu_rec(s1, l1 - 1, s2, l2 - 1) 
                        + (ch1 == ch2 ? 0 : 1));
        }
    }
    else
    {
        return min3(damereu_rec(s1, l1 - 1, s2, l2) + 1,
                    damereu_rec(s1, l1, s2, l2 - 1) + 1,
                    damereu_rec(s1, l1 - 1, s2, l2 - 1) 
                    + (ch1 == ch2 ? 0 : 1));
    }
}