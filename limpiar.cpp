#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

void reemplazar(string fichero, string camino) {
    ofstream nuevo;

    nuevo.open(fichero,ios::out);
    if(nuevo.fail()) {
        cout<<"error a remplazar"<<endl;
        exit(1);
    }
    nuevo<<camino;

    nuevo.close();
}

string replace(string word, string target, string replacement){
    int len, loop=0;
    string nword="", let;
    len=word.length();
    len--;

    while(loop<=len){
        let=word.substr(loop, 1);
        if(let==target){
            nword=nword+replacement;
        }else{
            nword=nword+let;
        }
        loop++;
    }

    return nword;
}

    ifstream camino;
    void limpiar(string ruta, string nombre) {
    string camLeido;
    string fichero = ruta + "/" + nombre;

    camino.open(fichero,ios::in);

    if(camino.fail()) {
        cout<<"error al reemplazar"<<endl;
        cout<<"error en el fichero: "<<fichero<<endl;
        system("pause");
    } else {
        string aux;
        int i = 0;
        while(!camino.eof()) {
            i++;
            getline(camino,camLeido);

            camLeido=replace(camLeido,"U","");
            camLeido=replace(camLeido,"n","");
            camLeido=replace(camLeido,"d","");
            camLeido=replace(camLeido,"i","");
            camLeido=replace(camLeido,"r","");
            camLeido=replace(camLeido,"e","");
            camLeido=replace(camLeido,"c","");
            camLeido=replace(camLeido,"t","");
            camLeido=replace(camLeido,"E","");
            camLeido=replace(camLeido,"g","");

            aux.append(camLeido);
        }

        cout<<"aux="<<aux<<endl;
        reemplazar(fichero, aux);

        camino.close();
    }
}
