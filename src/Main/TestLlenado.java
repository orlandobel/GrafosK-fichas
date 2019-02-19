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
public class TestLlenado {
    public static void main(String args[]) {
        Matriz m1 = new Matriz(4);
        ArrayList<Integer> m = new ArrayList<>();
        
        m.add(0);
        m.add(1);
        m.add(1);
        m.add(0);
        m.add(1);
        m.add(0);
        m.add(1);
        m.add(0);
        m.add(1);
        m.add(1);
        m.add(0);
        m.add(1);
        m.add(0);
        m.add(0);
        m.add(1);
        m.add(0);
        
        m1.llenar(m);
        m1.printMatriz();
        
    }
}
