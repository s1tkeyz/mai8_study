#include "libcp8-iter.h"

Iterator iter_create(List* list) {
    Iterator it;
    it.current_bi = !list ? -1 : list->head;
    it.current_li = !list ? -1 : 0;
    it.list = list;
    return it;
}

uint64_t iter_value(Iterator* it) {
    if(!it->list || list_empty(it->list))
        return LISTNODE_DEFAULT_VALUE;
    return it->list->buffer[it->current_bi].value;
}

ListNode* iter_node(Iterator* it) {
    return &(it->list->buffer[it->current_bi]);
}

void iter_next(Iterator* it) {
    if(!it->list || list_empty(it->list))
        return;
    it->current_bi = it->list->buffer[it->current_bi].next;
    it->current_li = (it->current_li + 1) % it->list->size;
}

void iter_prev(Iterator* it) {
    if(!it->list || list_empty(it->list))
        return;
    it->current_bi = it->list->buffer[it->current_bi].prev;
    it->current_li = it->current_li - 1 < 0 ? it->list->size - 1 : it->current_li - 1;
}

bool iter_equal(Iterator* lhs , Iterator* rhs) {
    if(!lhs || !rhs)
        return false;
    return (lhs->list == rhs->list) &&
            (lhs->current_li == rhs->current_li) &&
            (lhs->current_bi == rhs->current_bi);
}