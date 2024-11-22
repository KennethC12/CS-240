#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int strCompare(char *str1, char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] < str2[i])
            return -1;
        if (str1[i] > str2[i])
            return 1;
        i++;
    }
    if (str1[i] != 0)
        return 1;
    if (str2[i] != 0)
        return -1;
    return 0;
}

int isSubStr(char *str, int nStr, char *sub, int nSub)
{
    if (nStr < nSub)
        return 0;
    int flag = 1;
    for (int i = 0; i < nSub; i++)
    {
        if (str[i] != sub[i])
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
        return 1;
    return isSubStr(str + 1, nStr - 1, sub, nSub);
}

void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapStr(char **a, char **b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}
void bubbleSort(char *arr[], int indices[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strCompare(arr[j], arr[j + 1]) > 0)
            {
                swapStr(&arr[j], &arr[j + 1]);
                swapInt(&indices[j], &indices[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}
int strLen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

int main()
{
    char *arr[100000];
    int indices[10000];
    int nW = 0;
    int curIdx = 0;
    char *word = malloc(1000);
    char pattern[] = "CS240";
    int nPattern = strLen(pattern);
    while (scanf("%s", word) != EOF)
    {
        int nStr = strLen(word);
        if (isSubStr(word, nStr, pattern, nPattern))
        {
            arr[nW] = word;
            indices[nW++] = curIdx;
        }
        word = malloc(1000);
        curIdx++;
    }

    bubbleSort(arr, indices, nW);

    // print output
    if (nW == 0)
        return 0;
    for (int j = 0; j < nW; j++)
    {
        printf("%s", arr[j]);
        if (j < nW - 1)
            putchar(',');
    }
    putchar('\n');
    for (int j = 0; j < nW; j++)
    {
        printf("%d", indices[j]);
        if (j < nW - 1)
            putchar(',');
    }
}