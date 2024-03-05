#MakeFile squelette à modifier par les étudiants
# Brun Zelman Fontaine Paul CIR3 Caen

#TARGET = audisen_usb.exe # pour la partie USB
TARGET = audisen_sim.out

all: $(TARGET)

run: all
	@./$(TARGET)

#Etudiants : creez les cibles de votre makefile ICI, et completez
tests.out: autotests.c amp.o ams.o frame.o
	gcc autotests.c amp.o ams.o frame.o -o autotests.out -lm

audisen_sim.out: audisen_sim.c amp.o ams.o frame.o
	gcc audisen_sim.c amp.o ams.o frame.o -o audisen_sim.out -lm
amp.o: amp.c
	gcc -Wall -c amp.c -o amp.o
ams.o: ams.c
	gcc -Wall -c ams.c -o ams.o
frame.o: frame.c
	gcc -Wall -c frame.c -o frame.o

# ressources utilisées : anciens TPs sur VI + cours de CIR1 https://web.isen-ouest.fr/moodle4/pluginfile.php/2409/mod_resource/content/0/Cours9_FichiersSepares.pdf


#CIBLE a garder pour la partie USB
# Commande de compilation pour Windows mingw a copier en console PowerShell
#  mingw32-make -f Makefile clear test_usb.exe
#audisen_usb.exe : audisen_usb.c ftd2xx.h ftd2xx.lib
#	gcc audisen_usb.c ftd2xx.lib -o audisen_usb.exe

clean:
	rm *.o *.out *.exe

clear:
	del *.o *.exe


