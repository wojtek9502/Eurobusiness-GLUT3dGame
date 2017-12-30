#define GLUT_DISABLE_ATEXIT_HACK

#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include "Player.hpp"
#include "round.hpp"
#include "fields.hpp"
#include <string>
#include <vector>

#define ANIM_FPS 40	/* Docelowa liczba ramek animacji na sekund� */
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600

  vector<Field> fields;
  GLfloat angle;	/* K�t obrotu obiekt�w wok� �rodka sceny (animacja) */

  Player ptab[2]= { Player(1,"Player1",START_CASH,75.0, 3.0, 100.0,true),
                  Player(2,"Player2",300,75.0, 3.0, 105.0,false)
                };
/* Zmienne pomocnicze */
GLfloat lookA = 25;	/* K�t patrzenia w kierunku pionowym */

/* Parametry �wiat�a i materia��w */
GLfloat lightAmb[] = {0.1, 0.1, 0.1, 1.0};
GLfloat lightDif[] = {0.7, 0.7, 0.7, 1.0};
GLfloat lightPos[] = {0, 300, 0.0, 1.0};  ///defauktowo pierwszy param na 100 drugi na 200
GLfloat lightSpec[] = {1, 1, 1, 1};


void draw_objects_on_scene(Player ptab[])
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

	//GRACZE
    glPushMatrix();
		glTranslatef(ptab[0].position_x, ptab[0].position_y, ptab[0].position_z);
		glColor3f(1.0, 0.0, 0.0);
		glScalef(3.0, 3., 3); //gracz1
		glutSolidSphere(1,30,30);
	glPopMatrix();
	//glRotatef(100, 0, 1, 0);

	glPushMatrix();
		glTranslatef(ptab[1].position_x, ptab[1].position_y, ptab[1].position_z);
		glColor3f(1.0, 1.2, 0.0);
		glScalef(5.0, 5.0, 5.0); //gracz2
		glutSolidCube(1);
	glPopMatrix();
	//glRotatef(90, 0, 1, 0);

}


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




/* Funkcja zegarowa: */
void ZegarFun(int val) {

	/* Ponowne wystartowanie zegara: */
	glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
}




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
	draw_objects_on_scene(ptab);
///##################################################-----------FUNKCJA RYSUJACA OBIEKTY NA PLANSZY----------#############

	/* Zmiana bufora i opr�nienie kolejki renderowania */
	glutSwapBuffers();
}



/* Funkcja g��wna */
int main(int argc, char *argv[]) {

        ///wypelnij wektor pol
    fields = generate_fields(fields);

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
