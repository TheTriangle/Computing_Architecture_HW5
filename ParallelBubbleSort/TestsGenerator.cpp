#include <stdio.h>
#include <string.h>
#include <cstdlib>


double GetRandomDouble(double lowerbound, double upperbound)
{
    double frac = (double)rand() / RAND_MAX;
    return lowerbound + frac * (upperbound - lowerbound);
}


void RunGenerator(int argc, char* argv[]) {
    int amount = 0;
    double lowerbound, upperbound;
    char* filename = argv[5];
    amount = std::atoi(argv[2]);
    lowerbound = std::atof(argv[3]);
    upperbound = std::atof(argv[4]);

    FILE* tests = fopen(filename, "w");
    for (int i = 0; i < amount; i++) {
        fprintf(tests, "%d\n%d %d\n", rand() % 3 + 1,
                                      int(GetRandomDouble(lowerbound, upperbound)),
                                      int(GetRandomDouble(lowerbound, upperbound)));
    }

    fclose(tests);
    printf("Tests generation successful2.\nExiting.\n");
}


void GenerateTests(char* filename, double lowerbound, double upperbound, int amount) {
    FILE* testfile = fopen(filename, "w");

    for (int i = 0; i < amount; i++) {
        fprintf(testfile, "%d %d %d", rand() % 3 + 1, int(GetRandomDouble(lowerbound, upperbound)),
                                                  int(GetRandomDouble(lowerbound, upperbound)));
    }
}
