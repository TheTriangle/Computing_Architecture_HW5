//------------------------------------------------------------------------------
// main.cpp - содержит главную функцию,
// обеспечивающую простое тестирование
//------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "number.h"
#include "fraction.h"
#include "coordinates.h"
#include "TestsGenerator.cpp"
#include "deque.h"
#include "deque.cpp"

void PrintResultsToConsole(deque* numbers, FILE* input, int amount);
void PrintResultsToFile(deque* numbers, char* outputpath, FILE* input, int amount);
void LogError(char* errors);

// Условие 11, обработка 12
int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Run main <input.txt> to specify input file \n"
               "or\n"
               "run main <input.txt> <output.txt> to specify"
               "input file, output will be written into output.txt\n"
               "or\n"
               "run main -generate <amount> <lowerbound> <upperbound> <out.txt> to generate "
               "a text file with tests\n");
        return 0;
    }

    if (argc == 6) {
        if (strcmp(argv[1], "-generate") != 0) {
            printf("Unknown command %s\n"
                   "Exiting.\n", argv[1]);
            return 0;
        }
        RunGenerator(argc, argv);
        return 0;
    }
    double startingtime = (double)clock();
    startingtime = startingtime / CLOCKS_PER_SEC;

    char* inputpath;
    char* outputpath;

    inputpath = argv[1];
    if (argc == 3) {
        outputpath = argv[2];
    }

    FILE* inputfile = fopen(inputpath, "r");
    FILE* errorslog = fopen("errors.log", "w");
    int type;
    double first;
    double second;

    deque numbers;
    char* errors;
    int counter = 0;
    bool errorsrisen = false;

    while (fscanf(inputfile, "%d %lf %lf", &type, &first, &second) != EOF) {
        if ((type == 1) && (fabs(second) < 0.00001)) {
            fprintf(errorslog, "A provided fraction has a zero denumenator"
                                                  "(line %d)\n", counter + 1);
            errorsrisen = true;
            continue;
        }

        number* newnum;

        switch(type) {
        case 0:
            newnum = new complexnumber(first, second);
            break;
        case 1:
            newnum = new fraction(first, second);
            break;
        case 2:
            newnum = new coordinates(first, second);
            break;
        default:
            newnum = new number();
            break;
        }

        numbers.PushFront(newnum);
        counter++;
    }
    if (errorsrisen)
        printf("Errors produced during program execution. Check errors.log for further info\n");
    fclose(errorslog);
    numbers.BubbleSort();

    printf("Program finished in %f seconds.\n", (double)(clock())/CLOCKS_PER_SEC - startingtime);
    if (argc == 2) {
        printf("\nPrinting results to console, (%d lines)\n", counter);
        PrintResultsToConsole(&numbers, inputfile, counter);
    } else {
        printf("\nWriting results to file (%s)\n", outputpath);
        PrintResultsToFile(&numbers, outputpath, inputfile, counter);
    }
    return 0;
    fclose(inputfile);
    return 0;
}

void PrintResultsToConsole(deque* numbers, FILE* input, int amount) {
    printf("Given input file:\n"
           "---------------------------------------------------------\n");
    rewind(input);
    int c;
    while ((c = getc(input)) != EOF)
        printf("%c", c);

    printf("\n"
           "---------------------------------------------------------\n\n"
           "Output:\n");

    number* first;

    while(numbers->Size() != 0) {
        first = numbers->PopBack();
        printf("%s\n", first->ToString());
        delete first;
    }

    printf("\n%d lines in total.", amount);
}

void PrintResultsToFile(deque* numbers, char* outputpath, FILE* input, int amount) {
    FILE* outputfile = fopen(outputpath, "w");

    fprintf(outputfile, "Given input file:\n"
           "---------------------------------------------------------\n");
    rewind(input);
    int c;
    while ((c = getc(input)) != EOF)
        fprintf(outputfile, "%c", c);

    fprintf(outputfile, "\n"
           "---------------------------------------------------------\n\n"
           "Output:\n");
    number* first;
    while(numbers->Size() != 0) {
        first = numbers->PopBack();
        fprintf(outputfile, "%s\n", first->ToString());
        delete first;
    }
    fprintf(outputfile, "\n%d lines in total.", amount);
    fclose(outputfile);
}