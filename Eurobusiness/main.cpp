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
#include "Targa.h"

#define ANIM_FPS 40	/* Docelowa liczba ramek animacji na sekundê */
#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600

/* Dane globalne (animacja) */
GLuint tex[2];	/* tekstura */

  GLfloat angle;	/* K¹t obrotu obiektów wokó³ œrodka sceny (animacja) */

//@TODO
//Dorobić pola na planszy
  Field pfields[] = { Field("Start",86,3,83, 86,3,90, 0,-1),
                      Field("Saloniki",64,3,84, 64,3,91, 0,-1),
                      Field("SzansaN1",48,3,84, 48,3,91, 0,-1),
                      Field("Ateny",32,3,84, 32,3,91, 0,-1),
                      Field("Parking",16,3,84, 16,3,91, 0,-1),
                      Field("Koleje Pld.",0,3,84,  0,3,91, 0,-1),
                      Field("Neapol",-16,3,84, -16,3,91, 0,-1),
                      Field("SzansaR1",-32,3,84, -32,3,91, 0,-1),
                      Field("Mediolan",-48,3,84, -48,3,91, 0,-1),
                      Field("Rzym",-64,3,84, -64,3,91, 0,-1),
                      Field("Wiezienie",-84,3,80, -84,3,87, 0,-1),


                      Field("Barcelona",-86,3,60, -86,3,67, 0,-1),
                      Field("Elektrownie",-86,3,44, -86,3,51, 0,-1),
                      Field("Sewilla",-86,3,28, -86,3,35, 0,-1),
                      Field("Madryt",-86,3,12, -86,3,19, 0,-1),
                      Field("Koleje Zach.",-86,3,-4, -86,3,3, 0,-1),
                      Field("Liverpool",-86,3,-20, -86,3,-13, 0,-1),
                      Field("SzansaN2",-86,3,-36, -86,3,-29, 0,-1),
                      Field("Glasgow",-86,3,-52, -86,3,-45, 0,-1),
                      Field("Londyn",-86,3,-68, -86,3,-61, 0,-1),
                      Field("Parking Darmowy",-86,3,-92, -86,3,-85, 0,-1),

                      Field("Rotterdam",-64,3,-92, -64,3,-85, 0,-1),
                      Field("SzansaR2",-48,3,-92, -48,3,-85, 0,-1),
                      Field("Bruksela",-32,3,-92, -32,3,-85, 0,-1),
                      Field("Amsterdam",-16,3,-92, -16,3,-85, 0,-1),
                      Field("Koleje Pln",0,3,-92,   0,3,-85, 0,-1),
                      Field("Malmo",16,3,-92,  16,3,-85, 0,-1),
                      Field("Goteborg",32,3,-92,  32,3,-85, 0,-1),
                      Field("Wodociagi",48,3,-92,  48,3,-85, 0,-1),
                      Field("Sztokholm",64,3,-92,  64,3,-85, 0,-1),
                      Field("Do Wiezienia",86,3,-90,  86,3,-83, 0,-1),

                      Field("Frankfurt",86,3,-68, 86,3,-61, 0,-1),
                      Field("Kolonie",86,3,-52, 86,3,-45, 0,-1),
                      Field("SzansaN3",86,3,-36, 86,3,-29, 0,-1),
                      Field("Bonn",86,3,-20, 86,3,-13, 0,-1),
                      Field("Koleje Wsch.",86,3,-4, 86,3,3, 0,-1),
                      Field("SzansaR3",86,3,12, 86,3,19, 0,-1),
                      Field("Insbruck",86,3,28, 86,3,35, 0,-1),
                      Field("Podatek od wzbogacenia",86,3,44, 86,3,51, 0,-1),
                      Field("Wieden",86,3,60, 86,3,67, 0,-1)
                      };

    Player ptab[2]= { Player(1,"Player1",START_CASH, pfields[0].p1_position_x, 3.0, pfields[0].p1_position_z,true),
                  Player(2,"Player2",START_CASH, pfields[0].p2_position_x,3.0,pfields[0].p2_position_z ,false)
                };


/* Zmienne pomocnicze */
GLfloat lookA = 25;	/* K¹t patrzenia w kierunku pionowym */

/* Parametry œwiat³a i materia³ów */
GLfloat lightAmb[] = {0.6, 0.6, 0.6, 1.0}; //natezenie swiatla
GLfloat lightDif[] = {0.7, 0.7, 0.7, 1.0};
GLfloat lightPos[] = {0, 300, 0.0, 1.0};  ///defaultowo pierwszy param na 100 drugi na 200
GLfloat lightSpec[] = {1, 1, 1, 1};


