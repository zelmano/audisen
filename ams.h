/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#ifndef AUDISEN2024_AMS_H
#define AUDISEN2024_AMS_H

#include "define.h"

struct song initSong();
struct song readAMS(char* fileName);
void createAMS(char* txtFileName, char* amsFileName);


#endif //AUDISEN2024