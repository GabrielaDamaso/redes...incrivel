#ifndef GUARDATIPO_H
#define GUARDATIPO_H
#include<string>
using namespace std;

class guardaTipo {
 public:
    guardaTipo
    ();
    string getTipo(string tipo); //todos tipos de arquivos.
    string tipos[14][2]={{"jpeg","image/jpeg"},{"png","image/png"},{"html","text/html"},{"jpg","image/jpg"},
    {"gif","image/gif"}, {"css","text/css"}, {"au","audio/basic"}, {"wav","audio/wav"}, {"avi","video/x-msvideo"},
    {"mp3","audio/mpeg"}, {"txt","text/txt"}, {"js","text/js"}, {".ico", "image/x-icon"}, {"pdf", "application/pdf"}};
};
#endif 
