#ifndef ERASER_H
#define ERASER_H

#include "Pencil.h"

namespace PaintUIPrimitivas{
	class Eraser :public Pencil{
	public:
		Eraser();
		virtual ~Eraser();
		int tam = 10;
		void draw();

	};
}


#endif // ERASER_H
