#include "Stdafx.h"
#include "Poligono.h"

using namespace PaintUIPrimitivas;

void Poligono::draw(){
	float ang = 360.0 / lados, a;
	a = anguloInicial;
	Punto punto;
	Punto puntos[MAX_LADOS];
	int i;
	for (i = 0; i < lados; i++){
		punto = polar(centro.x, centro.y, radio, a);
		a += ang;
		puntos[i] = punto;
	}
	for (i = 0; i < lados - 1; i++)
		dibujarLinea(puntos[i].x, puntos[i].y, puntos[i + 1].x, puntos[i + 1].y, temp);
	dibujarLinea(puntos[i].x, puntos[i].y, puntos[0].x, puntos[0].y, temp);
}

void PolygonTool::MouseDown(Punto p){
	draging = TRUE;
	temp = TRUE;
	centro = p;
	
}
void PolygonTool::MouseMove(Punto p){
	if (draging){
		radio = Distancia(centro, p);
		anguloInicial = Angulo(centro, p);
	}
}
void PolygonTool::MouseUp(Punto p){
	draging = FALSE;
	temp = FALSE;
	radio = (int)Distancia(centro, p);
	anguloInicial = Angulo(centro, p);
}