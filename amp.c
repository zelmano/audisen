/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include "define.h"
#include "amp.h"

/**
 * tente d'ouvrir le fichier ams
 * ressource utilisée pour le rappel sur fopen() : https://koor.fr/C/cstdio/fopen.wp
 * * @param filename
 * @return a file pointer
 */
FILE* initAMP(char* filename){
    FILE * pf = fopen(filename, "r");

    if (pf == NULL){
        printf("error ! cannot open the file '%s'", filename);
        exit(1);
    }
   
    return pf;
}



void readAMP(FILE* pf, char * song_filename){

}

void closeAMP(FILE* pf){
    
}