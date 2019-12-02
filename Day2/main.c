#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

void run(const int LENGTH, int program[LENGTH]) {
    int i;

    for (i = 0; i < LENGTH - 4; i += 4) {
        int opCode = program[i];

        int firstArg  = program[i + 1];
        int secondArg = program[i + 2];
        int thirdArg  = program[i + 3];

        switch (opCode) {
        case 1:
            program[thirdArg] = program[firstArg] + program[secondArg];
            break;
        case 2:
            program[thirdArg] = program[firstArg] * program[secondArg];
            break;
        case 99:
            return;
        }
    }

    return;
}

int main() {
    int program[145], count = 0;

    FILE *file = fopen("input_mod.txt", "r");
    char buffer[BUFSIZE], *end;

    fgets(buffer, BUFSIZE, file);

    char *token = strtok(buffer, ",");

    while (token != NULL) {
        program[count++] = strtol(token, &end, 10);
        token            = strtok(NULL, ",");
    }

    int i, j, k;

    for (i = 0; i < 99; i++) {
        for (j = 0; j < 99; j++) {
            int result[145];

            for (k = 0; k < 145; k++)
                result[k] = program[k];

            result[1] = i;
            result[2] = j;

            run(145, result);

            if (result[0] == 19690720)
                printf("%d and %d: %d\n", i, j, 100 * i + j);
        }
    }

    return 0;
}
