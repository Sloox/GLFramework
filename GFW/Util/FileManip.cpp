#include "FileManip.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdio.h>


using namespace std;

///Constructors
SGFFileManip::SGFFileManip(){


}


///Destructors
SGFFileManip::~SGFFileManip(){



}



vector<string> SGFFileManip::GetFilesFromDir(string DirPath){
    vector<string> Files;
    char search_path[200];
    sprintf(search_path, "%s*.*", DirPath.c_str());

    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path, &fd);
    if(hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                Files.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return Files;

}


string SGFFileManip::Load_ASCII_File(string Path){

    ///Reads in shaders
        FILE *fp;
        long lSize;
        char *shaderFilebuffer;

        fp = fopen (Path.c_str() , "rb" );
        if(!fp) {
            cerr<<"Failed to open file:"<<Path<<endl;
            return "";
        }

        fseek(fp ,0L , SEEK_END);
        lSize = ftell( fp );
        rewind(fp) ;

        /* allocate memory for entire file */
        shaderFilebuffer = (char*)calloc( 1, lSize+1 );
        if(!shaderFilebuffer){
            fclose(fp);
            cerr<<"Failed to allocate (calloc) memory to File."<<endl;
            return "";
        }

        /* copy the file into the buffer */
        if( 1!=fread( shaderFilebuffer , lSize, 1 , fp) ){
            fclose(fp);
            free(shaderFilebuffer);
            cout<<"Failed to read File from "<<Path<<endl;
            return "";
        }

        string ReturnString = string(shaderFilebuffer);

        fclose(fp);
        free(shaderFilebuffer);
        return ReturnString;

}

string SGFFileManip::Load_ASCII_File(string Path, string stripchars){

    ///Reads in shaders
        FILE *fp;
        long lSize;
        char *shaderFilebuffer;

        fp = fopen (Path.c_str() , "rb" );
        if(!fp) {
            cerr<<"Failed to open file:"<<Path<<endl;
            return "";
        }

        fseek(fp ,0L , SEEK_END);
        lSize = ftell( fp );
        rewind(fp) ;

        /* allocate memory for entire file */
        shaderFilebuffer = (char*)calloc( 1, lSize+1 );
        if(!shaderFilebuffer){
            fclose(fp);
            cerr<<"Failed to allocate (calloc) memory to File."<<endl;
            return "";
        }

        /* copy the file into the buffer */
        if( 1!=fread( shaderFilebuffer , lSize, 1 , fp) ){
            fclose(fp);
            free(shaderFilebuffer);
            cout<<"Failed to read File from "<<Path<<endl;
            return "";
        }

        string ReturnString = stripfromstring(string(shaderFilebuffer), stripchars);

        fclose(fp);
        free(shaderFilebuffer);
        return ReturnString;

}




///Saver
void SGFFileManip::PPM3_Saver(uint32_t* Buffer, string path, int XResolution, int YResolution){
	//ASCII PPM P3
	FILE *fsave = fopen(path.c_str(), "wt");
	int i, j, k, jmax;
	int index = 0;

	fprintf (fsave, "P3\n");
	fprintf (fsave, "%d  %d\n", XResolution, YResolution);
	fprintf (fsave, "%d\n", 255);

	for (i = 0; i<YResolution; i++){
		for (k=0; k<XResolution; k=k+4){
			jmax = PPMmin(k + 4, XResolution);
			for (j = k; j < jmax; j++){
				index = ((j) * XResolution) + i;
				fprintf (fsave, "  %d  %d  %d", Buffer[index]%256 , Buffer[index]%256 , Buffer[index]%256);

			}
			fprintf(fsave, "\n" );
    }

  }
  fclose (fsave);
}


///Utility Functions
string SGFFileManip::GetFileExtension(const std::string& FileName){

    if(FileName.find_last_of(".") != string::npos)
        return FileName.substr(FileName.find_last_of(".")+1);
    return "";
}

void SGFFileManip::toLowercase(string& s){
        for(unsigned short l = s.size();l;s[--l]|=(1<<5));///Not safe but will do
}


string SGFFileManip::stripfromstring(string text, string stripchars){//not efficent
    string retstring = "";
    if((text.size()==0)||(stripchars.size()==0))
        return text;

    bool flags = false;
    for(int i = 0;i<text.size();++i){
        flags = false;
        for(int j = 0;j<stripchars.size();++j){
            if(text[i]==stripchars[j])
                flags = true;
        }
        if(!flags){
            retstring+=text[i];
        }

    }
    return retstring;
}



/// Helper functions
int SGFFileManip::PPMmin(int i1, int i2){
  if (i1 < i2)
    return i1;
  else
    return i2;
}
