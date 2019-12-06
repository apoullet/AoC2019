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

int *getExtremes(int size, int *arr, int min, int max) {
    int current = size >> 1, jump = size >> 2,
        *extremes = malloc(sizeof(int) << 1);

    do {
        current = (arr[current] > min) ? current - jump : current + jump;
        jump    = jump >> 1;
    } while (jump > 0);

    while (arr[current] > min)
        current--;

    extremes[0] = current;

    current = size >> 1, jump = size >> 2;

    do {
        current = (arr[current] > max) ? current - jump : current + jump;
        jump    = jump >> 1;
    } while (jump > 0);

    while (arr[current] < max)
        current++;

    extremes[1] = current;

    return extremes;
}

int hasRepeating(int n) {
    int current = n % 10, tmp = n / 10;

    while (tmp > 0) {
        int rem = tmp % 10;

        if (current == rem)
            return 1;

        current = rem;
        tmp /= 10;
    }

    return 0;
}

int hasDoubleRepeating(int n) {
    int current = n % 10, tmp = n / 10, count = 1;

    while (tmp > 0) {
        int rem = tmp % 10;

        if (current == rem) {
            count++;
        } else {
            if (count == 2)
                return 1;
            else
                count = 1;
        }

        current = rem;
        tmp /= 10;
    }

    return (count == 2);
}

int main() {
    int size = 0;

    int *nums     = generateIncreasingNums(284639, 748759, &size);
    int *extremes = getExtremes(size, nums, 284639, 748759);

    int min = extremes[0], max = extremes[1], i, count = 0;

    for (i = min + 1; i < max; ++i)
        count += (hasDoubleRepeating(nums[i])) ? 0 : 1;

    printf("%d\n", max - 1 - (min + 1) - count + 1);

    return 0;
}
