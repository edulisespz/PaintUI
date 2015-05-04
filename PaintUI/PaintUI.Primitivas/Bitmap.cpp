#include "stdafx.h"
#include "Bitmap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>



using namespace std;
namespace PaintUIPrimitivas{
	string ExePath() {
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		return string(buffer).substr(0, pos);
	}

	Bitmap::Bitmap(int width, int height)
	{

		_Path = ExePath() + "\\" + default_path;
		_height = height;
		_width = width;
		//ctor
	}

	Bitmap::Bitmap(string path, int width, int height){
		_Path = path;
		_height = height;
		_width = width;
	}

	Bitmap::~Bitmap()
	{
		deleteMemory();
	}

	void Bitmap::deleteMemory(){
		delete data;


	}

	void Bitmap::Save(){
		cout << "Guardando imagen en: " << _Path << endl;
		BITMAPFILEHEADER fileheader;
		BITMAPINFOHEADER infoheader;

		infoheader.biSize = sizeof(infoheader);
		infoheader.biWidth = _width;
		infoheader.biHeight = _height;
		infoheader.biPlanes = 1;
		infoheader.biBitCount = 24;
		infoheader.biCompression = BI_RGB;
		infoheader.biSizeImage = _width*_height * 3;
		infoheader.biXPelsPerMeter = 0;
		infoheader.biYPelsPerMeter = 0;
		infoheader.biClrUsed = 0;
		infoheader.biClrImportant = 0;

		fileheader.bfType = 0x4D42;
		fileheader.bfOffBits = sizeof(fileheader)+sizeof(infoheader);
		fileheader.bfSize = fileheader.bfOffBits + infoheader.biSizeImage;
		fileheader.bfReserved1 = 0;
		fileheader.bfReserved2 = 0;

		ofstream ofs(_Path.c_str(), ofstream::binary);
		ofs.write((char*)&fileheader, sizeof(BITMAPFILEHEADER));
		ofs.write((char*)&infoheader, sizeof(BITMAPINFOHEADER));
		ofs.write((char*)data, infoheader.biSizeImage);
		ofs.flush();
		ofs.close();
	}

	void Bitmap::Load(){
		cout << _Path << endl;

		ifstream ifs(_Path.c_str(), ifstream::binary);

		if (ifs.is_open()){
			char* temp = new char[sizeof(BITMAPFILEHEADER)];
			ifs.read(temp, sizeof(BITMAPFILEHEADER));
			BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)(temp);
			cout << "\n FILHEADER\n";
			cout << "\n File type: " << bfh->bfType << bfh->bfType << endl;
			cout << " File size: " << bfh->bfSize << endl;
			cout << " Offset(adress of beggining of the image information): " << bfh->bfOffBits << endl;
			// Reading information about BITMAPINFOHEADER
			temp = new char[sizeof(BITMAPINFOHEADER)];
			ifs.read(temp, sizeof(BITMAPINFOHEADER));
			BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(temp);

			cout << "\n INFOHEADER\n";
			cout << "\n Header size: " << bih->biSize << endl;
			cout << " Image width: " << bih->biWidth << endl;
			cout << " Image height: " << bih->biHeight << endl;
			cout << " Number of bytes for pixel: " << bih->biBitCount << endl;
			cout << " Used compression: " << bih->biCompression << endl;
			cout << " Image size: " << bih->biSizeImage << endl;
			cout << " Horizontal resolution: " << bih->biXPelsPerMeter << endl;
			cout << " Vertical resolution: " << bih->biYPelsPerMeter << endl;
			cout << " Number of colors in the color palette: " << bih->biClrUsed << endl;
			cout << " Number of important colors used: " << bih->biClrImportant << endl;

			ifs.seekg(bfh->bfOffBits);

			int size = bih->biSizeImage * 3;
			data = new unsigned char[size];
			ifs.read((char*)data, size);
			// cout<<data<<endl;

			ifs.close();

			delete bfh;
			delete bih;


		}
		else{
			cout << "Error abriendo el archivo" << endl;
		}


	}
}