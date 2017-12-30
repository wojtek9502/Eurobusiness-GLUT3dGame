#ifndef RENDER_SCENE_HPP_INCLUDED
#define RENDER_SCENE_HPP_INCLUDED

#include "draw_objects.hpp"


/* Zmienne pomocnicze */
GLfloat lookA = 45;	/* K�t patrzenia w kierunku pionowym */


/* Parametry �wiat�a i materia��w */
GLfloat lightAmb[] = {0.1, 0.1, 0.1, 1.0};
GLfloat lightDif[] = {0.7, 0.7, 0.7, 1.0};
GLfloat lightPos[] = {0, 300, 0.0, 1.0};  ///defauktowo pierwszy param na 100 drugi na 200
GLfloat lightSpec[] = {1, 1, 1, 1};

/* Funkcja rysuj�ca */
void RenderScene(void) {
	/* Wyczyszczenie t�a czarnym kolorem */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Wst�pne ustawienie sceny */
	glLoadIdentity();
	/* Odsuni�cie �rodka sceny od obserwatora */
	glTranslatef(0, 0, -300);
	/* Ustawienie k�ta obserwacji */
	glRotatef(lookA, 1, 0, 0);

	/* Pozycjonowanie �wiat�a */
	/* �wiat�o jest nieruchome wzgl�dem obiekt�w - one przesuwaj� si� pod �wiat�em */
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	/* Animacja */


///##################################################-----------FUNKCJA RYSUJACA OBIEKTY NA PLANSZY----------#############
	draw_objects_on_scene();
///##################################################-----------FUNKCJA RYSUJACA OBIEKTY NA PLANSZY----------#############

	/* Zmiana bufora i opr�nienie kolejki renderowania */
	glutSwapBuffers();
}


#endif // RENDER_SCENE_HPP_INCLUDED
