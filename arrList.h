//
// Created by heros on 9/12/24.
//

#ifndef ARRLIST_H
#define ARRLIST_H

#include <stdlib.h>
#include "types.h"

typedef struct list * list;

list listInit(size_t);
void listAppend(list, prime);
prime listGet(list, size_t);
size_t listSize(list);
void listFree(list);

#endif //ARRLIST_H
