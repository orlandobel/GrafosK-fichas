#include "bibliotecas.h"

class Herramientas {
    // Métodos
    public:
        static int combinatoria(int, int);
        static int factorial(int);
        static vector<int> diferenciaSimetrica(vector<int>, vector<int>);
        static int numDigitos(int);
        static string getString(int);
};

// Calcula la combinatoria n! / [r! (n-r)!]
int Herramientas::combinatoria(int n, int r) {
    return (factorial(n) / (factorial(r) * factorial(n-r)));
}
string Herramientas::getString(int num){
    int tamE=numDigitos(num);
    string espacio="";
    for(int i=0;i<tamE;i++){
        espacio+=" ";
    }
    return espacio;
}
int Herramientas::numDigitos(int num){
    int contador=0;
    while(num>0){
        //num=num%10;
        num/=10;
        contador++;
    }
    return contador;
}

int Herramientas::factorial(int n) {
    int resultado = 1, i;
    if (n == 0 || n == 1) return resultado;
    if (n > 1) {
        for (i = 2; i <= n;i++) {
            resultado *= i;
        }
    }
    return resultado;
}

vector<int> Herramientas::diferenciaSimetrica(vector<int> conjunto1,
    vector<int> conjunto2) {
    vector<int> resultado;
    // Ordenamos ambos conjuntos
    sort(conjunto1.begin(), conjunto1.end());
    sort(conjunto2.begin(), conjunto2.end());

    set_symmetric_difference(conjunto1.begin(), conjunto1.end(),
        conjunto2.begin(), conjunto2.end(), back_inserter(resultado));

    return resultado;
}


/*int main() {
    // Aquí hacer pruebas unitarias
    return 0;
}*/
