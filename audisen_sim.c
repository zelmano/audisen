/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"

void createPlaylistFRM(char* playlistFilename){
    FILE* AMPfile = initAMP(playlistFilename);
    char FRMfilename[MAX_SIZE_PLAYLIST_NAME] = "";
    strncpy(FRMfilename, playlistFilename, strlen(playlistFilename) - 3);
    strcat(FRMfilename, "frm");
    FILE* FRMfile = fopen(FRMfilename, "w");

    char AMSfilename[FILENAME_MAX] = "";
    readAMP(AMPfile, AMSfilename);
    while (strcmp(AMSfilename, "fin")) {
        s_song currentSong = readAMS(AMSfilename);
        char initFrame[INIT_FRAME_MAX_SIZE] = "";
        char tickFrame[TICK_FRAME_SIZE] = "";
        createInitFrame(currentSong, initFrame);
        fprintf(FRMfile, "%s", initFrame);
        for (int i = 0; i < currentSong.nTicks; ++i) {
            createTickFrame(currentSong.tickTab[i], tickFrame);
            fprintf(FRMfile, "%s", tickFrame);
        }
        readAMP(AMPfile, AMSfilename);
    }
    closeAMP(AMPfile);
    fclose(FRMfile);
}

int main(){
    createPlaylistFRM("working_playlist.amp");

    return 0;
}