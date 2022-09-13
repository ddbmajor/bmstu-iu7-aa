#include "stdio.h"
#include "stdlib.h"

int min3(int a, int b, int c)
{
    if ((a < b) && (a < c))
    {
        return a;
    }
    else if (b < c)
    {
        return b;
    }
    else
    {
        return c;
    }
}

int min4(int a, int b, int c, int d)
{
    int min = a;

    if (b < min)
    {
        min = b;
    }
    if (c < min)
    {
        min = c;
    }
    if (d < min)
    {
        min = d;
    }

    return min;
}

int damerau(char *s1, int l1, char *s2, int l2)
{
    int matrix[l1 + 1][l2 + 1];

    for (int i = 0; i < l1 + 1; i++)
    {
        for (int j = 0; j < l2 + 1; j++)
        {
            if (i == 0)
            {
                matrix[0][j] = j;
                continue;
            }
            if (j == 0)
            {
                matrix[i][0] = i;
                continue;
            }

            char ch1 = s1[i - 1];
            char ch2 = s2[j - 1];

            if (i > 1 && j > 1)
            {
                char pch1 = s1[i - 2];
                char pch2 = s2[j - 2];

                if (ch1 == pch2 && ch2 == pch1)
                {
                    matrix[i][j] = min4(matrix[i - 1][j] + 1,
                                        matrix[i][j - 1] + 1,
                                        matrix[i - 1][j - 1] + (ch1 == ch2 ? 0 : 1),
                                        matrix[i - 2][j - 2] + 1);
                }
                else
                {
                    matrix[i][j] = min3(matrix[i - 1][j] + 1,
                                        matrix[i][j - 1] + 1,
                                        matrix[i - 1][j - 1] + (ch1 == ch2 ? 0 : 1));
                }
            }
            else
            {
                matrix[i][j] = min3(matrix[i - 1][j] + 1,
                                    matrix[i][j - 1] + 1,
                                    matrix[i - 1][j - 1] + (ch1 == ch2 ? 0 : 1));
            }
        }
    }
    return matrix[l1][l2];
}

int levenshtein(char *s1, int l1, char *s2, int l2)
{
    int matrix[l1 + 1][l2 + 1];

    for (int i = 0; i < l1 + 1; i++)
    {
        for (int j = 0; j < l2 + 1; j++)
        {
            if (i == 0)
            {
                matrix[0][j] = j;
                continue;
            }
            if (j == 0)
            {
                matrix[i][0] = i;
                continue;
            }

            char ch1 = s1[i - 1];
            char ch2 = s2[j - 1];

            matrix[i][j] = min3(matrix[i - 1][j] + 1,
                                matrix[i][j - 1] + 1,
                                matrix[i - 1][j - 1] + (ch1 == ch2 ? 0 : 1));
        }
    }
    return matrix[l1][l2];
}

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
                        damereu_rec(s1, l1 - 1, s2, l2 - 1) + (ch1 == ch2 ? 0 : 1),
                        damereu_rec(s1, l1 - 2, s2, l2 - 2) + 1);
        }
        else
        {
            return min3(damereu_rec(s1, l1 - 1, s2, l2) + 1,
                        damereu_rec(s1, l1, s2, l2 - 1) + 1,
                        damereu_rec(s1, l1 - 1, s2, l2 - 1) + (ch1 == ch2 ? 0 : 1));
        }
    }
    else
    {
        return min3(damereu_rec(s1, l1 - 1, s2, l2) + 1,
                    damereu_rec(s1, l1, s2, l2 - 1) + 1,
                    damereu_rec(s1, l1 - 1, s2, l2 - 1) + (ch1 == ch2 ? 0 : 1));
    }
}

int do_rec(char *s1, int l1, char *s2, int l2, int **cache, int m, int n)
{
    if (cache[l1][l2] != -1)
    {
        return cache[l1][l2];
    }

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
            int dist = min4(do_rec(s1, l1 - 1, s2, l2, cache, m, n) + 1,
                            do_rec(s1, l1, s2, l2 - 1, cache, m, n) + 1,
                            do_rec(s1, l1 - 1, s2, l2 - 1, cache, m, n) + (ch1 == ch2 ? 0 : 1),
                            do_rec(s1, l1 - 2, s2, l2 - 2, cache, m, n) + 1);
            cache[l1][l2] = dist;
            return dist;
        }
        else
        {
            int dist = min3(do_rec(s1, l1 - 1, s2, l2, cache, m, n) + 1,
                            do_rec(s1, l1, s2, l2 - 1, cache, m, n) + 1,
                            do_rec(s1, l1 - 1, s2, l2 - 1, cache, m, n) + (ch1 == ch2 ? 0 : 1));
            cache[l1][l2] = dist;
            return dist;
        }
    }
    else
    {
        int dist = min3(do_rec(s1, l1 - 1, s2, l2, cache, m, n) + 1,
                        do_rec(s1, l1, s2, l2 - 1, cache, m, n) + 1,
                        do_rec(s1, l1 - 1, s2, l2 - 1, cache, m, n) + (ch1 == ch2 ? 0 : 1));
        cache[l1][l2] = dist;
        return dist;
    }
}

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

int main(void)
{
    printf("otvet1 - %d\n", levenshtein("kot", 3, "skat", 4));
    printf("otvet2d - %d\n", damerau("klass", 5, "klsas", 5));
    printf("otvet2l - %d\n", levenshtein("klass", 5, "klsas", 5));
    printf("otvet3 - %d\n", damereu_rec("klass", 5, "klsas", 5));
    printf("otvet4 - %d\n", damereu_rec_cache("klassd", 6, "klsas", 5));
    return 0;
}
