#include "Stdafx.h"
#include "Circulo.h"
#include <iostream>

using namespace std;
using namespace PaintUIPrimitivas;

PaintUIPrimitivas::Circulo::Circulo()
{
    //ctor
}

PaintUIPrimitivas::Circulo::~Circulo()
{
    //dtor
}


void PaintUIPrimitivas::Circulo::draw(){
    if(!temp)
        drawMidpoint();
    else
        drawPolar();
}

void PaintUIPrimitivas::Circulo::drawMidpoint(){
    int p;
    Punto coord;
    coord.x = 0;
    coord.y = r ;
    int acc=1;
    drawMidpointTranslated(coord);
    p = 1 -r;
    while(coord.x < coord.y){
        if(p < 0){
            coord.x++;
            p += 2 * coord.x + 1;
        }else{
            coord.x++;
            coord.y --;
            p+= 2 * (coord.x -coord.y) +1;
        }
        if(++acc%10<5||!temp)
            drawMidpointTranslated(coord);
    }
}



void PaintUIPrimitivas::Circulo::drawPolar(){
    //float inc=180.0/(M_PI*r);
    float i;
    Punto punto;

    int acc=0;
    for(i=0;i<360;i++)
    {

        if((acc++)%10>=5 || !temp){
            punto = polar(centro.x,centro.y,r,i);
            drawPixel(punto);
            if(DEBUG){
                cout<<"x:"<<punto.x<<", y:"<<punto.y<<endl;

            }
        }
    }
}

void PaintUIPrimitivas::Circulo::drawMidpointTranslated(Punto p){
    drawPixel(centro.x+p.x,centro.y+p.y);
    drawPixel(centro.x-p.x,centro.y+p.y);
    drawPixel(centro.x+p.x,centro.y-p.y);
    drawPixel(centro.x-p.x,centro.y-p.y);
    drawPixel(centro.x+p.y,centro.y+p.x);
    drawPixel(centro.x-p.y,centro.y+p.x);
    drawPixel(centro.x+p.y,centro.y-p.x);
    drawPixel(centro.x-p.y,centro.y-p.x);

}


void CircleTool::MouseDown(Punto p){
	draging = TRUE;
	centro = p;
	temp = TRUE;
}

void CircleTool::MouseMove(Punto p){
	if (draging){
		r = Distancia(centro, p);
	}

}

void CircleTool::MouseUp(Punto p){
	draging = FALSE;
	r = Distancia(centro, p);
	temp = FALSE;
}