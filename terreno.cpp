#include "terreno.h"

Terreno::Terreno(float fatts,int dimDaMod):fattoreScala(fatts){
	if(dimDaMod>DIM-24){
		dimDaModellare=DIM-24;
	}
	else
		dimDaModellare=dimDaMod;
}

float Terreno::getAltezzaTerreno(int i,int j){
	return mappaTerreno[i][j];
}

const float* Terreno::getNormali(int i, int j){
	return normali[i][j];
}


void Terreno::normalizzaTerreno(){
	M3DVector3f punti[3];
	M3DVector3f normaliTriangoli[6];
	int k, divisore;

	/*ogni vertice non marginale ha 6 triangoli in cui è incluso attorno a lui, la sua normale è la media delle 6 normali
	dei singoli triangoli, in questo modo c'è l'illusione che il terreno sia curvo e non composto da molti triangoli*/
	for(int i = 0; i < DIM; i++){
		for(int j = 0; j < DIM; j++){
			if(j<=DIM-2 && i>=1){ // triangolo del primo quadrante inferiore
				punti[0][0] = j;
				punti[0][2] = i;
				punti[0][1] = mappaTerreno[i][j]/fattoreScala;
				punti[1][0] = j+1;
				punti[1][2] = i-1;
				punti[1][1] = mappaTerreno[i-1][j+1]/fattoreScala;
				punti[2][0] = j+1;
				punti[2][2] = i;
				punti[2][1] = mappaTerreno[i][j+1]/fattoreScala;
				m3dFindNormal(normaliTriangoli[0], punti[0], punti[2], punti[1]);//risultato, punto 1, punto 2, punto 3 passati nel senso orario
				m3dNormalizeVector(normaliTriangoli[0]);
			}
			else{//sono fuori il quadrante, metto a zero le tre normali.
				normaliTriangoli[0][0] = 0;
				normaliTriangoli[0][1] = 0;
				normaliTriangoli[0][2] = 0;
			}
			if(j<=DIM-2 && i>=1){ // triangolo del primo quadrante superiore
				punti[0][0] = j;
				punti[0][2] = i;
				punti[0][1] = mappaTerreno[i][j]/fattoreScala;
				punti[1][0] = j;
				punti[1][2] = i-1;
				punti[1][1] = mappaTerreno[i-1][j]/fattoreScala;
				punti[2][0] = j+1;
				punti[2][2] = i-1;
				punti[2][1] = mappaTerreno[i-1][j+1]/fattoreScala;
				m3dFindNormal(normaliTriangoli[1], punti[0], punti[2], punti[1]);
				m3dNormalizeVector(normaliTriangoli[1]);
			}
			else{
				normaliTriangoli[1][0] = 0;
				normaliTriangoli[1][1] = 0;
				normaliTriangoli[1][2] = 0;
			}
			if(j>=1 && i>=1){ // triangolo del secondo quadrante
				punti[0][0] = j;
				punti[0][2] = i;
				punti[0][1] = mappaTerreno[i][j]/fattoreScala;
				punti[1][0] = j-1;
				punti[1][2] = i;
				punti[1][1] = mappaTerreno[i][j-1]/fattoreScala;
				punti[2][0] = j;
				punti[2][2] = i-1;
				punti[2][1] = mappaTerreno[i-1][j]/fattoreScala;
				m3dFindNormal(normaliTriangoli[2], punti[0], punti[2], punti[1]);
				m3dNormalizeVector(normaliTriangoli[2]);
			}
			else{
				normaliTriangoli[2][0] = 0;
				normaliTriangoli[2][1] = 0;
				normaliTriangoli[2][2] = 0;
			}
			if(j>=1 && i<=DIM-2){ // triangolo 3° quadrante superiore
				punti[0][0] = j;
				punti[0][2] = i;
				punti[0][1] = mappaTerreno[i][j]/fattoreScala;
				punti[1][0] = j-1;
				punti[1][2] = i+1;
				punti[1][1] = mappaTerreno[i+1][j-1]/fattoreScala;
				punti[2][0] = j-1;
				punti[2][2] = i;
				punti[2][1] = mappaTerreno[i][j-1]/fattoreScala;
				m3dFindNormal(normaliTriangoli[3], punti[0], punti[2], punti[1]);
				m3dNormalizeVector(normaliTriangoli[3]);
			}
			else{
				normaliTriangoli[3][0] = 0;
				normaliTriangoli[3][1] = 0;
				normaliTriangoli[3][2] = 0;
			}
			if(j>=1 && i<=DIM-2){// triangolo 3° quadrante inferiore
				punti[0][0] = j;
				punti[0][2] = i;
				punti[0][1] = mappaTerreno[i][j]/fattoreScala;
				punti[1][0] = j;
				punti[1][2] = i+1;
				punti[1][1] = mappaTerreno[i+1][j]/fattoreScala;
				punti[2][0] = j-1;
				punti[2][2] = i+1;
				punti[2][1] = mappaTerreno[i+1][j-1]/fattoreScala;
				m3dFindNormal(normaliTriangoli[4], punti[0], punti[2], punti[1]);
				m3dNormalizeVector(normaliTriangoli[4]);
			}
			else{
				normaliTriangoli[4][0] = 0;
				normaliTriangoli[4][1] = 0;
				normaliTriangoli[4][2] = 0;
			}
			if(j<=DIM-2 && i<=DIM-2){ // triangolo 4° quadrante
				punti[0][0] = j;
				punti[0][2] = i;
				punti[0][1] = mappaTerreno[i][j]/fattoreScala;
				punti[1][0] = j+1;
				punti[1][2] = i;
				punti[1][1] = mappaTerreno[i][j+1]/fattoreScala;
				punti[2][0] = j;
				punti[2][2] = i+1;
				punti[2][1] = mappaTerreno[i+1][j]/fattoreScala;
				m3dFindNormal(normaliTriangoli[5], punti[0], punti[2], punti[1]);
				m3dNormalizeVector(normaliTriangoli[5]);
			}
			else{
				normaliTriangoli[5][0] = 0;
				normaliTriangoli[5][1] = 0;
				normaliTriangoli[5][2] = 0;
			}
			// ottengo la normale effettiva del vertice facendo la media dei 6 triangoli adiacenti che sono stati normalizzati
			divisore = 0;
			normali[i][j][0] = 0;//i si riferisce ai valori dell'asse z, j a quelli dell'asse x.
			normali[i][j][1] = 0;
			normali[i][j][2] = 0;
			for(k=0; k<6; k++){
				if(!(normaliTriangoli[k][0] == 0 && normaliTriangoli[k][1] == 0 && normaliTriangoli[k][2] == 0)){
					normali[i][j][0] += normaliTriangoli[k][0];
					normali[i][j][1] += normaliTriangoli[k][1];
					normali[i][j][2] += normaliTriangoli[k][2];
					divisore++;
				}
			}
			//ortonormalizzazione
			normali[i][j][0] /= divisore;
			normali[i][j][1] /= divisore;
			normali[i][j][2] /= divisore;
		}
	}
}


