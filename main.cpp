#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

///Necessary Includes
#include <iostream>
#include <gl/gl.h>
#include <cstdlib>
#include <stdio.h>
#include "GFW/glContext/wContext.h"


///GPU Wrapper
#include "GFW/gpuHandler/glShaderWrapper.h"

///Project Includes
//#include "Projects/Parallel/MandleStart.h" //Parallel Project Implementation include start it with : StartParallelProject();

///Put Your Own Includes here

using namespace std;
//StartHere


int main()
{
    SGFShaderWrapper SW;
    SW.Load_Shader_Dir("..\\Debug\\shaders\\Mandelbrot\\");
    cout<<SW.Get_Fragment_Source();
    //system("pause");
    return 0;
}
