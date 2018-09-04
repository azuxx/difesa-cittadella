//granata.h
#ifndef GRANATA_H_
#define GRANATA_H_

#include "math.h"
#include "obiettivo.h"


class Granata{
	protected:
		static const float RADIANTE=180.0f/M_PI;
		float posx;
		float posy;
		float posz;
		bool sparato;
		bool collisione;
	public:
		Granata(float,float,float);
		virtual ~Granata();
		float getPosX()const;
		float getPosY()const;
		float getPosZ()const;
		bool isSparata()const;
		void setPosX(float);
		void setPosY(float);
		void setPosZ(float);
		void setSparato(bool);
		bool isCollisione()const;
		void setCollisione(bool);
};

class Bomba : public Granata{
	private:
		//il salvataggio delle informazioni nei due campi dati seguenti sono fatte nelle stesse posizioni così da garantire che a quell'obiettivo corrisponde eventual un palazzo
		Obiettivo* obiettivo;
		int* indiciPalazzoObiettivo;//-1 -1 se per quell'obiettivo non cè alcun palazzo
		static const float raggioBomba=2;
	public:
		Bomba(float,float,float);
		virtual ~Bomba();
		void addObiettivo(float,float,float);
		Obiettivo* getObiettivo();
		void addIndiciPalazzoObiettivo(int,int);
		bool isBombaSopraPalazzoObiettivo();
		int getIndiceCittadellaPalazzoObiettivo();
		int getIndicePalazzoObiettivo();
		static float getRaggioBomba();
};

class Proiettile : public Granata{
	private:
		float dirX,dirY,dirZ;
		float RotOssYSuSparo;
		float posXRotOssY;
		float posZRotOssY;
		static const float raggioProiettile=1;
	public:
		Proiettile(float,float,float);
		virtual ~Proiettile(){};
		void aggiornaDirezioni(float,float);
		float getDirX() const;
		float getDirY() const;
		float getDirZ() const;
		float getRotOssYSuSparo()const;
		float getPosZRotOssY()const;
		float getPosXRotOssY()const;
		void setPosZRotOssY(float);
		void setPosXRotOssY(float);
		void setRotYSuSparo(float);
		static float getRaggioProiettile();
};

#endif
