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
 61;
 0.00307;-0.00834;-0.01454;,
 1.27706;-0.29863;-1.28853;,
 0.00307;-0.29863;-1.81625;,
 0.00307;-0.00834;-0.01454;,
 1.80478;-0.29863;-0.01454;,
 0.00307;-0.00834;-0.01454;,
 1.27706;-0.29863;1.25944;,
 0.00307;-0.00834;-0.01454;,
 0.00307;-0.29863;1.78716;,
 0.00307;-0.00834;-0.01454;,
 -1.27091;-0.29863;1.25944;,
 0.00307;-0.00834;-0.01454;,
 -1.79863;-0.29863;-0.01454;,
 0.00307;-0.00834;-0.01454;,
 -1.27091;-0.29863;-1.28853;,
 0.00307;-0.00834;-0.01454;,
 0.00307;-0.29863;-1.81625;,
 2.20973;-1.09165;-2.22115;,
 0.00307;-1.09165;-3.13524;,
 3.12377;-1.09165;-0.01454;,
 2.20973;-1.09165;2.19207;,
 0.00307;-1.09165;3.10615;,
 -2.20354;-1.09165;2.19207;,
 -3.11758;-1.09165;-0.01454;,
 -2.20354;-1.09165;-2.22115;,
 0.00307;-1.09165;-3.13524;,
 2.55109;-2.17499;-2.56256;,
 0.00307;-2.17499;-3.61800;,
 3.60652;-2.17499;-0.01454;,
 2.55109;-2.17499;2.53347;,
 0.00307;-2.17499;3.58891;,
 -2.54495;-2.17499;2.53347;,
 -3.60040;-2.17499;-0.01454;,
 -2.54495;-2.17499;-2.56256;,
 0.00307;-2.17499;-3.61800;,
 2.20973;-3.25826;-2.22115;,
 0.00307;-3.25826;-3.13524;,
 3.12377;-3.25826;-0.01454;,
 2.20973;-3.25826;2.19207;,
 0.00307;-3.25826;3.10615;,
 -2.20354;-3.25826;2.19207;,
 -3.11758;-3.25826;-0.01454;,
 -2.20354;-3.25826;-2.22115;,
 0.00307;-3.25826;-3.13524;,
 1.27706;-4.05127;-1.28853;,
 0.00307;-4.05127;-1.81625;,
 1.80478;-4.05127;-0.01454;,
 1.27706;-4.05127;1.25944;,
 0.00307;-4.05127;1.78716;,
 -1.27091;-4.05127;1.25944;,
 -1.79863;-4.05127;-0.01454;,
 -1.27091;-4.05127;-1.28853;,
 0.00307;-4.05127;-1.81625;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;,
 0.00307;-4.34153;-0.01454;;
 
 48;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 3;45,44,53;,
 3;44,46,54;,
 3;46,47,55;,
 3;47,48,56;,
 3;48,49,57;,
 3;49,50,58;,
 3;50,51,59;,
 3;51,52,60;;
 
 MeshMaterialList {
  3;
  48;
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
   0.800000;0.680800;0.520800;1.000000;;
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
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  42;
  -0.000000;1.000000;0.000000;,
  -0.000001;0.939853;-0.341580;,
  0.241535;0.939852;-0.241534;,
  0.341577;0.939854;0.000000;,
  0.241534;0.939852;0.241535;,
  -0.000001;0.939853;0.341579;,
  -0.241539;0.939851;0.241536;,
  -0.341584;0.939851;0.000000;,
  -0.241539;0.939850;-0.241536;,
  -0.000002;0.667892;-0.744258;,
  0.526275;0.667886;-0.526272;,
  0.744262;0.667888;0.000000;,
  0.526275;0.667886;0.526273;,
  -0.000002;0.667892;0.744258;,
  -0.526272;0.667892;0.526269;,
  -0.744252;0.667898;0.000000;,
  -0.526273;0.667891;-0.526268;,
  -0.000001;-0.000012;-1.000000;,
  0.707110;-0.000011;-0.707104;,
  1.000000;-0.000012;0.000001;,
  0.707109;-0.000012;0.707105;,
  -0.000001;-0.000012;1.000000;,
  -0.707108;-0.000012;0.707106;,
  -1.000000;-0.000012;0.000000;,
  -0.707109;-0.000013;-0.707105;,
  -0.000001;-0.667903;-0.744248;,
  0.526269;-0.667896;-0.526266;,
  0.744253;-0.667898;0.000000;,
  0.526269;-0.667895;0.526267;,
  -0.000001;-0.667902;0.744249;,
  -0.526265;-0.667902;0.526261;,
  -0.744243;-0.667909;0.000000;,
  -0.526266;-0.667903;-0.526260;,
  -0.000001;-0.939857;-0.341569;,
  0.241528;-0.939856;-0.241528;,
  0.341567;-0.939857;0.000000;,
  0.241527;-0.939856;0.241528;,
  -0.000001;-0.939857;0.341569;,
  -0.241531;-0.939854;0.241529;,
  -0.341574;-0.939855;0.000000;,
  -0.241532;-0.939854;-0.241529;,
  -0.000000;-1.000000;0.000000;;
  48;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  3;33,34,41;,
  3;34,35,41;,
  3;35,36,41;,
  3;36,37,41;,
  3;37,38,41;,
  3;38,39,41;,
  3;39,40,41;,
  3;40,33,41;;
 }
 MeshTextureCoords {
  61;
  0.062500;0.000000;,
  0.125000;0.166670;,
  0.000000;0.166670;,
  0.187500;0.000000;,
  0.250000;0.166670;,
  0.312500;0.000000;,
  0.375000;0.166670;,
  0.437500;0.000000;,
  0.500000;0.166670;,
  0.562500;0.000000;,
  0.625000;0.166670;,
  0.687500;0.000000;,
  0.750000;0.166670;,
  0.812500;0.000000;,
  0.875000;0.166670;,
  0.937500;0.000000;,
  1.000000;0.166670;,
  0.125000;0.333330;,
  0.000000;0.333330;,
  0.250000;0.333330;,
  0.375000;0.333330;,
  0.500000;0.333330;,
  0.625000;0.333330;,
  0.750000;0.333330;,
  0.875000;0.333330;,
  1.000000;0.333330;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.666670;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.375000;0.666670;,
  0.500000;0.666670;,
  0.625000;0.666670;,
  0.750000;0.666670;,
  0.875000;0.666670;,
  1.000000;0.666670;,
  0.125000;0.833330;,
  0.000000;0.833330;,
  0.250000;0.833330;,
  0.375000;0.833330;,
  0.500000;0.833330;,
  0.625000;0.833330;,
  0.750000;0.833330;,
  0.875000;0.833330;,
  1.000000;0.833330;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}