#include "view.h"

View::View(Model* m):model(m),angoloVisivo(60){}

void View::stampaStringaBitMap(GLint x, GLint y, char* s,int dim,GLfloat r,GLfloat g,GLfloat b,int dimFont){//metodo per la stampa di testo

	glDisable(GL_TEXTURE_2D);
    char* p=s;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH),0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glColor3f(r,g,b);
			glRasterPos2i(x, y);
			for(int i=0; i<dim;i++){
				if(dimFont==12){
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
				}
				else if(dimFont==18){
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
				}
				else if(dimFont==24){
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
				}
				p=p+1;
			}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    if(model->isTextureAttive()==true)
    	glEnable(GL_TEXTURE_2D);
}


void View::disegnaPannelloDiGioco(){
	glDisable(GL_TEXTURE_2D);
	float winWidth=glutGet(GLUT_WINDOW_WIDTH),winHeight=glutGet(GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	    glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0, winWidth,0.0,winHeight , -1.0, 1.0);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
				//gli oggetti sono creati in ordine inverso perchè sono posizionati in primo piano
				//barra di caricamento
				char p[7]={"Charge"};
				glColor3f(1.0f,1.0f,1.0f);
				glRasterPos2i(3, 6);
				for(int i=0; i<7;i++){
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, p[i]);
				}
				glBegin(GL_QUADS);
					glColor3f(1,0,0);
					glVertex2f(10,20);
					glVertex2f(35,20);
					float t = model->getTempoCorrenteDiCarica();
					if(t==0){
						t=model->getCannone()->getTempoDiCarica();
					}
					if(model->getCannone()->getContatoreProiettili()<=0){
						t=0;
					}
					glVertex2f(35,0.0750*t);
					glVertex2f(10,0.0750*t);
				glEnd();
				glBegin(GL_QUADS);
					glColor3f(0.3f,0.3f,0.3f);
					glVertex2f(10,20);
					glVertex2f(35,20);
					glVertex2f(35,75);
					glVertex2f(10,75);
				glEnd();
				//barra vita cittadelle
				int posIniz=50;
				for(int i=0;i<model->getNumeroCittadelle();i++){
					int vitaAttuale=static_cast<int>(model->getCittadella(i)->getVitaCittadella()/2);
					int vitaIniziale=static_cast<int>(model->getCittadella(i)->getVitaIniziale()/2);
					glBegin(GL_QUADS);
						glColor3f(0,1,0);
						glVertex2f(50+vitaAttuale,posIniz);
						glVertex2f(50,posIniz);
						glVertex2f(50,posIniz-5);
						glVertex2f(50+vitaAttuale,posIniz-5);
					glEnd();
					glBegin(GL_QUADS);
						glColor3f(1.0f,1.0f,1.0f);
						glVertex2f(50+vitaIniziale,posIniz);
						glVertex2f(50,posIniz);
						glVertex2f(50,posIniz-5);
						glVertex2f(50+vitaIniziale,posIniz-5);
					glEnd();
					posIniz+=12;
				}
				//barra vita degli ufo
				int posInizUfo=posIniz;
				int posInizSinistra=50;
				for(int i=0;i<model->getNumeroUfo();i++){
					int vitaAttuale=model->getUfo(i)->getVita();
					int vitaIniziale=model->getUfo(i)->getNumeroBombeIniziali();
					glBegin(GL_QUADS);
						glColor3f(1,0.2,0);
						glVertex2f(posInizSinistra+vitaAttuale,posInizUfo);
						glVertex2f(posInizSinistra,posInizUfo);
						glVertex2f(posInizSinistra,posInizUfo-5);
						glVertex2f(posInizSinistra+vitaAttuale,posInizUfo-5);
					glEnd();
					glBegin(GL_QUADS);
						glColor3f(1.0f,1.0f,1.0f);
						glVertex2f(posInizSinistra+vitaIniziale,posInizUfo);
						glVertex2f(posInizSinistra,posInizUfo);
						glVertex2f(posInizSinistra,posInizUfo-5);
						glVertex2f(posInizSinistra+vitaIniziale,posInizUfo-5);
					glEnd();
					posInizUfo+=12;
					if(posInizUfo>110){
						posInizUfo=posIniz;
						posInizSinistra+=vitaIniziale+5;
					}
				}

				//proiettili cannone
				float numeroProiettAttuali=model->getCannone()->getContatoreProiettili();
				float numeroProiettIniziali=model->getCannone()->getNumeroProiettiliIniziale();
				float scala=80/numeroProiettIniziali;
				glBegin(GL_QUADS);
					glColor3f(0,0,0);
					glVertex2f(50+int(numeroProiettAttuali*scala),33);
					glVertex2f(50,33);
					glVertex2f(50,28);
					glVertex2f(50+int(numeroProiettAttuali*scala),28);
				glEnd();
				glBegin(GL_QUADS);
					glColor3f(1.0f,1.0f,1.0f);
					glVertex2f(50+int(numeroProiettIniziali*scala),33);
					glVertex2f(50,33);
					glVertex2f(50,28);
					glVertex2f(50+int(numeroProiettIniziali*scala),28);
				glEnd();
				//numero bombe ufo
				int numeroBombeAttuali=0,numeroBombeIniziali=0;
				for(int i=0;i<model->getNumeroUfo();i++){
					numeroBombeAttuali+=model->getUfo(i)->getNumeroBombe();
					numeroBombeIniziali+=model->getUfo(i)->getNumeroBombeIniziali();
				}
				glBegin(GL_QUADS);
					glColor3f(0,0,1);
					glVertex2f(50+numeroBombeAttuali,15);
					glVertex2f(50,15);
					glVertex2f(50,10);
					glVertex2f(50+numeroBombeAttuali,10);
				glEnd();
				glBegin(GL_QUADS);
					glColor3f(1.0f,1.0f,1.0f);
					glVertex2f(50+numeroBombeIniziali,15);
					glVertex2f(50,15);
					glVertex2f(50,10);
					glVertex2f(50+numeroBombeIniziali,10);
				glEnd();
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
	    glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	if(model->isTextureAttive()==true)
		glEnable(GL_TEXTURE_2D);
}

