#include "model.h"

Model::Model(int maxu, int maxcitt,int maxb,int maxp,float oX,float oY, float oZ,float dMaxVisuale):maxUfo(maxu),maxCittadelle(maxcitt),maxBombe(maxb),maxProiettili(maxp),ossX(oX),ossY(oY),ossZ(oZ),distanza(dMaxVisuale){
	t=0;
	tempoPrec=-1;
	tempoInizioCambioAvanzam=0;
	tempoInizioCarica=0;
	tempoInizioAttacco=0;
	velRotazioneOsservatore=25;
	prossimoCambioVerso=rand()% 2000 + 6000;
	prossimoAttacco = rand() % 2000 + 8000;
	RaggiungimentoObiettiviAttacco=true;//setto a true, così predispongo già gli ufo ad attaccare
	ossRotY=180;
	ossRotX=-10;
	t=0;
	c=0;
	textureAttive=true;
	terrenoMinimale=false;
	helpAttivo=false;
	numeroUfoInObiettivo=0;
	numeroUfoBombeEsaurite=0;
	fine=false;
	inizio=false;
	tipoFine=-1;
}

Model::~Model(){
	for(int i=0;i<vu.size();i++){
		delete vu.at(i);
	}
	for(int i=0;i<vcitt.size();i++){
			delete vcitt.at(i);
	}
	vcitt.clear();
	vu.clear();
	delete t;
	delete c;
}


void Model::creaTerreno(float fatts,int dimDaMod){
	if(!t){
		t=new Terreno(fatts,dimDaMod);
	}
}

void Model::creaCannone(int np,float cx,float cy ,float cz){
	if(!c){
		if(np>maxProiettili){
			np=maxProiettili;
		}
		c=new Cannone(np,cx,cy,cz);
		c->inserisciProiettiliCannone(ossX-cx,ossY+cy,ossZ-cz);//avuta anche la posizione dell'osservatore,posso inizializzare il vector di proiettili
	}
}


void Model::creaCittadella(float px,float pz,int larg,int lung){
	if(vcitt.size()<maxCittadelle){
		vcitt.push_back(new Cittadella(px,pz,larg,lung));
	}
}

void Model::creaUfo(int nb,float px,float py,float pz,float velx,float vely,float velz,float quota){
	if(vu.size()<maxUfo){
		if(nb>maxBombe){
			nb=maxBombe;
		}
		vu.push_back(new Ufo(nb,px,py,pz,velx,vely,velz,quota));
	}
}

