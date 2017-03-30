#ifndef GLCONTEXT_H_INCLUDED
#define GLCONTEXT_H_INCLUDED


///Setup a basic GLContext

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>



class openGLContext//inline to hopefully minimuze it all
{
public:

    openGLContext()
    {
        mhWnd = NULL;
        mhDC = NULL;
        mhRC = NULL;
    }

    ~openGLContext()
    {
        destroy();
    }

    HDC init(HWND hWnd)//inline to speed up the context
    {
        // remember the window handle (HWND)
        mhWnd = hWnd;

        // get the device context (DC)
        mhDC = GetDC(mhWnd);

        // set the pixel format for the DC
        PIXELFORMATDESCRIPTOR pfd;
        ZeroMemory(&pfd, sizeof(pfd));///used to be calloc...
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 24;
        pfd.cDepthBits = 16;
        pfd.iLayerType = PFD_MAIN_PLANE;
        int format = ChoosePixelFormat( mhDC, &pfd );
        SetPixelFormat( mhDC, format, &pfd );

        // create the render context
        mhRC = wglCreateContext( mhDC );

        // make it the current render context
        wglMakeCurrent(mhDC, mhRC);///Can be used to switch context if neceessary
        return mhDC;
    }

    void destroy()///cleanup for gl window
    {
        if (mhRC){
            wglMakeCurrent( NULL, NULL );
            wglDeleteContext( mhRC );
        }
        if (mhWnd && mhDC)
        {
            ReleaseDC( mhWnd, mhDC );
        }
        mhWnd = NULL;
        mhDC = NULL;
        mhRC = NULL;
    }

private:
    HWND mhWnd;
    HDC mhDC;
    HGLRC mhRC;

};

#endif // GLCONTEXT_H_INCLUDED
