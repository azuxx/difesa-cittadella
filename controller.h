//controller.h
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "model.h"
#include "view.h"

class Controller{
	private:
		Model* model;
		View* view;
	public:
		Controller(Model*,View*);
		void rilascioTastoFreccia(int, int , int);
		void azioneTastoFreccia(int, int , int);
		void azioneTasto(unsigned char, int , int );
		void rilascioTasto(unsigned char, int, int);
};

#endif
