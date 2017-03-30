#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

///Necessary Includes
#include <iostream>
#include <gl/gl.h>
#include <cstdlib>
#include "../../GFW/glContext/wContext.h"

#include "Mandlebrot.h" //Parallel Project Implementation include
using namespace std;

void startmandle(int choice);
void Menu(){
    int i = 0;
    system("cls");
    cout<<"----------------Parallel Mandlebrot------------"<<endl<<endl;
    cout<<"Written for IT00197 by Wright, MJ"<<endl;
    cout<<"Select an option to begin"<<endl;
    cout<<"1)Sequential Mandlebrot(Baseline)"<<endl;
    cout<<"2)SSE optimised Mandlebrot"<<endl;
    cout<<"3)OMP optimised Mandlebrot"<<endl;
    cout<<"4)SSE+OMP optimised Mandlebrot"<<endl;
    cout<<"5)Opengl GLSL Mandlebrot"<<endl;
    cout<<"Choice:";

    cin>>i;
    if(cin.fail()){
        cin.clear();
        Menu();
    }
    else{
        startmandle(i);
    }

}

void startmandle(int choice){
    OpenGlRenderingContext Mandlebrot = OpenGlRenderingContext(5,5,DEFAULTWIDTH,DEFAULTHEIGHT);//creates a window
    switch(choice){
        case 1:
                Mandlebrot.glinit(sequentialINIT);//init code here!
                Mandlebrot.setKeyHandler(sequentialKEYS);
                Mandlebrot.setResizerHandler(sequentialResizeer);
                Mandlebrot.MainLoop(sequentialLOOP);//rending code here!
            break;
        case 2:

                Mandlebrot.glinit(sseINIT);//init code here!
                Mandlebrot.setKeyHandler(sseKEYS);
                Mandlebrot.MainLoop(sseLOOP);//rending code here!
            break;
        case 3:

                Mandlebrot.glinit(ompINIT);//init code here!
                Mandlebrot.setKeyHandler(ompKEYS);
                Mandlebrot.MainLoop(ompLOOP);//rending code here!
            break;
        case 4:

                Mandlebrot.glinit(ompOPINIT);//init code here!
                Mandlebrot.setKeyHandler(ompOPKEYS);
                Mandlebrot.MainLoop(ompOPLOOP);//rending code here!
            break;
        case 5:

                Mandlebrot.glinit(shaderINIT);//init code here!

                Mandlebrot.setKeyHandler(shadermkeys);
                Mandlebrot.MainLoop(shaderLOOPmain);//rending code here!
            break;
        default:
        Menu();
    }
    return;
}

void StartParallelProject(){
    Menu();


}
