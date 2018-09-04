#include "cittadella.h"

void Cittadella::generaCittadella(){
	for(int i=0;i<numeroPalazzi;i++){//scelta random per la larghezza e l'altezza dei palazzi
		dimensionePalazzi[i][0]=rand()%8+6;//larghezza
		dimensionePalazzi[i][1]=rand()%15+8;//altezza
	}
	int i=0,segnoX=1,segnoZ=1,k=0;
	int contatoreDiControllo=0;
	while(i<numeroPalazzi){//creo la cittadella in modo random facendo il controllo che ogni palazzo che sarà disegnato non collidi con i palazzi finora creati
		cambiaSegno(k,segnoX,segnoZ);//cambio il segno ogni volta per distribuire il posizionamento del palazzo da creare in alto-sx o alto-dx o basso-sx o basso-dx rispetto al centro della cittadella
		posizionePalazzi[i][0]=centroCittadella[0]+segnoX*(rand()%(larghezza/2));
		posizionePalazzi[i][1]=centroCittadella[1];
		posizionePalazzi[i][2]=centroCittadella[2]+segnoZ*(rand()%(lunghezza/2));
		if(controllaCollisionePalazzi(i,posizionePalazzi[i][0],posizionePalazzi[i][2],dimensionePalazzi[i][0])==false){
			i++;
			contatoreDiControllo=0;
			if(k==3){//per il cambio del segno in X e Z ad ogni iterazione (+ o -)
				k=0;
			}
			else{
				k++;
			}
		}
		contatoreDiControllo++;
		if(contatoreDiControllo==40){//dopo 40 tentativi di generazione del palazzo, si passa avanti al prossimo palazzo
			posizionePalazzi[i][0]=-1;
			posizionePalazzi[i][1]=-1;
			posizionePalazzi[i][2]=-1;
			dimensionePalazzi[i][0]=0;
			dimensionePalazzi[i][1]=0;
			contatoreDiControllo=0;
			i++;
		}
	}
}

void Cittadella::cambiaSegno(int k,int & sx, int & sz){
	switch (k) {
		case 0: {sx=1; sz=1; break;}
		case 1: {sx=-1; sz=1; break;}
		case 2: {sx=1; sz=-1; break;}
		case 3: {sx=-1; sz=-1; break;}
	}
}

bool Cittadella::controllaCollisionePalazzi(int indicePalazzo,float px,float pz,float largh){
	float distanza;
	for(int i=0;i<indicePalazzo;i++){
		distanza=(float)(sqrt((px-posizionePalazzi[i][0])*(px-posizionePalazzi[i][0])+(pz-posizionePalazzi[i][2])*(pz-posizionePalazzi[i][2])));
		if(distanza<(largh+dimensionePalazzi[i][0]+4)){//se la distanza tra il centro del nuovo palazzo(indice palazzo) e l'i-esimo creato precedentemente è minore della somma della larghezza del nuovo palazzo e la larghezza dell'i-esimo più 4 metri di scarto, allora collide
			return true;
		}
	}
	return false;
}

Cittadella::Cittadella(float posx,float posz,int larg,int lung){//posizione nell'asse x, nell'asse z, larghezza e lunghezza
	centroCittadella[0]=posx;
	centroCittadella[1]=0;
	centroCittadella[2]=posz;
	larghezza=larg;
	lunghezza=lung;
	vitaIniziale=0;
	generaCittadella();
	for(int i=0;i<numeroPalazzi;i++){//la vita della cittadella è uguale alla somma delle altezze di ogni palazzo
		vitaIniziale+=dimensionePalazzi[i][1];
	}
}

int Cittadella::getNumeroPalazzi() const{
	return numeroPalazzi;
}

float* Cittadella::getPosizionePalazzo(int i){
	return posizionePalazzi[i];
}

float Cittadella::getRaggioPalazzo(int i) const{
	return dimensionePalazzi[i][0];
}

float Cittadella::getAltezzaPalazzo(int i) const{
	return dimensionePalazzi[i][1];
}

float* Cittadella::getCentroCittadella(){
	return centroCittadella;
}

int Cittadella::getLarghezza()const{
	return larghezza;
}

int Cittadella::getLunghezza()const{
	return lunghezza;
}

void Cittadella::danneggiaPalazzo(int i){
	dimensionePalazzi[i][1]-=2;
}

int Cittadella::getVitaCittadella(){
	int vita=0;
	for(int i=0;i<numeroPalazzi;i++){
		vita+=dimensionePalazzi[i][1];
	}
	return vita;
}


int Cittadella::getVitaIniziale()const{
	return vitaIniziale;
}


void Cittadella::crolla(){
	for(int i=0;i<numeroPalazzi;i++){
		dimensionePalazzi[i][1]=0;
	}
}