// permette la gestione simultanea della pressione di più tasti gestiti dal controller occupandosi del movimento temporizzato degli oggetti del mondo
void Model::movimento(){
	srand(time(NULL));
	tempo = glutGet(GLUT_ELAPSED_TIME);
	if(tempoPrec < 0){
		tempoPrec=tempo;
		dt = 0;
	}
	else{
		dt= (tempo - tempoPrec) / 1000.0f;//framerate
		//cout<<"   "<<(int)((float)1/dt);//fps
		tempoPrec = tempo;
	}
	// dt è il tempo passato dall'ultimo frame disegnato

    if(vettTasti[0]==true){//rotazione osservatore verso l'alto
       	ossRotX+=(velRotazioneOsservatore * dt);
       	if(ossRotX > 90)
       		ossRotX=90;
    }
    if(vettTasti[1]==true){//rotazione osservatore verso il basso
       	ossRotX-=(velRotazioneOsservatore * dt);
       	if(ossRotX < -20)
       		ossRotX=-20;
    }

    if(vettTasti[2]==true){//rotazione osservatore verso sinistra
    	ossRotY += (velRotazioneOsservatore * dt);
    	if(ossRotY > 360)
    		ossRotY -= 360;
    }

    if(vettTasti[3]==true){//rotazione osservatore verso destra
    	ossRotY -= (velRotazioneOsservatore * dt);
    	if(ossRotY < 0)
    		ossRotY = 360 + ossRotY;
    }


    if(inizio==true){//se il gioco è iniziato
		muoviCannone();

		muoviUfo();

		muoviProiettile();

		muoviBomba();

		calcolaCarica();

		controllaCollisioneBombaPalazzo();

		controllaCollisioneProiettileMondo();


		if(tipoFine==-1){//se non si è conclusa la partita

			if((tempo - tempoInizioAttacco > prossimoAttacco) && RaggiungimentoObiettiviAttacco==true){
				numeroUfoInObiettivo=0;
				RaggiungimentoObiettiviAttacco=false;
				tempoInizioAttacco = tempo;
				int contaCittadelleDistrutte=0;
				for(int i=0;i<vcitt.size();i++){//controllo se tutte le cittadelle sono state distrutte
					if(vcitt.at(i)->getVitaCittadella()<=(float)vcitt.at(i)->getVitaIniziale()*0.2){//se la vita della cittadella è inferiore o uguale al 20% della vita iniziale la cittadella crolla
						vcitt.at(i)->crolla();
						contaCittadelleDistrutte++;
					}
				}
				if(contaCittadelleDistrutte==vcitt.size()){//se tutte, faccio terminare il gioco.
					fine=true;
					tipoFine=1;//le cittadelle sono state distrutte
				}
				else{//almeno una cittadella non è stata distrutta
					prossimoAttacco = rand() % 3000 + 9000;
					int cittScelta=rand()%vcitt.size();
					while(vcitt.at(cittScelta)->getVitaCittadella()<=0){
						cittScelta=rand()%vcitt.size();//scelgo in modo random quale cittadella devono attaccare gli ufo
					}
					attaccoCittadella(cittScelta);
				}
			}

			if(tempo - tempoInizioCambioAvanzam > prossimoCambioVerso){//se vero, inverte la direzione in z (vz) del movimento dell'ufo
				tempoInizioCambioAvanzam = tempo;
				prossimoCambioVerso = rand() % 2000 + 10000;
				int iUfo=rand()%vu.size();
				vu.at(iUfo)->setVelocitaZ(-vu.at(iUfo)->getVelocitaZ());
			}
		}
    }
    else{
    	tempoInizioCambioAvanzam=tempo;
    	tempoInizioAttacco = tempo;
    	tempoInizioCarica=tempo;
    }
	// aggiorna la finestra
	glutPostRedisplay();
}

void Model::scegliSegno(int & sx, int & sz){
	int k=rand()%4;
	switch (k) {
		case 0: {sx=1; sz=1; break;}
		case 1: {sx=-1; sz=1; break;}
		case 2: {sx=1; sz=-1; break;}
		case 3: {sx=-1; sz=-1; break;}
	}
}

void Model::attaccoCittadella(int cittScelta){
	for(int i=0;i<vu.size();i++){
		if(vu.at(i)->isBombeEsaurite()==false){
			vu.at(i)->setAttacco(true);
			float*p=new float[3];
			float *centroCittadella=vcitt.at(cittScelta)->getCentroCittadella();
			int segnoX,segnoZ;
			scegliSegno(segnoX,segnoZ);
			p[0]=centroCittadella[0]+segnoX*(rand()%(vcitt.at(cittScelta)->getLarghezza()/2));
			p[1]=centroCittadella[1]+vu.at(i)->getQuotaAttacco();
			p[2]=centroCittadella[2]+segnoZ*(rand()%(vcitt.at(cittScelta)->getLunghezza()/2));
			Bomba*b=dynamic_cast<Bomba*>(vu.at(i)->getBombaDaSparare());
			if(b!=0){//se l'ufo ha una bomba da sparare
				b->addObiettivo(p[0],p[1],p[2]);//aggiunge l'obiettivo della cittadella scelto da colpire
			}
			else{
				vu.at(i)->setAttacco(false);//ritorno alla posizione di non attacco (esplorazione)
				vu.at(i)->setBombeEsaurite(true);
				numeroUfoBombeEsaurite++;
				if(numeroUfoBombeEsaurite==vu.size()){
					fine=true;
					tipoFine=0;//gli ufo finiscono le bombe
				}
			}
		}
	}
}

