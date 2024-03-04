/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#ifndef AUDISEN_USB_H
#define AUDISEN_USB_H

#include "ftd2xx.h"

FT_HANDLE initUSB();
void closeUSB(FT_HANDLE ftHandle);
void writeUSB(char* frame, FT_HANDLE ftHandle);

#endif //AUDISEN_USB_H
