#include "AdjacencyMatrix.cpp"
#include "combinacion_alter.cpp"
/*#include "Euler.cpp"*/

// Prototipos de funciones
void construirMatrizOriginal(AdjacencyMatrix &A);
void construirMatrizToken(vector < vector<int> > vv, AdjacencyMatrix &mg, AdjacencyMatrix &A);
void probarTokens(AdjacencyMatrix &A, int n/*, Euleriano En*/);
int menuMatricesToken();
void escribirArchivos(Combinacion_alter &ca, AdjacencyMatrix &mg, AdjacencyMatrix &A, string carpeta);
string obtenerNombreArchivo(int n, int k);
string obtenerNombreCarpeta();
void escribirMatrizOriginal(ofstream &fs, AdjacencyMatrix &A);
void escribirListaVectores(ofstream &fs, vector < vector < int > > vv);
void escribirMatrizToken(ofstream &fs, AdjacencyMatrix &mg, vector < vector < int > > vv);

int main() {
    int n;
    cout << "Inserte el orden de la matriz de adyacencia" << endl;
    cin >> n;
    // Instanciamos la matriz original
    AdjacencyMatrix A(n);
    /*Euleriano En(n);
    En.SetMatriz(A.getMatriz());*/
    // Método donde se construye de forma manual o el usuario debe
    // insertar el valor de cada posición.
    construirMatrizOriginal(A);
    // Mostramos la matriz original
    cout << "\nMatriz original: " << endl;
    A.showMatrix();
    cout << endl;

    // Se dispone al usuario de un menú para la parte del k-token
    probarTokens(A, n/*, En*/);
}

void construirMatrizOriginal(AdjacencyMatrix &A) {
    int opt;
    cout << "Inserte la forma de construccion de la matriz: "<< endl;
    cout << "(1) Forma automatica" << endl;
    cout << "(2) Forma manual" << endl;
    do {
        cout << ">> ";
        cin >> opt;
        if(opt == 1) {
            A.generateRandomMatrix(); // Se genera de forma aleatoria
            break;
        }
        else if(opt == 2){
            A.generateManualMatrix(); // El usuario introduce cada pos
            break;
        }
        else {
            // y se volverá a pedir una opción
            cout << "Elija una opcion valida" << endl;
        }
    } while(true);
}

void construirMatrizToken(vector <vector<int> > vv, AdjacencyMatrix &mg, AdjacencyMatrix &A) {
    vector <int> aux;
    // Se genera la matriz triangular superior G(k), y automáticamente se
    // va haciendo el reflejo, ya que es simétrica.
    for(unsigned int i = 0; i < vv.size(); i++) {
        for(unsigned int j = i; j < vv.size(); j++) {
            /* Se guarda el vector resultado en aux de la diferencia
            simétrica */
            aux = Herramientas::diferenciaSimetrica(vv[i], vv[j]);
            /* El tamaño del vector resultado es z, si z es igual a 2
            entonces se evalua, de otra forma no
            (ya la matriz_G(k) tiene ceros).*/
            if(aux.size() == 2) {
                if(A.queryPos(aux[0]-1, aux[1]-1)) {
                    mg.simetricReflex(i, j, 1);
                }
            }
        }
    }
}

void probarTokens(AdjacencyMatrix &A, int n/*, Euleriano En*/) {
    bool ans = true;
    int opt = 0;
    do {
        opt = menuMatricesToken();
        if(opt == 1) { // Para probar una k en específico
            int k;
            vector < vector<int> > vectores;
            cout << "Inserte el k token del grafo tal que 2 <= k <= " << int (n/2) << endl;
            cout << ">> ";
            cin >> k;
            Combinacion_alter ca(n, k);
            cout << "\nLista de vectores:" << endl;
            ca.imprimirVectores();
            vectores = ca.getVectores();
            AdjacencyMatrix mg(vectores.size());
            mg.generateZeroMatrix();
            construirMatrizToken(vectores, mg, A);
            cout << "\nMatriz generada con k:" << endl;
            mg.showMatrix(vectores);
        }
        else if(opt == 2) { // Generar archivos para las distintas k
            vector < vector<int> > vectores;
            string carpeta = obtenerNombreCarpeta();
            system(("mkdir " + carpeta).c_str());
            system(("cd " + carpeta).c_str());
            for (int k = 2; k <= int (n/2); k++) {
                Combinacion_alter ca(n, k);
                vectores = ca.getVectores();
                AdjacencyMatrix mg(vectores.size());
                mg.generateZeroMatrix();
                construirMatrizToken(vectores, mg, A);
                escribirArchivos(ca, mg, A, carpeta);
            }
            cout << "\nSe han escrito: " <<(n-1)<< " archivo(s)" << endl;
            ans = false; // con esto se termina el flujo del programa
        }
      /*  else if(opt == 4){
          if(En.EsEuleriano() != 0){
            cout << "\nEs Euleriano"<<endl;
          }else{
            cout << "\nNo es Euleriano"<<endl;
          }
        }*/
        else ans = false;
    } while(ans);
}

