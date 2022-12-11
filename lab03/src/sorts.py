# Sorts

def insertion_sort(arr, n):
    
    for i in range(1, n):
        j = i - 1
        tmp = arr[i]

        while (j >= 0 and arr[j] > tmp):
            arr[j + 1] = arr[j]
            j -= 1

        arr[j + 1] = tmp

    return arr


def bubble_sort(arr, n):
    n -= 1
    for i in range(n):
        for j in range(n - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

    return arr


def gnomme_sort(arr, n):
    
    i = 1

    while (i < n):
        if (arr[i] < arr[i - 1]):
            tmp = arr[i]
            arr[i] = arr[i - 1]
            arr[i - 1] = tmp

            if (i > 1):
                i -= 1
        else:
            i += 1

    return arr