void View::visualizzaInformazioniTestuali(){

	glDisable(GL_TEXTURE_2D);

	char* buffer1=new char[50];
	char* buffer2=new char[50];
	char* buffer3=new char[50];
	char* buffer4=new char[50];
	char* buffer5=new char[50];
	char* buffer6=new char[50];
	char* buffer7=new char[50];
	int dim1=sprintf (buffer1, "Posizione oss. %i , %i, %i", static_cast<int>(model->getOssX()), static_cast<int>(model->getOssY()), static_cast<int>(model->getOssZ()));
	int dim2=sprintf (buffer2, "Rotaz. visuale %i , %f", static_cast<int>(model->getOssRotX()), model->getOssRotY());
	int dim3=sprintf (buffer3, "Rotaz. cannone %f , %f", model->getCannone()->getCanRotX(), model->getCannone()->getCanRotY());
	int numeroBombeAttuali=0;
	for(int i=0;i<model->getNumeroUfo();i++){
		numeroBombeAttuali+=model->getUfo(i)->getNumeroBombe();
	}
	int dim4=sprintf (buffer4, "Bombe rimanenti %i", numeroBombeAttuali);
	int numP=model->getCannone()->getContatoreProiettili();
	int dim5;
	if(numP<=0){
		dim5=sprintf (buffer5, "Proiettili esauriti");
	}
	else{
		dim5=sprintf (buffer5, "Proiettili rimanenti %i", numP);
	}

	int dim6=sprintf (buffer6, "Vita cittadelle");
	int dim7=sprintf (buffer7, "Vita ufo");

	stampaStringaBitMap(glutGet(GLUT_WINDOW_WIDTH)-250,60,buffer1,dim1,1.0,1.0,1.0,12);
	stampaStringaBitMap(glutGet(GLUT_WINDOW_WIDTH)-250,40,buffer2,dim2,1.0,1.0,1.0,12);
	stampaStringaBitMap(glutGet(GLUT_WINDOW_WIDTH)-250,20,buffer3,dim3,1.0,1.0,1.0,12);
	stampaStringaBitMap(180,10,buffer4,dim4,1.0,1.0,1.0,12);
	stampaStringaBitMap(180,30,buffer5,dim5,1.0,1.0,1.0,12);
	stampaStringaBitMap(180,60,buffer6,dim6,1.0,1.0,1.0,12);
	stampaStringaBitMap(180,100,buffer7,dim7,1.0,1.0,1.0,12);
	if(model->isTextureAttive()==true)
		glEnable(GL_TEXTURE_2D);

}

