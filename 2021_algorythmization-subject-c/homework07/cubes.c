#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>

typedef struct dynArr {
    int * array;
    int count;
} dynArr;

void printarr(dynArr * arr, int until) {
    for (int i = 0; i <= until; i++)
        // char * format = ( i == until ? "%d\n" : "%d, " );
        printf(( i == until ? "%d\n" : "%d, " ), arr->array[i]);
}

int combine_recursive(dynArr cubes, dynArr * data, int start, int end, int level) { // start inclusive, end exclusive
    int combinations = 1;
    if (start >= end) {
        return 0;
    }

    // printf("%d\n", (*data).array[level]);
    if (level >= 0) {
        (*data).array[level] = cubes.array[start];
        printarr(data, level); // we'll print until @start
    }
    
    for (int i = start + 1; i < end; i++) {
        combinations += combine_recursive(cubes, data, i, end, level + 1);

        while (i >= 0 && i + 1 < cubes.count && cubes.array[i] == cubes.array[i + 1]) // data instead of cubes
            i++;
    }

    return combinations;
}

void recursion_block(dynArr cubes) {
    dynArr data; data.count = cubes.count+1; data.array = (int *)malloc(data.count * sizeof(data));

    int counter = combine_recursive(cubes, &data, -1, cubes.count, -1) - 1; // we start with -1st recursion
    printf("Celkem: %d\n", counter);

    free(data.array);
}

int icomp(const void * p1, const void * p2) {
    if (*((int*)p1) > *(int*)p2)
        return -1;
    return 1;
}

int main() {

    dynArr cubes;
    printf("Pocet kostek:\n");
    scanf("%d", &cubes.count);
    if (cubes.count < 1) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Velikosti:\n");
    
    cubes.array = (int *)malloc((cubes.count)*sizeof(cubes.count));
    int scan = 0, status = 0, t = 0;
    for (t = 0; t < cubes.count; t++) {
        scan = scanf("%d", cubes.array + t);
        if (cubes.array[t] < 1 || scan != 1) {
            status = 1;
            break;
        }
    }
    if ((t == cubes.count - 1 && !feof(stdin)) || (t != cubes.count - 1 && feof(stdin)) || status) {
        printf("Nespravny vstup.\n");
    }
    else {
        qsort(cubes.array, cubes.count, sizeof(int), icomp);
        // printf("FIRST MMBER: %d\n", cubes.array[0]);
        recursion_block(cubes);
    
        // printf("I'M FINDING COMBINATIONS\n");
    }
    free(cubes.array);
    return 0;
}