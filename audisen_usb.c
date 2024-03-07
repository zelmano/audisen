#define _WIN32
#include <stdio.h>
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
    while (strcmp(AMSfilename, "fin")) {
        s_song currentSong = readAMS(AMSfilename);
        char initFrame[INIT_FRAME_MAX_SIZE] = "";
        char tickFrame[TICK_FRAME_SIZE] = "";
        createInitFrame(currentSong, initFrame);
        writeUSB(initFrame, ftHandle);
        for (int i = 0; i < currentSong.nTicks; ++i) {
            createTickFrame(currentSong.tickTab[i], tickFrame);
            writeUSB(tickFrame, ftHandle);
        }
        readAMP(AMPfile, AMSfilename);
    }
    closeAMP(AMPfile);
}

int main(){
    FT_HANDLE myFtHandle = initUSB();

    sendUSBFramesPlaylist("working_playlist.amp", myFtHandle);

    closeUSB(myFtHandle);
    return 0;
}