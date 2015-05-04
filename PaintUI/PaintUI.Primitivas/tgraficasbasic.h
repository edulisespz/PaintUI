#ifndef TGRAFICASBASIC_H_INCLUDED
#define TGRAFICASBASIC_H_INCLUDED

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include "Punto.h"

#define MAX_LADOS 100
#define FALSE 0
#define TRUE 1
#define M_PI 3.14159265358979323846
#define DEBUG FALSE

using namespace std;
using namespace PaintUIPrimitivas;



namespace PaintUIPrimitivas{
	enum ToolType {
		EraserTool,
		PencilTool,
		SprayTool,
		BottleTool,
		CircleToolType,
		SPLineTool,
		ElipseToolType,
		LineToolType,
		PolygonToolType,
	};
	struct Color {
		unsigned char r, g, b;
		bool operator == (const Color &c2){
			return (r == c2.r && g == c2.g && b == c2.b);
		}
		bool operator != (const Color &c2){
			return (r != c2.r || g != c2.g || b != c2.b);
		}
	};
	class ToolControl{
	public:
		virtual void MouseUp(Punto p){}
		virtual void MouseDown(Punto p){}
		virtual void MouseMove(Punto p){}
	};
}



void setColor(float r, float g, float b);
void setColor(Color c);
void setDefaultColor();
Color getColor(int x, int y);
void getColors(const int width, const int height, Color colors[]);
void setColors(Color colors[], const int widht, const  int height);
void printColor(Color c);
void drawPixel(int x, int y);
void drawPixel(Punto p);
void drawSquare(int x, int y);
void drawPixel(Punto p, Color c);
void dibujarLineaMulti(int x0, int y0, int x1, int y1, bool temp, bool esCuadrado);
void dibujarLinea(int x0, int y0, int x1, int y1, bool temp);
void dibujarLinea(Punto p0, Punto p1, bool temp);
void dibujarLineaCuadrados(int x0, int y0, int x1, int y1, bool temp);
void dibujarLineaCuadrados(Punto p0, Punto p1, bool temp);
Punto polar(int xc, int yc, int r, float a);
void solidos(Punto c, int radio, int lados);
void curva(Punto p0, Punto p1, Punto p2, Punto p3);
float Distancia(Punto p1, Punto p2);
float Angulo(Punto p1, Punto p2);
float RandomAngle();
float Randomradius(float maxR);



#endif // TGRAFICASBASIC_H_INCLUDED
