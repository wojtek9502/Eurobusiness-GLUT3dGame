#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "setup_scene.hpp"
#include "keyboard.h"
#include <string>
#include <vector>

#define ANIM_FPS 40	/* Docelowa liczba ramek animacji na sekundê */
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600


/* Funkcja g³ówna */
int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	/* Przygotowanie okna */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutCreateWindow("Eurobusiness Game");

	/* Ustawienie funkcji rysuj¹cej zawartoœæ okna */
	glutDisplayFunc(RenderScene);
	/* Funkcja ustawiaj¹ca parametry po zmianie rozmiaru okna */
	glutReshapeFunc(ChangeSize);
	/* Funkcja obs³uguj¹ca klawiaturê */
	glutKeyboardFunc(KeyFunc);

	/* Ustawienia OpenGL */
	setupScene();
	/* Start zegara po raz pierwszy */
	glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
	/* Wejœcie do g³ównej pêtli programu */

    //vector<Player> players;
    //players = generate_players(players);


	glutMainLoop();
	return(0);
}
