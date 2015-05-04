#ifndef CIRCULO_H
#define CIRCULO_H
#include "tgraficasbasic.h"

namespace PaintUIPrimitivas{
	class Circulo{
		public:
			Circulo();
			virtual ~Circulo();
			Punto centro;
			int r;
			bool temp = FALSE;
			void draw();
			void drawMidpoint();
			void drawMidpointTranslated(Punto p);
			void drawPolar();
	};

	class CircleTool :public Circulo, public ToolControl{
	private:
		bool draging = FALSE;
	public:
		virtual void MouseDown(Punto p) override;
		virtual void MouseUp(Punto p) override;
		virtual void MouseMove(Punto p) override;

	};
}
#endif // CIRCULO_H
