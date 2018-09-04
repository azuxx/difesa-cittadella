//ufo.h
#ifndef UFO_H_
#define UFO_H_

#include<vector>
//#include<iostream>
#include "granata.h"
#include "obiettivo.h"

using namespace std;

class Ufo{
	private:
		const int numeroBombe;
		static const float larghezzaUfo=8;
		static const float altezzaUfo=3;
		float posx;
		float posy;
		float posz;
		float velocitaX;
		float velocitaY;
		float velocitaZ;
		float direzione;//espressa in angolo sessaggesimale
		int vita;
		bool attacco;
		bool sgancioBomba;
		float quotaAttacco;
		bool bombeEsaurite;
		vector<Granata*> vBombe;
	public:
		Ufo(int,float,float,float,float,float,float,float);
		~Ufo();

		static float getLarghezzaUfo();
		static float getAltezzaUfo();
		float getPosizioneX()const;
		float getPosizioneY()const;
		float getPosizioneZ()const;
		float getVelocitaX()const;
		float getVelocitaY()const;
		float getVelocitaZ()const;

		float getDirezione()const;
		void setDirezione(float);
		void setVelocitaX(float);
		void setVelocitaY(float);
		void setVelocitaZ(float);
		void aggiornaPosizione(float,float,float);

		Granata* getBomba(int);
		Granata* getBombaDaSparare();
		Granata* getBombaSparata();
		void togliBombaSganciata(int);
		int getNumeroBombe()const;
		int getNumeroBombeIniziali()const;

		void setAttacco(bool);
		bool isAttacco()const;
		float getQuotaAttacco()const;
		bool isSgancioBomba()const;
		void setSgancioBomba(bool);

		void setBombeEsaurite(bool);
		bool isBombeEsaurite()const;

		void danneggia();
		int getVita()const;
};

#endif
