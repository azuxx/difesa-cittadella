//cannone.h
#ifndef CANNONE_H_
#define CANNONE_H_

#include <vector>
//#include<iostream>
#include "granata.h"
#include "math.h"

using namespace std;

class Cannone{
	private:
		const int numeroProiettili;
		static const float larghezza=2;
		static const float lunghezza=10;
		float canX,canY,canZ;
		float canRotX,canRotY;
		float tempoDiCarica;
		float velRotazioneCannone;
		vector<Granata*> vProiettili;
		bool sparando;
		bool attendiCarica;
		int contatoreProiettili;
	public:
		Cannone(int,float,float,float);
		~Cannone();
		void inserisciProiettiliCannone(float,float,float);
		static float getLunghezza();
		static float getLarghezza();
		float getCanX() const;
		float getCanY() const;
		float getCanZ() const;
		float getCanRotX() const;
		float getCanRotY() const;
		float getTempoDiCarica()const;
		float getVelRotazioneCannone()const;
		void addCanRotX(float);
		void addCanRotY(float);
		void setCanRotX(float);
		void setCanRotY(float);
		bool isSparando() const;
		void setSparando(bool);
		Granata* getProiettile(int);
		Granata* getProiettileDaSparare();
		void togliProiettileSparato(int);
		int getNumeroProiettili()const;
		int getNumeroProiettiliIniziale()const;
		void setAttendiCarica(bool);
		bool isAttendiCarica() const;
		int getContatoreProiettili()const;
		void diminuisciContatoreProiettili();

};

#endif
