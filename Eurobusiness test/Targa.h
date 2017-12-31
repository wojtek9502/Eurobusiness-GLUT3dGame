#ifndef TARGA_H_INCLUDED
#define TARGA_H_INCLUDED


typedef struct {
	GLuint bpp;		// ilo�� bit�w na piksel
	GLuint width;	// rozmiary w pikselach
	GLuint height;
} TARGAINFO;

// Funkcje
GLubyte *LoadTGAImage(char *filename, TARGAINFO *info);
bool LoadTGATexture(char *filename);
bool LoadTGAMipmap(char *filename);



#endif // TARGA_H_INCLUDED
