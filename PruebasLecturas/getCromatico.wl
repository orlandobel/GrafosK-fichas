(* ::Package:: *)

Get["IGraphM`"];
myWorkspace = "C:\Users\david\Dropbox\Dev\k-token\archivosWolfram";
SetDirectory[myWorkspace];
m = Import["matrix.txt", "Table"];
m = Unitize[m];
g= AdjacencyGraph[m];
xr = IGChromaticNumber[g];
str = OpenWrite["cromatico.txt"];
Write[str, xr];
Close[str];
Print[xr]
cgraph = IGMinimumVertexColoring[g];
cgraph = StringJoin[ToString /@ Riffle[cgraph, " "]];
str = OpenWrite["coloracion.txt"];
Write[str, cgraph];
Close[str];
image = IGVertexMap[ColorData[97], VertexStyle->IGMinimumVertexColoring, Graph[g, VertexSize->Automatic]];
pathPhoto = Import["rutaImagen.txt"];
Export[pathPhoto, image];


(* ::InheritFromParent:: *)
(**)
