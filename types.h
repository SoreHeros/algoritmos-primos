//
// Created by heros on 9/12/24.
//

#ifndef TYPES_H
#define TYPES_H

typedef unsigned int prime;

typedef struct{
    unsigned int factor;
    unsigned int multiple;
} heapObj;

typedef struct{
    size_t size;
    heapObj arr[];
} heap;

#endif //TYPES_H
