/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include "define.h"
#include "ams.h"


s_song readAMS(char* fileName){
	//lire le fichier fileName de type .ams
	//retourner une structure de type s_song avec toutes les infos sur le morceau
	//si le fichier ne peut pas être ouvert, renvoyer une structure avec le titre vide
	//et que des 0 sur tous les champs

	//typedef
  //struct song{
	// 	int tpm;// tick par minutes
	// 	int nTicks;// Nombre de ticks dans le morceau
	// 	char title[MAX_SIZE_TITLE];// Titre du morceau
	// 	struct tick tickTab[MAX_NUMBER_TICKS];// Tableau de ticks
	//}s_song;
	
	FILE* pf = fopen(fileName, "r");

	s_song mySong;

	if(pf == NULL){
		
		strcpy(mySong.title, ""); //autre moyen de mettre un titre vide ?

		mySong.tpm = 0;
		mySong.nTicks = 0;

		// vraiment besoin de mettre tous les trucs à 0 ou juste un seul 0 ?
		for(int i = 0; i < MAX_NUMBER_TICKS; i++){
			mySong.tickTab[i].accent = 0;
			for(int j = 0; j < 4; j++){
				mySong.tickTab[i].note[j] = 0;
			}
		}
	}else{
		fgets(mySong.title, MAX_SIZE_TITLE, pf);
		fgets(mySong.tpm, 4, pf);

		nb_lines = 0;
		while(fgets(buffer, MAX_SIZE_LINE, pf) != EOF){
			nb_lines++;
		}
		mySong.nTicks = nb_lines-2;

	}

	return mySong;
}


void createAMS(char* txtFileName, char* amsFileName){


}