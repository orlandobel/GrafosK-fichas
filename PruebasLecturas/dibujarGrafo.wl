(* ::Package:: *)

myWorkspace = "C:\Users\Orlando\Desktop\k-token_Circuitos_v1\archivosWolfram";
SetDirectory[myWorkspace];


m= Import["matrix.txt","Table"];
m = Unitize[m];
g= AdjacencyGraph[m];
grafo = Import["rutaImagen.txt"];
CHal = Import["boolHam.txt"];
CEu = Import["boolEuler.txt"];

g= AdjacencyGraph[m, VertexLabels->All,PlotLabel-> StringJoin["Hamiltoniano: ",CHal," Euler: ",CEu]];
grafo = Import["rutaImagen.txt"];
Export[grafo,g];
