(* ::Package:: *)

myWorkspace = "C:\Users\Orlando\Desktop\k-token_Circuitos_v1\archivosWolfram";
SetDirectory[myWorkspace];



m= Import["matrix.txt","Table"];
m = Unitize[m];
g= AdjacencyGraph[m];
grafo = Import["rutaImagen.txt"];
Ham = FindHamiltonianCycle[g];
grafo= Import["rutaHam.txt"];
str = OpenWrite[grafo];
Write[str, Ham];
Close[str];
Print[Ham]
