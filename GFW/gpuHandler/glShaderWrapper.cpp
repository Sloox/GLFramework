///This is aimed at initalization and loading of shaders into GPU
///Works with glContext


#include "glShaderWrapper.h"
#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;



///Constructors
SGFShaderWrapper::SGFShaderWrapper(){
    VertexFlag = false;
    FragmentFlag = false;
    sgfF = SGFFileManip();
}

///Destructor
SGFShaderWrapper::~SGFShaderWrapper(){


}

///Shader Loading
bool SGFShaderWrapper::Load_Shader_Vertex(string FileName){///Must be of *.vert
    int retMSG = 0;
    char* VsBuff;
    retMSG = Load_Shader(FileName, VsBuff);
    if(retMSG == 1){//Vertex loaded
        VertexFlag = true;//shader now loaded
        Vertext_Shader = VsBuff;
        return true;
    }
    else if(retMSG!=-1){
        cerr<<"Wrong File extension recieved for Vertex shader, expected *.vert"<<endl;
        return false;
    }
    else
        return false;

}

bool SGFShaderWrapper::Load_Shader_Fragment(string FileName){///Must be of *.frag
    int retMSG = 0;
    char* FsBuff;
    retMSG = Load_Shader(FileName, FsBuff);
   if(retMSG==2){//Fragment loaded
        FragmentFlag = true;//shader now loaded
        Fragment_Shader = FsBuff;
        return true;
    }
    else if(retMSG!=-1){
        cerr<<"Wrong File extension recieved for fragment shader, expected *.frag"<<endl;
        return false;
    }
    else
        return false;

}

bool SGFShaderWrapper::Load_Shader_Dir(string DirLocation){
    vector<string> Files = sgfF.GetFilesFromDir(DirLocation);

    if(Files.size()>2){
         cerr<<"Currently do not support more than 1 shader program(1 vert & 1 frag) per directory"<<endl;
         return false;
    }
    else{
        bool atleast1loaded = false;
        for(int i = 0;i<Files.size();++i){
            char* Buff;
            int retMSG = Load_Shader(DirLocation+Files[i],Buff);
            if(retMSG==2){//fragment
                atleast1loaded = true;
                FragmentFlag = true;//shader now loaded
                Fragment_Shader = Buff;
            }else if(retMSG==1){//vertex
                atleast1loaded = true;
                VertexFlag = true;//shader now loaded
                Vertext_Shader = Buff;
            }
        }
        return atleast1loaded;
    }

}


int SGFShaderWrapper::Load_Shader(string ShaderLocation, char*& Buff){
    ///Check Extension
    string ext = sgfF.GetFileExtension(ShaderLocation);
    sgfF.toLowercase(ext);
    if(ext==""){
        cerr<<"Invalid File extension, expected: *.frag || *.vert"<<endl;
        return -1;
    }else if((ext!="frag")&&(ext!="vert")){
        cerr<<"Invalid File extension, expected: *.frag || *.vert, Got:"<<ext<<endl;
        return -1;
    }
    string temp = sgfF.Load_ASCII_File(ShaderLocation, "\n\r\t");
    if(temp!=""){
        Buff = new char[temp.size() + 1];
        copy(temp.begin(), temp.end(), Buff);
        Buff[temp.size()]='\0';
        if(ext=="frag")
            return 2;
        else
            return 1;
    }
    return -1;//failed

}


///Getters
const char* SGFShaderWrapper::Get_Vertex_Source(){
    if(!VertexFlag){
        cerr <<"No Vertex Shader has been loaded"<<endl;
    }else{
        string Temp(Vertext_Shader);
        return Temp.c_str();
    }

}

const char* SGFShaderWrapper::Get_Fragment_Source(){
    if(!FragmentFlag){
        cerr <<"No Fragment Shader has been loaded"<<endl;
    }else{
        string Temp(Fragment_Shader);
        return Temp.c_str();
    }

}
