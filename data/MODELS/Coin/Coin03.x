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
 0.00000;22.45973;0.46568;,
 5.00000;21.11998;0.46568;,
 5.00000;21.11998;-0.47020;,
 0.00000;22.45973;-0.47020;,
 8.66025;17.45973;0.46568;,
 8.66025;17.45973;-0.47020;,
 10.00000;12.45974;0.46568;,
 10.00000;12.45974;-0.47020;,
 8.66025;7.45974;0.46568;,
 8.66025;7.45974;-0.47020;,
 5.00000;3.79948;0.46568;,
 5.00000;3.79948;-0.47020;,
 0.00000;2.45974;0.46568;,
 0.00000;2.45974;-0.47020;,
 -5.00000;3.79948;0.46568;,
 -5.00000;3.79948;-0.47020;,
 -8.66025;7.45973;0.46568;,
 -8.66025;7.45973;-0.47020;,
 -10.00000;12.45973;0.46568;,
 -10.00000;12.45973;-0.47020;,
 -8.66026;17.45972;0.46568;,
 -8.66026;17.45972;-0.47020;,
 -5.00001;21.11998;0.46568;,
 -5.00001;21.11998;-0.47020;,
 0.00000;22.45973;0.46568;,
 0.00000;22.45973;-0.47020;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;0.46568;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;12.45974;-0.47020;,
 0.00000;24.89541;1.34849;,
 6.21784;23.22935;1.34849;,
 6.21784;23.22935;-1.35301;,
 0.00000;24.89541;-1.35301;,
 4.96253;21.05508;1.34849;,
 0.00000;22.38478;1.34849;,
 0.00000;22.38478;-1.35301;,
 4.96253;21.05508;-1.35301;,
 10.76962;18.67756;1.34849;,
 10.76962;18.67756;-1.35301;,
 8.59535;17.42226;1.34849;,
 8.59535;17.42226;-1.35301;,
 12.43568;12.45974;1.34849;,
 12.43568;12.45974;-1.35301;,
 9.92506;12.45974;1.34849;,
 9.92506;12.45974;-1.35301;,
 10.76962;6.24189;1.34849;,
 10.76962;6.24189;-1.35301;,
 8.59535;7.49721;1.34849;,
 8.59535;7.49721;-1.35301;,
 6.21784;1.69012;1.34849;,
 6.21784;1.69012;-1.35301;,
 4.96253;3.86438;1.34849;,
 4.96253;3.86438;-1.35301;,
 0.00000;0.02405;1.34849;,
 0.00000;0.02405;-1.35301;,
 0.00000;2.53468;1.34849;,
 0.00000;2.53468;-1.35301;,
 -6.21784;1.69011;1.34849;,
 -6.21784;1.69011;-1.35301;,
 -4.96253;3.86438;1.34849;,
 -4.96253;3.86438;-1.35301;,
 -10.76962;6.24189;1.34849;,
 -10.76962;6.24189;-1.35301;,
 -8.59535;7.49721;1.34849;,
 -8.59535;7.49721;-1.35301;,
 -12.43568;12.45973;1.34849;,
 -12.43568;12.45973;-1.35301;,
 -9.92506;12.45973;1.34849;,
 -9.92506;12.45973;-1.35301;,
 -10.76962;18.67756;1.34849;,
 -10.76962;18.67756;-1.35301;,
 -8.59536;17.42226;1.34849;,
 -8.59536;17.42226;-1.35301;,
 -6.21785;23.22935;1.34849;,
 -6.21785;23.22935;-1.35301;,
 -4.96253;21.05508;1.34849;,
 -4.96253;21.05508;-1.35301;,
 0.00000;24.89541;1.34849;,
 0.00000;24.89541;-1.35301;,
 0.00000;22.38478;1.34849;,
 0.00000;22.38478;-1.35301;,
 4.96253;21.05508;1.34849;,
 6.21784;23.22935;1.34849;,
 0.00000;24.89541;-1.35301;,
 6.21784;23.22935;-1.35301;,
 4.96253;21.05508;-1.35301;,
 0.00000;22.38478;-1.35301;,
 8.59535;17.42226;1.34849;,
 10.76962;18.67756;1.34849;,
 10.76962;18.67756;-1.35301;,
 8.59535;17.42226;-1.35301;,
 9.92506;12.45974;1.34849;,
 12.43568;12.45974;1.34849;,
 12.43568;12.45974;-1.35301;,
 9.92506;12.45974;-1.35301;,
 8.59535;7.49721;1.34849;,
 10.76962;6.24189;1.34849;,
 10.76962;6.24189;-1.35301;,
 8.59535;7.49721;-1.35301;,
 4.96253;3.86438;1.34849;,
 6.21784;1.69012;1.34849;,
 6.21784;1.69012;-1.35301;,
 4.96253;3.86438;-1.35301;,
 0.00000;2.53468;1.34849;,
 0.00000;0.02405;1.34849;,
 0.00000;0.02405;-1.35301;,
 0.00000;2.53468;-1.35301;,
 -4.96253;3.86438;1.34849;,
 -6.21784;1.69011;1.34849;,
 -6.21784;1.69011;-1.35301;,
 -4.96253;3.86438;-1.35301;,
 -8.59535;7.49721;1.34849;,
 -10.76962;6.24189;1.34849;,
 -10.76962;6.24189;-1.35301;,
 -8.59535;7.49721;-1.35301;,
 -9.92506;12.45973;1.34849;,
 -12.43568;12.45973;1.34849;,
 -12.43568;12.45973;-1.35301;,
 -9.92506;12.45973;-1.35301;,
 -8.59536;17.42226;1.34849;,
 -10.76962;18.67756;1.34849;,
 -10.76962;18.67756;-1.35301;,
 -8.59536;17.42226;-1.35301;,
 -4.96253;21.05508;1.34849;,
 -6.21785;23.22935;1.34849;,
 -6.21785;23.22935;-1.35301;,
 -4.96253;21.05508;-1.35301;;
 
 84;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 3;26,1,0;,
 3;27,4,1;,
 3;28,6,4;,
 3;29,8,6;,
 3;30,10,8;,
 3;31,12,10;,
 3;32,14,12;,
 3;33,16,14;,
 3;34,18,16;,
 3;35,20,18;,
 3;36,22,20;,
 3;37,24,22;,
 3;38,3,2;,
 3;39,2,5;,
 3;40,5,7;,
 3;41,7,9;,
 3;42,9,11;,
 3;43,11,13;,
 3;44,13,15;,
 3;45,15,17;,
 3;46,17,19;,
 3;47,19,21;,
 3;48,21,23;,
 3;49,23,25;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;51,58,59,52;,
 4;60,54,57,61;,
 4;58,62,63,59;,
 4;64,60,61,65;,
 4;62,66,67,63;,
 4;68,64,65,69;,
 4;66,70,71,67;,
 4;72,68,69,73;,
 4;70,74,75,71;,
 4;76,72,73,77;,
 4;74,78,79,75;,
 4;80,76,77,81;,
 4;78,82,83,79;,
 4;84,80,81,85;,
 4;82,86,87,83;,
 4;88,84,85,89;,
 4;86,90,91,87;,
 4;92,88,89,93;,
 4;90,94,95,91;,
 4;96,92,93,97;,
 4;94,98,99,95;,
 4;100,96,97,101;,
 4;50,55,102,103;,
 4;104,105,106,107;,
 4;103,102,108,109;,
 4;105,110,111,106;,
 4;109,108,112,113;,
 4;110,114,115,111;,
 4;113,112,116,117;,
 4;114,118,119,115;,
 4;117,116,120,121;,
 4;118,122,123,119;,
 4;121,120,124,125;,
 4;122,126,127,123;,
 4;125,124,128,129;,
 4;126,130,131,127;,
 4;129,128,132,133;,
 4;130,134,135,131;,
 4;133,132,136,137;,
 4;134,138,139,135;,
 4;137,136,140,141;,
 4;138,142,143,139;,
 4;141,140,144,145;,
 4;142,146,147,143;,
 4;145,144,55,50;,
 4;146,104,107,147;;
 
 MeshMaterialList {
  5;
  84;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.674400;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.718400;0.000000;0.000000;1.000000;;
   9.000000;
   0.300000;0.300000;0.300000;;
   0.044900;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.500000;0.866025;0.000000;,
  0.866025;0.500001;0.000000;,
  1.000000;0.000000;0.000000;,
  0.866026;-0.500000;-0.000000;,
  0.500000;-0.866025;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.499999;-0.866026;0.000000;,
  -0.866025;-0.500000;0.000000;,
  -1.000000;-0.000001;0.000000;,
  -0.866026;0.499999;0.000000;,
  -0.500001;0.866025;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.500000;0.866025;0.000000;,
  0.866026;0.499999;0.000000;,
  1.000000;0.000001;0.000000;,
  0.866025;-0.500000;-0.000000;,
  0.500000;-0.866025;-0.000000;,
  0.000001;-1.000000;-0.000000;,
  -0.500000;-0.866026;0.000000;,
  -0.866026;-0.500000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.866026;0.499999;0.000000;,
  -0.500000;0.866025;0.000000;,
  -0.499999;-0.866026;0.000000;,
  -0.866025;-0.500001;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.866026;0.500000;0.000000;,
  -0.500000;0.866025;0.000000;,
  0.000000;1.000000;0.000000;,
  0.866025;0.500000;0.000000;,
  1.000000;0.000001;0.000000;,
  0.866025;-0.500000;-0.000000;,
  0.499999;-0.866026;-0.000000;;
  84;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,1,1,12;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  4;14,15,15,14;,
  4;26,7,7,26;,
  4;15,16,16,15;,
  4;27,26,26,27;,
  4;16,17,17,16;,
  4;28,27,27,28;,
  4;17,18,18,17;,
  4;29,28,28,29;,
  4;18,19,19,18;,
  4;30,29,29,30;,
  4;19,20,20,19;,
  4;31,30,30,31;,
  4;20,21,21,20;,
  4;15,31,31,15;,
  4;21,22,22,21;,
  4;32,15,15,32;,
  4;22,23,23,22;,
  4;33,32,32,33;,
  4;23,24,24,23;,
  4;34,33,33,34;,
  4;24,25,25,24;,
  4;35,34,34,35;,
  4;25,14,14,25;,
  4;7,35,35,7;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;13,13,13,13;;
 }
 MeshTextureCoords {
  148;
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.083330;1.000000;,
  0.000000;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.416670;0.000000;,
  0.416670;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.583330;0.000000;,
  0.583330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.916670;0.000000;,
  0.916670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.041670;0.000000;,
  0.125000;0.000000;,
  0.208330;0.000000;,
  0.291670;0.000000;,
  0.375000;0.000000;,
  0.458330;0.000000;,
  0.541670;0.000000;,
  0.625000;0.000000;,
  0.708330;0.000000;,
  0.791670;0.000000;,
  0.875000;0.000000;,
  0.958330;0.000000;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.083330;1.000000;,
  0.000000;1.000000;,
  0.083330;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.083330;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.416670;0.000000;,
  0.416670;1.000000;,
  0.416670;0.000000;,
  0.416670;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.583330;0.000000;,
  0.583330;1.000000;,
  0.583330;0.000000;,
  0.583330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.916670;0.000000;,
  0.916670;1.000000;,
  0.916670;0.000000;,
  0.916670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
