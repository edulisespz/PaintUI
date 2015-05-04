#ifndef POLIGONO_H
#define POLIGONO_H
#include "tgraficasbasic.h"
namespace PaintUIPrimitivas{
	class Poligono{
	public:
		Punto centro;
		int lados=3;
		int radio=0;
		bool temp = FALSE;
		float anguloInicial = 0;
		void draw();
	};

	class PolygonTool : public Poligono, public ToolControl{
	private:
		bool draging = FALSE;
	public:
		virtual void MouseDown(Punto p) override;
		virtual void MouseUp(Punto p) override;
		virtual void MouseMove(Punto p) override;
	};
}
#endif