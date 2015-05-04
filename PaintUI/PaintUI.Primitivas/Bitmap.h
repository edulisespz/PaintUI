#ifndef BITMAP_H
#define BITMAP_H
#include <string>

using namespace std;

namespace PaintUIPrimitivas {
	const string default_path = "default.bmp";
	const int defWidth = 400, defHeight = 400;
	string ExePath();
	class Bitmap
	{
	public:
		Bitmap(int width = defWidth, int height = defHeight);
		Bitmap(string path, int width = defWidth, int height = defHeight);
		virtual ~Bitmap();
		string GetPath() { return _Path; }
		void SetPath(string val) { _Path = val; }
		void Load();
		void Save();
		unsigned char* GetData(){ return data; };
		void SetData(unsigned char* val){ data = val; }
		int GetWidth(){ return _width; }
		void SetWidth(int val){ _width = val; }
		int GetHeight(){ return  _height; }
		void SetHeight(int val){ _height = val; }
	protected:
	private:
		string _Path;
		void deleteMemory();
		unsigned char* data;
		int _width, _height;
	};



}
#endif // BITMAP_H
