#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int calcFuel(int mass) { return mass / 3 - 2; }

int calcTrickleFuel(int mass) {
    int fuel = 0;

    do {
        mass = calcFuel(mass);
        fuel += mass;
    } while (mass > 5);

    return fuel;
}

int main() {
    int totalFuelReq = 0;

    FILE *file = fopen("input.txt", "r");
    char buffer[BUFSIZE], *end;

    while (fgets(buffer, BUFSIZE, file))
        totalFuelReq += calcTrickleFuel(strtol(buffer, &end, 10));

    fclose(file);

    printf("%d\n", totalFuelReq);

    return 0;
}
