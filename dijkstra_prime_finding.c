//
// Created by heros on 30/01/25.
//

#include "dijkstra_prime_finding.h"
#include "commons.h"

heapObj heappop(heap * h){
    heapObj ret = h->arr[0];
    h->size--;
    h->arr[0] = h->arr[h->size];

    //hundir cima
    size_t i = 0;
    while(1){
        size_t l = i * 2 + 1, r = i * 2 + 2;

        if (l >= h->size)
            break;
        if (r >= h->size){
            if (h->arr[i].multiple > h->arr[l].multiple){
                heapObj aux = h->arr[i];
                h->arr[i] = h->arr[l];
                h->arr[l] = aux;
            }
            break;
        }

        size_t smaller = l;

        if(h->arr[r].multiple < h->arr[l].multiple)
            smaller = r;

        if(h->arr[i].multiple > h->arr[smaller].multiple){
            heapObj aux = h->arr[i];
            h->arr[i] = h->arr[smaller];
            h->arr[smaller] = aux;
            i = smaller;
        }else
            break;
    }

    return ret;
}

void heappush(heap * h, heapObj obj){
    h->arr[h->size] = obj;
    size_t indx = h->size;
    h->size++;

    while(1){
        size_t prnt = (indx - 1) / 2;

        if(h->arr[prnt].multiple > h->arr[indx].multiple){
            heapObj aux = h->arr[indx];
            h->arr[indx] = h->arr[prnt];
            h->arr[prnt] = aux;
            indx = prnt;
        }else
            break;
    }
}

list dijkstra_prime_finding(prime number){
    list l = listInit(prime_prediction(number));

    if(number >= 2)
        listAppend(l, 2);

    if(number >= 3)
        listAppend(l, 3);

    heap * h = malloc(sizeof(heap) + sizeof(heapObj) * prime_prediction(number));
    h->size = 0;


    heapObj obj = {3 * 2, 3 * 3};

    for (prime p = 5; p <= number; p+=2){
        if(p < obj.multiple){
            heapObj aux = {p * 2, p * p};
            heappush(h, aux);
            listAppend(l, p);
        }else{
            while(obj.multiple <= p){
                obj.multiple += obj.factor;
                heappush(h, obj);
                obj = heappop(h);
            }
        }
    }

    free(h);

    return l;
}