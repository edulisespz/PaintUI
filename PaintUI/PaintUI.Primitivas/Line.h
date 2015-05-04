#ifndef LINE_H
#define LINE_H
#include "tgraficasbasic.h"

namespace PaintUIPrimitivas{
	class Line {
	public:
		Line();
		~Line();
		int x1, y1, x2, y2;
		virtual void draw();
	};

	class LineTool :public Line{
	protected:
		bool draging;
	public:
		LineTool();
		virtual ~LineTool();
		void MouseDown(int x, int y);
		void MouseDown(Punto p);
		void MouseUp(int x, int y);
		void MouseUp(Punto p);
		void MouseMove(int x, int y);
		void MouseMove(Punto p);

	};
}


#endif // LINE_H
