#include "Stdafx.h"
#include "Elipse.h"

using namespace PaintUIPrimitivas;

void Elipse::drawPointTranslated(Punto p){
	drawPixel(centro.x + p.x, centro.y + p.y);
	drawPixel(centro.x - p.x, centro.y + p.y);
	drawPixel(centro.x + p.x, centro.y - p.y);
	drawPixel(centro.x - p.x, centro.y - p.y);
}

void Elipse::drawPolar(){
	float q = (float) (2.0*M_PI / 360.0);
	int acc = 1;
	for (float i = 0; i < 2 * M_PI; i += q){
		if (++acc % 10<5 || !temp){
			drawPixel(centro.x + (int)((float)rx*cos(i)), centro.y + (int)((float)ry*sin(i)));
			drawPixel(centro.x + (int)((float)-rx*cos(i)), centro.y + (int)((float)ry*sin(i)));
			drawPixel(centro.x + (int)((float)rx*cos(i)), centro.y + (int)((float)-ry*sin(i)));
			drawPixel(centro.x + (int)((float)-rx*cos(i)), centro.y + (int)((float)-ry*sin(i)));
		}
	}
}

void Elipse::draw(){
	if (temp)
		drawPolar();
	else
		drawMidpoint();
}

void Elipse::drawMidpoint(){

	Punto punto;
	int p, px, py;
	double ry2, rx2, tworx2, twory2;

	ry2 = (double)ry*ry;
	rx2 = (double)rx*rx;

	twory2 = 2 * ry2;
	tworx2 = 2 * rx2;
	//region 1
	punto.x = 0;
	punto.y = ry;
	drawPointTranslated(punto);


	p = (int)ceil(ry2 - rx2*ry + (0.25*rx2));
	px = 0;
	py =(int) tworx2*punto.y;

	while (px<py)
	{
		punto.x++;
		px += (int)twory2;
		if (p >= 0)
		{
			punto.y--;
			py -= (int)tworx2;
		}
		if (p<0)
		{
			p +=(int) ry2 + px;
		}
		else{
			p += (int) ry2 + px - py;
		}
		drawPointTranslated(punto);

	}

	//region 2
	p = (int) ceil(ry2*(punto.x + 0.5)*(punto.x + 0.5) + rx2*(punto.y - 1)*(punto.y - 1) - rx2*ry2);
	while (punto.y>0)
	{
		punto.y--;
		py -= (int) tworx2;
		if (p <= 0)
		{
			punto.x++;
			px += (int) twory2;
		}
		if (p>0)
		{
			p += (int) rx2 - py;
		}
		else{
			p +=(int) rx2 - py + px;
		}
		drawPointTranslated(punto);
	}
}

void ElipseTool::MouseDown(Punto p){
	draging = TRUE;
	temp = TRUE;
	centro = p;
}

void ElipseTool::MouseMove(Punto p){
	if (draging){
		rx = abs(centro.x - p.x);
		ry = abs(centro.y - p.y);
	}
}

void ElipseTool::MouseUp(Punto p){
	draging = FALSE;
	rx = abs(centro.x - p.x);
	ry = abs(centro.y - p.y);
	temp = FALSE;
}