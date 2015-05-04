#include "stdafx.h"
#include "Bottle.h"
#include <queue>

using namespace PaintUIPrimitivas;

Bottle::Bottle()
{
	//ctor
	width = height = 400;
	defaultColor.r = 255;
	defaultColor.g = 0;
	defaultColor.b = 0;
}

Bottle::~Bottle()
{
	//dtor
}

void Bottle::Paint(Punto p, Color c){
	defaultColor = c;
	Paint(p);
}

void Bottle::Paint(Punto p){
	vector<Color> colors(width*height);
	getColors(width, height, colors.data());
	Color fondo = colors[p.y*width + p.x];
	queue<Punto> colapuntos;
	colapuntos.push(p);
	while (colapuntos.size() > 0){
		Punto punto = colapuntos.front();
		colapuntos.pop();
		Color c = colors[punto.y*width + punto.x];
		if (fondo == c && c != defaultColor){
			colors[punto.y*width + punto.x] = defaultColor;//pintar
			punto.x++;
			if (punto.x >= 0 && punto.x < width){
				colapuntos.push(punto);
			}
			punto.x -= 2;
			if (punto.x >= 0 && punto.x < width){
				colapuntos.push(punto);
			}
			punto.x++;
			punto.y++;
			if (punto.y < height && punto.y >= 0){
				colapuntos.push(punto);
			}
			punto.y -= 2;
			if (punto.y < height && punto.y >= 0){
				colapuntos.push(punto);
			}
		}
	}
	setColors(colors.data(), width, height);
}
