#ifndef DRAW_OBJECTS_HPP_INCLUDED
#define DRAW_OBJECTS_HPP_INCLUDED
#include <vector>
#include "Player.hpp"
#include <iostream>

GLfloat angle;	/* K¹t obrotu obiektów wokó³ œrodka sceny (animacja) */

using namespace std;

//@TODO
 Player p1 = Player(1,"Player1",START_CASH, 200, 100, 100); ///nie dziala
 Player p2 = Player(2,"Player2",START_CASH, 0.0, 1.0, 0.0);

void draw_objects_on_scene()
{

     //potrzebne do obrotu obiektow
    if(angle >= 360)	angle -= 360;
    glRotatef(angle, 0, -1, 0);

    ///PLANSZA
    glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor3f(0, 1, 0);
		glScalef(200.0, 1, 200); //rozmiary planszy
		glutSolidCube(1);
	glPopMatrix();
	glRotatef(10, 0, 1, 0);

    ///-----------------------------------------PROBLEM
            //to widzi          //a tego nie
	//cout << p1.name << " " << p1.position_x << "    ";

    ///------------------------- dopiero tu zmienia a powinno od razu brac z konstruktora
	p1.position_x =100;
	p1.position_y = 20;

	//GRACZE
    glPushMatrix();
		glTranslatef(p1.position_x, p1.position_y, p1.position_z);
		glColor3f(0.5, 0.2, 0.5);
		glScalef(3.0, 3., 3); //gracz1
		glutSolidSphere(1,30,30);
	glPopMatrix();
    next_round();


}

#endif // DRAW_OBJECTS_HPP_INCLUDED
