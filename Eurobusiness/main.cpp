#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "setup_scene.hpp"
#include "keyboard.h"
#include <string>
#include <vector>

#define ANIM_FPS 40	/* Docelowa liczba ramek animacji na sekund� */
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600


/* Funkcja g��wna */
int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	/* Przygotowanie okna */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutCreateWindow("Eurobusiness Game");

	/* Ustawienie funkcji rysuj�cej zawarto�� okna */
	glutDisplayFunc(RenderScene);
	/* Funkcja ustawiaj�ca parametry po zmianie rozmiaru okna */
	glutReshapeFunc(ChangeSize);
	/* Funkcja obs�uguj�ca klawiatur� */
	glutKeyboardFunc(KeyFunc);

	/* Ustawienia OpenGL */
	setupScene();
	/* Start zegara po raz pierwszy */
	glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
	/* Wej�cie do g��wnej p�tli programu */

    //vector<Player> players;
    //players = generate_players(players);


	glutMainLoop();
	return(0);
}
