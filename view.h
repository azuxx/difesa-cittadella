//view.h
#ifndef VIEW_H_
#define VIEW_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "time.h"
#include "model.h"
#include <iostream>

using namespace std;

class View{
	private:
		static const int TEXTURE_COUNT=9;
		Model * model;
		GLuint texture[TEXTURE_COUNT];// array che conterrà gli indici interi che servono per il bind texture
		GLubyte texTerreno[256 * 256 * 3], skyBox[512 * 512 * 3],texPianoCittadella[256*192*3],texPalazzo[28*44*3],texHelp[500*375*3];// texture del terreno, del cielo
		GLint xMin, xMax, zMin, zMax;
		GLint viewport[4];//range della zona di terreno da elaborare, il viewport
		GLdouble tassoAspetto,angoloVisivo;
		void disegnaCannone();
		void disegnaMirino();
		void disegnaProiettile();
		void disegnaCielo();
		void disegnaTerreno();
		void disegnaGriglia();
		void disegnaCittadelle();
		void disegnaUfo();
		void disegnaBomba();
		void disegnaPannelloDiGioco();
		void visualizzaInformazioniTestuali();
		void disegnaStruttura(GLfloat*,GLfloat, GLfloat,GLfloat);
		void stampaStringaBitMap(GLint, GLint, char* ,int ,GLfloat,GLfloat ,GLfloat,int );//x e y sullo schermo, stringa, sua lunghezza, colori rgb, dimensioni font
		void mostraHelp();
		void visualizzaInformazioniFineGioco();
	public:
		View(Model*);
		void cambiaDimensione(int,int);
		void disegnaMondo();
		void caricaTexture();
		void impostaLuce();
		void nonCaricaTexture();
};

#endif
