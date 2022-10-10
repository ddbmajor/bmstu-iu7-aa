#include "stdio.h"
#include "stdlib.h"
#include "time.h"

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

char *inputString(FILE* fp, size_t size, size_t *l){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    *l = len;
    return realloc(str, sizeof(*str)*len);
}

void iomode()
{
    size_t l1, l2;
    char *str1, *str2;
    int ch;
    while(EOF!=(ch=fgetc(stdin)) && ch != '\n');
    printf("Введите 1 строку:\n");
    str1 = inputString(stdin, 10, &l1);
    printf("Введите 2 строку:\n");
    str2 = inputString(stdin, 10, &l2);
    printf("otvet levenshtain - %d\n", levenshtein(str1, l1, str2, l2));
    printf("otvet damerau - %d\n", damerau(str1, l1, str2, l2));
    printf("otvet recursive - %d\n", damereu_rec(str1, l1, str2, l2));
    printf("otvet recursive cache - %d\n", damereu_rec_cache(str1, l1, str2, l2));

}

double exp(int mode, int func(char*, int, char*, int))
{
    char *str1;
    char *str2;
    int l1, l2;
    int times;
    switch (mode)
    {
    case 0:
        str1 = "qwerty";
        str2 = "asdfgh";
        l1 = l2 = 6;
        times = 10000;
        break;
    case 1:
        str1 = "qwertyuiopqwertyuioqwertyuiopqwertyuiopqqwertyuioq";
        str2 = "ertyujnbvcdtyjkmnbvcdyukhjfyujnbvcdrklkytfcvbnkugg";
        l1 = l2 = 50;
        times = 1;
        if (func == damereu_rec)
        {
            times = 1;
        }
        break;
    case 2:
        str1 = "qwertyuiopqwertyuioqwertyuiopqwertyuiopqqwertyuioqertyujnbvcdtyjkmnbvcdyukhjfyujnbvcdrklkytfcvbnkugg";
        str2 = "ertyujnbvcdtyjkmnbvcdyukhjfyujnbvcdrklkytfcvbnkuggqwertyuiopqwertyuioqwertyuiopqwertyuiopqqwertyuioq";
        l1 = l2 = 100;
        times = 10;
        if (func == damereu_rec)
        {
            times = 1;
        }
        break;
    default:
        break;
    }

    double cpu_time_used = 0;
    for (size_t i = 0; i < times; i++)
    {
        clock_t start = clock();
        func(str1, l1, str2, l2);
        clock_t end = clock();
        cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    cpu_time_used /= times;
    return cpu_time_used;
}


void experiment()
{
    // short word
    double l = exp(0, &levenshtein);
    double d = exp(0, &damerau);
    double dr = exp(0, &damereu_rec);
    double drc = exp(0, &damereu_rec_cache);

    printf("Короткое слово (6 символов), количество повторение - 10000\n\n");
    printf("Левенштейн - %f\nДамерау - %f\nДамерау c рекурсией - %f\nДамерау с рекурсией и кэшем - %f\n", l, d, dr, drc);
    
    // medium word
    l = exp(1, &levenshtein);
    printf("1 done\n");
    d = exp(1, &damerau);
    printf("2 done\n");
    drc = exp(1, &damereu_rec_cache);
    printf("3 done\n");
    dr = exp(1, &damereu_rec);
    printf("4 done\n");

    printf("Среднее слово (50 символов), количество повторение - 100\n\n");
    printf("Левенштейн - %f\nДамерау - %f\nДамерау c рекурсией - %f\nДамерау с рекурсией и кэшем - %f\n", l, d, dr, drc);

    // long word
}


int main(void)
{

    int choice;
    printf("Выберете режим работы: 1 - основной, 2 - экспериментальный, 0 - выход из программы\n");
    int rc = scanf("%d", &choice);
    switch (choice)
    {
    case 0:
        return 0;
        break;
    case 1:
        iomode();
        break;
    case 2:
        experiment();
        break;
    default:
        printf("Неверный выбор");
        break;
    }
    return 0;
}
