#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *array, int left, int right){
    if(left < right){
        int middle = left +(right - left) / 2;
        merge_sort(array,left,middle);
        merge_sort(array,middle + 1, right);
        merge(array,left,middle,right);
    }
}
    void merge(int *x, int l, int m, int r) {
 int i, j, k, n1 = m - l + 1, n2 = r - m;
 int left[n1], right[n2];
    for (i = 0; i < n1; i++) left[i] = x[l + i];
        for (j = 0; j < n2; j++) right[j] = x[m + 1 + j];
            i = 0; j = 0; k = l;
            while (i < n1 && j < n2) {
                if (left[i] <= right[j]) x[k++] = left[i++];
                else x[k++] = right[j++];
    }
        while (i < n1) x[k++] = left[i++];
        while (j < n2) x[k++] = right[j++];
}
