#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096

int manhattan(int fstX, int sndX, int fstY, int sndY) {
    return abs(fstX - sndX) + abs(fstY - sndY);
}

int traceCables(int lenFst, char *fstWire, const int lenSnd, char *sndWire) {
    int side         = 30000;
    int *wireBox     = calloc(side * side, sizeof(int));
    int *breadCrumbs = calloc(side * side, sizeof(int));
    int shortest     = INT_MAX;

    int currentX = side / 2, currentY = side / 2;

    char *fstToken = strtok(fstWire, ","), *end;

    int stepCountX = 0, stepCountY = 0;

    while (fstToken != NULL) {
        switch (fstToken++ [0]) {
        case 'U':
            for (int i = 0; i < strtol(fstToken, &end, 10); ++i) {
                stepCountY++;

                if (!wireBox[currentX + side * --currentY])
                    wireBox[currentX + side * currentY] =
                        stepCountX + stepCountY;
            }
            break;
        case 'R':
            for (int i = 0; i < strtol(fstToken, &end, 10); ++i) {
                stepCountX++;

                if (!wireBox[++currentX + side * currentY])
                    wireBox[currentX + side * currentY] =
                        stepCountX + stepCountY;
            }
            break;
        case 'D':
            for (int i = 0; i < strtol(fstToken, &end, 10); ++i) {
                stepCountY++;

                if (!wireBox[currentX + side * ++currentY])
                    wireBox[currentX + side * currentY] =
                        stepCountX + stepCountY;
            }
            break;
        case 'L':
            for (int i = 0; i < strtol(fstToken, &end, 10); ++i) {
                stepCountX++;

                if (!wireBox[--currentX + side * currentY])
                    wireBox[currentX + side * currentY] =
                        stepCountX + stepCountY;
            }
            break;
        }

        fstToken = strtok(NULL, ",");
    }

    int x, y;

    for (y = 0; y < side; y++)
        for (x = 0; x < side; x++)
            breadCrumbs[x + side * y] = INT_MAX;

    currentX = side / 2, currentY = side / 2;

    char *sndToken = strtok(sndWire, ",");

    stepCountX = 0, stepCountY = 0;

    while (sndToken != NULL) {
        switch (sndToken++ [0]) {
        case 'U':
            for (int i = 0; i < strtol(sndToken, &end, 10); ++i) {
                stepCountY++;

                if (wireBox[currentX + side * --currentY]) {
                    breadCrumbs[currentX + side * currentY] =
                        stepCountX + stepCountY +
                        wireBox[currentX + side * currentY];

                    int current =
                        manhattan(side / 2, currentX, side / 2, currentY);

                    shortest = (current < shortest) ? current : shortest;
                }
            }
            break;
        case 'R':
            for (int i = 0; i < strtol(sndToken, &end, 10); ++i) {
                stepCountX++;

                if (wireBox[++currentX + side * currentY]) {
                    breadCrumbs[currentX + side * currentY] =
                        stepCountX + stepCountY +
                        wireBox[currentX + side * currentY];

                    int current =
                        manhattan(side / 2, currentX, side / 2, currentY);

                    shortest = (current < shortest) ? current : shortest;
                }
            }
            break;
        case 'D':
            for (int i = 0; i < strtol(sndToken, &end, 10); ++i) {
                stepCountY++;

                if (wireBox[currentX + side * ++currentY]) {
                    breadCrumbs[currentX + side * currentY] =
                        stepCountX + stepCountY +
                        wireBox[currentX + side * currentY];

                    int current =
                        manhattan(side / 2, currentX, side / 2, currentY);

                    shortest = (current < shortest) ? current : shortest;
                }
            }
            break;
        case 'L':
            for (int i = 0; i < strtol(sndToken, &end, 10); ++i) {
                stepCountX++;

                if (wireBox[--currentX + side * currentY]) {
                    breadCrumbs[currentX + side * currentY] =
                        stepCountX + stepCountY +
                        wireBox[currentX + side * currentY];

                    int current =
                        manhattan(side / 2, currentX, side / 2, currentY);

                    shortest = (current < shortest) ? current : shortest;
                }
            }
            break;
        }

        sndToken = strtok(NULL, ",");
    }

    shortest = INT_MAX;

    for (y = 0; y < side; y++)
        for (x = 0; x < side; x++)
            shortest = (breadCrumbs[x + side * y] < shortest)
                           ? breadCrumbs[x + side * y]
                           : shortest;

    return shortest;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    char buffer[BUFSIZE];

    char fstWire[BUFSIZE], sndWire[BUFSIZE];

    fgets(buffer, BUFSIZE, file);

    strcpy(fstWire, buffer);

    fgets(buffer, BUFSIZE, file);

    strcpy(sndWire, buffer);

    int shortestDistance =
        traceCables(strlen(fstWire), fstWire, strlen(sndWire), sndWire);

    printf("%d\n", shortestDistance);

    return 0;
}
