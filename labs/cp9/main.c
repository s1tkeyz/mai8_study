#include "libcp9-sort.h"

// On error
void die(const char* message) {
    printf("[FATAL]: %s\n", message);
    exit(EXIT_FAILURE);
}

// Creates table from plain text file
Table* readfromfile(FILE* content, FILE* keys) {
    if(!content || !keys)
        return NULL;
    Table* t = create_table();
    if(!t) {
        destroy_table(t);
        return NULL;
    }
    int i = 0;
    Row nr;
    while(fgets(nr.line, LINE_SIZE, content)) {
        if(!fgets(nr.key, KEY_SIZE, keys)) {
            destroy_table(t);
            return NULL;
        }
        nr.key[strcspn(nr.key, "\n")] = 0;
        nr.line[strcspn(nr.line, "\n")] = 0;
        table_add(t, nr);
        i++;
    }
    printf("%d\n", i);
    return t;
}

int main(void) {
    FILE* c = fopen("ascii.txt", "r");
    FILE* k = fopen("keys.txt", "r");
    if(!c || !k)
        die("Can't read content and keys files");
    Table* table = readfromfile(c, k);
    fclose(c);
    fclose(k);
    if(!table)
        die("Unable to build table");

    printf("Random shuffled table:\n");
    shuffle_rows(table);
    print_table(table);

    putchar('\n');

    printf("After Shell sort:\n");
    shell_sort(table);
    print_table(table);

    putchar('\n');

    printf("Reversed table:\n");
    reverse_table(table);
    print_table(table);

    putchar('\n');

    printf("After Shell sort:\n");
    shell_sort(table);
    print_table(table);

    putchar('\n');
    printf("Binary search sequence: \n");
    while(!feof(stdin)) {
        char k[KEY_SIZE];
        scanf("%s", k);
        int r = table_search(table, k);
        if(r == -1) {
            printf("Not found\n");
            continue;
        }
        printf("For the first time appeared on index [%d] -> (%s)\n", r, table->rows[r].line);
    }
    return EXIT_SUCCESS;
}