void Model::ottieniIndiciPalazzoSottoObiettivoUfo(int iufo,float xRagg,float zRagg){
	bool trovato=false;
	Bomba*b=dynamic_cast<Bomba*>(vu.at(iufo)->getBombaDaSparare());
	for(int i=0;i<vcitt.size() && !trovato;i++){
		for(int j=0;j<vcitt.at(i)->getNumeroPalazzi() && !trovato;j++){
			float xCentroPalazzo=vcitt.at(i)->getPosizionePalazzo(j)[0];
			float zCentroPalazzo=vcitt.at(i)->getPosizionePalazzo(j)[2];
			float distanza=(float)sqrt((xRagg-xCentroPalazzo)*(xRagg-xCentroPalazzo)+(zRagg-zCentroPalazzo)*(zRagg-zCentroPalazzo));//distanza proiezione obiettivo sul piano e centro del palazzo j-esimo della cittadella i-esima
			if((distanza<(vcitt.at(i)->getRaggioPalazzo(j)+Bomba::getRaggioBomba())) && vcitt.at(i)->getAltezzaPalazzo(j)>0){//se cè un palazzo sotto l'obiettivo del ufo e non è stato distrutto.
				trovato=true;
				b->addIndiciPalazzoObiettivo(i,j);
			}
		}
	}
	if(!trovato){
		b->addIndiciPalazzoObiettivo(-1,-1);//-1 =valore discriminante che in questo caso indica che all'obiettivo non corrisponde alcun palazzo
	}
}



bool Model::isContattoBombaTettoPalazzo(float xBomba,float yBomba, float zBomba,float rBomba,float xPalazzo,float yPalazzo,float zPalazzo){
	double distanzaCentri=sqrt((xBomba-xPalazzo)*(xBomba-xPalazzo)+(yBomba-yPalazzo)*(yBomba-yPalazzo)+(zBomba-zPalazzo)*(zBomba-zPalazzo));//distanza proiezioni
	if(distanzaCentri<=(rBomba)){
		return true;
	}
	else{
		return false;
	}
}

bool Model::isContattoProiettileBomba(float xProiett,float yProiett, float zProiett,float rProiett,float xBomba,float yBomba,float zBomba,float rBomba){
	float distanzaCentri=(float)sqrt((xProiett-xBomba)*(xProiett-xBomba)+(yProiett-yBomba)*(yProiett-yBomba)+(zProiett-zBomba)*(zProiett-zBomba));//distanza proiettile-bomba
	if(distanzaCentri<=(rProiett+rBomba+0.5)){//0.5=tolleranza
		return true;
	}
	else{
		return false;
	}
}


bool Model::isContattoProiettileUfo(float xProiett,float yProiett, float zProiett,float rProiett,float xUfo,float yUfo,float zUfo,float largh,float altezza){
	float distanzaCentri=(float)sqrt((xProiett-xUfo)*(xProiett-xUfo)+(zProiett-zUfo)*(zProiett-zUfo));//distanza proiettile centro ufo
	if(distanzaCentri<=(rProiett+largh+0.5)){//0.5=tolleranza
		if((yProiett-yUfo+rProiett)>-0.5 && (yProiett-yUfo)<(altezza-distanzaCentri*altezza/largh)+0.5+rProiett){//la proiezione del proiettile è sulla base dell ufo e il proiettile interseca l'ufo. altezza/largh è il rapporto di pendenza della forma a cono dell'ufo
			return true;
		}
		else{//la proiezione del proiettile è sulla base dell ufo ma il proiettile non interseca l'ufo
			return false;
		}
	}
	else{
		return false;
	}
}

bool Model::isContattoProiettileCittadella(float xProiett,float yProiett, float zProiett,float rProiett,float xCentroPalazzo, float zCentroPalazzo,float larghezza,float altezza){
	float distanzaCentri=(float)sqrt((xProiett-xCentroPalazzo)*(xProiett-xCentroPalazzo)+(zProiett-zCentroPalazzo)*(zProiett-zCentroPalazzo));//distanza proiettile centro palazzo
	if(distanzaCentri<=(rProiett+larghezza+0.5)){//0.5=tolleranza per via della velocità del proiettile
		if((yProiett-altezza+rProiett)>-0.5-altezza && (yProiett-altezza)<0.5+rProiett){//la proiezione del proiettile è sulla base del palazzo e il proiettile interseca il palazzo
			return true;
		}
		else{//la proiezione del proiettile è sulla base del palazzo ma il proiettile non lo interseca.
			return false;
		}
	}
	else{
		return false;
	}
}

