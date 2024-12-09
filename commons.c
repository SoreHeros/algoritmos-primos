//
// Created by heros on 9/12/24.
//

#include "commons.h"
#include <math.h>

size_t prime_prediction(size_t size){
    if(size < 1024){
        return size;
    }

    return size / (log(size) - 2);
}