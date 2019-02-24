#include "bibliotecas.h"

class Euleriano{
  private:
    int n;
    int ** MatrizDeVectores;
  public:
    Euleriano(int n);
    void SetMatriz(int **matriz);
    int EsEuleriano();
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
Euleriano::~Euleriano(){
  for(int x=0;x<n;x++){
      for(int y=0;y<n;y++){
          MatrizDeVectores[x][y]='\0';
      }
  }

}