void Model::controllaCollisioneBombaPalazzo(){
	for(int k=0;k<vu.size();k++){
		bool stop=false;
		for(int i=vu.at(k)->getNumeroBombe()-1;i>=0 && !stop;i--){
			Granata*g=vu.at(k)->getBomba(i);
			if(g!=0){//faccio il controllo sulle bombe attive (che non sono state tolte perchè cadute a terra o collise)
				if(g->isSparata()==true){//faccio il controllo se è stata sganciata
					//bomba in caduta, controllo collisione
					Obiettivo*o=dynamic_cast<Bomba*>(g)->getObiettivo();
					if(o!=0){
						//ottengo le coordinate del obiettivo raggiunto, dove è stata sganciata la bomba (non considero la quota)
						float xRaggiunto=o->getXObiettivo();
						float zRaggiunto=o->getZObiettivo();
						if(dynamic_cast<Bomba*>(g)->isBombaSopraPalazzoObiettivo()==true){
							//c'è un palazzo sotto l'obiettivo dove è stata sganciata la bomba
							//ottengo gli indici del palazzo della cittadella che è sotto l'obiettivo (indiceObiettivo) dell'ufo
							int indiceCitt=dynamic_cast<Bomba*>(g)->getIndiceCittadellaPalazzoObiettivo();
							int indicePal=dynamic_cast<Bomba*>(g)->getIndicePalazzoObiettivo();
							//ottieni il raggio e l'altezza del palazzo della cittadella, che è sotto l'obiettivo dell'ufo
							float altezzaPalazzo=vcitt.at(indiceCitt)->getAltezzaPalazzo(indicePal);
							if(altezzaPalazzo>0){//se il palazzo non è stato distrutto
								if(isContattoBombaTettoPalazzo(g->getPosX(),g->getPosY(),g->getPosZ(),Bomba::getRaggioBomba(),xRaggiunto,altezzaPalazzo,zRaggiunto)==true){
									//la bomba è entrata in collisione con il palazzo
									vcitt.at(indiceCitt)->danneggiaPalazzo(indicePal);
									g->setCollisione(true);
								}
							}
						}
					}
				}
				else{//è ancora da sganciare
					stop=true;
				}
			}
		}
	}
}

void Model::controllaCollisioneProiettileMondo(){
	bool stop=false;
	for(int i=c->getNumeroProiettili()-1;i>=0 && !stop;i--){
		Granata*gProiettile=c->getProiettile(i);
		if(gProiettile!=0){
			if(gProiettile->isSparata()==true){
				Proiettile*p=dynamic_cast<Proiettile*>(c->getProiettile(i));
				//controllo collisione con bomba
				for(int k=0;k<vu.size();k++){
					bool stop2=false;
					//controllo collisione con bombe in caduta
					for(int j=vu.at(k)->getNumeroBombe()-1;j>=0 && !stop2;j--){
						Granata*gBomba=vu.at(k)->getBomba(j);
						if(gBomba!=0){
							if(gBomba->isSparata()==true){
								if(isContattoProiettileBomba(p->getPosXRotOssY(),gProiettile->getPosY(),p->getPosZRotOssY(),Proiettile::getRaggioProiettile(),gBomba->getPosX(),gBomba->getPosY(),gBomba->getPosZ(),Bomba::getRaggioBomba())==true){
									gProiettile->setCollisione(true);
									gBomba->setCollisione(true);
									stop2=true;
								}
							}
						}
					}
				}
				//controllo collisione con terreno
				if(gProiettile->getPosY()<0 || p->getPosZRotOssY()> distanza || p->getPosZRotOssY()< -distanza || p->getPosXRotOssY()> distanza|| p->getPosXRotOssY()< -distanza){
					gProiettile->setCollisione(true);
				}
				//controllo collisione con ufo
				for(int k=vu.size()-1;k>=0;k--){
					if(vu.at(k)->isSgancioBomba()==false){
						if(vu.at(k)->getVita()>0){
							if(isContattoProiettileUfo(p->getPosXRotOssY(),gProiettile->getPosY(),p->getPosZRotOssY(),Proiettile::getRaggioProiettile(),vu.at(k)->getPosizioneX(),vu.at(k)->getPosizioneY(),vu.at(k)->getPosizioneZ(),Ufo::getLarghezzaUfo(),Ufo::getAltezzaUfo())==true){
								gProiettile->setCollisione(true);
								vu.at(k)->danneggia();
							}
						}
						else{
							delete vu.at(k);
							vu.at(k)=0;
							AggiornaVectorUfo();
							if(vu.size()==0){//sono stati distrutti tutti gli ufo
								fine=true;
								tipoFine=2;
							}
						}
					}
				}
				bool trovato=false;
				//controllo collisione con cittadella
				int contaCittadelleDistrutteOss=0;
				for(int i=0;i<vcitt.size() && !trovato;i++){
					for(int j=0;j<vcitt.at(i)->getNumeroPalazzi() && !trovato;j++){
						float xCentroPalazzo=vcitt.at(i)->getPosizionePalazzo(j)[0];
						float zCentroPalazzo=vcitt.at(i)->getPosizionePalazzo(j)[2];
						float altezza=vcitt.at(i)->getAltezzaPalazzo(j);
						if(altezza>0){
							if(isContattoProiettileCittadella(p->getPosXRotOssY(),gProiettile->getPosY(),p->getPosZRotOssY(),Proiettile::getRaggioProiettile(),xCentroPalazzo,zCentroPalazzo,vcitt.at(i)->getRaggioPalazzo(j),altezza)){
								gProiettile->setCollisione(true);
								vcitt.at(i)->danneggiaPalazzo(j);
								trovato=true;
							}
						}
					}
					if(vcitt.at(i)->getVitaCittadella()<=(float)vcitt.at(i)->getVitaIniziale()*0.2){//se la vita della cittadella è inferiore o uguale al 20% della vita iniziale la cittadella crolla
						vcitt.at(i)->crolla();
						contaCittadelleDistrutteOss++;
					}
				}
				if(contaCittadelleDistrutteOss==vcitt.size()){//se tutte, faccio terminare il gioco.
					fine=true;
					tipoFine=1;//le cittadelle sono state distrutte
				}
			}
			else{//è ancora da sparare
				stop=true;
			}
		}
	}
}

