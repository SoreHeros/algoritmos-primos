//
// Created by heros on 9/12/24.
//

#include "arrList.h"

struct list{
    size_t top;
    prime arr[];
};

list inline listInit(const size_t size){
    list l = malloc(sizeof(struct list) + size * sizeof(prime));
    l->top = 0;
    return l;
}

void inline listAppend(struct list * restrict l, const prime p){
    l->arr[l->top++] = p;
}

prime inline listGet(struct list * restrict l, const size_t pos){
    return l->arr[pos];
}

size_t inline listSize(struct list * restrict l){
    return l->top;
}

void inline listFree(struct list * restrict l){
    free(l);
}