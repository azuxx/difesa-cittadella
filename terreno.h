//terreno.h
#ifndef TERRENO_H_
#define TERRENO_H_

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "math3d.h"

class Terreno{
	private:
		static const int DIM=512;
		float fattoreScala;
		int dimDaModellare;
		float mappaTerreno[DIM][DIM];//le righe rappresentano l'asse z positivo, le colonne rappr. l'asse x positivo
		M3DVector3f normali[DIM][DIM];// le normali per i vertici del terreno (per gli indici stesso ragionamento di mappaTerreno)
		void pianaTerrenoNonModellato();
	public:
		Terreno(float,int);
		~Terreno(){};
		float getAltezzaTerreno(int ,int );
		const float* getNormali(int, int);
		void normalizzaTerreno();
		void modellaTerreno();
		int getDimensione()const;
		float getFattoreScala()const;
		void creaCollina(float,float,float);
		void spianaTerrenoEdificabile(float,float,float,float);
};

#endif
