#include "controller.h"

Controller::Controller(Model*m,View*v):model(m),view(v){}

void Controller::rilascioTastoFreccia(int key, int x, int y){
	switch (key) {
		case GLUT_KEY_UP: {model->setVettTasti(0,false); break;}
		case GLUT_KEY_DOWN: {model->setVettTasti(1,false); break;}
		case GLUT_KEY_LEFT: {model->setVettTasti(2,false); break;}
		case GLUT_KEY_RIGHT: {model->setVettTasti(3,false); break;}
	}
}

void Controller::azioneTastoFreccia(int key, int x, int y){
	switch (key) {
		case GLUT_KEY_UP: {model->setVettTasti(0,true); break;}
		case GLUT_KEY_DOWN: {model->setVettTasti(1,true); break;}
		case GLUT_KEY_LEFT: {model->setVettTasti(2,true); break;}
		case GLUT_KEY_RIGHT: {model->setVettTasti(3,true); break;}
		case GLUT_KEY_F1: {
			model->avviaGioco();
			break;
		}
	}
}


void Controller::azioneTasto(unsigned char key, int x, int y){
	switch (key) {
		case 't': {
			if(model->isTextureAttive()==true){
				view->nonCaricaTexture();
				model->setTextureAttive(false);
			}
			else{
				view->caricaTexture();
				model->setTextureAttive(true);
			}
			break;
		}
		case 'g': {
			if(model->isTerrenoMinimale()==true){
				model->setTerrenoMinimale(false);
			}
			else{
				model->setTerrenoMinimale(true);
			}
			break;
		}
		case 'h': {
			if(model->isHelpAttivo()==true){
				model->setHelpAttivo(false);
			}
			else{
				model->setHelpAttivo(true);
			}
			break;
		}
		case 'a': {model->setVettTasti(6,true); break;}
		case 'd': {model->setVettTasti(7,true); break;}
		case 'w': {model->setVettTasti(8,true); break;}
		case 's': {model->setVettTasti(9,true); break;}
		case ' ': {model->setVettTasti(10,true); break;}
	}
}


void Controller::rilascioTasto(unsigned char key, int x, int y){
	switch (key) {
		case 'a': {model->setVettTasti(6,false); break;}
		case 'd': {model->setVettTasti(7,false); break;}
		case 'w': {model->setVettTasti(8,false); break;}
		case 's': {model->setVettTasti(9,false); break;}
		case ' ': {model->setVettTasti(10,false); break;}
	}
}
