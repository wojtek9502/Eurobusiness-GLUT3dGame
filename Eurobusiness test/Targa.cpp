/*
 *	Uniwersalne procedury �aduj�ce pliki typu TARGA
 *	z uwzgl�dnieniem kana�u ALFA.
 *	Na podstawie tutorial'u NEHE nr 25.
 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>

#include "Targa.h"


///////////////////////////////////////////////////////////////////////////////
// Procedura �aduje plik o podanej nazwie
// wype�nia podan� struktur� TARGAINFO
// oraz zwraca adres bufora z pikselami (je�li nie by�o b��du)
// Je�li by� b��d - zwraca NULL
GLubyte *LoadTGAImage(char *filename, TARGAINFO *info)
{
    puts(filename);
	GLubyte	TGAHeader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Nag��wek TGA bez kompresji
	GLubyte	TGACompare[12];			// Tu si� za�aduje dane z pliku
	GLubyte	Header[6];			// Pierwsze potrzebne 6 bajt�w z pliku
	GLubyte *Bits = NULL;	// Wska�nik na bufor z danymi pikseli

	FILE *plik = fopen(filename, "rb");	// Pr�ba otwarcia do odczytu
	if(plik)
	{
		fread(TGACompare, 1, sizeof(TGACompare), plik);	// Odczytanie nag��wka pliku
		if(memcmp(TGAHeader, TGACompare, sizeof(TGAHeader)) == 0)	// Nag��wek identyczny?
		{
			fread(Header, 1, sizeof(Header), plik);	// Odczyt u�ytecznych danych

			// Wy�uskanie informacji o rozmiarach
			info->width  = Header[1] * 256 + Header[0];
			info->height = Header[3] * 256 + Header[2];
			info->bpp = Header[4];

			// Sprawdzenie czy rozmiary > 0 oraz czy bitmapa 24 lub 32-bitowa
			if(info->width>0 && info->height>0 && (info->bpp==24 || info->bpp==32))
			{
				long ImageSize = info->height * info->width * info->bpp / 8;	// Obliczenie ilo�ci danych
				Bits = (GLubyte*)malloc(ImageSize);	// Alokacja pami�ci na dane

				if(Bits)
				{
					fread(Bits, 1, ImageSize, plik);	// Odczyt w�a�ciwych danych pikseli z pliku

					// Konwersja BGR -> RGB
					int i;
					GLubyte tmp;	// Miejsce przechowania jednej warto�ci koloru

					for(i=0;i < ImageSize;i += info->bpp / 8)	// Wszystkie warto�ci RGB lub RGBA
					{
						tmp = Bits[i];
						Bits[i] = Bits[i+2];
						Bits[i+2] = tmp;
					}
				}
			}
    	}

		fclose(plik);
	}
	else
        std::cout << "Brak pliku image" << std::endl;

	return(Bits);
}

///////////////////////////////////////////////////////////////////////////////
// Procedury na podstawie przekazanych danych �aduj�
// i tworz� tekstur� lub tekstur� z Mip-Map'ami
bool LoadTGATexture(char *filename)
{
	TARGAINFO info;	// Dane o bitmapie
	GLubyte *bits;	// Dane o pikselach

	// �adowanie pliku
	bits = LoadTGAImage(filename, &info);	// Pr�ba wczytania tekstury
	if(bits == NULL)	return(FALSE);	// ERROR

	// Ustawienie parametr�w tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if(info.bpp == 24)	// Bitmapa z danymi RGB
		glTexImage2D(GL_TEXTURE_2D, 0, 3, info.width, info.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
	else	// Bitmapa z danymi RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, 4, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);

	free(bits);
	return(TRUE);
}

bool LoadTGAMipmap(char *filename)
{
	TARGAINFO info;	// Dane o bitmapie
	GLubyte *bits;	// Dane o pikselach

	// �adowanie pliku
	bits = LoadTGAImage(filename, &info);	// Pr�ba wczytania tekstury
	if(bits == NULL)	return(FALSE);	// ERROR

	// Ustawienie parametr�w tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if(info.bpp == 24)	// Bitmapa z danymi RGB
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, info.width, info.height, GL_RGB, GL_UNSIGNED_BYTE, bits);
	else	// Bitmapa z danymi RGBA
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, info.width, info.height, GL_RGBA, GL_UNSIGNED_BYTE, bits);

	free(bits);
	return(TRUE);
}
