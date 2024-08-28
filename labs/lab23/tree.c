#include "tree.h"

GTNStack* GTNStack_create() {
    GTNStack* s = (GTNStack*)malloc(sizeof(GTNStack));
    if(!s)
        return NULL;
    s->size = 0;
    s->top = NULL;
    return s;
}

GTNode* GTNStack_pop(GTNStack* s) {
    GTNStackNode* t = s->top;
    if(!t)
        return NULL;
    GTNode* v = t->pointer;
    GTNStackNode* new_top = s->top->next;
    free(s->top);
    s->top = new_top;
    s->size--;
    return v;
}

void GTNStack_push(GTNStack* s, GTNode* v) {
    if(!v)
        return;
    GTNStackNode* n = (GTNStackNode*)malloc(sizeof(GTNStackNode));
    n->pointer = v;
    n->next = s->top;
    s->top = n;
    s->size++;
}

bool GTNStack_empty(GTNStack* s) { return s->size == 0; }

void GTNStack_destroy(GTNStack* s) {
    GTNStackNode* n = s->top;
    while(n) {
        GTNStackNode* d = n;
        n = n->next;
        free(d);
    }
    free(s);
}

GTNode* build_tree(City v) {
    GTNode* node = (GTNode*)malloc(sizeof(GTNode));
    if(!node)
        return NULL;
    node->major_child = NULL;
    node->next_brother = NULL;
    node->value = v;
    return node;
}

GTNode* get_major_child(GTNode* node) { return node->major_child; }

GTNode* get_next_brother(GTNode* node) { return node->next_brother; }

void set_value(GTNode* node, City v) { node->value = v; }

void delete_tree(GTNode* node) {
    if(!node)
        return;
    GTNode* f = node->major_child;
    while(f) {
        GTNode* d = f;
        f = f->next_brother;
        delete_tree(d);
    }
    free(node);
}

void delete_child(GTNode* node, int idx) {
    if(!node || idx < 0)
        return;
    if(idx == 0) {
        GTNode* d = get_major_child(node);
        if(!d)
            return;
        node->major_child = get_next_brother(d);
        delete_tree(d);
        return;
    }
    GTNode* prev = get_child(node, idx - 1);
    if(!prev)
        return;
    GTNode* d = get_next_brother(prev);
    if(!prev)
        return;
    prev->next_brother = get_next_brother(d);
    delete_tree(d);
}

GTNode* get_child(GTNode* node, int idx) {
    GTNode* f = node->major_child;
    int i = 0;
    while(i < idx) {
        if(!f)
            return NULL;
        f = f->next_brother;
        i++;
    }
    return f;
}

bool add_child(GTNode* parent, City v) {
    if(!parent)
        return false;
    GTNode* new_child = build_tree(v);
    if(!new_child)
        return false;
    GTNode* c = get_major_child(parent);
    if(!c) {
        parent->major_child = new_child;
        return true;
    }
    while(c->next_brother) 
        c = c->next_brother;
    c->next_brother = new_child;
    return true;
}

int count_children(GTNode* node) {
    if(!node)
        return 0;
    int cnt = 0;
    GTNode* c = get_major_child(node);
    while(c) {
        cnt++;
        c = c->next_brother;
    }
    return cnt;
}

int count_brothers(GTNode* major_brother) {
    int cnt = 0;
    while(major_brother) {
        cnt++;
        major_brother = get_next_brother(major_brother);
    }
    return cnt;
}

void print_tree(GTNode* root, int level) {
    if(!root)
        return;
    for(int i = 0; i < level; ++i)
        printf("- ");

    printf("%s\n", c_to_string(root->value));

    print_tree(root->major_child, level + 1);
    print_tree(root->next_brother, level);
}

GTNStack* measure_tree_layer(GTNStack* layer, int ln, TaskAnswer* a) {
    int cnt = 0;
    GTNStack* next_layer = GTNStack_create();
    while(!GTNStack_empty(layer)) {
        GTNode* node = GTNStack_pop(layer);
        while(node) {
            cnt++;
            GTNStack_push(next_layer, get_major_child(node));
            node = get_next_brother(node);
        }
    }
    if(a->nodes_count < cnt) {
        a->level_number = ln;
        a->nodes_count = cnt;
    }
    GTNStack_destroy(layer);
    return next_layer;
}