void View::visualizzaInformazioniFineGioco(){

	glDisable(GL_TEXTURE_2D);

	char* messFine=new char[80];
	int dimMessFine;
	int tipoFine=model->getTipoFine();

	if(tipoFine==0){
		dimMessFine=sprintf (messFine, "Le cittadelle sono salve! Gli ufo hanno esaurito le bombe");
	}
	else if(tipoFine==1){
		dimMessFine=sprintf (messFine, "Hai perso! Le cittadelle sono state distrutte ");
	}
	else if(tipoFine==2){
		dimMessFine=sprintf (messFine, "Hai vinto! Hai distrutto tutti gli ufo");
	}

	stampaStringaBitMap(180,180,messFine,dimMessFine,1.0,1.0,1.0,24);

	if(model->isTextureAttive()==true)
		glEnable(GL_TEXTURE_2D);

}

void View::mostraHelp(){

	glDisable(GL_LIGHTING);
	float winWidth=glutGet(GLUT_WINDOW_WIDTH),winHeight=glutGet(GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0, winWidth,0.0,winHeight , -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glColor3f(1,1,1);
			//texture per l'help
			glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-6]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.020,0);
				glVertex2f(100,180);
				glTexCoord2f(1,0);
				glVertex2f(600,180);
				glTexCoord2f(1,0.95);
				glVertex2f(600,555);
				glTexCoord2f(0.020,0.95);
				glVertex2f(100,555);
			glEnd();

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}


