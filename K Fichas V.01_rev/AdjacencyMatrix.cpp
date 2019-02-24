#include "bibliotecas.h"
#include "herramientas.cpp"

class AdjacencyMatrix{
    private:
        //This is the tam of the matrix and how is it a squere matriz is tam x tam
        int tam;
        //This are the spaces in memory
        int ** matrix;
    public:
        AdjacencyMatrix(int n);  // contructor
        ~AdjacencyMatrix(); //destructor
        void showMatrix(); //this function show all the values of the matrix
        void generateRandomMatrix(); //this function fill the matrix with random values
        void generateManualMatrix(); //with this function is posible insert values by way of manual
        void generateZeroMatrix();
        bool queryPos(int x,int y); // with this function it is consulted a value of the matrix
        void showMatrix(vector < vector<int> >  index);
        void setPos(int x,int y,int value);
        void simetricReflex(int x,int y,int value);
        int getTam();// return the tam of the matrix
        int ** getMatriz();

};
AdjacencyMatrix::AdjacencyMatrix(int n){
    tam=n;
    //Create a array of arrays to dinamic way
    matrix = new int*[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];
    }
void AdjacencyMatrix::showMatrix(){
    cout<<endl;
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            cout<<matrix[x][y]<<" ";
        }
        cout<<endl;
    }
}
void AdjacencyMatrix::showMatrix(vector < vector<int> >  index){
    //hacer el aumento de espacios para cada uno
    cout<<endl;

    for(unsigned int i=0;i<index.size();i++){
        if(i==0){
            cout<<"   V"<<i+1<<" ";
        }else{
            cout<<"V"<<i+1<<" ";
        }

    }
    cout<<endl;
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            if(y==0){
                cout<<"V"<<x+1<<Herramientas::getString(Herramientas::numDigitos(tam)-(Herramientas::numDigitos(x+1)))+" ";
            }
            cout<<matrix[x][y]<<Herramientas::getString((Herramientas::numDigitos(y+1)))+Herramientas::getString(y+1);
        }
        cout<<endl;
    }
}
void AdjacencyMatrix::generateRandomMatrix(){
    int num;
    srand(time(NULL));
    for(int x=0;x<tam;x++){
        for(int y=x;y<tam;y++){
            if(x==y){
                matrix[x][y]=0;
            }
    	  	else if(x!=y){
                  num=rand() % 2;
                  simetricReflex(x,y,num);
    		      //matrix[x][y]=num;
                  //matrix[y][x]=num;
    	    }
        }
    }
}
void AdjacencyMatrix::generateManualMatrix(){
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            cout<<"("<<x<<","<<y<<")"<<endl;
            scanf("%d", &matrix[x][y]);
        }
    }
}
void AdjacencyMatrix::generateZeroMatrix(){
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            matrix[x][y]=0;
        }
    }
}
bool AdjacencyMatrix::queryPos(int x,int y){
    if(matrix[x][y]==1){
        return true;
    }else{
        return false;
    }
}
int AdjacencyMatrix::getTam(){
    return tam;
}
int ** AdjacencyMatrix::getMatriz() {
    return matrix;
}
void AdjacencyMatrix::simetricReflex(int x,int y,int value){
    setPos(x,y,value);
    setPos(y,x,value);

}
void AdjacencyMatrix::setPos(int x,int y,int value){
    matrix[x][y]=value;
}
AdjacencyMatrix::~AdjacencyMatrix(){
    for(int x=0;x<tam;x++){
        for(int y=0;y<tam;y++){
            matrix[x][y]='\0';
        }
    }
    /*
    for (int i = 0; i < tam; ++i)
        delete [] matrix[i];
    delete [] matrix;
    */
}



/*int main(){
    AdjacencyMatrix m1(5);
    m1.generateRandomMatrix();
    m1.showMatrix();
    cout<<m1.queryPos(1,2)<<endl;
    cout<<m1.getTam()<<endl;
    m1.~AdjacencyMatrix();
    return 0;
}*/
