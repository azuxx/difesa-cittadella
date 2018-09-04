//model.h
#ifndef MODEL_H_
#define MODEL_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "math.h"
#include "time.h"
#include "cittadella.h"
#include "ufo.h"
#include "terreno.h"
#include "cannone.h"

using namespace std;

class Model{
	private:
		static const float RADIANTE=180.0f/M_PI;
		const int maxUfo;
		const int maxCittadelle;
		const int maxBombe;
		const int maxProiettili;
		float ossX,ossY,ossZ;
		float distanza;
		long tempo;
		long tempoPrec;
		float tempoInizioCambioAvanzam,tempoInizioCarica,tempoInizioAttacco;
		float dt;
		float prossimoCambioVerso,prossimoAttacco;
		float velRotazioneOsservatore;
		float ossRotX,ossRotY;
		bool vettTasti[255];
		bool RaggiungimentoObiettiviAttacco;
		bool textureAttive;
		bool terrenoMinimale;
		bool helpAttivo;
		bool fine;
		bool inizio;
		int tipoFine;
		int numeroUfoInObiettivo;//serve per determinare se tutti gli ufo possono procedere ad un altro attacco (perchè gli ufo attaccano tutti assieme)
		int numeroUfoBombeEsaurite;
		vector<Cittadella*> vcitt;
		vector<Ufo*> vu;
		Terreno*t;
		Cannone*c;
		void AggiornaVectorUfo();
		void scegliSegno(int &, int &);
		void attaccoCittadella(int);
		void muoviUfo();
		void muoviBomba();
		void muoviProiettile();
		void muoviCannone();
		void calcolaCarica();
		void controllaCollisioneBombaPalazzo();
		void controllaCollisioneProiettileMondo();
		void ottieniIndiciPalazzoSottoObiettivoUfo(int,float,float);
		bool isContattoBombaTettoPalazzo(float,float, float,float,float,float,float);
		bool isContattoProiettileBomba(float,float, float,float,float,float,float,float);
		bool isContattoProiettileUfo(float,float, float,float,float,float,float,float,float);
		bool isContattoProiettileCittadella(float,float, float ,float,float, float,float,float);
	public:
		Model(int,int,int,int,float,float,float,float);
		~Model();
		void creaTerreno(float,int);//fattore scala, dimensione (lato) dato è un quadrato
		void creaCittadella(float,float,int,int);//numero palazzi, posizione in x, posizione in z
		void creaUfo(int,float,float,float,float,float,float,float);//posizione in x, posizione in z,velocità in x, velocità in z
		void creaCannone(int,float,float,float);
		void movimento();
		void setVettTasti(int,bool);
		Terreno* getTerreno();
		Cittadella* getCittadella(int i);
		Ufo* getUfo(int i);
		Cannone* getCannone();
		int getNumeroUfo()const;
		int getNumeroCittadelle()const;
		float getOssX()const;
		float getOssY()const;
		float getOssZ()const;
		float getOssRotX()const;
		float getOssRotY()const;
		float getDistanzaMassimaVisuale()const;
		bool isTextureAttive()const;
		void setTextureAttive(bool);
		bool isTerrenoMinimale()const;
		void setTerrenoMinimale(bool);
		bool isHelpAttivo()const;
		void setHelpAttivo(bool);
		float getTempoCorrenteDiCarica()const;
		bool isFine()const;
		bool isInizio()const;
		void avviaGioco();
		int getTipoFine()const;
};

#endif
