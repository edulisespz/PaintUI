#ifndef BOTTLE_H
#define BOTTLE_H
#include "tgraficasbasic.h"
namespace PaintUIPrimitivas {
	class Bottle
	{
	public:
		int width, height;
		Color defaultColor;
		Bottle();
		virtual ~Bottle();
		void Paint(Punto p, Color c);
		void Paint(Punto p);
	protected:
	private:
	};

	

}

#endif // BOTTLE_H
