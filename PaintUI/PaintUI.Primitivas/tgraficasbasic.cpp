#include "Stdafx.h"
#include "tgraficasbasic.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

void setColor(float r, float g, float b){
	glColor3f(r, g, b);
}

void setColor(Color c){
	setColor((float)c.r / 255.0, (float)c.g / 255.0, (float)c.b / 255.0);
}

void setDefaultColor(){
	setColor(0.0, 0.0, 1.0);
}

Color getColor(int x, int y){
	Color c;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
	return c;
}

void getColors(const int width, const int height, Color colors[]){
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, colors);
}

void setColors(Color colors[], const int widht, const  int height){
	glDrawPixels(widht, height, GL_RGB, GL_UNSIGNED_BYTE, colors);
}

void printColor(Color c){
	cout << "r: " << (int)c.r << ", g: " << (int)c.g << ", b: " << (int)c.b << endl;
}

void drawPixel(int x, int y){
	glBegin(GL_POINTS); // primitiva grásfica a visualizar
		glVertex2i(x, y); // coordenas iniciales
	glEnd();
	//printf("%d,%d\n",x,y);
}

void drawPixel(Punto p){
	drawPixel(p.x, p.y);
}

void drawSquare(int x, int y){
	int tam = 20;
	glBegin(GL_QUADS); // primitiva grásfica a visualizar
	glVertex2i(x + tam, y + tam);
	glVertex2i(x + tam, y - tam);
	glVertex2i(x - tam, y - tam);
	glVertex2i(x - tam, y + tam);
	glEnd();
}

void drawPixel(Punto p, Color c){
	setColor(c);
	drawPixel(p);
}

void dibujarLineaMulti(int x0, int y0, int x1, int y1, bool temp, bool esCuadrado){
	int x, y, dx, dy, p, incE, incNE, stepx, stepy, cont = 0;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	/* determinar que punto usar para empezar, cual para terminar */
	if (y0 > y1) stepy = -1;
	else stepy = 1;

	if (x0 > x1) stepx = -1;
	else stepx = 1;

	x = x0;
	y = y0;
	++cont;
	if (esCuadrado)
		drawSquare(x, y);
	else
		drawPixel(x, y);
	/* se cicla hasta llegar al extremo de la línea */
	if (dx>dy){
		p = 2 * dy - dx;
		incE = 2 * dy;
		incNE = 2 * (dy - dx);
		while (x != x1){
			x = x + stepx;
			if (p < 0){
				p = p + incE;
			}
			else {
				y = y + stepy;
				p = p + incNE;
			}
			if (++cont % 10 > 5 || !temp){
				if (esCuadrado)
					drawSquare(x, y);
				else
					drawPixel(x, y);
			}
		}
	}
	else{
		p = 2 * dx - dy;
		incE = 2 * dx;
		incNE = 2 * (dx - dy);
		while (y != y1){
			y = y + stepy;
			if (p < 0){
				p = p + incE;
			}
			else {
				x = x + stepx;
				p = p + incNE;
			}
			if (++cont % 10 > 5 || !temp){
				if (esCuadrado)
					drawSquare(x, y);
				else
					drawPixel(x, y);
			}
		}
	}
}

void dibujarLinea(int x0, int y0, int x1, int y1, bool temp){
	dibujarLineaMulti(x0, y0, x1, y1, temp, FALSE);
}

void dibujarLinea(Punto p0, Punto p1, bool temp){
	dibujarLinea(p0.x, p0.y, p1.x, p1.y, temp);
}

void dibujarLineaCuadrados(int x0, int y0, int x1, int y1, bool temp){
	dibujarLineaMulti(x0, y0, x1, y1, temp, TRUE);
}

void dibujarLineaCuadrados(Punto p0, Punto p1, bool temp){
	dibujarLineaCuadrados(p0.x, p0.y, p1.x, p1.y, temp);
}

Punto polar(int xc, int yc, int r, float a){
	Punto punto;
	float radian;
	radian = 180.0 / M_PI;
	punto.x = xc + round(r*cos(a / radian));
	punto.y = yc + round(r*sin(a / radian));
	return punto;
}

void solidos(Punto c, int radio, int lados){
	float ang = 360.0 / lados, a;
	a = ang;
	Punto punto;
	Punto puntos[MAX_LADOS];
	int i;
	for (i = 0; i < lados; i++){
		punto = polar(c.x, c.y, radio, a);
		a += ang;
		puntos[i] = punto;
	}
	for (i = 0; i < lados / 1; i++)
		dibujarLinea(puntos[i].x, puntos[i].y, puntos[i + 1].x, puntos[i + 1].y, FALSE);
	dibujarLinea(puntos[i].x, puntos[i].y, puntos[0].x, puntos[0].y, FALSE);
}

void curva(Punto p0, Punto p1, Punto p2, Punto p3){
	double time;
	Punto p;
	for (time = 0; time <= 1.0; time += 0.001){
		p.x = pow(1 - time, 3) * p1.x +
			3 * time*pow(1 - time, 2) * p1.x +
			3 * pow(time, 2) *(1 - time) * p2.x +
			pow(time, 3) * p3.x;

		p.y = pow(1 - time, 3) * p1.y +
			3 * time*pow(1 - time, 2) * p1.y +
			3 * pow(time, 2) *(1 - time) * p2.y +
			pow(time, 3) * p3.y;
		drawPixel(p);
	}
}

float Distancia(Punto p1, Punto p2){
	float x = abs(p1.x - p2.x);
	float y = abs(p1.y - p2.y);
	float dist = sqrt(x*x + y*y);
	return dist;
}

float Angulo(Punto p1, Punto p2){
	Punto p;
	float ang;
	p.x = p2.x - p1.x;
	p.y = p2.y - p1.y;
	ang = atan((float)p.y / p.x) * 180.0 / M_PI;

	return ang;
}

float RandomAngle(){
	float f;
	f = rand() % 3601;
	f /= 10;
	return f;
}

float Randomradius(float maxR){
	float f;
	f = (maxR*(rand() % 1001) / 1000);
	return f;
}