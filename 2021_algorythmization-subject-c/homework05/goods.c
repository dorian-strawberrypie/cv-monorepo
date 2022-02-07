#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item {
    char name[100];
    size_t count;
} item;

typedef struct list {
    size_t capacity;
    size_t tail;
    item * arr;
} list;

void append(list * l, char i[100]) {
    if (l->capacity > l->tail - 1) {
        l->capacity += l->capacity / 2 + 10;
        l->arr = (item *)realloc(l->arr, l->capacity * sizeof(*l->arr));
    }
    item new_item; strncpy(new_item.name, i, 99); new_item.count = 1;
    l->arr[l->tail] = new_item;
    l->tail++;
}

size_t item_in_list(char item[100], list * items) {
    size_t idx = items->tail;
    
    for (size_t t = 0; t < items->tail; ++t) {
        if (strncmp(item, items->arr[t].name, 99) == 0)
            idx = t;
    }
    return idx;
}

int add_item(list * items) {
    char item[100];
    int scan = scanf(" %s", item);
    size_t idx = item_in_list(item, items);
    if (idx == items->tail) {
        append(items, item);
    }
    else {
        items->arr[idx].count++;
        // OPTIMISATION: while idx.cnt > idx-1 + cnt => shuffle?
    }
    return scan > 0 ? 1 : 2; // 1 for ok, 2 for err
}


void print_statistics(int n, list * goods) {
    size_t sum = 0;
    int rank = 1;

    for (size_t t = 0; rank <= n; rank++, t++) {
        if (t == goods->tail) break;
        sum += goods->arr[t].count;
        if (t+1 != goods->tail && goods->arr[t].count == goods->arr[t+1].count) rank--;
    }
    printf("Nejprodavanejsi zbozi: prodano %lu kusu\n", sum);
}

void print_top(int n) {
    int rank = 0;
    int prev_cnt = 0;
    while (rank <= n) {

        printf("1. Milk, 5x\n");
    }
}

int item_compare(const void * p1, const void * p2) {
    int sign = 0;
    if ((*(item*)p2).count > (*(item*)p1).count)
        sign = 1;
    else if ((*(item*)p1).count > (*(item*)p2).count)
        sign = -1;
    return sign;
}

void print_sorted(list g) {
    for (size_t t = 0; t < g.tail; t++)
        printf("name: %s, count: %lu\n", g.arr[t].name, g.arr[t].count);
}

int main() {
    int n;
    char cmd;
    int status = 0; // no IN = 0, IN alright = 1, IN error = 2
    
    printf("Pocet sledovanych:\n");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    list goods = {512, 0, (item*)malloc(goods.capacity * sizeof(*(goods.arr)))};

    printf("Pozadavky:\n");
    while (scanf(" %c", &cmd) > 0) {
        switch (cmd) {
            case '+':
                status = add_item(&goods); // 1 for OK, 2 for ERR
                break;
            case '?':
                qsort(goods.arr, goods.tail, sizeof(item), item_compare);
                print_sorted(goods);
                print_statistics(n, &goods);
                break;
            case '#':
                qsort(goods.arr, goods.tail, sizeof(item), item_compare);
                print_top(n);
                print_statistics(n, &goods);
                break;
            default:
                status = 2;
                break;
        }        
        if (status == 2) {  // or another mistake
            break;
        }
        status = 1;

    }
    if (status == 2 || status == 0 || !feof(stdin))
        printf("Nespravny vstup.\n");

    free(goods.arr);
    return 1;
}