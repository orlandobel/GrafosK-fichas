#include "bibliotecas.h"

class Euleriano{
  private:
    int n;
    int **MatrizDeVectores;
    int aris;
  public:
    Euleriano(int n);
    void SetMatriz(int **matriz);
    int EsEuleriano();
    int GradoMayor();
    bool gradoUno(int i);
    string camino();
    int aristas();
    int nodoSiguiente(int matriz[], int v);
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
  aris = aristas();
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

int Euleriano::aristas() {
    int aristas=0;
    for(int i=0;i<n;i++) {
        for(int j=i;j<n;j++) {
            if(i==j && MatrizDeVectores[i][j]>0) {
                aristas++;
            } else {
                aristas += MatrizDeVectores[i][j];
            }
        }
    }
    return aristas;
}

string Euleriano::camino(){
    int i=0;
    int j=GradoMayor();
    int inicio=j;
    /*i y j son las coordenadas de los nodos*/
    int v=0;

    bool vacio = false;
    string caminos[aris+1];
    do {
        i=j; //se ueve i al valor anterior de j para iniciar desde el nodo anterior
        j=nodoSiguiente(MatrizDeVectores[i],i); //se aumentaa j en uno para empezar a buscar el siguiente nodo
        int ceros=0;

        string camino;
        if(MatrizDeVectores[i][i]>0 ) {
            j=i;
            MatrizDeVectores[i][j] = 0;
            camino = to_string(i)+"-"+to_string(j);
        } else {
            for(int k=0;k<(n*n);k++) {
                j%=n; //busca la siguiente coordenada de j  para el proximo nodo
                camino = to_string(i)+"-"+to_string(j); //crea el caino i-j para comprovar si es valido

                if(j==inicio && gradoUno(i)==false) {
                    j++;
                }
                if(MatrizDeVectores[i][j]==0) {
                    j++;
                    ceros++;
                    k=-1; //reinicia el ciclo
                }
                if(ceros == (n*n)) {
                    vacio = true;
                    break;
                }
            }
        }

        string aux = to_string(j)+"-"+to_string(i); //camino inverso, evita repetir aristas y vertices
        MatrizDeVectores[i][j]--;
        MatrizDeVectores[j][i]--;
        //if i!=j

        caminos[v]=camino;
        v++;
    } while(vacio==false);

    string cam; //variable en la que se concanetaran los caminos para imprimirlos
    for(int k=0;k<aris;k++) {
        cam += caminos[k]+","; //concatenación de los caminos
    }

    return cam;
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

bool Euleriano::gradoUno(int i) {
    int grado = 0;
    for(int j=0;j<n;j++) {
        if(MatrizDeVectores[i][j]>0) {
            grado++;
        }
    }
    if(grado==1) {
        return true;
    } else {
        return false;
    }
}

int Euleriano::nodoSiguiente(int matriz[], int v) {
    int mayor = 0;
    int nodo = 0;

    cout<<"actual: "<<v<<endl;
    for(int i=0;i<n;i++) {
        if(matriz[i]>0) {
            int grado=0;
            for(int j=0;j<n;j++){
                grado += MatrizDeVectores[i][j];
                if(grado>mayor) {
                    mayor = grado;
                    nodo = i;
                    cout<<"grado: "<<grado<<endl;
                    cout<<"mayor: "<<mayor<<endl;

                }
            }
        }
    }
    cout<<"siguiente: "<<nodo<<endl;
    return nodo;
}

Euleriano::~Euleriano(){
  for(int x=0;x<n;x++){
      for(int y=0;y<n;y++){
          MatrizDeVectores[x][y]='\0';
      }
  }

}
