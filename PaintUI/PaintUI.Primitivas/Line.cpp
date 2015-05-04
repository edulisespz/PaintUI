#include "Stdafx.h"
#include "Line.h"
#include "tgraficasbasic.h"
using namespace PaintUIPrimitivas;
Line::Line()
{
    //ctor
	x1 = x2 = y1 = y2 = 0;
	
}

Line::~Line()
{
    //dtor
}

void Line::draw(){
        dibujarLinea(x1,y1,x2,y2,FALSE);
}

LineTool::LineTool(){
	draging = FALSE;
}
LineTool::~LineTool(){

}


void LineTool::MouseDown(int x, int y){
	draging = TRUE;
	x1 = x2 = x;
	y1 = y2 = y;

}

void LineTool::MouseDown(Punto p){
	MouseDown(p.x, p.y);
}

void LineTool::MouseUp(int x, int y){
	draging = FALSE;
	x2 = x;
	y2 = y;
}

void LineTool::MouseUp(Punto p){
	MouseUp(p.x, p.y);
}

void LineTool::MouseMove(int x, int y){
	if (draging){
		x2 = x;
		y2 = y;
	}
}

void LineTool::MouseMove(Punto p){
	MouseMove(p.x, p.y);
}