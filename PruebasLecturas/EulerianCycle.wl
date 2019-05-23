(* ::Package:: *)

myWorkspace = "C:\Users\Orlando\Desktop\k-token_Circuitos_v1\archivosWolfram";
SetDirectory[myWorkspace];


m= Import["matrix.txt","Table"];
m = Unitize[m];
g= AdjacencyGraph[m];
grafo= Import["rutaEuler.txt"];
Eu = FindEulerianCycle[g];
str = OpenWrite[grafo];
Write[str, Eu];
Close[str];
Print[Eu]
