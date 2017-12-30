#ifndef DRAW_OBJECTS_HPP_INCLUDED
#define DRAW_OBJECTS_HPP_INCLUDED
#include <vector>
#include "Player.hpp"
#include "round.hpp"
#include <iostream>

GLfloat angle;	/* K¹t obrotu obiektów wokó³ œrodka sceny (animacja) */

using namespace std;


Player ptab[2]= { Player(1,"Player1",START_CASH,75.0, 3.0, 100.0,true),
                  Player(2,"Player2",START_CASH,75.0, 3.0, 105.0,false)
                };

void draw_objects_on_scene()
{
    next_round(ptab);

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


	//cout << ptab[0].name << " " << ptab[0].position_x << "    ";



	//GRACZE
    glPushMatrix();
		glTranslatef(ptab[0].position_x, ptab[0].position_y, ptab[0].position_z);
		glColor3f(1.0, 0.0, 0.0);
		glScalef(3.0, 3., 3); //gracz1
		glutSolidSphere(1,30,30);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(ptab[1].position_x, ptab[1].position_y, ptab[1].position_z);
		glColor3f(1.0, 1.2, 0.0);
		glScalef(5.0, 5.0, 5.0); //gracz2
		glutSolidCube(1);
	glPopMatrix();



}

#endif // DRAW_OBJECTS_HPP_INCLUDED
