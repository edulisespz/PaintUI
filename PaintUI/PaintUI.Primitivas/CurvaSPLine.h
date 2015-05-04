#ifndef CURVASPLINE_H
#define CURVASPLINE_H
#include "tgraficasbasic.h"
namespace PaintUIPrimitivas{
	class CurvaSPLine{
	public:
		int state = 0;
		Punto p0, p1, p2, p3;
		void setPoint(Punto p);
		void setMovePoint(Punto p);
		void draw();
		void reset();
	};
}

#endif