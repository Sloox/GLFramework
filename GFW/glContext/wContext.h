/*  Written and made by Michael Wright
 Here lies the Window Context Generator,
 All Wrapped In a nice class

Basic Usage:
    Steps to get it all running
    1)Call Constructor To Init Winodw
    2)Call Glinit and place ur own GLinit function in the function call, must be void function ATM
    3)Add key handler, rezier, mousehandler functions to the classes
    4)Call Mainloop function, add glMainloop function of ur own or just call with no param

Basic .dll includes and other prerequisets
Please ensure the following is included
    1)glut32.dll is in bin folder-->omp
    2)libgomp-1.dll is in bin folder -->omp
    3)Check file locations so that there are no errors in linking
    4)

Compiler Options
-fexpensive-optimizations //FUNZIES
-msse4.1 //SSE
-fopenmp //OMP enable
-mstackrealign for SSE

Linker Options
			<Add library="opengl32" />
			<Add library="gdi32" />
			<Add library="Glu32" />
			<Add library="glut32" />
			<Add library="gomp" />

*/
#ifndef WCONTEXT_H_INCLUDED
#define WCONTEXT_H_INCLUDED

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "glContext.h"

using namespace std;





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* const myclass = "windowClass" ;//class of the window
long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp );//handles window stuff

class OpenGlRenderingContext{//creates a window32 window then creates a rendering context for opengl for that window

    public:
        OpenGlRenderingContext();//default overloaded constructor
        OpenGlRenderingContext(int posx, int posy, int width, int height);//Overloaded
        OpenGlRenderingContext(int posx, int posy, int width, int height, string wTitle);//Overloaded + title
        ~OpenGlRenderingContext();//default destructor

        //GL Init Functions, Pass a initializer function to initialize GL
        void glinit(void (*glsetup)());
        void glinit();

        ///Glut like stuff
        //Main Loop
        void MainLoop(void (*routingtorun)());//Main Loop
        void MainLoop();//Main Loop

        //KeyHandler
        void setKeyHandler(void (*kh)(bool key[256]));//Key Press hanlding


        //Resize Handler
        void setResizerHandler(void (*rz)(int xRes, int yRez));//Resize handler needs fix

        //Mouse Handler
        void setMouseHandlerLeftMouseButtonDown(void (*mh)(int xPos, int yPos));


    private:
        openGLContext glContext;
        bool glEnabled;
        HWND window;
        HDC wHdc;

        void (*resizer)(int xRes, int yRez);
        void (*keyHandling)(bool key[256]);
        void (*mouseHandlingLMBD)(int xPos, int yPos);



};





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // WCONTEXT_H_INCLUDED
