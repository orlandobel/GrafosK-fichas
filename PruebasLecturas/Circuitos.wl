(* ::Package:: *)

myWorkspace = "c:\\users\orlando\desktop\GrafosK-fichas\archivosWolfram";
SetDirectory[myWorkspace];
m= Import["matrix.txt","Table"];
m= Unitize[m];
g= AdjacencyGraph[m];
grafo = Import["rutaImagen.txt"];
Export[grafo,g];

Ham = FindHamiltonianCycle[g];
grafo= Import["rutaHam.txt"];
str = OpenWrite[grafo];
Write[str, Ham];
Close[str];
Print[Ham]

grafo= Import["rutaEuler.txt"];
Eu = FindEulerianCycle[g];
str = OpenWrite[grafo];
Write[str, Eu];
Close[str];
Print[Eu];












