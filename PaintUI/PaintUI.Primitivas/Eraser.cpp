#include "Stdafx.h"
#include "Pencil.h"
#include "Eraser.h"

using namespace PaintUIPrimitivas;

Eraser::Eraser()
{
	//ctor
}

Eraser::~Eraser()
{
	//dtor
}

void Eraser::draw(){
	setColor(0.0, 0.0, 1.0);
	if (puntos.size() >= 2){
		unsigned int i;
		Punto p0, p1;
		for (i = 0; i < puntos.size() - 1; i++){
			p0 = puntos[i];
			p1 = puntos[i + 1];
			dibujarLineaCuadrados(p0, p1, FALSE);
		}
	}
}
