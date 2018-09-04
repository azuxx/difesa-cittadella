//cittadella.h
#ifndef CITTADELLA_H_
#define CITTADELLA_H_

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "math.h"

using namespace std;


class Cittadella{
	private:
		static const int numeroPalazzi=10;
		int vitaIniziale;
		float centroCittadella[3];
		int larghezza,lunghezza;
		float dimensionePalazzi[numeroPalazzi][2];
		float posizionePalazzi[numeroPalazzi][3];
		void cambiaSegno(int,int &, int &);
		bool controllaCollisionePalazzi(int,float,float,float);
	public:
		Cittadella(float,float,int,int);
		int getNumeroPalazzi()const;
		float* getPosizionePalazzo(int);
		float getRaggioPalazzo(int) const;
		float getAltezzaPalazzo(int)const ;
		void danneggiaPalazzo(int);
		void generaCittadella();
		float* getCentroCittadella();
		int getLarghezza()const;
		int getLunghezza()const;
		int getVitaCittadella();
		int getVitaIniziale()const;
		void crolla();
};

#endif
