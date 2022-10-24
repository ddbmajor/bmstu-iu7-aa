int start = clock();
// some code
int end = clock();
cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;