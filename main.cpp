//Andrea Zorzi 561818

#ifdef WIN32
#include <windows.h>
#endif

#include "model.h"
#include "view.h"
#include "controller.h"

//creo i tre oggetti principali dell'architettura usata
Model *m=new Model(10,3,20,1000,220,31,220,512);
View *v=new View(m);
Controller *c=new Controller(m,v);

void callMuoviti(){
	if(m->getNumeroCittadelle()==0 || (m->getNumeroUfo()==0 && m->isInizio()==false) || m->getCannone()==0 || m->getTerreno()==0){
		//se non ci sono cittadelle, o non ci sono ufo e il gioco deve ancora iniziare, o non cè il cannone, o non è presente il terreno
		cout<<"Errore. Non è possibile iniziare il gioco perchè mancano oggetti fondamentali per il gioco "<<endl;
	}
	else{
		return m->movimento();
	}
}

void callDisegnaMondo(){
	v->disegnaMondo();
}

void callCambiaDimensione(int w,int h){
	v->cambiaDimensione(w,h);
}

void callRilascioTastoFreccia(int key, int x, int y){
	c->rilascioTastoFreccia(key,x,y);
}

void callAzioneTastoFreccia(int key, int x, int y){
	c->azioneTastoFreccia(key,x,y);
}

void callRilascioTasto(unsigned char key, int x, int y){
	c->rilascioTasto(key,x,y);
}

void callAzioneTasto(unsigned char key, int x, int y){
	c->azioneTasto(key,x,y);
}





GLint main(GLint argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );//double buffering
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800, 590);
	glutCreateWindow("Difesa della cittadella");

	glEnable(GL_DEPTH_TEST);//z-buffer
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	srand(time(NULL));

	//con il modello creato, creo il terreno, il cannone, gli ufo e le cittadelle
	m->creaTerreno(6,512);
	m->creaCittadella(180,400,80,80);
	m->creaCittadella(400,240,90,90);
	m->creaUfo(15,290,95,320,15,2,2,65);
	m->creaUfo(15,270,90,310,20,2,1,58);
	m->creaUfo(15,240,80,290,20,2,1,58);
	m->creaUfo(15,220,78,330,20,2,3,70);
	m->creaUfo(15,210,70,310,20,2,1,75);
	m->creaUfo(15,190,90,350,15,2,1,80);
	m->creaUfo(25,170,85,310,15,2,3,85);
	m->creaCannone(800,0,-6,0);

	//effettuo alcune operazioni di modellazione del terreno
	m->getTerreno()->modellaTerreno();
	m->getTerreno()->spianaTerrenoEdificabile(180,400,100,100);
	m->getTerreno()->spianaTerrenoEdificabile(400,240,100,100);
	m->getTerreno()->creaCollina(30,220,220);
	m->getTerreno()->creaCollina(30,300,430);
	m->getTerreno()->creaCollina(50,50,450);
	m->getTerreno()->creaCollina(20,350,400);
	m->getTerreno()->creaCollina(30,35,35);
	m->getTerreno()->creaCollina(50,400,60);

	//carico le texture
	v->caricaTexture();

	//normalizzo il terreno, rendendolo più realistico
	m->getTerreno()->normalizzaTerreno();

	glutReshapeFunc(callCambiaDimensione);
	glutDisplayFunc(callDisegnaMondo);
	glutSpecialFunc(callAzioneTastoFreccia);
	glutSpecialUpFunc(callRilascioTastoFreccia);
	glutKeyboardFunc(callAzioneTasto);
	glutKeyboardUpFunc(callRilascioTasto);
	glutIdleFunc(callMuoviti);


	// anti aliasing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glutMainLoop();
	return(0);
}


