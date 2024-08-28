#include "libcp8-list.h"
#include "libcp8-log.h"

#define MAX_CMD_LENGTH 16

// Task 8
void do_task(List* list, int k, uint64_t value) {
    if(!list)
        return;
    if(k <= list->size)
        return;
    while(list->size < k) {
        if(!list_push(list, value))
            break;
    }
}

// Help message
void print_help() {
    printf("Cycled double-linked list program.\nCommands:\n");
    printf("i - insert value\nr - remove value\np - push value\ns - print list size\ng - get value from list\nc - change value\n");
    printf("t - do task\nd - print list\nx - clean list\nh - print help message\nq - quit program\n");
}

int main(void) {
    List* list = list_create();
    if(!list)
        return EXIT_FAILURE;
    log_info("List created successfully");
    while(true) {
        int cmd = getchar();
        if(cmd == ' ' || cmd == '\n' || cmd == '\t')
            continue;
        if(cmd == EOF) { log_info("Recieved EOF"); exit(EXIT_SUCCESS); }
        int li =  0;
        uint64_t val =  0ul;
        switch (cmd) {
        case 'i':
            log_input("Enter insertion index");
            li =  0;
            if(!scanf("%d", &li)) {
                log_error("Failed to read list index");
                continue;
            }
            log_input("Enter value");
            val =  0;
            if(!scanf("%lu", &val)) {
                log_error("Failed to read value");
                continue;
            }
            if(!list_insert(list, li, val)) {
                log_error("Unable to insert value");
                continue;
            }
            log_info("Insert value to the list");
            break;
        case 'r':
            log_input("Enter index");
            li =  0;
            if(!scanf("%d", &li)) {
                log_error("Failed to read list index");
                continue;
            }
            list_remove(list, li);
            log_info("Remove value from list");
            break;
        case 's':
            printf("List size is %d\n", list->size);
            break;
        case 'p':
            log_input("Enter value");
            val =  0;
            if(!scanf("%lu", &val)) {
                log_error("Failed to read value");
                continue;
            }
            if(!list_push(list, val)) {
                log_error("Can't push value");
                continue;
            }
            log_info("Push value");
            break;
        case 'g':
            log_input("Enter index");
            li =  0;
            if(!scanf("%d", &li)) {
                log_error("Failed to read list index");
                continue;
            }
            printf("List[%d] = %lu\n", li, list_get(list, li));
            break;
        case 'c':
            log_input("Enter node index");
            li =  0;
            if(!scanf("%d", &li)) {
                log_error("Failed to read list index");
                continue;
            }
            log_input("Enter value");
            val =  0;
            if(!scanf("%lu", &val)) {
                log_error("Failed to read value");
                continue;
            }
            list_set(list, li, val);
            log_info("Change value");
            break;
        case 't':
            log_input("Enter k");
            int k = 0;
            if(!scanf("%d", &k)) {
                log_error("Failed to read parameter");
                continue;
            }
            log_input("Enter value");
            val = 0;
            if(!scanf("%lu", &val)) {
                log_error("Failed to read value");
                continue;
            }
            do_task(list, k, val);
            log_info("Task done");
            break;
        case 'd':
            list_print(list);
            break;
        case 'x':
            list_clean(list);
            log_info("List cleaned");
            break;
        case 'h':
            print_help();
            break;
        case 'q':
            list_destroy(list);
            log_info("Exit");
            exit(EXIT_SUCCESS);
            break;
        default:
            log_error("Unknown command");
            while(getchar() != '\n');
            break;
        }
    }
    return EXIT_SUCCESS;
}