int menuMatricesToken() {
    int opt;
    cout << "\nElija una opcion: " << endl;
    cout << "(1) Probar con una k" << endl;
    cout << "(2) Generar archivos para todas las k" << endl;
  //  cout << "(4) Probar si es euleriano" << endl;
    cout << "(3) Sair"<<endl;
    do {
        cout << ">> ";
        cin >> opt;
        if(opt != 1 && opt != 2 && opt != 3 /*&& opt !=4 */) {
            cout << "Elija una opcion valida" << endl;
        }
        else break;
    } while(true);
    return opt;
}

/*Lo que hace es escribir en un archivo la matriz original, la
lista de vectores etiquetados y la matriz G(k) generada*/
void escribirArchivos(Combinacion_alter &ca, AdjacencyMatrix &mg, AdjacencyMatrix &A, string carpeta) {
    string nombre = obtenerNombreArchivo(ca.getNumeroVertices(), ca.getToken());
    string path = carpeta + "/" + nombre;
    ofstream fs(path);
    vector < vector<int> > vectores = ca.getVectores();
    escribirMatrizOriginal(fs, A);
    fs << "\nk token = " << ca.getToken() << "\n\n";
    escribirListaVectores(fs, vectores);
    escribirMatrizToken(fs, mg, vectores);
    fs.close();
}

/* Es solo para generar el nombre del archivo txt, fecha, hora,
orden y k-token */
string obtenerNombreArchivo(int n, int k) {
    // Ejemplo: n6_k2.txt
    string nombre = "n"  +  to_string(n)  +  " k"  +  to_string(k)  +  ".txt";
    return nombre;
}

string obtenerNombreCarpeta() {
    // Ejemplo: 2018-10-30 22:16
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);

    string date = to_string(now->tm_year + 1900) + "_";
    date += to_string(now->tm_mon + 1) + "_" + to_string(now->tm_mday);
    // Se construye la hora
    string hour;
    if(now->tm_hour < 10) hour = "0" + to_string(now->tm_hour);
    else hour = to_string(now->tm_hour);
    // Los minutos
    string min;
    if(now->tm_min < 10) min = "0" + to_string(now->tm_min);
    else min = to_string(now->tm_min);
    // Formamos la cadena HH:MM
    string tiempo = "__" + hour + "%" + min;
    date += tiempo;
    string nombre = date;
    return nombre;
}

void escribirListaVectores(ofstream &fs, vector < vector < int > > vv) {
    fs << "Lista de vectores:" << endl;
    if(!vv.empty()) {
        for (size_t i = 0; i < vv.size(); i++) {
            fs << "V" << i + 1 << "=" << "(";
            for (size_t j = 0; j < vv[i].size(); j++) {
                if(j != vv[i].size() - 1)
                    fs << vv[i][j] << ",";
                else
                    fs << vv[i][j];
            }
            fs <<") "<<endl;
        }
    }
    else fs << "El conjunto esta vacio." << endl;
}

void escribirMatrizOriginal(ofstream &fs, AdjacencyMatrix &A) {
    int ** matrix = A.getMatriz(); // Se recupera la matriz
    int tam = A.getTam(); // Y su tamaño
    fs << "Matriz original: " << endl;
    for(int x = 0; x < tam; x++){
        for(int y = 0; y < tam; y++){
            fs << matrix[x][y] << " ";
        }
        fs << endl;
    }
	if(A.Dirac())
		fs<<"Cumple teomera Dirac"<<endl;
	else
		fs<<"No cumple teomera Dirac"<<endl;
    fs << "---------------------------------------" << endl;
}

void escribirMatrizToken(ofstream &fs, AdjacencyMatrix &mg, vector < vector < int > > vv) {
    fs << "\nMatriz generada con k:" << endl;
    for(unsigned int i = 0; i < vv.size(); i++){
        if(i==0) fs << "   V" << i+1 << " ";
        else fs << "V" << i+1 << " ";
    }
    fs << endl;
    int tam = mg.getTam(); // recuperamos el tamaño de la matriz
    int ** matrix = mg.getMatriz(); // y se recupera la matriz
    for(int x = 0;x < tam;x++){
        for(int y = 0; y < tam; y++){
            if(y == 0) {
                fs << "V" << x+1 << Herramientas::getString(Herramientas::numDigitos(tam)-(Herramientas::numDigitos(x+1))) + " ";
            }
            fs << matrix[x][y] << Herramientas::getString((Herramientas::numDigitos(y+1)))+Herramientas::getString(y+1);
        }
        fs << endl;
    }
	if(mg.Dirac())
		fs<<"Cumple teomera Dirac"<<endl;
	else
		fs<<"No cumple teomera Dirac"<<endl;
}
