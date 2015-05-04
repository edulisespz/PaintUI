#ifndef SPRAY_H
#define SPRAY_H
#include "tgraficasbasic.h"
#include "Pencil.h"


namespace PaintUIPrimitivas{

	class Spray : public Pencil{
	private:
		int state = 0;
	public:
		Spray();
		virtual ~Spray();
		int density = 50, milis = 100, radius = 30;
		bool isPressed();
		void startPresded();
		void endPressed();
		void draw();
		void nextPoint(Punto p);
	};
}


#endif // SPRAY_H