/* Funkcja ustawia parametry renderowania i oœwietlenie... */
/* wywo³ywana na pocz¹tku programu */
void setupScene(void) {
	/* Bufor g³êbokoœci */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);    /* Włączenie teksturowania */

   /* Wygenerowanie trzech tzw. "obiektów" dla tekstur */
	glGenTextures(2, tex);

    /* Aktywacja każdej tekstury po kolei i ładowanie z plików TGA */
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	LoadTGAMipmap("C:\\Users\\Wojtek\\Documents\\GitHub\\Eurobusiness-GLUT3dGame\\Eurobusiness\\scene_tex.tga");   //PATH TO TEXTURE def: scene_tex.tga
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	LoadTGAMipmap("C:\\Users\\Wojtek\\Documents\\GitHub\\Eurobusiness-GLUT3dGame\\Eurobusiness\\h_tex.tga");   //PATH TO TEXTURE  def: h_tex.tga

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

	glClearColor(1.0, 0.3, 0.3, 1.0);
}

void draw_objects_on_scene(Player ptab[])
{
     //potrzebne do obrotu obiektow
    if(angle >= 360)	angle -= 360;
    glRotatef(angle, 0, -1, 0);

    ///PLANSZA
    //glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
        glColor4f(1.0, 1.0, 1.0, 1.0);
		// Ściana bliższa
		//glTexCoord2f(0, 0);
		glVertex3f(-100,  1,  100);
		//glTexCoord2f(1, 0);
		glVertex3f( 100,  1,  100);
		//glTexCoord2f(1, 1);
		glVertex3f( 100, -1,  100);
		//glTexCoord2f(0, 1);
		glVertex3f(-100, -1,  100);

		// Ściana dalsza
		glTexCoord2f(0, 0);
		//glVertex3f(-100,  1, -100);
		glTexCoord2f(1, 0);
		//glVertex3f( 100,  1, -100);
		glTexCoord2f(1, 1);
		//glVertex3f( 100, -1, -100);
		glTexCoord2f(0, 1);glVertex3f(-100, -1, -100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
		// Ściana górna
		glTexCoord2f(0, 0);glVertex3f(-100,  1, -100);
		glTexCoord2f(0, 1);glVertex3f( 100,  1, -100);
		glTexCoord2f(1, 1);glVertex3f( 100,  1,  100);
		glTexCoord2f(1, 0);glVertex3f(-100,  1,  100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBegin(GL_QUADS);
        // Ściana dolna
		glTexCoord2f(0, 0);
		glVertex3f(-100, -1, -100);
		glTexCoord2f(1, 0);
		glVertex3f( 100, -1, -100);
        glTexCoord2f(1, 1);
		glVertex3f( 100, -1,  100);
		glTexCoord2f(0, 1);
		glVertex3f(-100, -1,  100);
    glEnd();

	//glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
		// Ściana lewa
		//glTexCoord2f(0, 0);
		glVertex3f(-100,  1,  100);
		//glTexCoord2f(1, 0);
		glVertex3f(-100,  1, -100);
		//glTexCoord2f(1, 1);
		glVertex3f(-100, -1, -100);
		//glTexCoord2f(0, 1);
		glVertex3f(-100, -1,  100);

		// Ściana prawa
		//glTexCoord2f(0, 0);
		glVertex3f( 100,  1,  100);
		//glTexCoord2f(1, 0);
		glVertex3f( 100,  1, -100);
		//glTexCoord2f(1, 1);
		glVertex3f( 100, -1, -100);
		//glTexCoord2f(0, 1);
		glVertex3f( 100, -1,  100);
	glEnd();

/*
    // STARY OBIEKT PLANSZY
    glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor3f(0, 1, 0);
		glScalef(200.0, 1, 200); //rozmiary planszy
		glutSolidCube(1);
	glPopMatrix();
	glRotatef(10, 0, 1, 0);
*/

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

/* Funkcja rysuj¹ca */
void RenderScene(void) {
	/* Wyczyszczenie t³a czarnym kolorem */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Wstêpne ustawienie sceny */
	glLoadIdentity();
	/* Odsuniêcie œrodka sceny od obserwatora */
	glTranslatef(0, 0, -300);
	/* Ustawienie k¹ta obserwacji */
	glRotatef(lookA, 1, 0, 0);

	/* Pozycjonowanie œwiat³a */
	/* Œwiat³o jest nieruchome wzglêdem obiektów - one przesuwaj¹ siê pod œwiat³em */
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	/* Animacja */


///##################################################-----------FUNKCJA RYSUJACA OBIEKTY NA PLANSZY----------#############
	draw_objects_on_scene(ptab);
///##################################################-----------FUNKCJA RYSUJACA OBIEKTY NA PLANSZY----------#############

	/* Zmiana bufora i opró¿nienie kolejki renderowania */
	glutSwapBuffers();
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
        angle-=4;
        camera_move=true;
        glutPostRedisplay();
    }
   // cout << "rotacja obiektow w stopniach = " << angle << endl;
    /* Odrysowanie sceny: */
    if(key==13)
    {
       camera_move=false;
       glutPostRedisplay();
       next_round(ptab,pfields);
    }
    if(key == 0x1B)		exit(0);
}




/* Funkcja zegarowa: */
void ZegarFun(int val) {

	/* Ponowne wystartowanie zegara: */
	glutTimerFunc(1000/ANIM_FPS, ZegarFun, 0);
}








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
