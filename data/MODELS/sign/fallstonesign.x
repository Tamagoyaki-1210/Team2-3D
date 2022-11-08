xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 148;
 0.00000;76.97033;0.85000;,
 -16.97055;59.99978;0.85000;,
 0.00000;43.02922;0.85000;,
 16.97055;59.99978;0.85000;,
 -16.97055;59.99978;0.85000;,
 -16.97055;59.99978;-0.35000;,
 -0.00000;43.02922;-0.35000;,
 0.00000;43.02922;0.85000;,
 -16.97055;59.99978;-0.35000;,
 -0.00000;76.97033;-0.35000;,
 16.97055;59.99978;-0.35000;,
 -0.00000;43.02922;-0.35000;,
 -0.00000;76.97033;-0.35000;,
 0.00000;76.97033;0.85000;,
 16.97055;59.99978;0.85000;,
 16.97055;59.99978;-0.35000;,
 0.00000;62.60732;0.55000;,
 -0.22962;62.60732;0.50434;,
 -0.22962;2.60732;0.50434;,
 0.00000;2.60732;0.55000;,
 -0.42426;62.60732;0.37426;,
 -0.42426;2.60732;0.37426;,
 -0.55434;62.60732;0.17962;,
 -0.55434;2.60732;0.17962;,
 -0.60000;62.60732;-0.05000;,
 -0.60000;2.60732;-0.05000;,
 -0.55434;62.60732;-0.27962;,
 -0.55434;2.60732;-0.27962;,
 -0.42426;62.60732;-0.47426;,
 -0.42426;2.60732;-0.47426;,
 -0.22962;62.60732;-0.60434;,
 -0.22962;2.60732;-0.60434;,
 -0.00000;62.60732;-0.65000;,
 -0.00000;2.60732;-0.65000;,
 0.22962;62.60732;-0.60434;,
 0.22962;2.60732;-0.60434;,
 0.42426;62.60732;-0.47426;,
 0.42426;2.60732;-0.47426;,
 0.55434;62.60732;-0.27962;,
 0.55434;2.60732;-0.27962;,
 0.60000;62.60732;-0.05000;,
 0.60000;2.60732;-0.05000;,
 0.55434;62.60732;0.17962;,
 0.55434;2.60732;0.17962;,
 0.42426;62.60732;0.37426;,
 0.42426;2.60732;0.37426;,
 0.22962;62.60732;0.50434;,
 0.22962;2.60732;0.50434;,
 0.00000;62.60732;0.55000;,
 0.00000;2.60732;0.55000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;62.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.60732;-0.05000;,
 0.00000;2.99977;4.75000;,
 -1.83687;2.99977;4.38463;,
 -1.83687;-0.00023;4.38463;,
 0.00000;-0.00023;4.75000;,
 -3.39411;2.99977;3.34411;,
 -3.39411;-0.00023;3.34411;,
 -4.43463;2.99977;1.78687;,
 -4.43463;-0.00023;1.78687;,
 -4.80000;2.99977;-0.05000;,
 -4.80000;-0.00023;-0.05000;,
 -4.43463;2.99977;-1.88687;,
 -4.43463;-0.00023;-1.88687;,
 -3.39411;2.99977;-3.44411;,
 -3.39411;-0.00023;-3.44411;,
 -1.83687;2.99977;-4.48463;,
 -1.83687;-0.00023;-4.48463;,
 -0.00000;2.99977;-4.85000;,
 -0.00000;-0.00023;-4.85000;,
 1.83687;2.99977;-4.48463;,
 1.83687;-0.00023;-4.48463;,
 3.39411;2.99977;-3.44411;,
 3.39411;-0.00023;-3.44411;,
 4.43463;2.99977;-1.88687;,
 4.43463;-0.00023;-1.88687;,
 4.80000;2.99977;-0.05000;,
 4.80000;-0.00023;-0.05000;,
 4.43463;2.99977;1.78687;,
 4.43463;-0.00023;1.78687;,
 3.39411;2.99977;3.34411;,
 3.39411;-0.00023;3.34411;,
 1.83687;2.99977;4.38463;,
 1.83687;-0.00023;4.38463;,
 0.00000;2.99977;4.75000;,
 0.00000;-0.00023;4.75000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;2.99977;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;,
 0.00000;-0.00023;-0.05000;;
 
 102;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,4,13;,
 4;14,7,6,15;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 3;50,17,16;,
 3;51,20,17;,
 3;52,22,20;,
 3;53,24,22;,
 3;54,26,24;,
 3;55,28,26;,
 3;56,30,28;,
 3;57,32,30;,
 3;58,34,32;,
 3;59,36,34;,
 3;60,38,36;,
 3;61,40,38;,
 3;62,42,40;,
 3;63,44,42;,
 3;64,46,44;,
 3;65,48,46;,
 3;66,19,18;,
 3;67,18,21;,
 3;68,21,23;,
 3;69,23,25;,
 3;70,25,27;,
 3;71,27,29;,
 3;72,29,31;,
 3;73,31,33;,
 3;74,33,35;,
 3;75,35,37;,
 3;76,37,39;,
 3;77,39,41;,
 3;78,41,43;,
 3;79,43,45;,
 3;80,45,47;,
 3;81,47,49;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 3;116,83,82;,
 3;117,86,83;,
 3;118,88,86;,
 3;119,90,88;,
 3;120,92,90;,
 3;121,94,92;,
 3;122,96,94;,
 3;123,98,96;,
 3;124,100,98;,
 3;125,102,100;,
 3;126,104,102;,
 3;127,106,104;,
 3;128,108,106;,
 3;129,110,108;,
 3;130,112,110;,
 3;131,114,112;,
 3;132,85,84;,
 3;133,84,87;,
 3;134,87,89;,
 3;135,89,91;,
 3;136,91,93;,
 3;137,93,95;,
 3;138,95,97;,
 3;139,97,99;,
 3;140,99,101;,
 3;141,101,103;,
 3;142,103,105;,
 3;143,105,107;,
 3;144,107,109;,
 3;145,109,111;,
 3;146,111,113;,
 3;147,113,115;;
 
 MeshMaterialList {
  5;
  102;
  0,
  4,
  2,
  2,
  2,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\����.png";
   }
  }
  Material {
   0.800000;0.718400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.615200;0.615200;0.615200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.213600;0.213600;0.213600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.530400;0.530400;0.530400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  42;
  0.000000;0.000000;1.000000;,
  -0.707107;-0.707107;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.707107;-0.000000;,
  -0.707107;0.707107;0.000000;,
  0.707107;-0.707107;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.382698;0.000000;0.923874;,
  -0.707107;0.000000;0.707107;,
  -0.923873;0.000000;0.382698;,
  -1.000000;0.000000;0.000000;,
  -0.923873;0.000000;-0.382698;,
  -0.707107;0.000000;-0.707107;,
  -0.382698;0.000000;-0.923873;,
  -0.000000;0.000000;-1.000000;,
  0.382698;0.000000;-0.923874;,
  0.707107;0.000000;-0.707107;,
  0.923873;0.000000;-0.382698;,
  1.000000;0.000000;-0.000000;,
  0.923874;0.000000;0.382698;,
  0.707107;0.000000;0.707107;,
  0.382698;0.000000;0.923873;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.382683;0.000000;0.923880;,
  -0.707107;0.000000;0.707107;,
  -0.923880;0.000000;0.382683;,
  -1.000000;0.000000;0.000000;,
  -0.923880;0.000000;-0.382683;,
  -0.707107;0.000000;-0.707107;,
  -0.382683;0.000000;-0.923880;,
  -0.000000;0.000000;-1.000000;,
  0.382683;0.000000;-0.923880;,
  0.707107;0.000000;-0.707107;,
  0.923880;0.000000;-0.382683;,
  1.000000;0.000000;-0.000000;,
  0.923880;0.000000;0.382683;,
  0.707107;0.000000;0.707107;,
  0.382683;0.000000;0.923880;,
  0.000000;-1.000000;-0.000000;;
  102;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,7,7,22;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,25,25,40;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;24,24,24;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;;
 }
 MeshTextureCoords {
  148;
  0.500841;0.005411;,
  0.999975;0.504545;,
  0.500841;1.003679;,
  0.001708;0.504545;,
  1.006820;0.500000;,
  1.006820;0.500000;,
  0.492560;1.014260;,
  0.492560;1.014260;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.492560;-0.014260;,
  0.492560;-0.014260;,
  -0.021700;0.500000;,
  -0.021700;0.500000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.187500;0.000000;,
  0.187500;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.312500;0.000000;,
  0.312500;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.562500;0.000000;,
  0.562500;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.687500;0.000000;,
  0.687500;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.812500;0.000000;,
  0.812500;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.937500;0.000000;,
  0.937500;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.031250;0.000000;,
  0.093750;0.000000;,
  0.156250;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.906250;0.000000;,
  0.968750;0.000000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.187500;0.000000;,
  0.187500;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.312500;0.000000;,
  0.312500;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.562500;0.000000;,
  0.562500;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.687500;0.000000;,
  0.687500;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.812500;0.000000;,
  0.812500;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  0.937500;0.000000;,
  0.937500;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.031250;0.000000;,
  0.093750;0.000000;,
  0.156250;0.000000;,
  0.218750;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.906250;0.000000;,
  0.968750;0.000000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;;
 }
}