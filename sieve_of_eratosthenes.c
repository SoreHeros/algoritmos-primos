//
// Created by heros on 30/01/25.
//

#include "sieve_of_eratosthenes.h"
#include "commons.h"

list sieve_of_eratosthenes(prime number){
    list l = listInit(prime_prediction(number));
    if(number >= 2)
        listAppend(l, 2);

    prime size = number / 2 + 1;
    unsigned char binArr[size];

    for (int i = 0; i < size; i++)
        binArr[i] = 1;

    prime p, sqr;
    for(p = 3; (sqr = p * p) <= number; p+=2){
        if(binArr[p / 2]){
            listAppend(l, p);
            for(;sqr <= number; sqr += 2 * p) //como p es impar, sumarle 2p se salta los pares
                binArr[sqr / 2] = 0;
        }
    }

    for(; p <= number; p+=2){
        if (binArr[p/2])
            listAppend(l, p);
    }

    return l;
}