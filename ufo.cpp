#include "ufo.h"


Ufo::Ufo(int nb,float px,float py,float pz,float velx,float vely,float velz,float quota):numeroBombe(nb),posx(px),posy(py),posz(pz),velocitaX(velx),velocitaY(vely),velocitaZ(velz),direzione(0){
	vita=numeroBombe;
	attacco=false;
	sgancioBomba=false;
	quotaAttacco=quota;
	bombeEsaurite=false;
	for(int i=0;i<numeroBombe;i++){
		vBombe.push_back(new Bomba(posx,posy,posz));
	}
}

Ufo::~Ufo(){
	for(int i=0;i<vBombe.size();i++){
		delete vBombe.at(i);
	}
	vBombe.clear();
}

float Ufo::getPosizioneX()const{
	return posx;
}

float Ufo::getPosizioneY()const{
	return posy;
}

float Ufo::getPosizioneZ()const{
	return posz;
}

float Ufo::getVelocitaX()const{
	return velocitaX;
}

float Ufo::getVelocitaY()const{
	return velocitaY;
}

float Ufo::getVelocitaZ()const{
	return velocitaZ;
}

float Ufo::getDirezione()const{
	return direzione;
}

void Ufo::setDirezione(float d){
	direzione=d;
}


void Ufo::setVelocitaX(float v){
	velocitaX=v;
}

void Ufo::setVelocitaY(float v){
	velocitaY=v;
}

void Ufo::setVelocitaZ(float v){
	velocitaZ=v;
}

void Ufo::aggiornaPosizione(float addx,float addy,float addz){
	posx+=addx;
	posy+=addy;
	posz+=addz;
}


void Ufo::setAttacco(bool b){
	attacco=b;
}

bool Ufo::isAttacco()const{
	return attacco;
}

float Ufo::getQuotaAttacco()const{
	return quotaAttacco;
}

bool Ufo::isSgancioBomba()const{
	return sgancioBomba;
}

void Ufo::setSgancioBomba(bool b){
	sgancioBomba=b;
}

int Ufo::getNumeroBombe()const{
	return vBombe.size();
}
int Ufo::getNumeroBombeIniziali()const{
	return numeroBombe;
}

Granata::Granata* Ufo::getBomba(int i){
	return vBombe.at(i);
}

void Ufo::togliBombaSganciata(int i){
	delete vBombe.at(i);
	vBombe.at(i)=0;
}

Granata::Granata* Ufo::getBombaDaSparare(){
	for(int i=vBombe.size()-1;i>=0 ;i--){
		if(vBombe.at(i)!=0){
			if(vBombe.at(i)->isSparata()==false){
				return vBombe.at(i);
			}
		}
		else{//dato scorro dalla fine e trovo che non cè più la bomba, posso diminuire la size del vector senza problemi
			vBombe.pop_back();
		}
	}
	return 0;
}


void Ufo::setBombeEsaurite(bool b){
	bombeEsaurite=b;
}

bool Ufo::isBombeEsaurite()const{
	return bombeEsaurite;
}

void Ufo::danneggia(){
	vita-=2;
}

int Ufo::getVita()const{
	return vita;
}

float Ufo::getLarghezzaUfo(){
	return larghezzaUfo;
}

float Ufo::getAltezzaUfo(){
	return altezzaUfo;
}




