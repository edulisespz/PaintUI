#include "ToolsWindow.h"
#include <Windows.h>
#include <GL\glu.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
//#include "tgraficas.h"
//#include "Eraser.h"
//#include "Pencil.h"
//#include "Spray.h"
//#include "Bottle.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace PaintUIPrimitivas;

#define DEBUG FALSE

using namespace std;


//int width = 400, heigh = 400;
//vector<float> colorArray(width*heigh);
//int toolNumber = 1;

//Eraser eraser; //tool 1
//Pencil pencil; //tool 2
//Spray spray; //tool 3
//Bottle bottle; //tool 4

//void mouse_startTool(Punto p, int toolNumber);
//void mouse_moveTool(Punto p, int toolNumber);
//void mouse_endTool(Punto p, int toolNumber);
//void display_tool(int toolNumber);
//void timerFunc(int);
//int select_tool();
//
//void init(void)
//{
//	srand(time(NULL));
//	glClearColor(1.0, 1.0, 1.0, 0.0); // se establece el color de la ventana de visualización
//	glMatrixMode(GL_PROJECTION); // proyección ortogonal en una zona rectangular bidimensional
//	gluOrtho2D(0.0, width, heigh, 0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glReadPixels(0.0, 0.0, width, heigh, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
//	//glutSwapBuffers();
//	//glReadPixels( 0.0, 0.0,wSizeX,wSizeY,GL_RGB,GL_UNSIGNED_BYTE,colorArray);
//}
//
//void resize(int w, int h)
//{
//	width = w;
//	heigh = h;
//	colorArray.resize(width*heigh, 1.0);
//	bottle.height = h;
//	bottle.width = w;
//	glViewport(0, 0, w, h); //NEW
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0, w, h, 0);
//
//}
//
//void display(void) {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glDrawPixels(width, heigh, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
//	display_tool(toolNumber);
//	glFlush();
//	//glutSwapBuffers();
//}
//void onMouse(int button, int state, int x, int y) {
//	Punto p;
//	p.x = x;
//	p.y = y;
//	if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
//		if (DEBUG)
//			cout << "left-down" << endl;
//		glReadPixels(0.0, 0.0, width, heigh, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
//		mouse_startTool(p, toolNumber);
//	}
//	if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_UP)){
//		if (DEBUG)
//			cout << "left-up" << endl;
//		mouse_endTool(p, toolNumber);
//
//	}
//}
//void onMotion(int x, int y) {
//	Punto p;
//	p.x = x;
//	p.y = y;
//	glReadPixels(0.0, 0.0, width, heigh, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
//	mouse_moveTool(p, toolNumber);
//	glFlush();
//	glutPostRedisplay();
//
//}
//
//void mouse_startTool(Punto p, int toolNumber){
//	switch (toolNumber){
//	case 1://eraser
//		eraser.newLine(p);
//		eraser.nextPoint(p);
//		glutPostRedisplay();
//		break;
//	case 2: //pencil
//		pencil.newLine(p);
//		pencil.nextPoint(p);
//		glutPostRedisplay();
//		break;
//	case 3:
//		spray.nextPoint(p);
//		spray.startPresded();
//		spray.draw();
//		glFlush();
//		glutTimerFunc(spray.milis, timerFunc, 0);
//		break;
//	}
//}
//
//void mouse_endTool(Punto p, int toolNumber){
//	switch (toolNumber){
//	case 1://eraser
//
//		break;
//	case 2: //pencil
//
//		break;
//	case 3://spray
//
//		spray.endPressed();
//		break;
//	case 4:
//		bottle.Paint(p);
//		glFlush();
//		glReadPixels(0.0, 0.0, width, heigh, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
//		break;
//	}
//}
//
//void mouse_moveTool(Punto p, int toolNumber){
//	switch (toolNumber){
//	case 1:
//		eraser.nextPoint(p);
//		eraser.draw();
//		break;
//	case 2:
//		pencil.nextPoint(p);
//		pencil.draw();
//		break;
//	case 3:
//		spray.nextPoint(p);
//		break;
//	}
//}
//
//void display_tool(int toolNumber){
//	switch (toolNumber){
//	case 1: //eraser
//		eraser.draw();
//		break;
//	case 2://pencil
//		pencil.draw();
//		break;
//	case 3://spray
//		if (spray.isPressed())
//			spray.draw();
//		break;
//	}
//}
//
//int select_tool(){
//	int ntool = 0;
//	string val;
//	do{
//		stringstream  ss;
//		cout << "Seleccione la herramienta: " << endl;
//		cout << "\t[1] Borrador" << endl;
//		cout << "\t[2] L" << (char)160 << "piz" << endl;
//		cout << "\t[3] Spray" << endl;
//		getline(cin, val);
//		ss << val;
//		ss >> ntool;
//		cout << "Escogida: " << ntool << endl;
//	} while (ntool<1 || ntool>3);
//	return ntool;
//}
//
//void timerFunc(int value){
//	if (DEBUG)
//		cout << ".";
//	if (spray.isPressed()){
//		glReadPixels(0.0, 0.0, width, heigh, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
//		spray.draw();
//		glFlush();
//		if (spray.isPressed())
//			glutTimerFunc(spray.milis, timerFunc, 0);
//	}
//}
//
//void onKeyboard(unsigned char key, int x, int y){
//	switch (key){
//	case 27:
//	case 'q':
//		exit(0);
//		break;
//	case '1':
//		toolNumber = 1;
//		if (DEBUG)
//			cout << "Borrador " << endl;
//		break;
//	case '2':
//		toolNumber = 2;
//		if (DEBUG)
//			cout << "Lapiz " << endl;
//		break;
//	case '3':
//		toolNumber = 3;
//		if (DEBUG)
//			cout << "Spray " << endl;
//		break;
//	case '4':
//		toolNumber = 4;
//		if (DEBUG)
//			cout << "Bottle " << endl;
//		break;
//
//	}
//}
//
//int mainglut()
//{
//
//	glutInitDisplayMode( /*GLUT_DOUBLE | */GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(width, heigh);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Area de dibujo");
//	glutReshapeFunc(resize);
//	init();
//	glutDisplayFunc(display);
//	glutMouseFunc(onMouse);
//	glutMotionFunc(onMotion);
//	glutKeyboardFunc(onKeyboard);
//	glutMainLoop();
//	return 0;
//}


System::Void PaintUI::ToolsWindow::label1_Click(System::Object^  sender, System::EventArgs^  e) {
	dlgColor->ShowDialog();
	System::Drawing::Color color = dlgColor->Color;
	((System::Windows::Forms::Label^)sender)->BackColor = color;
	//actualiza color primario
	primary.r = label1->BackColor.R;
	primary.g = label1->BackColor.G;
	primary.b = label1->BackColor.B;
	//actualiza color secundario
	secondary.r = label2->BackColor.R;
	secondary.g = label2->BackColor.G;
	secondary.b = label2->BackColor.B;
}

[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	//TestForma es el nombre del proyecto
	//mainglut();
	Application::Run(gcnew PaintUI::ToolsWindow());


}