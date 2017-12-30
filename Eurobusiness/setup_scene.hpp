#ifndef SETUP_SCENE_HPP_INCLUDED
#define SETUP_SCENE_HPP_INCLUDED

#include "render_scene.hpp"

#define ANIM_FPS 40	/* Docelowa liczba ramek animacji na sekund� */


/* Funkcja ustawia parametry renderowania i o�wietlenie... */
/* wywo�ywana na pocz�tku programu */
void setupScene(void) {
	/* Bufor g��boko�ci */
	glEnable(GL_DEPTH_TEST);
	/* W��czenie o�wietlenia */
	glEnable(GL_LIGHTING);

	/* Nat�enie �wiat�a otoczenia (AMBIENT) */
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	/* Nat�enie �wiat�a rozpraszaj�cego (DIFFUSE) */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	/* �wiat�o nr 0 umieszczone nad scen� z prawej strony */
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	/* Nat�enie odb�ysk�w */
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	/* W��czenie �wiat�a nr 0 */
	glEnable(GL_LIGHT0);

	/* Ustawienie odb�ysku materia��w */
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	/* Skupienie i jasno�� plamy �wiat�a */
	glMateriali(GL_FRONT, GL_SHININESS, 64); //defaultowo ostatni param to 64

	/* �ledzenie kolor�w */
	/* Wsp�czynniki odbicia �wiat�a s� takie same jak kolor */
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

/* Zmiana rozmiar�w okna */
void ChangeSize(int w, int h) {
	/* Zabezpieczenie przed dzieleniem przez zero */
	if(h==0)	h=1;
	/* Ustawienie widoku */
	glViewport(0, 0, w, h);

	/* Ustawienie obszaru obcinania z uwzgl�dnieniem proporcji okna */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Rzutowanie perspektywiczne */
	gluPerspective(40, (float)w/h, 130, 470);  ///DOMYSLNIE gluPerspective(50, (float)w/h, 130, 470);

	/* Wyzerowanie macierzy widoku modelu dla funkcji rysuj�cej */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



/* Funkcja zegarowa: */
void ZegarFun(int val) {
	/* Odrysowanie sceny: */
	glutPostRedisplay();
	/* Ponowne wystartowanie zegara: */
	glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
}



#endif // SETUP_SCENE_HPP_INCLUDED
