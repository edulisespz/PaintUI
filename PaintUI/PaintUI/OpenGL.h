#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ctime>
#include <vector>
#include "tgraficas.h"
#include "Line.h"
#define DEBUG TRUE

using namespace System;
using namespace System::Windows::Forms;
using namespace PaintUIPrimitivas;

vector<float> colorArray;
int width, height;

namespace OpenGLForm 
{
	public ref class COpenGL: public System::Windows::Forms::NativeWindow
	{
	public:
		COpenGL(System::Windows::Forms::Form ^ parentForm,int posX,int posY, GLsizei iWidth, GLsizei iHeight)
		{
			CreateParams^ cp = gcnew CreateParams;

			// Set the position on the form
			cp->X = posX;
			cp->Y = posY;
			cp->Height = iHeight;
			cp->Width = iWidth;
			colorArray.resize(iWidth*iHeight);
			width = iWidth;
			height = iHeight;
			// Specify the form as the parent.
			cp->Parent = parentForm->Handle;

			// Create as a child of the specified parent and make OpenGL compliant (no clipping)
			cp->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

			// Create the actual window
			this->CreateHandle(cp);

			m_hDC = GetDC((HWND)this->Handle.ToPointer());

			line = new LineTool;
			circle = new CircleTool;
			elipse = new ElipseTool;
			polygon = new PolygonTool;

			if(m_hDC)
			{
				MySetPixelFormat(m_hDC);
				ReSizeGLScene(iWidth, iHeight);
				InitGL();
			}			
		}


		System::Void Render(System::Void)
		{
				glClear(GL_COLOR_BUFFER_BIT);
				glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
				setColor(primary);
				switch (activeTool)
				{
					case LineToolType:
						line->draw();
						break;
					case CircleToolType:
						circle->draw();
						break;
					case ElipseToolType:
						elipse->draw();
						break;
					case PolygonToolType:
						polygon->draw();
						break;
				}
				
	
									// Decrease the rotation variable for the quad

		
		}

		System::Void SwapOpenGLBuffers(System::Void)
		{
			SwapBuffers(m_hDC) ;
		}

		System::Void ChangeTool(System::Int32 tool){
			activeTool = tool;
		}
		System::Void ChangeSidesNumber(System::Int32 sides){
			polygon->lados = sides;
		}
	private:
		HDC m_hDC;
		HGLRC m_hglrc;
		LineTool *line;
		CircleTool* circle;
		ElipseTool* elipse;
		PolygonTool* polygon;
		
		Boolean draging;
		int activeTool;
	protected:
		~COpenGL(System::Void)
		{
			this->DestroyHandle();
			delete line;
		}

		GLint MySetPixelFormat(HDC hdc)
		{
			static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
				{
					sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
					1,											// Version Number
					PFD_DRAW_TO_WINDOW |						// Format Must Support Window
					PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
					PFD_DOUBLEBUFFER,							// Must Support Double Buffering
					PFD_TYPE_RGBA,								// Request An RGBA Format
					16,										// Select Our Color Depth
					0, 0, 0, 0, 0, 0,							// Color Bits Ignored
					0,											// No Alpha Buffer
					0,											// Shift Bit Ignored
					0,											// No Accumulation Buffer
					0, 0, 0, 0,									// Accumulation Bits Ignored
					16,											// 16Bit Z-Buffer (Depth Buffer)  
					0,											// No Stencil Buffer
					0,											// No Auxiliary Buffer
					PFD_MAIN_PLANE,								// Main Drawing Layer
					0,											// Reserved
					0, 0, 0										// Layer Masks Ignored
				};
			
			GLint  iPixelFormat; 
		 
			// get the device context's best, available pixel format match 
			if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
			{
				MessageBox::Show("ChoosePixelFormat Failed");
				return 0;
			}
			 
			// make that match the device context's current pixel format 
			if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
			{
				MessageBox::Show("SetPixelFormat Failed");
				return 0;
			}

			if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
			{
				MessageBox::Show("wglCreateContext Failed");
				return 0;
			}

			if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				MessageBox::Show("wglMakeCurrent Failed");
				return 0;
			}


			return 1;
		}

		bool InitGL(GLvoid)										// All setup for opengl goes here
		{
			srand(time(NULL));
			glClearColor(1.0, 1.0, 1.0, 0.0); // se establece el color de la ventana de visualización
			glMatrixMode(GL_PROJECTION); // proyección ortogonal en una zona rectangular bidimensional
			glClear(GL_COLOR_BUFFER_BIT);
			glReadPixels(0.0, 0.0, width, height, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
			//glutSwapBuffers();
			//glReadPixels( 0.0, 0.0,wSizeX,wSizeY,GL_RGB,GL_UNSIGNED_BYTE,colorArray);
			return TRUE;										// Initialisation went ok
		}

		GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize and initialise the gl window
		{
			if (height==0)										// Prevent A Divide By Zero By
			{
				height=1;										// Making Height Equal One
			}

			glViewport(0,0,width,height);						// Reset The Current Viewport

			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix

			// Calculate The Aspect Ratio Of The Window
			gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glLoadIdentity();									// Reset The Modelview Matrix

			colorArray.resize(width*height, 1.0);

			glViewport(0, 0, width, height); //NEW
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0, width, height, 0);
		}

	public:

		Void PanelMouseDown(Object^ sender, MouseEventArgs^ e){
			//System::Diagnostics::Debug::WriteLine("Mouse down");
			Punto p(e->X, e->Y);
			switch (activeTool){
			case LineToolType://Mouse
				line->MouseDown(p);
				break;
			case CircleToolType://circle
				circle->MouseDown(p);
				break;
			case ElipseToolType://elipse
				elipse->MouseDown(p);
				break;
			case PolygonToolType:
				polygon->MouseDown(p);
				break;
			}
			
		}
		Void PanelMouseUp(Object^ sender, MouseEventArgs^ e){
			//System::Diagnostics::Debug::WriteLine("Mouse up");
			Punto p(e->X, e->Y);
			switch (activeTool){
				case LineToolType://Mouse
					line->MouseUp(p);
					break;
				case CircleToolType://circle
					circle->MouseUp(p);
					glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
					circle->draw();
					glFlush();
					break;
				case ElipseToolType:
					elipse->MouseUp(p);
					glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
					elipse->draw();
					glFlush();
					break;
				case PolygonToolType:
					polygon->MouseUp(p);
					glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
					polygon->draw();
					glFlush();
					break;
			}
			glReadPixels(0.0, 0.0, width, height, GL_RGB, GL_UNSIGNED_BYTE, colorArray.data());
			

		}
		Void PanelMouseMove(Object^ sender, MouseEventArgs^ e){
			//System::Diagnostics::Debug::WriteLine("Mouse move");
			Punto p(e->X, e->Y);
			switch (activeTool){
				case LineToolType://Mouse
					line->MouseMove(p);
					break;
				case CircleToolType://circle
					circle->MouseMove(p);
					break;
				case ElipseToolType://elipse
					elipse->MouseMove(p);
					break;
				case PolygonToolType:
					polygon->MouseMove(p);
					break;
			}
		}
	};


}