void Model::AggiornaVectorUfo(){//funzione che evita di fare controlli su puntatori nulli in ogni metodo che usa il vector ufo (vu)
	vector<Ufo*> vettTemp;
	for(int i=0;i<vu.size();i++){//fa una copia del vector ufo nel vector d'ausilio
		if(vu.at(i)!=0){//copia nel vector d'ausilio solo gli ufo non ancora distrutti.
			vettTemp.push_back(vu.at(i));
		}
	}
	vu.clear();//elimina tutti gli elementi del vector ufo da aggiornare
	for(int i=0;i<vettTemp.size();i++){//copia gli ufo salvati nel vector d'ausilio nel vector ufo.
		vu.push_back(vettTemp.at(i));
	}
	vettTemp.clear();
}


void Model::muoviProiettile(){
	if(vettTasti[10]==true && c->isAttendiCarica()==false){
		cout<<"ho premuto il pulsante e il cannone era carico"<<endl;
		c->diminuisciContatoreProiettili();
		c->setSparando(true);
		Proiettile*p=dynamic_cast<Proiettile*>(c->getProiettileDaSparare());
		if(p!=0){
			//sparato il proiettile g
			p->setSparato(true);
			p->setRotYSuSparo(ossRotY);
			p->aggiornaDirezioni(c->getCanRotX(),c->getCanRotY());
			//cout<<"direzioni proiettile "<<p->getDirX()<<" "<<p->getDirY()<<" "<<p->getDirZ()<<endl;
		}
	}
	bool stop=false;
	for(int i=c->getNumeroProiettili()-1;i>=0 && !stop;i--){
		Granata*g=c->getProiettile(i);
		if(g!=0){
			if(g->isSparata()==true){
				if(g->isCollisione()==true){
					c->togliProiettileSparato(i);
					cout<<"tolto proiettile"<<endl;
				}
				else{
					Proiettile*p=dynamic_cast<Proiettile*>(c->getProiettile(i));
					//spara il proiettile nella direzione del cannone
					g->setPosX(g->getPosX()-110*dt*p->getDirX());
					g->setPosY(g->getPosY()+110*dt*p->getDirY());
					g->setPosZ(g->getPosZ()+110*dt*p->getDirZ());
					//calcolo la posizione tenendo conto della rotazione sull'asse Y dell'osservatore. formula della rototraslazione
					float zConRot=(g->getPosZ()-(ossZ-c->getCanZ()))*cos((p->getRotOssYSuSparo())/RADIANTE)+(g->getPosX()-(ossX-c->getCanX()))*sin((p->getRotOssYSuSparo())/RADIANTE);
					p->setPosZRotOssY(ossZ-c->getCanZ()+zConRot);
					float xConRot=-(g->getPosZ()-(ossZ-c->getCanZ()))*sin((p->getRotOssYSuSparo())/RADIANTE)+(g->getPosX()-(ossX-c->getCanX()))*cos((p->getRotOssYSuSparo())/RADIANTE);
					p->setPosXRotOssY(ossX-c->getCanX()-xConRot);
					//cout<<"coordinate proiett x: "<<p->getPosXRotOssY()<<" y: "<<g->getPosY()<<" z: "<<p->getPosZRotOssY()<<endl;
				}
			}
			else{
				// primo proiettile in canna non muovere, quindi ferma tutto dato che anche i prossimi non sono da sparare
				stop=true;
			}
		}
	}
}


