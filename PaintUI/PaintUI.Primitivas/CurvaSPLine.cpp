#include "Stdafx.h"
#include "CurvaSPLine.h"

namespace PaintUIPrimitivas{

	void CurvaSPLine::setPoint(Punto p){
		switch (++state){
		case 1:
			p0 = p;
			break;
		case 2:
			p1 = p2 = p;
			break;
		case 3:
			p2 = p;
			break;
		}
	}

	void CurvaSPLine::setMovePoint(Punto p){
		switch (state){
		case 1:
			p1 = p2 = p3 = p;
			break;
		case 2:
			p1 = p2 = p;
			break;
		case 3:
			p2 = p;
			break;
		}
		if (DEBUG)
			cout << state << endl;
	}

	void CurvaSPLine::draw(){
		setDefaultColor();
		double time;
		Punto p;
		for (time = 0; time <= 1.0; time += 0.001){
			p.x =(int) (pow(1 - time, 3) * p0.x +
				3 * time*pow(1 - time, 2) * p1.x +
				3 * pow(time, 2) *(1 - time) * p2.x +
				pow(time, 3) * p3.x);

			p.y = (int) (pow(1 - time, 3) * p0.y +
				3 * time*pow(1 - time, 2) * p1.y +
				3 * pow(time, 2) *(1 - time) * p2.y +
				pow(time, 3) * p3.y);
			drawPixel(p);
		}
		if (DEBUG){
			dibujarLinea(p0, p1, TRUE);
			dibujarLinea(p0, p2, TRUE);
			dibujarLinea(p1, p3, TRUE);
			dibujarLinea(p2, p3, TRUE);
		}
	}

	void CurvaSPLine::reset(){
		state = 0;
	}
}