void Terreno::modellaTerreno(){//immagino un terreno non tanto sfasato, ma appena rugoso/ondulato
	float pendenza=0,precedenteX, precedenteZ, mediaAdiacente, altezzaVertice;
	int tipoZona;
	for(int i=0;i<dimDaModellare;i++){
		for(int j=0;j<dimDaModellare;j++){
			if(j%100==0){
				pendenza=rand()%2+1;
			}
			tipoZona=rand()%3;
			if(i>0)
				precedenteZ = mappaTerreno[i-1][j];
			else
				precedenteZ = 0;
			if(j>0)
				precedenteX = mappaTerreno[i][j-1];
			else
				precedenteX = 0;
			mediaAdiacente = (precedenteX + precedenteZ) / 2;
			switch(tipoZona){
				case 0 :
					altezzaVertice = mediaAdiacente - pendenza;
					if(altezzaVertice < 0)
						altezzaVertice = 0;
					mappaTerreno[i][j] = altezzaVertice;
				break;
				case 1 :
					mappaTerreno[i][j] = mediaAdiacente;
				break;
				case 2 :
					altezzaVertice = mediaAdiacente + pendenza;
					if(altezzaVertice > 255)
						altezzaVertice = 255;
					mappaTerreno[i][j] = altezzaVertice;
				break;
			}
		}
	}
	pianaTerrenoNonModellato();
}

void Terreno::spianaTerrenoEdificabile(float centrox,float centroz,float lunghezza,float larghezza){
	for(int i=centroz-larghezza/2;i<centroz+larghezza/2;i++){
		for (int j = centrox-lunghezza/2; j < centrox+lunghezza/2; ++j) {
			mappaTerreno[i][j] = 0;
		}
	}
}

void Terreno::pianaTerrenoNonModellato(){
		for(int i=dimDaModellare; i<DIM; i++)
		{
			for(int j=0; j<DIM; j++)
			{
				mappaTerreno[i][j] = 0;
			}
		}
		for(int i=0; i<DIM; i++)
		{
			for(int j=dimDaModellare; j<DIM; j++)
			{
				mappaTerreno[i][j] = 0;
			}
		}

		for(int j = 0; j < DIM; j++)
			mappaTerreno[0][j] = 0;
		for(int j = 0; j < DIM; j++)
			mappaTerreno[DIM-1][j] = 0;
		for(int i = 0; i < DIM; i++)
			mappaTerreno[i][0] = 0;
		for(int i = 0; i < DIM; i++)
			mappaTerreno[i][DIM-1] = 0;
}

void Terreno::creaCollina(float altezza,float xcentro, float zcentro){//metodo che mi permette di creare una collina uniforme e già dalla forma arrodondata
	float distanza,altezzaIxIz;
	if(xcentro-altezza>=0 && zcentro-altezza>=0){
		for(int iz=zcentro-altezza;iz<=zcentro+altezza;iz++){
				for(int ix=xcentro-altezza;ix<=xcentro+altezza;ix++){
					distanza=(float)(sqrt((ix-xcentro)*(ix-xcentro)+(iz-zcentro)*(iz-zcentro)));
					altezzaIxIz=altezza-((1/altezza)*(distanza*distanza));//mi baso sulla funzione y=altezza-(1/altezza)*x^2 che è una parabola, rispetto al classico calcolo y=altezza-x che porterebbe invece ad una collina a forma di piramide.
					if(altezzaIxIz<0){//dà l'effetto base a cerchio
						altezzaIxIz=0;
					}
					//moltiplico per fattore scala che divido per un costante vicina ad 1  per evitare l'eccessivo smussamento della normalizzazione, che invece sarà necessaria per il resto del terreno modellato
					mappaTerreno[iz][ix]=altezzaIxIz*(fattoreScala/1.2);
				}
		}
	}
}


int Terreno::getDimensione()const{
	return DIM;
}

float Terreno::getFattoreScala()const{
	return fattoreScala;
}
