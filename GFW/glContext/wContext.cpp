//Written and made by Michael Wright
#include <windows.h>
#include <iostream>
#include "wContext.h"
#include "glContext.h"

using namespace std;

///Necessary Globals!!/////////////////////////////////////////////////////
///Ugly as heck, FIX THIS SHIT
 int nxRez = 0, nyRez = 0;
 bool windowchange = false;

 bool MouseHLMBEven = false;
 int xPosLMBD = 0;
 int yPosLMBD = 0;
 bool keyPress[256];
 void nulls(){};//having difficulty
///Necessary Globals!!///////////////////////////////////////////////////



OpenGlRenderingContext::OpenGlRenderingContext(){//default constructor
    WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
                            0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
    if(RegisterClassEx(&wndclass) )
    {
        window = CreateWindowEx( 0, myclass, "SGF - MJ Wright" ,
                    WS_OVERLAPPEDWINDOW, 100, 100,
                   640, 470, 0, 0, GetModuleHandle(0), 0 ) ;

    }
}

OpenGlRenderingContext::OpenGlRenderingContext(int posx, int posy, int width, int height){//default constructor
    WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
                            0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
    if(RegisterClassEx(&wndclass) )
    {
        window = CreateWindowEx( 0, myclass, "SGF - MJ Wright",
                    WS_OVERLAPPEDWINDOW, posx, posy,
                   width, height, 0, 0, GetModuleHandle(0), 0 ) ;

    }
}
OpenGlRenderingContext::OpenGlRenderingContext(int posx, int posy, int width, int height, string wTitle){
 WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
                            0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
    if(RegisterClassEx(&wndclass) )
    {
        window = CreateWindowEx( 0, myclass, wTitle.c_str(),
                    WS_OVERLAPPEDWINDOW, posx, posy,
                   width, height, 0, 0, GetModuleHandle(0), 0 ) ;

    }


}
///Deconstructor
OpenGlRenderingContext::~OpenGlRenderingContext(){
    if (glEnabled)
        glContext.destroy();//only kill if was created sucessfully

}


void OpenGlRenderingContext::MainLoop(void (*routingtorun)(void)){///called when want to start application, sits in loop until exited
        if(window){
            ShowWindow( window, SW_SHOWDEFAULT ) ;
            MSG msg ;

            while (true){
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE )){
                    if ( msg.message == WM_QUIT ){
                        break;
                    }else{
                        TranslateMessage( &msg );
                        DispatchMessage( &msg );
                        }
                }else{//opengl code goes here
                    ///MainLoop function is called here
                    (*routingtorun)();//call the drawing routine continously

                    if ((keyHandling)!=NULL)
                        (keyHandling)(keyPress);

                    if ((resizer)!=NULL)
                        if(windowchange==true){
                            windowchange=false;
                            resizer(nxRez, nyRez);
                        }

                    ///MouseHandlingHere
                     if ((mouseHandlingLMBD)!=NULL)
                     {
                         if ((MouseHLMBEven==true)){
                             MouseHLMBEven = false;
                             (mouseHandlingLMBD)(xPosLMBD,yPosLMBD);

                         }
                     }

                    ///Refres/Update
                     wglSwapLayerBuffers( wHdc, WGL_SWAP_MAIN_PLANE );//SwapBuffers( GetDC(window) );//display to screen
                }
            }
        }
        else{
            cerr<<"Window Was not Created"<<endl;
        }



}


void OpenGlRenderingContext::MainLoop(){///called when want to start application, sits in loop until exited
   MainLoop(nulls);
}

void OpenGlRenderingContext::glinit(){
    glEnabled = true;//for destructor
    (keyHandling) = NULL;
    (resizer) = NULL;
    (mouseHandlingLMBD) = NULL;
    wHdc = glContext.init(window);

}

void OpenGlRenderingContext::glinit(void (*glsetup)()){
    glinit();
    (*glsetup)();//call the drawing routine continously
}

void OpenGlRenderingContext::setKeyHandler(void (*kh)(bool key[256])){
    (keyHandling) =(kh);
}


void OpenGlRenderingContext::setResizerHandler(void (*rz)(int xRez, int yRez)){
    (resizer) =(rz);
}

void OpenGlRenderingContext::setMouseHandlerLeftMouseButtonDown(void (*mh)(int xPos, int yPos)){
    (mouseHandlingLMBD) =(mh);
}

//handling the window and everything to do with it
bool KeyboardPress[256];///for keyboard input handling
long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
    switch(msg)
    {
        case WM_DESTROY:
            cout << "\nExiting Window Context...\n" ;
            PostQuitMessage(0) ;
            return 0 ;
        case WM_LBUTTONDOWN:
            MouseHLMBEven = true;
            xPosLMBD = ((int)LOWORD(lp));
            yPosLMBD = ((int)HIWORD(lp));
            //cout << "\nmouse left button down at (" << LOWORD(lp) << ',' << HIWORD(lp) << ")\n" ;
            return 0 ;
        case WM_KEYDOWN:
             keyPress[wp]=true;
           return 0 ;
		case WM_KEYUP:
            keyPress[wp]=false;
            return 0 ;
        case WM_SIZE:
                nxRez = LOWORD(lp);
                nyRez = HIWORD(lp);
                windowchange=true;
                //glViewport(0,0,LOWORD(lp),HIWORD(lp));//resizes window!///This should be done by the user
           return 0 ;

        default:
            return DefWindowProc( window, msg, wp, lp ) ;
    }
}
