/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include <stdio.h>
#include "amp.h"

void test_reformat(){
    char test[15] = "A_____Bb''cc#d";
    reformat(test);
    printf("%s", test);
}

int main(){
    
    return 0;
}