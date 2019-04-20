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
cgraph = IGMinimumVertexColoring[g];
cgraph = StringJoin[ToString /@ Riffle[cgraph, " "]];
str = OpenWrite["coloracion.txt"];
Write[str, cgraph];
Close[str];
Print[xr]
image = IGVertexMap[ColorData[97], VertexStyle->IGMinimumVertexColoring, Graph[g, VertexSize->Automatic]];
pathPhoto = Import["rutaImagen.txt"];
Export[pathPhoto, image];


(* ::InheritFromParent:: *)
(**)
