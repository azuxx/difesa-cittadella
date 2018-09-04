//obiettivo.h
#ifndef OBIETTIVO_H_
#define OBIETTIVO_H_


class Obiettivo{
	private:
		float obx;
		float oby;
		float obz;
		bool attivo;

	public:
		Obiettivo(float,float,float);
		float getXObiettivo()const ;
		float getYObiettivo()const ;
		float getZObiettivo()const ;
		bool isAttivo()const;
		void setAttivo(bool);
};

#endif
