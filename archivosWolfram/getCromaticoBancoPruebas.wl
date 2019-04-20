(* ::Package:: *)

Get["IGraphM`"];
myWorkspace = "C:\Users\Orlando\Desktop\k-token_v5\archivosWolfram";
SetDirectory[myWorkspace];
m = Import["matrix.txt", "Table"];
m = Unitize[m];
g= AdjacencyGraph[m];
xr = IGChromaticNumber[g];
str = OpenWrite["cromatico.txt"];
Write[str, xr];
Close[str];
Print[xr]


(* ::InheritFromParent:: *)
(**)
