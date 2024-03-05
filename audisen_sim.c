/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"


int main(){
    s_song s = readAMS("bohemian_rhapsody.ams");
    printf("%s", s.title);
    
    return 0;
}