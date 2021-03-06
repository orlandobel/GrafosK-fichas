#include "AdjacencyMatrix.cpp"
#include "combinacion_alter.cpp"
#include "leerArchivoMatrizAdyacencia.cpp"
#include "limpiar.cpp"

int construirMatrizOriginal(int &n);
void construirMatrizToken(vector < vector<int> > vv, AdjacencyMatrix &mg, AdjacencyMatrix &A);
void probarTokens(AdjacencyMatrix &A, int n);
int menuMatricesToken();
void escribirArchivos(Combinacion_alter &ca, AdjacencyMatrix &mg, AdjacencyMatrix &A, string carpeta);
string obtenerNombreArchivo(int n, int k);
string obtenerNombreCarpeta(int tam);
void escribirMatrizOriginal(ofstream &fs, AdjacencyMatrix &A);
void escribirListaVectores(ofstream &fs, vector < vector < int > > vv);
void escribirMatrizToken(ofstream &fs, AdjacencyMatrix &mg, vector < vector < int > > vv);
char extraerCaracter(ifstream &archivo, int puntero);
void escribirRutaImagen(string ruta);
void escribirRutaCaminos(string ruta1, string ruta2);
void escribirBoolHam(string ruta);
void escribirBoolEuler(string ruta);

int main() {
	system("clear"); // Limpiar la pantalla GNU/Linux
	system("cls");   // Limpiar la pantalla Windows

    int n = 0;
    int opt = construirMatrizOriginal(n);
    int ** matrix;

    if(opt == 3) {
        LecturaMatriz lector;
        matrix = lector.leerArchivo();
        n = lector.getOrden();
        cout << "\nLa matriz leida desde el archivo es de orden " << n  << endl;
    }

    // Instanciamos la matriz original
    AdjacencyMatrix A(n);

    if(opt == 1) A.generateRandomMatrix(); // Se genera de forma aleatoria
    else if(opt == 2) A.generateManualMatrix(); // El usuario introduce cada pos
    else A.setMatriz(matrix); // Se define la matriz generada del archivo

    // Escribimos la matrix en un archivo aparte, la que usa Wolfram
    LecturaMatriz::escribirEnArchivo("archivosWolfram/matrix.txt", A);

    // Limpiamos la pantalla
    system("clear"); // Limpiar la pantalla GNU/Linux
    system("cls");   // Limpiar la pantalla Windows

    // Mostramos la matriz original
    cout << "\n\nMatriz original: " << endl;
    A.showMatrix();
    cout << endl;

    // Se dispone al usuario de un menú para la parte del k-token
    probarTokens(A, n);
}

int construirMatrizOriginal(int &n) {
    int opt;
    cout << "Inserte la forma de construccion de la matriz: "<< endl;
    cout << "(1) Forma automatica" << endl;
    cout << "(2) Forma manual" << endl;
    cout << "(3) Leer desde archivo" << endl;

    do {
        cout << ">> ";
        cin >> opt;

        if(opt == 1 || opt == 2) {
            cout << "Inserte el orden de la matriz de adyacencia" << endl;
            cin >> n;
            break;
        }

        if(opt == 1 || opt == 2 || opt == 3) break;
        else cout << "Elija una opcion valida" << endl;

    } while(true);
    return opt;
}

void construirMatrizToken(vector <vector<int> > vv, AdjacencyMatrix &mg, AdjacencyMatrix &A) {
    vector <int> aux;

	/* Se genera la matriz triangular superior G(k), y automáticamente se
    va haciendo el reflejo, ya que es simétrica. */
    for(unsigned int i = 0; i < vv.size(); i++) {
        for(unsigned int j = i; j < vv.size(); j++) {
            /* Se guarda el vector resultado en aux de la diferencia
            simétrica */
            aux = Herramientas::diferenciaSimetrica(vv[i], vv[j]);

	        /* El tamaño del vector resultado es z, si z es igual a 2 entonces
            se evalua, de otra forma no (ya la matriz G(k) tiene ceros). */
            if(aux.size() == 2) {
                if(A.queryPos(aux[0]-1, aux[1]-1)) {
                    mg.simetricReflex(i, j, 1);
                }
            }
        }
    }
}

