#ifndef ELIPSE_H
#define ELIPSE_H
#include "tgraficasbasic.h"

namespace PaintUIPrimitivas{
	class Elipse{
		public:
			Punto centro;
			int rx, ry;
			bool temp = FALSE;
			void draw();
			void drawMidpoint();
			void drawPointTranslated(Punto p);
			void drawPolar();
	};
	class ElipseTool : public Elipse, public ToolControl{
	private:
		bool draging = FALSE;
	public:
		virtual void MouseDown(Punto p) override;
		virtual void MouseUp(Punto p) override;
		virtual void MouseMove(Punto p) override;
	};
}
#endif // ELIPSE_H