void Model::calcolaCarica(){
	if((tempo - tempoInizioCarica < c->getTempoDiCarica()) && c->isSparando()==true){
			c->setAttendiCarica(true);
	}
	else{
		c->setSparando(false);
		tempoInizioCarica = tempo;
		c->setAttendiCarica(false);
	}
}

void Model::muoviCannone(){
	if(vettTasti[6]==true){
			c->addCanRotY(c->getVelRotazioneCannone() * dt);
			if(c->getCanRotY() > 360)
				c->addCanRotY(-360);
	}

	if(vettTasti[7]==true){
		c->addCanRotY(-c->getVelRotazioneCannone() * dt);
		if(c->getCanRotY() < 0)
			c->setCanRotY(360 + c->getCanRotY());
	}

	if(vettTasti[8]==true){
		c->addCanRotX(c->getVelRotazioneCannone() * dt);
		if(c->getCanRotX() > 310)
			c->setCanRotX(310);
	}

	if(vettTasti[9]==true){
		c->addCanRotX(-c->getVelRotazioneCannone() * dt);
		if(c->getCanRotX() < 255)
			c->setCanRotX(255);
	}
}

void Model::muoviBomba(){
	for(int k=0;k<vu.size();k++){
		bool stop=false;
		int nBombe=vu.at(k)->getNumeroBombe()-1;
		for(int i=nBombe;i>=0 && !stop;i--){
			Granata*g=vu.at(k)->getBomba(i);
			if(g!=0){
				if(g->isSparata()==true){//controllo se è stata sganciata
					if(g->getPosY()<0 || (g->isCollisione()==true)){
						vu.at(k)->togliBombaSganciata(i);
						if(vu.at(k)->getNumeroBombe()==1){//è rimasta solo una bomba, faccio subito popback perchè l'ufo non attaccherà più e quindi non c'è più l'opportunità di pulire l'array delle bombe e così aggiornare il contatore bombe.
							vu.at(k)->getBombaDaSparare();
						}
						//%TODO implementa "controlli" per esplosione da gestire nella view
					}
					else{
						//fa scendere la bomba, perpendicolare al terreno, lungo la "linea" dell'obiettivo dove è stata sganciata
						g->setPosY(g->getPosY()-4*dt);
					}
				}
				else{
					//bomba ancora da sganciare, termina il for.
					stop=true;
				}
			}
		}
	}
}

