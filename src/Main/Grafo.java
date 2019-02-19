package Main;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Hector
 */
public class Grafo {
    int grafo[][];
    int nodos;
    
    boolean Euleriano(){
        int i,j, grado;
        for(i=0;i<nodos;i++){
            grado =0;
            for(j=0;j<nodos;j++){
                grado+= grafo[i][j];
            }
            if(grado%2!=0){
                return false;
            }
        }
        return true;
    }
    
}
