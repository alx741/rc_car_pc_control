/*
 * ============================================================================
 *
 *       Filename:  rc.cpp
 *
 *    Description:  Código para controlar auto RC por puerto paralelo
 *
 *        Version:  1.0
 *        Created:  12/10/12 20:23:28
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Daniel Campoverde Carrión [Alx741]
 *   Organization:  www.silly-bytes.blogspot.com
 *
 * ===========================================================================
 */


#include <iostream>
#include <ncurses.h>
#include <sys/io.h>

#define puerto (0x378) //Puede ser (0x278)


using namespace std;

int main(void){

//inicializamos ncurses
initscr();
cbreak();
noecho();
nonl();
intrflush(stdscr, FALSE);
keypad(stdscr, TRUE);


//Abrir puerto y configurar permisos
if(ioperm(puerto,1,1)){
	cout << "Error de permisos" << endl << flush;
    }


    int ch;

    //recibimos las pulsaciones
    //bit1,bit3 -> adelante
    //bit2,bit4 -> atras
    //bit3,bit2 -> derecha
    //bit4,bit1 -> izquierda
    while(true){

		ch=getch();
		if(ch==32) outb(0,puerto);
		if(ch==259) outb(5,puerto); //ascii 259=(arriba)
		if(ch==258) outb(10,puerto); //ascii 258=(abajo)
		if(ch==261) outb(6,puerto); //ascii 261=(derecha)
		if(ch==260) outb(9,puerto); //ascii 260=(izquierda)
		if(ch==27){ outb(0,puerto); break;}
    }


    //finalizamos ncurses (regresamos la consola a la normalidad)
    echo();
    resetty();
    endwin();

    return 0;
}
