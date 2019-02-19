/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Main;

import java.util.ArrayList;

/**
 *
 * @author Orlando
 */
public class Matriz {
    private int len;
    private ArrayList<ArrayList<Integer>> matriz;
    
    public Matriz(int len) {
        this.len = len;
        this. matriz = new ArrayList<ArrayList<Integer>>();
    }
    
    public void llenar(ArrayList<Integer> datos) {
        int i=0;
        int j=0;
        int k=0;
        
        for(i=0;i<len;i++) {
            ArrayList<Integer> aux = new ArrayList<Integer>();
            for(j=0;j<len;j++) {
                aux.add(datos.get(k));
                k++;
            }
            matriz.add(aux);
        }
    }
    
    public void printMatriz() {
        int i=0;
        int j=0;
        
        for(i=0;i<len;i++) {
            for(j=0;j<len*3;j++) {
                System.out.print("_");
            }
            System.out.println();
            for(j=0;j<len;j++) {
                System.out.print("|"+matriz.get(i).get(j)+"|");
            }
            System.out.println();
        }
    }
    
}
