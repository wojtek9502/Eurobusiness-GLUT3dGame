#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED
#include <iostream>
#include "round.hpp"


/* Funkcja obs³uguj¹ca klawiaturê */
void KeyFunc(unsigned char key, int x, int y) {
    //rotacja gora dol
    if(lookA <=15) lookA=15;
    if(lookA >=75) lookA=75;

    if(key=='w' || key=='W')   { camera_move=true; lookA += 5; glutPostRedisplay();}
    if(key=='s' || key=='S')   { camera_move=true;  lookA -= 5; glutPostRedisplay(); }
   // cout << "Kat kamery gora dol= " << lookA << endl;

    //rotacja
    if(key=='r' || key=='R')
    {
        angle+=4;
        camera_move=true;
        glutPostRedisplay();
    }
   // cout << "rotacja obiektow w stopniach = " << angle << endl;


    /* Odrysowanie sceny: */
    if(key==13)
    {
       camera_move=false;
       glutPostRedisplay();
    }


    if(key == 0x1B)		exit(0);

}

#endif // KEYBOARD_H_INCLUDED