void probarTokens(AdjacencyMatrix &A, int n) {
    int xf_kg;
    bool ans = true;
    int opt = 0;

	do {
        opt = menuMatricesToken();
		else if( opt == 1){
			string carpeta = obtenerNombreCarpeta(A.getTam()) + "_camino_original";
			system(("mkdir " + carpeta).c_str());
			system(("cd " + carpeta).c_str());

			LecturaMatriz::escribirEnArchivo("archivosWolfram/matrix.txt", A);
			escribirRutaImagen("../" + carpeta + "/grafo.jpg");
			escribirRutaCaminos("../" + carpeta + "/euler.txt", "../" + carpeta + "/ham.txt");

			system("wolframscript -file PruebasLecturas/EulerianCycle.wl");
			escribirBoolEuler("" + carpeta + "/euler.txt");

			string nombre = "euler.txt";
			limpiar(carpeta,nombre);

			system("wolframscript -file PruebasLecturas/HamiltonianCycle.wl");
			escribirBoolHam("" + carpeta + "/ham.txt");

			nombre = "ham.txt";
			limpiar(carpeta,nombre);

			system("wolframscript -file PruebasLecturas/dibujarGrafo.wl");

			system("clear");
			system("cls");
			cout<<"¡Archivos creados!"<< endl;

		}
		else if (opt == 2){
			vector < vector<int> > vectores;
			string carpeta =obtenerNombreCarpeta(A.getTam())+"_caminos";
			system(("mkdir "+ carpeta).c_str());
			system(("cd "+ carpeta).c_str());

			LecturaMatriz::escribirEnArchivo("archivosWolfram/matrix.txt", A);
			escribirRutaImagen("../" + carpeta + "/grafo_Original.jpg");
			escribirRutaCaminos("../" + carpeta + "/euler_Original.txt", "../" + carpeta + "/ham_Original.txt");

			system("wolframscript -file PruebasLecturas/EulerianCycle.wl");
			escribirBoolEuler("" + carpeta + "/euler_Original.txt");

			string nombre = "euler_Original.txt";
			limpiar(carpeta,nombre);

			system("wolframscript -file PruebasLecturas/HamiltonianCycle.wl");
			escribirBoolHam("" + carpeta + "/ham_Original.txt");

			nombre = "ham_Original.txt";
			limpiar(carpeta,nombre);

			system("wolframscript -file PruebasLecturas/dibujarGrafo.wl");

			system("clear");
			system("cls");

			for (int k = 2; k <= int(n/2); k++) {
				Combinacion_alter ca(n, k);
				vectores = ca.getVectores();
				AdjacencyMatrix mg(vectores.size());

				mg.generateZeroMatrix();
				construirMatrizToken(vectores, mg, A);

				LecturaMatriz::escribirEnArchivo("archivosWolfram/matrix.txt", mg);

				escribirRutaImagen("../" + carpeta + "/grafo_" + to_string(k) + ".jpg");
				escribirRutaCaminos("../" + carpeta + "/euler_"+to_string(k)+".txt", "../" + carpeta + "/ham"+to_string(k)+".txt");

				// Se ejecuta el script de wolfram
				system("wolframscript -file PruebasLecturas/EulerianCycle.wl");
				escribirBoolEuler("" + carpeta + "/euler_"+to_string(k)+".txt");

				string nombre = "euler_" + to_string(k) + ".txt";
				limpiar(carpeta,nombre);

				system("wolframscript -file PruebasLecturas/HamiltonianCycle.wl");
				escribirBoolHam("" + carpeta + "/ham"+to_string(k)+".txt");

				nombre = "ham" + to_string(k) + ".txt";
				limpiar(carpeta,nombre);

				system("wolframscript -file PruebasLecturas/dibujarGrafo.wl");
			}

			system("clear");
			system("cls");

			cout<<"¡Archivos creados!"<<endl;
			ans= false;
		}
		else ans = false;
    } while(ans);
}

int menuMatricesToken() {
    int opt;
    cout << "\nElija una opcion: " << endl;
	cout << "(1) Generar caminos euleriano y hamiltoniano solo para el grafo original" << endl;
	cout << "(2) Generar caminos para el grafo original y todas sus k-fichas" << endl;
    cout << "(3) Salir" << endl;
    do {
        cout << ">> ";
        cin >> opt;
        if(opt != 1 && opt != 2 && opt != 3 && opt != 4 && opt != 5) {
            cout << "Elija una opcion valida" << endl;
        }
        else break;
    } while(true);
    return opt;
}

