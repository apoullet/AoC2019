#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    int product = 1, i;

    for (i = 2; i < n + 1; i++)
        product *= i;

    return product;
}

int combination(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int *generateIncreasingNums(int start, int end, int *size) {
    int *nums     = calloc(end - start, sizeof(int));
    int lookup[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    int index = 0, mark = 0, level = 1, i, firstDigit;

    do {
        start /= 10;
        firstDigit = start;
    } while (start > 10);

    for (i = firstDigit; i < 10; ++i)
        nums[index++] = i;

    int cutoff = index, base, multiplier;

    for (multiplier = 10; end / multiplier > 0; multiplier *= 10) {
        for (base = 2; base < 10; ++base) {
            int i;

            for (i = mark + lookup[base - 2]; i < cutoff; ++i)
                nums[index++] = base * multiplier + nums[i];
        }

        for (int i = 1; i < 9; ++i)
            lookup[i] = lookup[i - 1] + combination(8 - i + level, 8 - i);

        level++;

        mark   = cutoff;
        cutoff = index;
    }

    (*size) = index;

    return nums;
}

/* TODO: Find in between which numbers from arr min and max fit*/
int *getExtremes(int size, int arr[size], int min, int max) { return arr; }

/* TODO: Count numbers that don't contain any identical adjacent digits*/
int main() {
    int size = 0;

    int *nums = generateIncreasingNums(284639, 748759, &size);

    return 0;
}
