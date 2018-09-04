#include "obiettivo.h"


Obiettivo::Obiettivo(float x,float y,float z):obx(x),oby(y),obz(z),attivo(false){}

float Obiettivo::getXObiettivo()const{
	return obx;
}

float Obiettivo::getYObiettivo()const{
	return oby;
}

float Obiettivo::getZObiettivo()const{
	return obz;
}

bool Obiettivo::isAttivo()const{
	return attivo;
}

void Obiettivo::setAttivo(bool b){
	attivo=b;
}
