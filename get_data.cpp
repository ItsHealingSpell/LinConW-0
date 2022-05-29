#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
 
using namespace std;
using namespace Gdiplus;

std::wstring GetWStringByChar(const char* szString)
{
    std::wstring wstrString;
    if (szString != NULL)
    {
        std::string str(szString);
        wstrString.assign(str.begin(), str.end());
    }

    return wstrString; 
}

int main(int argc,char* argv[]){
    if(argc<2) return 0;
    GdiplusStartupInput gdiplusstartupinput;
    ULONG_PTR gdiplustoken;
    GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);
 
    string infilename(argv[1]);
    string outfilename(argv[2]);
 
    Bitmap* bmp = new Bitmap(GetWStringByChar(infilename.c_str()).c_str());
    UINT height = bmp->GetHeight();
    UINT width  = bmp->GetWidth();
 
    Color color;
    freopen(outfilename.c_str(),"w",stdout);
 
    for (UINT y = 0; y < height; y++)
    for (UINT x = 0; x < width ; x++) {
            bmp->GetPixel(x, y, &color);
            cout<<(long double)color.GetRed()/256<<endl;
    }
 
    delete bmp;
    GdiplusShutdown(gdiplustoken);
    return 0;
}
