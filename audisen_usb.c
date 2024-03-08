#define _WIN32
#include <stdio.h>
#include <unistd.h>
#include "ftd2xx.h"
#include "define.h"
#include "usb.h"
#include "amp.h"
#include "ams.h"
#include "frame.h"


void sendUSBFramesPlaylist(char* AMPfilename, FT_HANDLE ftHandle){
    FILE* AMPfile = initAMP(AMPfilename);

    char AMSfilename[FILENAME_MAX] = "";
    readAMP(AMPfile, AMSfilename);
    while (strcmp(AMSfilename, "fin")) { // readAMP renvoie "fin" quand il n'y a plus de musique dans le fichier amp
        s_song currentSong = readAMS(AMSfilename);
        char initFrame[INIT_FRAME_MAX_SIZE] = "";
        char tickFrame[TICK_FRAME_SIZE] = "";
        createInitFrame(currentSong, initFrame);
        printf("%s", initFrame);
        writeUSB(initFrame, ftHandle);
        for (int i = 0; i < currentSong.nTicks; ++i) {
            createTickFrame(currentSong.tickTab[i], tickFrame);
            writeUSB(tickFrame, ftHandle);
        }
        sleep(1); // sans ce délai la carte ne charge que la première musique
        readAMP(AMPfile, AMSfilename);
    }
    closeAMP(AMPfile);
}

int main(){
    printf("---------------------USB------------------------\n");
    FT_HANDLE myFtHandle = initUSB();
    sendUSBFramesPlaylist("working_playlist.amp", myFtHandle);
    closeUSB(myFtHandle);
    return 0;
}