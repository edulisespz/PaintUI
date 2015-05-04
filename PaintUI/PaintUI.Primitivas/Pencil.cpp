#include "Stdafx.h"
#include "Pencil.h"

using namespace PaintUIPrimitivas;

Pencil::Pencil()
{
	//ctor
}

Pencil::~Pencil()
{
	//dtor
}

void Pencil::draw(){
	setColor(1.0, 0.0, 1.0);
	if (puntos.size() >= 2){
		unsigned int i;
		Punto p0, p1;
		for (i = 0; i < puntos.size() - 1; i++){
			p0 = puntos[i];
			p1 = puntos[i + 1];
			dibujarLinea(p0, p1, FALSE);
		}
	}
}

void Pencil::newLine(Punto p){
	puntos.clear();
	puntos.push_back(p);
}

void Pencil::nextPoint(Punto p){
	puntos.push_back(p);
}


