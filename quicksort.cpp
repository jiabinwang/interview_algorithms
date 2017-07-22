#include <iostream>

void swap(int* a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
int partition(int* a, int left, int right) {
    int smallindex = left - 1;
    for (int i = left; i < right; ++i) {
        if (a[i] < a[right]) {
            ++smallindex;
            swap(a, smallindex, i);
        }
    }
    swap(a, smallindex + 1, right);
    return smallindex + 1;
}
void quicksort(int* a, int left, int right) {
    if (left < right) {
        int p = partition(a, left, right);
        quicksort(a, left, p - 1);
        quicksort(a, p + 1, right);
    }
}

int main() {
    int a1[] = {6, 3, 5, 7, 9, 0, 1, 4, 2, 2, 9 ,0};
    int len = sizeof(a1)/sizeof(a1[0]);
    quicksort(a1, 0, len -1);
    for (int i = 0; i < len; ++i) {
        std::cout << a1[i] << std::endl;
    }
    return 0;
}
