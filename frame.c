/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"

// exemple de trame : #<content>*<checksum><CR><LF>


void createInitFrame(s_song mySong, char* frame){
    //init frame : #Bohemian Rhapsody,144,16*<checksum><CR><LF>
    char myFrame[MAX_SIZE_LINE];
    myFrame[0] = '#';
    strcat(myFrame, mySong.title);
    strcat(myFrame,",");

    //conversion du tpm en chaine de caracteres
    char tpm_str[4];
    sprintf(tpm_str, "%d", mySong.tpm);
    strcat(myFrame,tpm_str);

    strcat(myFrame,",");

    //pareil pour nTicks
    char nTicks_str[4];
    sprintf(nTicks_str, "%d", mySong.nTicks);
    strcat(myFrame,nTicks_str);

    strcat(myFrame,"*");

    //checksum : XOR bit à bit des codes ASCII des caractères compris strictement entre # et *, y compris les virgules.
    //résultat en hexadécimal sur 2 caractères en minuscules
    int checksum = 0;
    for(int i = 1; i < strlen(myFrame); i++){
        checksum ^= myFrame[i];
    }
    char checksum_str[3];
    sprintf(checksum_str, "%02x", checksum); //02 pour forcer 2 un zéro devant si 1 seul caractere
    strcat(myFrame,checksum_str);

    strcat(myFrame,"\r\n");

    strcpy(frame, myFrame);

    //printf("Frame : %s\n", frame);
}

void createTickFrame(s_tick myTick, char* frame){

}
