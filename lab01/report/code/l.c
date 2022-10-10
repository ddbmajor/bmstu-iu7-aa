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
                                matrix[i - 1][j - 1] 
                                + (ch1 == ch2 ? 0 : 1));
        }
    }
    return matrix[l1][l2];
}