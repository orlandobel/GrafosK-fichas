package Main;

import java.util.ArrayList;

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
    
    
    
    
    boolean Euleriano( Matriz matriz){
        int grado;
        for(ArrayList<Integer> aristas: matriz.getMatriz()){
            grado=0;    
            for(Integer arista: aristas){
                grado+=arista;
            }
            if(grado%2!=0){
                return false;
            }
        }
        return true;
    }
}
    