void View::cambiaDimensione(int w,int h){
		//previene di dividere per zero
		if(h==0){
			h=1;
		}
		glViewport(0,0,w,h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		tassoAspetto = (GLdouble) w / (GLdouble) h;
		gluPerspective(angoloVisivo, tassoAspetto, 0.9, model->getDistanzaMassimaVisuale());

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void View::disegnaMondo(){
	glClearColor( 0.0f , 0.0f , 0.0f ,1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(model->isInizio()==false){
		char* buffer0=new char[100];
		char*bufferHelp=new char[100];
		int dim0=sprintf (buffer0,"Difesa della cittadella. Premi F1 per iniziare il gioco.");
		stampaStringaBitMap(200,200,buffer0,dim0,0,0,1.0,18);
		int dimHelp=sprintf (bufferHelp,"Premi h per visualizzare/nascondere l'help dei comandi di gioco.");
		stampaStringaBitMap(200,180,bufferHelp,dimHelp,0,0,1.0,18);
	}

	if(model->isHelpAttivo()){
		mostraHelp();
	}

	disegnaPannelloDiGioco();

	visualizzaInformazioniTestuali();

	if(model->isFine()){
		visualizzaInformazioniFineGioco();
	}

	// movimento osservatore
	glRotatef(-model->getOssRotX(),1,0,0);

	//rendo indipendente gli oggetti seguenti dalla rotazione in x dell'osservatore (alto/basso)

	// cannone
	disegnaCannone();//fisso al terreno. lo metto qua, xk non posso "alzare" il cannone

	glRotatef(-model->getOssRotY(),0,1,0);

	//rendo indipendente gli oggetti seguenti dalla rotazione in y dell'osservatore (sinistra/destra)

	impostaLuce();
	disegnaCielo();


	glTranslatef(-model->getOssX(),-model->getOssY(),-model->getOssZ());

	//i seguenti oggetti seguono il sistema di riferimento del mondo

	disegnaProiettile();

	disegnaCittadelle();

	disegnaUfo();

	disegnaBomba();

	if(model->isTerrenoMinimale()==true){
		disegnaGriglia();
	}
	else{
		disegnaTerreno();
	}

	glFlush();
	glutSwapBuffers();
}

void View::impostaLuce(){
	GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat diffuseLight[] = {1,1,1,1};
	GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPos[] = {50,25,30, 0};// posizione luce che rispecchia il sole nello skybox, il quarto valore è messo a zero perchè è una sorgente di tipo all'infinito (raggi luminosi paralleli
	GLfloat black[] = {0,0,0,1};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//posizionamento luce sole
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


void View::disegnaCannone(){
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
		glTranslatef(model->getCannone()->getCanX(),model->getCannone()->getCanY(),model->getCannone()->getCanZ());
		glRotatef(model->getCannone()->getCanRotY(),0,1,0);
		glRotatef(model->getCannone()->getCanRotX(),1,0,0);
		glColor3f (0.3, 0.3, 0.3);
		float angolo,zCannone,xCannone,passo;
		passo=(M_PI*2.0)/64;//divido la circonferenza goniometrica in 64 "pezzi" per far ottenere un cilindro
		float lunghezza=Cannone::getLunghezza(),larghezza=Cannone::getLarghezza();
		glBegin(GL_QUADS);
			for(angolo=passo;angolo<M_PI*2.0;angolo+=passo){
				zCannone=sin(angolo-passo)*larghezza;
				xCannone=cos(angolo-passo)*larghezza;
				glNormal3f(xCannone,0,zCannone);
				glVertex3f(xCannone,0,zCannone);
				glVertex3f(xCannone/2,lunghezza,zCannone/2);
				zCannone=sin(angolo)*larghezza;
				xCannone=cos(angolo)*larghezza;
				glNormal3f(xCannone,0,zCannone);
				//inverto i segni di y per soddisfare il senso antiorario del rettangolo
				glVertex3f(xCannone/2,lunghezza,zCannone/2);
				glVertex3f(xCannone,0,zCannone);
			}
		glEnd();
		disegnaMirino();
		glEnable(GL_CULL_FACE);
		if(model->isTextureAttive()==true)
				 glEnable(GL_TEXTURE_2D);
	glPopMatrix();

}

void View::disegnaMirino(){
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	 glColor3f (0.9, 0.9, 0.9);
	 glEnable (GL_LINE_STIPPLE);
		 glLineStipple (1, 0x00FF);  //linea tratteggiata
		 glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,400,0);
		 glEnd();
	 glDisable (GL_LINE_STIPPLE);
	 glEnable(GL_LIGHTING);
	 if(model->isTextureAttive()==true)
		 glEnable(GL_TEXTURE_2D);
}


void View::disegnaProiettile(){
	bool stop=false;
	GLfloat brillante_l[4] = { 0.8, 0.8, 0.8, 1 };
	GLfloat brillante_m[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante_l);
	for(int i=model->getCannone()->getNumeroProiettili()-1;i>=0 && !stop;i--){
		glPushMatrix();
			Granata*g=model->getCannone()->getProiettile(i);
			if(g!=0){
				if(g->isSparata()==true){
					glColor3f(0,0,1);
					Proiettile*p=dynamic_cast<Proiettile*>(model->getCannone()->getProiettile(i));
					glTranslatef(p->getPosXRotOssY(),g->getPosY(),p->getPosZRotOssY());
					glutSolidSphere(Proiettile::getRaggioProiettile(),20,20);
				}
				else{
					stop=true;
				}
			}
		glPopMatrix();
	}
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante_m);
}

void View::disegnaBomba(){
	GLfloat brillante_l[4] = { 0.8, 0.8, 0.8, 1 };
	GLfloat brillante_m[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante_l);//effetto riflesso sulla bomba, la ipotizzo lucida che riflette.
	for(int k=0;k<model->getNumeroUfo();k++){
		bool stop=false;
		for(int i=model->getUfo(k)->getNumeroBombe()-1;i>=0 && !stop;i--){
			glPushMatrix();
				Granata*g=model->getUfo(k)->getBomba(i);
				if(g!=0){
					if(g->isSparata()==true){
						glColor3f(0.3,0.3,0.3);
						glTranslatef(g->getPosX(),g->getPosY(),g->getPosZ());
						glutSolidSphere(Bomba::getRaggioBomba(),20,20);
					}
					else{
						stop=true;
					}
				}
			glPopMatrix();
		}
	}
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante_m);//disabilito la riflettenza altrimenti rifletteranno la luce anche gli oggetti creati in seguito
}

void View::disegnaGriglia(){
	glClearColor( 0.0f , 0.0f , 0.0f ,1.0f);
	float a;
	glColor3f(1,1,1);
	glNormal3f(0,1,0);
	float limite=model->getDistanzaMassimaVisuale();
	glBegin(GL_LINES);
		for (a = 0; a < limite;a=a+5.0f) {
			glVertex3f(a,-1,0);
			glVertex3f(a,-1,limite);
		}
		for (a = 0; a <limite;a=a+5.0f) {
			glVertex3f(0,-1,a);
			glVertex3f(limite,-1,a);
		}
	glEnd();
}

/*
 * Per fare il cielo uso una skybox, ovvero un cubo in cui attacco a 5 delle 6 facce
 * una texture adatta che rappresenta quella visuale del cielo.
 */
void View::disegnaCielo(){
	// salva la matrice corrente
    glPushMatrix();
		// abbasso un po' il cubo, resto al centro in x e z ma non in y
		glTranslatef(0,-10,0);

		// disegno i vertici bianchi
		if(model->isTextureAttive()==true)
			glColor3f(1,1,1);
		else
			glColor3f(0.3,0.3,1);

		glDisable(GL_LIGHTING);

		float dMaxVisuale=model->getDistanzaMassimaVisuale();
		float intersezione=dMaxVisuale/1000;

		// carica il quadro per l'asse negativo delle z (p cardinale: nord)
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.035f,0.0001f);
			glVertex3f(-dMaxVisuale/2-intersezione, -dMaxVisuale/2, -dMaxVisuale/2); // basso sx
			glTexCoord2f(1.025f,0.0001f);
			glVertex3f(dMaxVisuale/2+intersezione, -dMaxVisuale/2, -dMaxVisuale/2); // basso dx
			glTexCoord2f(1.015f,1);
			glVertex3f(dMaxVisuale/2+intersezione, dMaxVisuale/2, -dMaxVisuale/2); // alto dx
			glTexCoord2f(0.035f,1.0001f);
			glVertex3f(-dMaxVisuale/2-intersezione, dMaxVisuale/2, -dMaxVisuale/2); // alto sx
		glEnd();

		// carica il quadro per l'asse positivo delle x (p cardinale: est)
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.045f,0.0001f);
			glVertex3f(dMaxVisuale/2, -dMaxVisuale/2, -dMaxVisuale/2-intersezione); // basso sx
			glTexCoord2f(1.045f,0.0001f);
			glVertex3f(dMaxVisuale/2, -dMaxVisuale/2, dMaxVisuale/2+intersezione); // basso dx
			glTexCoord2f(1.025f,1);
			glVertex3f(dMaxVisuale/2, dMaxVisuale/2, dMaxVisuale/2+intersezione); // alto dx
			glTexCoord2f(0.045f,1.0001f);
			glVertex3f(dMaxVisuale/2, dMaxVisuale/2, -dMaxVisuale/2-intersezione); // alto sx
		glEnd();

		// carica il quadro per l'asse positivo delle z (p cardinale: sud)
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.035f,0.0001f);
			glVertex3f(dMaxVisuale/2+intersezione, -dMaxVisuale/2, dMaxVisuale/2); // basso sx
			glTexCoord2f(1.030f,0.0001f);
			glVertex3f(-dMaxVisuale/2-intersezione, -dMaxVisuale/2, dMaxVisuale/2); // basso dx
			glTexCoord2f(1.035f,1);
			glVertex3f(-dMaxVisuale/2-intersezione, dMaxVisuale/2, dMaxVisuale/2); // alto dx
			glTexCoord2f(0.035f,1.0001f);
			glVertex3f(dMaxVisuale/2+intersezione, dMaxVisuale/2, dMaxVisuale/2); // alto sx
		glEnd();

		// carica il quadro per l'asse negativo delle x (p cardinale: ovest)
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-5]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.050f,0.0001f);
			glVertex3f(-dMaxVisuale/2, -dMaxVisuale/2, dMaxVisuale/2+intersezione); // basso sx
			glTexCoord2f(1.050f,0.0001f);
			glVertex3f(-dMaxVisuale/2, -dMaxVisuale/2, -dMaxVisuale/2-intersezione); // basso dx
			glTexCoord2f(1.015f,1);
			glVertex3f(-dMaxVisuale/2, dMaxVisuale/2, -dMaxVisuale/2-intersezione); // alto dx
			glTexCoord2f(0.035f,1.0001f);
			glVertex3f(-dMaxVisuale/2, dMaxVisuale/2, dMaxVisuale/2+intersezione); // alto sx
		glEnd();

		// carica il quadro per l'asse positivo delle y (sopra la testa)
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.030f,0.0001f);
			glVertex3f(-dMaxVisuale/2-0.01f, dMaxVisuale/2-intersezione*2, -dMaxVisuale/2-intersezione); // basso sx
			glTexCoord2f(1.030f,0.0001f);
			glVertex3f(dMaxVisuale/2+0.01f, dMaxVisuale/2-intersezione*2, -dMaxVisuale/2-intersezione); // basso dx
			glTexCoord2f(1.030f,1);
			glVertex3f(dMaxVisuale/2+0.01f, dMaxVisuale/2-intersezione, dMaxVisuale/2+intersezione); // alto dx
			glTexCoord2f(0.038f,1.0013f);
			glVertex3f(-dMaxVisuale/2-0.01f, dMaxVisuale/2-intersezione, dMaxVisuale/2+intersezione); // alto sx
		glEnd();

		glEnable(GL_LIGHTING);

    glPopMatrix();

}

