/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#ifndef AUDISEN2024_AMS_H
#define AUDISEN2024_AMS_H

#include "define.h"

void split(char* src, char* delim, char** dest);

struct tick tickFromLine(char* line);

struct song initSong();
struct song readAMS(char* fileName);
void createAMS(char* txtFileName, char* amsFileName);


#endif //AUDISEN2024