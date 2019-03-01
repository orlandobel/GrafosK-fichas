#include "bibliotecas.h"

class Euleriano{
  private:
    int n;
    int **MatrizDeVectores;
  public:
    Euleriano(int n);
    void SetMatriz(int **matriz);
    int EsEuleriano();
    int GradoMayor();
    string camino();
    int aristas();
    ~Euleriano();
};

Euleriano::Euleriano(int n){
  this->n=n;
  MatrizDeVectores = new int*[n];
  for (int i = 0; i < n; i++)
    MatrizDeVectores[i] = new int[n];

}

void Euleriano::SetMatriz(int **matriz){
  this->MatrizDeVectores=matriz;
}

int Euleriano::EsEuleriano(){

  for(int x=0;x<n;x++){
    int Grado=0;
      for(int y=0;y<n;y++){
              Grado += MatrizDeVectores[x][y];
      }
      if (Grado %2 != 0){
        return 0;
      }
  }
  return 1;
}

string Euleriano::camino(){
    int i=0;
    int j=GradoMayor();
    /*i y j son las coordenadas de los nodos*/
    int v=0; //variable que nos indica en numero de vuelta del ciclo
    int u=0; //variable para guardar los caminos usados
    string caminos[n]; //arreglo en el que se almacenan los caminos a impriir
    string usados[2*n]; //se guardan los caminos encontrados y sus inveros para evitar repetirlos
    do {
        i=j; //se ueve i al valor anterior de j para iniciar desde el nodo anterior
        j++; //se aumentaa j en uno para empezar a buscar el siguiente nodo

        string camino;
        for(int k=0;k<(n*n);k++) {
            j%=n; //busca la siguiente coordenada de j  para el proximo nodo
            camino = to_string(i)+"-"+to_string(j); //crea el caino i-j para comprovar si es valido
            if(camino.compare(usados[k])==0 || MatrizDeVectores[i][j]==0) {
                //entra cuando el camino usado ya existe o si no hay conección en el nodo
                j++;
                k=-1; //reinicia el ciclo
            }
        }

        string aux = to_string(j)+"-"+to_string(i); //camino inverso, evita repetir aristas y vertices
        usados[u]=camino;
        usados[u+1]=aux;
        //guarda el camino enconttrado y sun inerso en el arreglo usados para que no se repitan
        caminos[v]=camino;
        //guarda el camino en el arreglo para su impreci´pn

        v++;
        u += 2; //se aumenta en dos para no sobreescribir ningun camino en el arreglo de usados
    } while(v<n); //el ciclo termina cuando dio el mismo numero de vueltas que el grado del grafo

    string cam; //variable en la que se concanetaran los caminos para imprimirlos
    for(int k=0;k<n;k++) {
        cam += caminos[k]+","; //concatenación de los caminos
    }

    return cam;
}

int Euleriano::aristas(){
  int aristas=0;
  int lazos=0;
  for(int x=0;x<n;x++){
      for(int y=0;y<n;y++){
            if(x!=y){
              aristas += MatrizDeVectores[x][y];
            }else{
              lazos+= MatrizDeVectores[x][y];
            }
      }
  }
  return ((aristas/2)+lazos);
}

int Euleriano::GradoMayor() {
    int Grado=0;
    int aux=0, aux2=0;
    for(int x=0;x<n;x++){
        int aux=0;
        for(int y=0;y<n;y++){
            aux += MatrizDeVectores[x][y];
        }
        if(aux2<aux){
            Grado=x;
            aux2=aux;
        }
    }
    return Grado;
}

Euleriano::~Euleriano(){
  for(int x=0;x<n;x++){
      for(int y=0;y<n;y++){
          MatrizDeVectores[x][y]='\0';
      }
  }

}