void View::disegnaTerreno(){
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glColor3f(1,1,1);

	GLfloat xPlane[] = {1,0,0,0}, zPlane[] = {0,0,1,0};//piano x, piano z,

	// contorni per non avere il vuoto fuori dalla mappa, le dimensioni
	// sono pensate per mantenere l'orizzonte
	glTexGenfv(GL_S, GL_OBJECT_PLANE, xPlane);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, zPlane);

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-9]);

	glNormal3f(0,1,0);

	float dMaxVisuale=model->getDistanzaMassimaVisuale();
	float dim=model->getTerreno()->getDimensione();

	//i quattro quadrati che fanno il contorno, per simulare il terreno all'orizzonte
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(-dMaxVisuale/2, 0, 0);
		glVertex3f(-dMaxVisuale/2, 0, dim-1);
		glVertex3f(0, 0, dim-1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(dim-1, 0, 0);
		glVertex3f(dim-1, 0, dim);
		glVertex3f(dim-1 + dMaxVisuale/2, 0, dim-1);
		glVertex3f(dim-1 + dMaxVisuale/2, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(-dMaxVisuale/2, 0, 0);
		glVertex3f(dim-1 + dMaxVisuale/2, 0, 0);
		glVertex3f(dim-1 + dMaxVisuale/2, 0, -dMaxVisuale/2);
		glVertex3f(-dMaxVisuale/2, 0, -dMaxVisuale/2);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(-dMaxVisuale/2, 0, dim-1);
		glVertex3f(-dMaxVisuale/2, 0, dim-1 + dMaxVisuale/2);
		glVertex3f(dim-1 + dMaxVisuale/2, 0, dim-1 + dMaxVisuale/2);
		glVertex3f(dim-1 + dMaxVisuale/2, 0, dim-1);
	glEnd();



	// elaboro solo la zona di terreno entro il limite visivo dello skybox

	zMin = (GLint)(model->getOssZ() - dMaxVisuale/2);
	if(zMin < 0)
		zMin = 0;
	zMax = (GLint)(model->getOssZ() + dMaxVisuale/2 + 1);
	if(zMax > dim-2)
		zMax = dim-2;
	xMin = (GLint)(model->getOssX() - dMaxVisuale/2);
	if(xMin < 0)
		xMin = 0;
	xMax = (GLint)(model->getOssX() + dMaxVisuale/2 + 1);
	if(xMax > dim-2)
		xMax = dim-2;

	// ora dato che so che ho limitato l'area al quadrato dello skybox e che
	// l'angolo di visuale è di 60°, posso sempre creare solo metà del quadrato,
	// quella alle spalle non la considero

	// elimino la metà superiore
	if(model->getOssRotY() > 270 + angoloVisivo || model->getOssRotY() < 90 - angoloVisivo)
		zMax -= (GLint)(zMax - model->getOssZ());
	// elimino la metà sinistra
	if(model->getOssRotY() > angoloVisivo && model->getOssRotY() < 180 - angoloVisivo)
		xMax -= (GLint)(xMax - model->getOssX());
	// elimino la metà inferiore
	if(model->getOssRotY() > 90 + angoloVisivo && model->getOssRotY() < 270 - angoloVisivo)
		zMin += (GLint)model->getOssZ() - zMin;
	// elimino la metà destra
	if(model->getOssRotY() > 180 + angoloVisivo && model->getOssRotY() < 360 - angoloVisivo)
		xMin += (GLint)model->getOssX() - xMin;

	//riempie la griglia del terreno con la texture i scorre l'asse z visibile mentre j l'asse x visibile
	for(GLint i = zMin; i <= zMax; i++){
		glBegin(GL_TRIANGLE_STRIP);
			//i quattro vertici del primo quadrato della "prima riga" di z con vertici z=i e z=i+1
			glNormal3fv(model->getTerreno()->getNormali(i,xMin));
			glVertex3f(xMin, model->getTerreno()->getAltezzaTerreno(i,xMin)/model->getTerreno()->getFattoreScala(), i);
			glNormal3fv(model->getTerreno()->getNormali(i+1,xMin));
			glVertex3f(xMin, model->getTerreno()->getAltezzaTerreno(i+1,xMin)/model->getTerreno()->getFattoreScala(), i+1);
			glNormal3fv(model->getTerreno()->getNormali(i,xMin+1));
			glVertex3f(xMin+1, model->getTerreno()->getAltezzaTerreno(i,xMin+1)/model->getTerreno()->getFattoreScala(), i);
			glNormal3fv(model->getTerreno()->getNormali(i+1,xMin+1));
			glVertex3f(xMin+1, model->getTerreno()->getAltezzaTerreno(i+1,xMin+1)/model->getTerreno()->getFattoreScala(), i+1);
			//completa con tutti i quadrati della "prima riga" di z visibile
			for(GLint j = xMin+1; j <= xMax; j++){
				glNormal3fv(model->getTerreno()->getNormali(i,j+1));
				glVertex3f(j+1, model->getTerreno()->getAltezzaTerreno(i,j+1)/model->getTerreno()->getFattoreScala(), i);
				glNormal3fv(model->getTerreno()->getNormali(i+1,j+1));
				glVertex3f(j+1,model->getTerreno()->getAltezzaTerreno(i+1,j+1)/model->getTerreno()->getFattoreScala(), i+1);
			}
		glEnd();
	}
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void View::disegnaCittadelle(){
	glDisable(GL_CULL_FACE);
	glColor3f(1,1,1);


	for(int k=0;k<model->getNumeroCittadelle();k++){
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-8]);
		glNormal3f(0,1,0);


		float larghezzaCittadella=model->getCittadella(k)->getLarghezza();
		float lunghezzaCittadella=model->getCittadella(k)->getLunghezza();
		float*centro=model->getCittadella(k)->getCentroCittadella();

		glBegin(GL_QUADS);//disegno un quadrato dove poi posiziono la texture del porfido
			glTexCoord2f(0,0);
			glVertex3f(centro[0]-larghezzaCittadella/2,0,centro[2]-lunghezzaCittadella/2);
			glTexCoord2f(3,0);
			glVertex3f(centro[0]+larghezzaCittadella/2,0,centro[2]-lunghezzaCittadella/2);
			glTexCoord2f(3,3);
			glVertex3f(centro[0]+larghezzaCittadella/2,0,centro[2]+lunghezzaCittadella/2);
			glTexCoord2f(0,3);
			glVertex3f(centro[0]-larghezzaCittadella/2,0,centro[2]+lunghezzaCittadella/2);
		glEnd();

		for(int i=0;i<model->getCittadella(k)->getNumeroPalazzi();i++){
			disegnaStruttura(model->getCittadella(k)->getPosizionePalazzo(i),64,model->getCittadella(k)->getRaggioPalazzo(i),model->getCittadella(k)->getAltezzaPalazzo(i));//palazzo cilindrico
		}
		glColor3f(1,1,1);//metto bianco, altrimenti la texture della cittadella seguente, prende il colore dei palazzi

	}
	glEnable(GL_CULL_FACE);
}

