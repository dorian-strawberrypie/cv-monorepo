#include <stdio.h>
#include <stdlib.h>

const int arrsize = 1000000;
/*
* struct: databank
*   -arr: to store data
*   -tail: to store last index
*  to ease passing an array as argument
*/
typedef struct databank {
    int arr[arrsize];
    int tail;
} Databank; const Databank db_default = { {0}, -1 }; // template instance

/*
* function: check_input
*   -char cmd, int arg1, int arg2: scanned values
*   -int tail
*   -int scan: how many args scanned
*  return 0 for ok input, 1 for wrong input
*/
int check_input(char cmd, int arg1, int arg2, int tail, int scan) {
    int status = 0; // 0: input okay, 1: wrong input
    switch(cmd) {
        case '+':
            if (arg1 < 0 || arg1 > 99999 || tail == arrsize - 1 || scan != 2)
                status = 1;
            break;
        case '?':
            if (arg1 < 0 || arg1 > arg2 || arg2 > tail || scan != 3)
                status = 1;
            break;
        default:
            status = 1;
            break;
    }
    if (status == 1)
        printf("Nespravny vstup.\n");
    return status;
}

/*
* function: new_access
*   -int id
*   -Databank * access
*  to register a new access of id
*  print id's access count
*/
void new_access(int id, Databank * access, int id_count) {
    // put new access into array
    (*access).tail++;
    (*access).arr[(*access).tail] = id;

    // check id's access count and print it
    int access_count = id_count;
    if (access_count == 1)
        printf("> prvni navsteva\n");
    else if (access_count > 1)
        printf("> navsteva #%d\n", access_count);
}

/*
* function: int_cmp
*   -Databank access
*   -int id
*  quicksort int comparator
*/
int int_cmp(const void * p1, const void * p2) {
    int sign = 0;
    if ((*(int*)p2) > (*(int*)p1))
        sign = -1;
    else if (((*(int*)p2) < (*(int*)p1)))
        sign = 1;
    return sign; 
}

/*
* function: query
*   -int from: starting position
*   -int to: end position
*   -int * data: access array
*  count and print unique accesses in from-to interval and interval total len
*/
void query(int from, int to, int * data) {
    int unique = 1;
    int total = to - from + 1; 
    
    // clone array; qsort; count uniq occurences;
    int arr[arrsize];
    for (int i = from; i <= to; i++) {
        arr[i] = data[i];
    }
    qsort(arr + from, total, sizeof(int), int_cmp);
    for (int i = from + 1; i <= to; ++i) {
        if (arr[i] != arr[i-1])
            unique++;
    }
    printf("> %d / %d\n", unique, total);
}

/*
* function: scan_args
*   -char cmd: '+' or '?'
*   -int * arg1, int * arg2: scanned output arguments
*  scans either arg1 for '+' cmd, or both for '?' cmd
*/
int scan_args(char cmd, int * arg1, int * arg2) {
    int scan = 0;
    if (cmd == '+')
            scan = scanf(" %d ", arg1);
    if (cmd == '?')
            scan = scanf(" %d %d ", arg1, arg2);

    return scan;
}

int id_indexer[100000] = {0};
int main(void) {
    Databank access = db_default;
    
    printf("Pozadavky:\n");
    char cmd; // valid input either '+' for new access, or '?' for query
    int arg1 = 0, arg2 = 0; // arguments after cmd in input
    
    char scanned = 0; // to check if any input was given
    int scan = 0;
    while ((scan = scanf(" %c ", &cmd) + scan_args(cmd, &arg1, &arg2)) > 0) {
        
        if(check_input(cmd, arg1, arg2, access.tail, scan))
            return 1;        
        
        if (cmd == '+') {
            id_indexer[arg1] = id_indexer[arg1] + 1;
            new_access(arg1, &access, id_indexer[arg1]);
        }
        if (cmd == '?')
            query(arg1, arg2, access.arr);

        scanned = 1;
    }
    
    if (!feof(stdin) || !scanned) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    return 0;
}