void Model::muoviUfo(){
	for(int i=0;i<vu.size();i++){
		if(vu.at(i)!=0){
			//per ogni ufo
			//se l'ufo non sta attaccando fa un movimento zig zag stabilito
			if(vu.at(i)->isAttacco()==false){
				if(vu.at(i)->isBombeEsaurite()==true || tipoFine==1){
					//l'ufo fugge perchè ha finito le bombe o ha distrutto le cittadella;
					vu.at(i)->aggiornaPosizione(vu.at(i)->getVelocitaX() *dt, vu.at(i)->getVelocitaY() *2* dt, vu.at(i)->getVelocitaZ() *10*dt);
				}
				else{
					float ang=vu.at(i)->getDirezione()/RADIANTE;
					vu.at(i)->aggiornaPosizione(sin(ang)*vu.at(i)->getVelocitaX() * dt, vu.at(i)->getVelocitaY() * dt, -vu.at(i)->getVelocitaZ() *dt);
					if(vu.at(i)->getDirezione()==360){
						vu.at(i)->setDirezione(0);
					}
					float valIncr=vu.at(i)->getDirezione()+3;
					vu.at(i)->setDirezione(valIncr);
				}
			}
			else{//se sta attaccando
				//se è in posizione di sgancio bomba (ha raggiunto l'obiettivo da colpire)
				if(vu.at(i)->isSgancioBomba()==true){
					vu.at(i)->setAttacco(false);//torna al movimento random
					Granata*g=vu.at(i)->getBombaDaSparare();
					if(g!=0){
						//si sgancia la bomba
						g->setSparato(true);
						g->setPosX(vu.at(i)->getPosizioneX());
						g->setPosY(vu.at(i)->getPosizioneY());
						g->setPosZ(vu.at(i)->getPosizioneZ());
						vu.at(i)->setSgancioBomba(false);
					}
				}
				else{//se sta attaccando e deve raggiungere l'obiettivo da colpire
					Bomba*b=dynamic_cast<Bomba*>(vu.at(i)->getBombaDaSparare());
					float obX=b->getObiettivo()->getXObiettivo();
					float obY=b->getObiettivo()->getYObiettivo();
					float obZ=b->getObiettivo()->getZObiettivo();
					float posX=vu.at(i)->getPosizioneX();
					float posY=vu.at(i)->getPosizioneY();
					float posZ=vu.at(i)->getPosizioneZ();
					float vx=posX,vy=posY,vz=posZ;
					double distanzaObiettivo=sqrt((posX-obX)*(posX-obX)+(posY-obY)*(posY-obY)+(posZ-obZ)*(posZ-obZ));
					if(distanzaObiettivo<-1 || distanzaObiettivo>1){//se non è ancora a meno di un metro dall'obiettivo
						//moto rettilineo uniforme
						vx=(obX-posX)/40;
						vy=(obY-posY)/40;
						vz=(obZ-posZ)/40;
						vu.at(i)->aggiornaPosizione(vx,vy,vz);
					}
					else{//se raggiunto, imposta booleano lo sgancio della bomba
						ottieniIndiciPalazzoSottoObiettivoUfo(i,obX,obZ);
						b->getObiettivo()->setAttivo(true);//raggiunto
						numeroUfoInObiettivo++;
						vu.at(i)->setSgancioBomba(true);//setta a true lo sgancio bomba
						//controllo se tutti gli ufo hanno raggiunto l'obiettivo e se vero, si rendono disponibili per un altro attacco
						if(numeroUfoInObiettivo==vu.size()){
							RaggiungimentoObiettiviAttacco=true;
							tempoInizioAttacco = tempo;//resetto il tempo inizio attacco, così lascio l'ufo spostarsi a zig zag per un pò prima di riattaccare, (il campo dati attacco dell'ufo è ancora a true, quindi si sposteranno a zig zag appena sganciata la bomba)
						}
					}
				}
			}
		}
	}
}

void Model::setVettTasti(int pos,bool value){
	vettTasti[pos]=value;
}

Terreno::Terreno* Model::getTerreno(){
	return t;
}

Cannone::Cannone* Model::getCannone(){
	return c;
}

Cittadella::Cittadella* Model::getCittadella(int i){
	return vcitt.at(i);
}

Ufo::Ufo* Model::getUfo(int i){
	return vu.at(i);
}

int Model::getNumeroUfo()const{
	return vu.size();
}

int Model::getNumeroCittadelle()const{
	return vcitt.size();
}

float Model::getOssX()const{
	return ossX;
}

float Model::getOssY()const{
	return ossY;
}

float Model::getOssZ()const{
	return ossZ;
}

float Model::getOssRotX()const{
	return ossRotX;
}

float Model::getOssRotY()const{
	return ossRotY;
}

float Model::getDistanzaMassimaVisuale()const{
	return distanza;
}

bool Model::isTextureAttive()const{
	return textureAttive;
}

void Model::setTextureAttive(bool b){
	textureAttive=b;
}

float Model::getTempoCorrenteDiCarica()const{
	return tempo-tempoInizioCarica;
}

bool Model::isFine()const{
	return fine;
}

int Model::getTipoFine()const{
	return tipoFine;
}

bool Model::isInizio()const{
	return inizio;
}

void Model::avviaGioco(){
	inizio=true;
}

bool Model::isTerrenoMinimale()const{
	return terrenoMinimale;
}

void Model::setTerrenoMinimale(bool b){
	terrenoMinimale=b;
}

bool Model::isHelpAttivo()const{
	return helpAttivo;
}

void Model::setHelpAttivo(bool b){
	helpAttivo=b;
}