void View::disegnaStruttura(GLfloat *posizione,GLfloat spigoli, GLfloat larghezza,GLfloat altezza){
	if(posizione[0]!=-1 && posizione[2]!=-1){//se è disegnabile (è una mia scelta considerare -1 come discriminante, dato anche viene usato solo il quadrante positivo del piano. vedi normali terreno)
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-7]);
		glPushMatrix();
			glColor3f(0.5,0.3,0.01);
			glTranslatef(posizione[0],posizione[1],posizione[2]);
			float angolo,zPalazzo,xPalazzo,passo;
			passo=(M_PI*2.0)/spigoli;
			glBegin(GL_QUADS);
				for(angolo=passo;angolo<M_PI*2.0;angolo+=passo){
					zPalazzo=sin(angolo-passo)*larghezza;
					xPalazzo=cos(angolo-passo)*larghezza;
					glNormal3f(xPalazzo,0,zPalazzo);
					//if(angolo==passo){
						glTexCoord2f(0,0);
					//}
					glVertex3f(xPalazzo,0,zPalazzo);
					//if(angolo==passo){
						glTexCoord2f(0,0.9);
					//}
					glVertex3f(xPalazzo,altezza,zPalazzo);
					zPalazzo=sin(angolo)*larghezza;
					xPalazzo=cos(angolo)*larghezza;
					glNormal3f(xPalazzo,0,zPalazzo);
					//if((M_PI*2.0)-angolo<0.1){
						glTexCoord2f(0.9,0.9);
					//}
					glVertex3f(xPalazzo,altezza,zPalazzo);
					//if((M_PI*2.0)-angolo<0.1){
						glTexCoord2f(0.9,0);
					//}
					glVertex3f(xPalazzo,0,zPalazzo);

				}
			glEnd();
			float x,z;
			glBegin(GL_TRIANGLE_FAN);//disegno il tetto (copro la parte superiore del cilindro)
				glNormal3f(1,1,1);
				glVertex3f(0,altezza,0);
				for(angolo=0;angolo<=M_PI*2.0;angolo+=passo){
					x = cos(angolo)*larghezza;
			        z = sin(angolo)*larghezza;
			        glNormal3f(0,1,0);
			        glVertex3f(x,altezza,z);
				}
	        glEnd();
		glPopMatrix();
	}

}


