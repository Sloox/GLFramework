#ifndef GLSHADERWRAPPER_H_INCLUDED
#define GLSHADERWRAPPER_H_INCLUDED

#include <string>
#include "../Util/FileManip.h"
using namespace std;

class SGFShaderWrapper{
    public:
        ///Constructors
        SGFShaderWrapper();//default
        ///Destructor
        ~SGFShaderWrapper();
        ///Load Shaders
        bool Load_Shader_Vertex(string FileName);
        bool Load_Shader_Fragment(string FileName);
        ///Could do with some nice expansion
        bool Load_Shader_Dir(string DirLocation);//Attempts to load two shaders from a directory

        ///Getters
        const char* Get_Vertex_Source();
        const char* Get_Fragment_Source();

        ///SetParam Vertex
        bool Set_Vertex_Attribute(string name, int value );
        bool Set_Vertex_Attribute(string name, vec4 value );
        bool Set_Vertex_Attribute(string name, int value );
        bool Set_Vertex_Attribute(string name, int value );
        bool Set_Vertex_Attribute(string name, int value );

    private:
    //Shaders
        ///For testing if they are loaded
        bool VertexFlag;
        bool FragmentFlag;
        ///Contains the actual code
        char* Vertext_Shader;
        char* Fragment_Shader;
        ///General Shader Loader
        int Load_Shader(string ShaderLocation, char*& Buff);

    //Utility
        ///FileManip
        SGFFileManip sgfF;


};


#endif // GLSHADERWRAPPER_H_INCLUDED
