#include "granata.h"


Granata::Granata(float px,float py,float pz):posx(px),posy(py),posz(pz),sparato(false),collisione(false){}


Granata::~Granata(){}


float Granata::getPosX()const{
	return posx;
}

float Granata::getPosY()const{
	return posy;
}

float Granata::getPosZ()const{
	return posz;
}

void Granata::setPosX(float px){
	posx=px;
}

void Granata::setPosY(float py){
	posy=py;
}

void Granata::setPosZ(float pz){
	posz=pz;
}

bool Granata::isSparata()const{
	return sparato;
}

void Granata::setSparato(bool b){
	sparato=b;
}


bool Granata::isCollisione()const{
	return collisione;
}

void Granata::setCollisione(bool b){
	collisione=b;
}


Bomba::Bomba(float px,float py,float pz): Granata(px,py,pz),obiettivo(0){
	indiciPalazzoObiettivo=new int[2];
}

Bomba::~Bomba(){
	delete obiettivo;
	delete indiciPalazzoObiettivo;
}


void Bomba::addObiettivo(float x,float y,float z){
	if(obiettivo==0){
		obiettivo=new Obiettivo(x,y,z);
	}
}

Obiettivo::Obiettivo* Bomba::getObiettivo(){
	return obiettivo;
}


void Bomba::addIndiciPalazzoObiettivo(int indCittadella,int indPalazzo){
		indiciPalazzoObiettivo[0]=indCittadella;
		indiciPalazzoObiettivo[1]=indPalazzo;
}

bool Bomba::isBombaSopraPalazzoObiettivo(){
	if(indiciPalazzoObiettivo!=0){
		if(indiciPalazzoObiettivo[0]==-1 && indiciPalazzoObiettivo[1]==-1){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}

int Bomba::getIndiceCittadellaPalazzoObiettivo(){
	if(indiciPalazzoObiettivo!=0){
		return indiciPalazzoObiettivo[0];
	}
	return -1;
}

int Bomba::getIndicePalazzoObiettivo(){
	if(indiciPalazzoObiettivo!=0){
		return indiciPalazzoObiettivo[1];
	}
	return -1;
}


float Bomba::getRaggioBomba(){
	return raggioBomba;
}


Proiettile::Proiettile(float px,float py,float pz): Granata(px,py,pz){}

float Proiettile::getDirX() const{
	return dirX;
}

float Proiettile::getDirY() const{
	return dirY;
}

float Proiettile::getDirZ() const{
	return dirZ;
}

float Proiettile::getPosXRotOssY()const{
	return posXRotOssY;
}

float Proiettile::getPosZRotOssY()const{
	return posZRotOssY;
}

void Proiettile::setPosXRotOssY(float f){
	posXRotOssY=f;
}

void Proiettile::setPosZRotOssY(float f){
	posZRotOssY=f;
}

float Proiettile::getRotOssYSuSparo()const{
	return RotOssYSuSparo;
}

void Proiettile::setRotYSuSparo(float r){
	RotOssYSuSparo=r;
}

void Proiettile::aggiornaDirezioni(float canRotX,float canRotY){//per mette di aggiornare la posizione del proiettile a secondo delle rotazioni sul cannone
	dirX=sin((canRotY)/RADIANTE)*sin((canRotX)/RADIANTE);
	dirY=cos((canRotX)/RADIANTE);
	dirZ=cos((canRotY)/RADIANTE)*sin((canRotX)/RADIANTE);
}

float Proiettile::getRaggioProiettile(){
	return raggioProiettile;
}