void escribirArchivos(Combinacion_alter &ca, AdjacencyMatrix &mg, AdjacencyMatrix &A, string carpeta) {
    string nombre = obtenerNombreArchivo(ca.getNumeroVertices(), ca.getToken());
    string path = carpeta + "/" + nombre;
    vector < vector<int> > vectores = ca.getVectores();

	ofstream fs(path);
	escribirMatrizOriginal(fs, A);

    fs << "\nK-token = " << ca.getToken() << "\n\n";
	escribirListaVectores(fs, vectores);

    if(mg.getTam() < 30)
        escribirMatrizToken(fs, mg, vectores);
    else
        fs << "\nMatriz muy grande" << endl;

    fs.close();
}

string obtenerNombreArchivo(int n, int k) {
    // Ejemplo: n6_k2.txt
    string nombre = "n"  +  std::to_string(n)  +  " k"  +  std::to_string(k)  +  ".txt";
    return nombre;
}

string obtenerNombreCarpeta(int tam) {
    // Ejemplo: 2018_10_30__22?16
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
    // Los segundos
    string sec;
    if(now->tm_sec < 10) sec = "0" + to_string(now->tm_sec);
    else sec = to_string(now->tm_sec);
    // Formamos la cadena HH:MM
    string tiempo = "__" + hour + "%" + min + "%" + sec;
    date += tiempo;
    string nombre = to_string(tam) + "n__" + date;
    return nombre;
}

void escribirMatrizOriginal(ofstream &fs, AdjacencyMatrix &A) {
    int ** matrix = A.getMatriz(); // Se recupera la matriz
    int tam = A.getTam(); // Y su tamaño
    fs << "Matriz original: " << endl;
    for(int x = 0; x < tam; x++){
        for(int y = 0; y < tam; y++){
            fs << matrix[x][y] << " ";
        }
        fs << "\n";
    }
    fs << "---------------------------------------" << endl;
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
            fs << ") "<<endl;
        }
    }
    else fs << "El conjunto esta vacio." << endl;
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
}

char extraerCaracter(ifstream &archivo, int puntero) {
    char caracter[1];

    archivo.seekg(puntero);
    archivo.read(caracter,1);

    return caracter[0];
}

void escribirRutaImagen(string ruta) {
    ofstream fs("archivosWolfram/rutaImagen.txt");
    fs << ruta;
    // Cerramos el archivo
    fs.close();
}

void escribirRutaCaminos(string ruta1, string ruta2) {
    ofstream Eu("archivosWolfram/rutaEuler.txt");
    Eu << ruta1;
    Eu.close();

		ofstream Ham("archivosWolfram/rutaHam.txt");
		Ham << ruta2;
		Ham.close();

}

void escribirBoolHam(string ruta) {
	ifstream hamCompare;
	ofstream hamWrite;
	string ham;
	string fichero = "archivosWolfram/boolHam.txt";

	hamCompare.open(ruta,ios::in);

	if(hamCompare.fail()) {
		cout<<"error al comprobar ciclo"<<endl;
		system("pause");
		exit(1);
	} else {
		string aux;
		ham = "Si";
		getline(hamCompare,aux);
		if(aux.compare("{}")==0) {
			ham = "No";
		}
	}

	hamCompare.close();
	hamWrite.open(fichero,ios::out);
	if(hamWrite.fail()) {
		cout<<"error en la escritura"<<endl;
		system("pause");
		exit(1);
	}

	hamWrite<<ham;
	hamWrite.close();
}

void escribirBoolEuler(string ruta) {
	ifstream eulerCompare;
	ofstream eulerWrite;
	string euler;
	string fichero = "archivosWolfram/boolEuler.txt";

	eulerCompare.open(ruta,ios::in);

	if(eulerCompare.fail()) {
		cout<<"error al comprobar ciclo"<<endl;
		system("pause");
		exit(1);
	} else {
		string aux;
		euler = "Si";
		getline(eulerCompare,aux);
		if(aux.compare("{}")==0) {
			euler = "No";
		}
	}
	eulerCompare.close();

	eulerWrite.open(fichero,ios::out);
	if(eulerWrite.fail()) {
		cout<<"error en la escritura"<<endl;
		system("pause");
		exit(1);
	}

	eulerWrite<<euler;
	eulerWrite.close();
}
