#ifndef SETUP_SCENE_HPP_INCLUDED
#define SETUP_SCENE_HPP_INCLUDED

#include "render_scene.hpp"

#define ANIM_FPS 40	/* Docelowa liczba ramek animacji na sekundê */


/* Funkcja ustawia parametry renderowania i oœwietlenie... */
/* wywo³ywana na pocz¹tku programu */
void setupScene(void) {
	/* Bufor g³êbokoœci */
	glEnable(GL_DEPTH_TEST);
	/* W³¹czenie oœwietlenia */
	glEnable(GL_LIGHTING);

	/* Natê¿enie œwiat³a otoczenia (AMBIENT) */
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	/* Natê¿enie œwiat³a rozpraszaj¹cego (DIFFUSE) */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	/* Œwiat³o nr 0 umieszczone nad scen¹ z prawej strony */
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	/* Natê¿enie odb³ysków */
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
	/* W³¹czenie œwiat³a nr 0 */
	glEnable(GL_LIGHT0);

	/* Ustawienie odb³ysku materia³ów */
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	/* Skupienie i jasnoœæ plamy œwiat³a */
	glMateriali(GL_FRONT, GL_SHININESS, 64); //defaultowo ostatni param to 64

	/* Œledzenie kolorów */
	/* Wspó³czynniki odbicia œwiat³a s¹ takie same jak kolor */
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

/* Zmiana rozmiarów okna */
void ChangeSize(int w, int h) {
	/* Zabezpieczenie przed dzieleniem przez zero */
	if(h==0)	h=1;
	/* Ustawienie widoku */
	glViewport(0, 0, w, h);

	/* Ustawienie obszaru obcinania z uwzglêdnieniem proporcji okna */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* Rzutowanie perspektywiczne */
	gluPerspective(40, (float)w/h, 130, 470);  ///DOMYSLNIE gluPerspective(50, (float)w/h, 130, 470);

	/* Wyzerowanie macierzy widoku modelu dla funkcji rysuj¹cej */
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
