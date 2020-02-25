/*! \mainpage Kueraufgaben (Version 07.12.2019)
 *
 * \section intro_sec Introduction
 * Documentation for the PC part of the project, for file Nibahn_PC.c
 * \subsection used  Used software
 * As the template was taken HelloXBee_PC.c
 */


//includes libraries
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

//defines which serial port will be used for the communication
#define dev "/dev/ttyUSB0"


/**
 * @file Nibahn_PC.c
 * @author Alexandr Petrov
 *
 * @version 04.12.2019
 *
 * @brief This is the control console of the Nibahn
 */

int main(void)
{

	struct termios old_termios;
	struct termios new_termios;
	//buffer to save the chars
	//pointed on the opened serial device
	int fd;
	char formedbyte = 255;
	//to save the count of chars received
	int res;
	int wahl;

	//opens the serial port
	fd = open(dev, O_RDWR | O_NOCTTY);
	//if the selected serial port is not found
	if (fd < 0) {
		fprintf(stderr, "error, counldn't open file %s\n", dev);
		return 1;
	}
	//returns an integer that either indicates success or failure of the prot opening
	if (tcgetattr(fd, &old_termios) != 0) {
		fprintf(stderr, "tcgetattr(fd, &old_termios) failed: %s\n", strerror(errno));
		return 1;
	}
	//configure the serial port -> for more information: http://en.wikibooks.org/wiki/Serial_Programming/termios
	memset(&new_termios, 0, sizeof(new_termios));
	new_termios.c_iflag = IGNPAR; //ignore parity bit
	new_termios.c_oflag = 0;
	new_termios.c_cflag = CS8 | CREAD | CLOCAL | HUPCL; //sets the serial port to 8N1
	new_termios.c_lflag = 0;
	new_termios.c_cc[VINTR]    = 0;
	new_termios.c_cc[VQUIT]    = 0;
	new_termios.c_cc[VERASE]   = 0;
	new_termios.c_cc[VKILL]    = 0;
	new_termios.c_cc[VEOF]     = 4;
	new_termios.c_cc[VTIME]    = 0;
	new_termios.c_cc[VMIN]     = 1;
	new_termios.c_cc[VSWTC]    = 0;
	new_termios.c_cc[VSTART]   = 0;
	new_termios.c_cc[VSTOP]    = 0;
	new_termios.c_cc[VSUSP]    = 0;
	new_termios.c_cc[VEOL]     = 0;
	new_termios.c_cc[VREPRINT] = 0;
	new_termios.c_cc[VDISCARD] = 0;
	new_termios.c_cc[VWERASE]  = 0;
	new_termios.c_cc[VLNEXT]   = 0;
	new_termios.c_cc[VEOL2]    = 0;
	//sets the input speed of the serial interdace to 9600baud
	if (cfsetispeed(&new_termios, B9600) != 0) {
		fprintf(stderr, "cfsetispeed(&new_termios, B9600) failed: %s\n", strerror(errno));
		return 1;
	}
	//sets the output speed of the serial interdace to 9600baud
	if (cfsetospeed(&new_termios, B9600) != 0) {
		fprintf(stderr, "cfsetospeed(&new_termios, B9600) failed: %s\n", strerror(errno));
		return 1;
	}
	//sets the termios struct of the file handle fd from the options defined via the options
	if (tcsetattr(fd, TCSANOW, &new_termios) != 0) {
		fprintf(stderr, "tcsetattr(fd, TCSANOW, &new_termios) failed: %s\n", strerror(errno));
		return 1;
	}

	/// starts the user interaction cycle
	 do {
			 /// Sets the forming byte to 00000000
			 /// allows user to choose the destination address and forms destination address part of the byte accordingly
			formedbyte = 0;
			printf(" -1 Broadcast\n");
			printf(" -2 zu Master \n");
			printf(" -3 zu Nibo Sklave 1 \n");
			printf(" -4 zu Nibo Sklave 2 \n");
			printf(" -0 Exit\n");
			printf(" Ihre Auswahl : \n");
			scanf("%d",&wahl);
			switch (wahl)
				{
					case 1: formedbyte = formedbyte|(0<<6);  break; // current byte is 00xxxxxx
					case 2: formedbyte = formedbyte|(1<<6);  break; // current byte is 01xxxxxx
					case 3: formedbyte = formedbyte|(2<<6);  break; // current byte is 10xxxxxx
					case 4: formedbyte = formedbyte|(3<<6);  break; // current byte is 11xxxxxx
				}
			/// Sets Source address to 00 because byte is going to be sent from the PC send from PC
			formedbyte = formedbyte|(0<<4); // current byte is xx00xxxx
			/// allows user to choose the commands set and forms commands set part of the byte accordingly
			printf(" -1 Vorwarts/Stop/Ruckwaerts (Zug mode) \n");
			printf(" -2 Links/Rechts Rausfahren (Selbstaendig) \n");
			printf(" -3 Master Prozess \n");
			printf(" -0 Exit\n");
			printf(" Ihre Auswahl : \n");
			scanf("%d",&wahl);
			switch (wahl)
				{
					case 1: formedbyte = formedbyte|(0<<2);  break; // current byte is xx0000xx
					case 2: formedbyte = formedbyte|(1<<2);  break; // current byte is xx0001xx
					case 3: formedbyte = formedbyte|(2<<2);  break; // current byte is xx0010xx
				}
			/// allows user to choose the command from the first set if chosen and forms command part of the byte accordingly
			if (wahl == 1)
				{
					printf(" -1 Stopp/Vorwaerts\n");
					printf(" -2 Stopp/Backwards\n");
					printf(" -3 Links Richtung wechseln \n");
					printf(" -4 Rechts Richtung wechseln \n");
					printf(" -0 Exit\n");
					printf(" Ihre Auswahl : \n");
					scanf("%d",&wahl);
					switch (wahl)
						{
							case 1: formedbyte = formedbyte|(0);  break; // current byte is xx000000
							case 2: formedbyte = formedbyte|(1);  break; // current byte is xx000001
							case 3: formedbyte = formedbyte|(2);  break; // current byte is xx000010
							case 4: formedbyte = formedbyte|(3);  break; // current byte is xx000011
						}
				}
			/// allows user to choose the command from the second set if chosen and forms command part of the byte accordingly
			else if (wahl == 2)
			{
				printf(" -1 Stopp/Vorwaerts\n");
				printf(" -2 Stopp/Backwards\n");
				printf(" -3 Links biegen \n");
				printf(" -4 Rechts biegen \n");
				printf(" -0 Exit\n");
				printf(" Ihre Auswahl : \n");
				scanf("%d",&wahl);
				switch (wahl)
				{
					case 1: formedbyte = formedbyte|(0);  break; // current byte is xx000100
					case 2: formedbyte = formedbyte|(1);  break; // current byte is xx000101
					case 3: formedbyte = formedbyte|(2);  break; // current byte is xx000110
					case 4: formedbyte = formedbyte|(3);  break; // current byte is xx000111
				}
			}
			/// allows user to choose the command from the third set if chosen and forms command part of the byte accordingly
			else if (wahl == 3)
			{
				printf(" -3 Auswahl neustarten\n");
				printf(" -4 Nicht mehr Teil der Kolonne sein und Auswahl neustarten\n");
				printf(" -0 Exit\n");
				printf(" Ihre Auswahl : \n");
				scanf("%d",&wahl);

				switch (wahl)
				{
					case 3: formedbyte = formedbyte|(2);  break; // current byte is xx001010
					case 4: formedbyte = formedbyte|(3);  break; // current byte is xx001011
				}
			}
			/// sends formed Byte
			write(fd, &formedbyte , 1);
		}
	 /// before user chooses 0
	while ( wahl != 0 );


// Before leaving, reset the old serial settings and close the serial port
tcsetattr(fd, TCSANOW, &old_termios);
close(fd);
printf("Serial port closed");
return 0;
	}
