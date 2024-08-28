#include "logs.h"
#include "tree.h"
#include "enum.h"
#include <signal.h>

void print_help() {
    printf("General tree program.\nUsage: <command>\n");
    printf("r - switch to the root node\n");
    printf("c - switch to the major child of the current node\n");
    printf("b - switch to the next child of the current node\n");
    printf("s - set value of the current node [dialog]\n");
    printf("v - print value of the current node\n");
    printf("d - delete child by index [dialog]\n");
    printf("a - add child to the current node [dialog]\n");
    printf("t - count max tree width level\n");
    printf("q - quit the program\n");
    printf("h - print this message\n");
}

// Вариант 34
TaskAnswer do_task(GTNode* root) {
    TaskAnswer a = {.level_number = 0, .nodes_count = 0};
    if(!root)
        return a;
    GTNStack* layer_stack = GTNStack_create();
    GTNStack_push(layer_stack, root);
    int ln = 1;
    while(!GTNStack_empty(layer_stack)) {
        layer_stack = measure_tree_layer(layer_stack, ln, &a);
        ln++;
    }
    return a;
}

void parse_command(int cmd, GTNode** root, GTNode** current) {
    if(cmd == ' ' || cmd == '\t' || cmd == '\n' || cmd == '\0') // Skip separators
        return;
    if(cmd == EOF) { // EOF handler
        log_info("Recieved EOF");
        exit(EXIT_SUCCESS);
    }
    if(!*current) {
        log_error("Can't work with NULL node");
        return;
    }
    switch (cmd) {
        case 'x': ;// Delete entire tree
            GTNode* d = *root;
            delete_tree(d);
            *root = build_tree(EMPTY);
            *current = *root;
            log_info("Full tree purge");
            break;
        case 'r': // Go to root node
            if(!*root) {
                log_error("Root node is NULL");
                return;
            }
            *current = *root;
            log_info("Switched to root");
            break;
        case 's': ; // Set value to the current node
            char n[32];
            printf("Enter new value: ");
            if(scanf("%s", n) != 1) {
                log_error("Failed to read value");
                return;
            }
            City val = c_from_string(n);
            if(!val) {
                log_error("Invalid value");
                return;
            }
            (*current)->value = val;
            log_info("Set value");
            break;
        case 'v': // Print value of the current node
            printf("Value is [%s]\n", c_to_string((*current)->value));
            break;
        case 'c': ; // Go to major child
            GTNode* c = get_major_child(*current);
            if(!c) {
                log_error("No children found");
                return;
            }
            *current = c;
            log_info("Switched to major child");
            break;
        case 'b': ; // Go to next brother
            GTNode* b = get_next_brother(*current);
            if(!b) {
                log_error("No brother found");
                return;
            }
            *current = b;
            log_info("Switched to next brother");
            break;
        case 'q': // Quit program
            log_info("Quit");
            exit(EXIT_SUCCESS);
            break;
        case 't': ; // Do task
            TaskAnswer res = do_task(*root);
            printf("Level: %d -> %d node(s)\n", res.level_number, res.nodes_count);
            break;
        case 'd': // Delete child node
            printf("Child index: ");
            int idx = 0;
            if(scanf("%d", &idx) != 1) {
                log_error("Failed to read value");
                return;
            }
            delete_child(*current, idx);
            log_info("Delete child tree");
            break;
        case 'a': ; // Add child to the current node
            char name[32];
            printf("Enter child value: ");
            if(scanf("%s", name) != 1) {
                log_error("Failed to read value");
                return;
            }
            City v = c_from_string(name);
            if(!v) {
                log_error("Invalid value");
                return;
            }
            if(!add_child(*current, v)) {
                log_error("Failed to allocate memory for new node");
                return;
            }
            log_info("Add child node");
            break;
        case 'p': // Print tree
            print_tree(*root, 0);
            break;
        case 'h':
            print_help();
            break;
        default:
            log_error("Unknown command. Try again");
            break;
    }
}

// Program entrypoint
int main(void) {
    GTNode* root = build_tree(EMPTY);
    GTNode* current = root;

    int cmd = 0;
    signal(SIGINT, stop_handler); // Setting SIGINT handler
    while(true) { // Program loop
        cmd = getchar();
        parse_command(cmd, &root, &current);
    }
    return EXIT_SUCCESS;
}