void View::disegnaUfo(){
	GLfloat brillante_l[4] = { 0.8, 0.8, 0.8, 1 };
	GLfloat brillante_m[4] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante_l);
	for(int i=0;i<model->getNumeroUfo();i++){
		glPushMatrix();
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_BACK,GL_FILL);
			glTranslatef(model->getUfo(i)->getPosizioneX(),model->getUfo(i)->getPosizioneY(),model->getUfo(i)->getPosizioneZ());
			glRotatef(-90,1,0,0);
			glColor3f(0.7f,0.7f,0.7f);
			//disegno l'ufo

			glutSolidCone(8,3,20,20);

			glEnable(GL_CULL_FACE);
		glPopMatrix();
	}
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante_m);
}





void View::caricaTexture(){
	const char * texturesVarie[TEXTURE_COUNT-5]={"terreno.bmp", "porfido.bmp","palazzoSmall.bmp","help.bmp"};// array che contengono i nomi dei file delle textures
	const char * texturesSkybox[TEXTURE_COUNT-4] = {"neg_x.bmp", "neg_z.bmp","pos_x.bmp","pos_z.bmp","pos_y.bmp"};

	FILE *fHan;

	GLfloat ambiente[4] = { 1, 1, 1, 1 };
	GLfloat direttiva[4] = { 1, 1, 1, 1 };

	glMateriali(GL_FRONT, GL_SHININESS, 32);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_MULTISAMPLE);

	//contenitore di tutte le texture
	glGenTextures(TEXTURE_COUNT, texture);

	//texture terreno

	fHan = fopen(texturesVarie[TEXTURE_COUNT-9], "rb");
	if(fHan == NULL) return;
	fread(texTerreno, 256 * 256, 3, fHan);
	fclose(fHan);

	//caricamento terreno
	glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-9]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,8);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 256, 256, GL_BGR, GL_UNSIGNED_BYTE, texTerreno);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	//fine caricamento

	// texture dello skybox
	for(int k=TEXTURE_COUNT-5; k<TEXTURE_COUNT; k++){
		fHan = fopen(texturesSkybox[k-(TEXTURE_COUNT-5)], "rb");
		if(fHan == NULL) return;
		fread(skyBox, 512 * 512, 3, fHan);
		fclose(fHan);

		glBindTexture(GL_TEXTURE_2D, texture[k]);
		//i due parametri per l'alta qualità delle texture per il cielo
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 512, 512, GL_BGR, GL_UNSIGNED_BYTE, skyBox);

	}

	//texture help

	fHan = fopen(texturesVarie[TEXTURE_COUNT-6], "rb");
	if(fHan == NULL) return;
	fread(texHelp, 500 * 375, 3, fHan);
	fclose(fHan);

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-6]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 500, 375, GL_BGR, GL_UNSIGNED_BYTE, texHelp);


	//texture palazzo

	fHan = fopen(texturesVarie[TEXTURE_COUNT-7], "rb");
		if(fHan == NULL) return;
		fread(texPalazzo, 28 * 44, 3, fHan);
		fclose(fHan);

		glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-7]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 28, 44, GL_BGR, GL_UNSIGNED_BYTE, texPalazzo);

	//texture piano cittadella

	fHan = fopen(texturesVarie[TEXTURE_COUNT-8], "rb");
	if(fHan == NULL) return;
	fread(texPianoCittadella, 256 * 192, 3, fHan);
	fclose(fHan);

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURE_COUNT-8]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 256, 192, GL_BGR, GL_UNSIGNED_BYTE, texPianoCittadella);

	//glDisable(GL_MULTISAMPLE);
}


void View::nonCaricaTexture(){
	glDisable(GL_TEXTURE_2D);
}

