#ifndef PENCIL_H
#define PENCIL_H
#include <vector>
#include "tgraficasbasic.h"
using namespace std;

namespace PaintUIPrimitivas{
	class Pencil {
	protected:
		vector<Punto> puntos;
	public:
		Pencil();
		virtual ~Pencil();
		virtual void draw();
		virtual void nextPoint(Punto p);
		virtual void newLine(Punto p);
	};

}

#endif // PENCIL_H
