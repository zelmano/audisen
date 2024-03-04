/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#ifndef AUDISEN2024_AMP_H
#define AUDISEN2024_AMP_H

#include "define.h"


FILE* initAMP(char* filename);

void readAMP(FILE* pf, char * song_filename);

void closeAMP(FILE* pf);

#endif //AUDISEN2024_AMP_H