//
// Created by heros on 9/12/24.
//

#include "trial_by_division.h"
#include "commons.h"
#include <math.h>

list trial_by_division(prime number){
    list l = listInit(prime_prediction(number));

    if(number < 2)
        return l;

    listAppend(l, 2);

    if(number < 3)
        return l;

    listAppend(l, 3);

    for(prime p = 5; p <= number; p+=2){
        prime d, sqr = sqrtl(p) + 0.1;
        for(prime i = 1; (d = listGet(l, i)) <= sqr; i++){
            if(!(p % d))
                goto SKIP;
        }
        listAppend(l, p);
        SKIP:
    }


    return l;
}
