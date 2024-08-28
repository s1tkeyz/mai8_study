#include "libcp8-list.h"
#include "libcp8-iter.h"

// Shrinks list's buffer if it nessesary
static void shrink_buffer(List* list) {
    if(BUFFER_EXPAND_FACTOR * BUFFER_EXPAND_FACTOR * list->size > list->capacity)
        return;
    ListNode* tmp = (ListNode*)realloc(list->buffer, sizeof(ListNode) * list->capacity / BUFFER_EXPAND_FACTOR);
    if(!tmp)
        return;
    list->buffer = tmp;
    list->capacity /= BUFFER_EXPAND_FACTOR;
}

// Expands list's buffer if it nessesary
static bool expand_buffer(List* list) {
    if(list->size < list->capacity)
        return true;
    ListNode* tmp = (ListNode*)realloc(list->buffer, list->capacity * BUFFER_EXPAND_FACTOR * sizeof(ListNode));
    if(!tmp)
        return false;
    list->buffer = tmp;
    list->capacity *= BUFFER_EXPAND_FACTOR;
    return true;
}

// Returns iterator to the node by list index
Iterator seek(List* list, int li) {
    if(!list || list_empty(list) || li < 0)
        return iter_create(list);
    Iterator it = iter_create(list);
    li %= list->size;
    int i = 0;
    while(i < li) {
        iter_next(&it);
        i++;
    }
    return it;
}

ListNode empty_node() {
    ListNode n;
    n.next = -1;
    n.prev = -1;
    n.value = LISTNODE_DEFAULT_VALUE;
    return n;
}

List* list_create() {
    List* l = (List*)malloc(sizeof(List));
    if(!l)
        return NULL;
    l->capacity = MIN_BUFFER_CAPACITY;
    l->size = 0;
    l->head = -1;

    ListNode* buff = (ListNode*)malloc(l->capacity * sizeof(ListNode));
    if(!buff) {
        free(l);
        return NULL;
    }
    l->buffer = buff;
    return l;
}

void list_destroy(List* list) {
    free(list->buffer);
    free(list);
}

bool list_push(List* list, uint64_t value) {
    if(!list)
        return false;
    if(!expand_buffer(list))
        return false;

    ListNode new_node = empty_node();
    new_node.value = value;
    
    if(list_empty(list)) {
        new_node.next = 0;
        new_node.prev = 0;
        list->buffer[0] = new_node;
        list->head = 0;
    } else {
        Iterator it = iter_create(list);
        iter_prev(&it);
        new_node.next = list->head;
        ListNode* p = iter_node(&it);
        p->next = list->size;
        new_node.prev = it.current_bi;
        list->buffer[list->head].prev = list->size;
        list->buffer[list->size] = new_node;
    }
    list->size++;
    return true;
}

bool list_insert(List* list, int li, uint64_t value) {
    if(!list || list_empty(list) || li < 0)
        return false;
    li %= list->size;
    if(!expand_buffer(list))
        return false;

    ListNode new_node = empty_node();
    new_node.value = value;

    int mli = li < 1 ? list->size - 1 : li - 1;
    Iterator it = seek(list, mli);
    int pbi = it.current_bi;
    iter_next(&it);
    int nbi = it.current_bi;

    new_node.next = nbi;
    new_node.prev = pbi;
    list->buffer[list->size] = new_node;
    list->buffer[pbi].next = list->size;
    list->buffer[nbi].prev = list->size;
    if(li == 0)
        list->head = list->size;
    list->size++;
    return true;
}

void list_remove(List* list, int li) {
    if(!list || list_empty(list) || li < 0)
        return;
    li %= list->size;

    if(list->size == 1) {
        list->head = -1;
    } else {
        Iterator it = seek(list, li);
        int dbi = it.current_bi;
        ListNode* d = iter_node(&it);
        iter_prev(&it);
        iter_node(&it)->next = d->next;
        iter_next(&it);
        iter_node(&it)->prev = d->prev;
        if(dbi == list->head)
            list->head = it.current_bi;
        list->buffer[dbi] = list->buffer[list->size - 1];
        int p = list->buffer[dbi].prev;
        int n = list->buffer[dbi].next;
        list->buffer[p].next = dbi;
        list->buffer[n].prev = dbi;
    }
    list->size--;
    shrink_buffer(list);
}

uint64_t list_get(List* list, int li) {
    if(list_empty(list))
        return LISTNODE_DEFAULT_VALUE;
    li %= list->size;
    Iterator it = seek(list, li);
    return iter_value(&it);
}

void list_set(List* list, int li, uint64_t value) {
    if(!list || list_empty(list) || li < 0)
        return;
    li %= list->size;
    Iterator it = seek(list, li);
    list->buffer[it.current_bi].value = value;
}

bool list_empty(List* list) { return list->size == 0; }

void list_print(List* list) {
    printf("head=%d, size=%d, capacity=%d\n", list->head, list->size, list->capacity);
    printf("List: ");
    Iterator it = iter_create(list);
    int i = 0;
    while(i < list->size) {
        printf("%ld ", iter_value(&it));
        iter_next(&it);
        i++;
    }
    putchar('\n');
}

void list_clean(List* list) {
    list->size = 0;
    list->head = -1;
    while(list->capacity > MIN_BUFFER_CAPACITY)
        shrink_buffer(list);
}