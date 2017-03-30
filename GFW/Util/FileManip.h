///All file manipulation through this class
///Loading, Saving, etc



#ifndef FILEMANIP_H_INCLUDED
#define FILEMANIP_H_INCLUDED

#include <string>
#include <vector>
using namespace std;


class SGFFileManip{
    public:
        ///Constructors
        SGFFileManip();
        ///Destructor
        ~SGFFileManip();

        ///Loaders
        string Load_ASCII_File(string Path);
        string Load_ASCII_File(string Path, string stripchars);//for stripping linebreaks etc
        vector<string> GetFilesFromDir(string DirPath);

        ///Savers
        //PPM
        void PPM3_Saver(uint32_t* Buffer, string path, int XResolution, int YResolution);

        ///Utility Functions
         string GetFileExtension(const std::string& FileName);
         void toLowercase(string& s);//Not SAFE
         string stripfromstring(string text, string stripchars);
    private:
        ///Helper functions
        int PPMmin(int i1, int i2);





};

#endif // FILEMANIP_H_INCLUDED
