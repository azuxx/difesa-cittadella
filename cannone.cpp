#include "cannone.h"

Cannone::Cannone(int np,float cx,float cy,float cz):numeroProiettili(np),canX(cx),canY(cy),canZ(cz){
	canRotX=180+90;
	canRotY=0;
	tempoDiCarica=1000;
	velRotazioneCannone=10;
	sparando=false;
	attendiCarica=false;
	contatoreProiettili=numeroProiettili;
}

Cannone::~Cannone(){
	vProiettili.clear();
}

void Cannone::inserisciProiettiliCannone(float x,float y ,float z){
	for (int i = 0; i < numeroProiettili; i++) {
		vProiettili.push_back(new Proiettile(x,y,z));
	}
}

float Cannone::getCanX()const{
	return canX;
}

float Cannone::getCanY()const{
	return canY;
}

float Cannone::getCanZ()const{
	return canZ;
}

float Cannone::getCanRotX()const{
	return canRotX;
}

float Cannone::getCanRotY()const{
	return canRotY;
}

float Cannone::getTempoDiCarica()const{
	return tempoDiCarica;
}

float Cannone::getVelRotazioneCannone()const{
	return velRotazioneCannone;
}

void Cannone::addCanRotX(float r){
	canRotX+=r;

}
void Cannone::addCanRotY(float r){
	canRotY+=r;
}

void Cannone::setCanRotX(float r){
	canRotX=r;
}

void Cannone::setCanRotY(float r){
	canRotY=r;
}

bool Cannone::isSparando() const{
	return sparando;
}

void Cannone::setSparando(bool b){
	sparando=b;
}

Granata* Cannone::getProiettile(int i){
	return vProiettili.at(i);
}

void Cannone::togliProiettileSparato(int i){
	delete vProiettili.at(i);
	vProiettili.at(i)=0;
}

int Cannone::getNumeroProiettili()const{
	return vProiettili.size();
}

void Cannone::setAttendiCarica(bool b){
	attendiCarica=b;
}

bool Cannone::isAttendiCarica() const{
	return attendiCarica;
}


Granata* Cannone::getProiettileDaSparare(){
	bool stop=false;
	for(int i=vProiettili.size()-1;i>=0 && !stop;i--){
		if(vProiettili.at(i)!=0){
			if(vProiettili.at(i)->isSparata()==false){
				return vProiettili.at(i);
			}
		}
		else{//solo qui riduco la dimensione del vector, togliendo la posizione della bomba che è stata tolta del metodo togliBombaSganciata
			//essendo che scorro in ordine il vector con il controllo che la bomba sia stata tolta. (qui non possono esserci buchi! altrimenti il pop_back usato altrove creerebbe inconsistenza)
			vProiettili.pop_back();
		}
	}
	return 0;
}

int Cannone::getNumeroProiettiliIniziale()const{
	return numeroProiettili;
}

int Cannone::getContatoreProiettili()const{
	return contatoreProiettili;
}

void Cannone::diminuisciContatoreProiettili(){
	contatoreProiettili--;
}

float Cannone::getLunghezza(){
	return lunghezza;
}

float Cannone::getLarghezza(){
	return larghezza;
}

