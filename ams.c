/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include "define.h"
#include "ams.h"
#include "amp.h"

/**
 * tested, it works !
 * ressource utilisée pour séparer une ligne avec '|' : https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
 * @param char* line
 * @return s_tick
 */
s_tick tickFromLine(char* line){
    s_tick tick_;
    for (int i = 0; i < 4; ++i) {
        tick_.note[i] = 0;
    }
    int j = 0;

    char* token = strtok(line, "|"); // ignore la première colonne aka l'index
    token = strtok(NULL, "|");
    for (int i = 0; token != NULL; ++i) {
        switch (token[0]) {
            case '^':
                tick_.accent = 1;
                tick_.note[j] = i+1;
                j++;
                break;
            case 'x':
                tick_.accent = 0;
                tick_.note[j] = i+1;
                j++;
                break;
        }
        token = strtok(NULL, "|");
    }
    return tick_;
}

int durationFromLetter(char letter){
    switch (letter){
        case 'R':
            return 8;
        case 'B':
            return 4;
        case 'N':
            return 2;
        case 'C':
            return 1;
        default:
            printf("Format error, I don't know this note %c", letter);
            return 0;
    }
}

int noteNumberFromString(char* string){
    char notes[60][4] = {
            "C1", "C1#", "D1", "D1#", "E1", "F1", "F1#", "G1", "G1#", "A1", "A1#", "B1",
            "C2", "C2#", "D2", "D2#", "E2", "F2", "F2#", "G2", "G2#", "A2", "A2#", "B2",
            "C3", "C3#", "D3", "D3#", "E3", "F3", "F3#", "G3", "G3#", "A3", "A3#", "B3",
            "C4", "C4#", "D4", "D4#", "E4", "F4", "F4#", "G4", "G4#", "A4", "A4#", "B4",
            "C5", "C5#", "D5", "D5#", "E5", "F5", "F5#", "G5", "G5#", "A5", "A5#", "B5"
    };
    int index = -1;
    for (int i = 0; i < 60; ++i) {
        if (!strcmp(notes[i], string)){
            index = i+1;
        }
    }
    return index;
}

s_song readAMS(char* fileName){
	FILE* pf = fopen(fileName, "r");
	s_song mySong;

	if(pf == NULL){
        printf("file not opened ! A song filled with 0 is returned. from readAMS()\n");
		mySong.title[0] = '\0';
		mySong.tpm = 0;
		mySong.nTicks = 0;
        for (int i = 0; i < MAX_NUMBER_TICKS; ++i) {
            mySong.tickTab[i].accent = 0;
            for (int j = 0; j < 4; ++j) {
                mySong.tickTab[i].note[j] = 0;
            }
        }

	}else{
		fgets(mySong.title, MAX_SIZE_TITLE, pf); // 1ere ligne : titre
        removeCharAtIndex(mySong.title, strlen(mySong.title)-1); // but : enlever le \n à la fin pour passer l'autotest
        char bpm[MAX_TPM_SIZE] ="";
		fgets(bpm, MAX_TPM_SIZE, pf); // 2eme ligne : tpm
        mySong.tpm = atoi(bpm)*2; // 1 tick = 0.5 temps. D'où le * 2.

        char buffer[MAX_SIZE_LINE] = "";
        fgets(buffer,MAX_SIZE_LINE,pf); // la ligne 3 est vide
        fgets(buffer,MAX_SIZE_LINE,pf); // la ligne 4 contient les entêtes des colonnes

        int nb_ticks = 0;
		while(!feof(pf)){
            fgets(buffer, MAX_SIZE_LINE, pf);
            mySong.tickTab[nb_ticks] = tickFromLine(buffer);
			nb_ticks++;
		}
		mySong.nTicks = nb_ticks;
	}
    fclose(pf);
	return mySong;
}

void createAMS(char* txtFileName, char* amsFileName){
    FILE* rpf = fopen(txtFileName, "r");
    FILE* wpf = fopen(amsFileName, "w");

    char title[MAX_SIZE_TITLE] = "";
    fgets(title, MAX_SIZE_TITLE, rpf); // 1ere ligne : titre
    char tpm[MAX_TPM_SIZE] ="";
    fgets(tpm, MAX_TPM_SIZE, rpf); // 2eme ligne : tpm
    fprintf(wpf, title);
    fprintf(wpf, tpm);
    fprintf(wpf, "\r\n");

    // entêtes de colonnes
    fprintf(wpf, "    ");
    for(int i = 1; i <= 60; i++){
        fprintf(wpf, "%02d ", i);
    }
    fprintf(wpf, "\r\n");

    char buffer[10] = "";
    fgets(buffer, 10, rpf); // 3ème ligne vide

    char temp_tab[MAX_NUMBER_TICKS][60];
    for (int i = 0; i < MAX_NUMBER_TICKS; ++i) {
        for (int j = 0; j < 60; ++j) {
            temp_tab[i][j] = ' ';
        }
    }

    int nb_ticks = 0;
    char line[MAX_SIZE_LINE] = "";
    for (int i = 0; fgets(line, MAX_SIZE_LINE, rpf) != NULL; ++i) { // i = indice d'un tick/ligne d'ams
        char* token = strtok(line, ",\r\n");
        for (int j = 0; token != NULL; ++j){
            // séparation de la note et du nombre de ticks
            int duration = durationFromLetter(token[strlen(token)-1]);
            char note_str[4] = "";
            if (token[0] == ' '){ removeCharAtIndex(token, 0);}
            strncpy(note_str, token, strlen(token)-2);
            int note_int = noteNumberFromString(note_str);


            // remplissage du tableau
            temp_tab[i][note_int-1] = '^';
            for (int k = 1; k < duration; ++k){
                temp_tab[i+k][note_int-1] = 'x';
            }
            token = strtok(NULL, ",\r\n");
        }
        nb_ticks++;
    }

    // écriture dans le fichier à partir du tableau
    for (int i = 0; i < nb_ticks; ++i) {
        fprintf(wpf, "%03d|", i+1);
        for (int j = 0; j < 60; ++j) {
            fprintf(wpf, "%c", temp_tab[i][j]);
            fprintf(wpf, " |");
        }
        if (i != nb_ticks-1) {
            fprintf(wpf, "\r\n");
        }
    }

    fclose(wpf);
    fclose(rpf);
}