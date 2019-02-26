#include "bibliotecas.h"

class Euleriano{
  private:
    int n;
    int ** MatrizDeVectores;
  public:
    Euleriano(int n);
    void SetMatriz(int **matriz);
    int EsEuleriano();
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
  while(aristas()!=0){

  }
  return "";
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

int Euleriano::GradoMayor(){
int Grado=0;
int aux=0;
  for(int x=0;x<n;x++){
    int Grado=0;
      for(int y=0;y<n;y++){
              aux += MatrizDeVectores[x][y];
      }
      if(Grado<aux){
        Grado==x;
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
