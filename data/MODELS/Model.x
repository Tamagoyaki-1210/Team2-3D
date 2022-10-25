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
 259;
 0.00000;22.22461;0.00000;,
 1.03341;21.93391;-1.03341;,
 0.00000;21.93391;-1.46147;,
 0.00000;22.22461;0.00000;,
 1.46147;21.93391;0.00000;,
 0.00000;22.22461;0.00000;,
 1.03341;21.93391;1.03341;,
 0.00000;22.22461;0.00000;,
 -0.00000;21.93391;1.46147;,
 0.00000;22.22461;0.00000;,
 -1.03341;21.93391;1.03341;,
 0.00000;22.22461;0.00000;,
 -1.46147;21.93391;-0.00000;,
 0.00000;22.22461;0.00000;,
 -1.03341;21.93391;-1.03341;,
 0.00000;22.22461;0.00000;,
 0.00000;21.93391;-1.46147;,
 1.90950;21.10606;-1.90950;,
 0.00000;21.10606;-2.70044;,
 2.70044;21.10606;0.00000;,
 1.90950;21.10606;1.90950;,
 -0.00000;21.10606;2.70044;,
 -1.90950;21.10606;1.90950;,
 -2.70044;21.10606;-0.00000;,
 -1.90950;21.10606;-1.90950;,
 0.00000;21.10606;-2.70044;,
 2.49488;19.86708;-2.49488;,
 0.00000;19.86708;-3.52830;,
 3.52830;19.86708;0.00000;,
 2.49488;19.86708;2.49488;,
 -0.00000;19.86708;3.52830;,
 -2.49488;19.86708;2.49488;,
 -3.52830;19.86708;-0.00000;,
 -2.49488;19.86708;-2.49488;,
 0.00000;19.86708;-3.52830;,
 2.70044;18.40562;-2.70044;,
 0.00000;18.40562;-3.81900;,
 3.81900;18.40562;0.00000;,
 2.70044;18.40562;2.70044;,
 -0.00000;18.40562;3.81900;,
 -2.70044;18.40562;2.70044;,
 -3.81900;18.40562;-0.00000;,
 -2.70044;18.40562;-2.70044;,
 0.00000;18.40562;-3.81900;,
 2.49488;16.94415;-2.49488;,
 0.00000;16.94415;-3.52830;,
 3.52830;16.94415;0.00000;,
 2.49488;16.94415;2.49488;,
 -0.00000;16.94415;3.52830;,
 -2.49488;16.94415;2.49488;,
 -3.52830;16.94415;-0.00000;,
 -2.49488;16.94415;-2.49488;,
 0.00000;16.94415;-3.52830;,
 1.90950;15.70517;-1.90950;,
 0.00000;15.70517;-2.70044;,
 2.70044;15.70517;0.00000;,
 1.90950;15.70517;1.90950;,
 -0.00000;15.70517;2.70044;,
 -1.90950;15.70517;1.90950;,
 -2.70044;15.70517;-0.00000;,
 -1.90950;15.70517;-1.90950;,
 0.00000;15.70517;-2.70044;,
 1.03341;14.87732;-1.03341;,
 0.00000;14.87732;-1.46147;,
 1.46147;14.87732;0.00000;,
 1.03341;14.87732;1.03341;,
 -0.00000;14.87732;1.46147;,
 -1.03341;14.87732;1.03341;,
 -1.46147;14.87732;-0.00000;,
 -1.03341;14.87732;-1.03341;,
 0.00000;14.87732;-1.46147;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 0.00000;14.58662;0.00000;,
 -2.80320;15.21902;-1.71941;,
 2.80320;15.21902;-1.71941;,
 2.80320;4.33547;-1.71941;,
 -2.80320;4.33547;-1.71941;,
 2.80320;15.21902;-1.71941;,
 2.80320;15.21902;1.71941;,
 2.80320;4.33547;1.71941;,
 2.80320;4.33547;-1.71941;,
 2.80320;15.21902;1.71941;,
 -2.80320;15.21902;1.71941;,
 -2.80320;4.33547;1.71941;,
 2.80320;4.33547;1.71941;,
 -2.80320;15.21902;1.71941;,
 -2.80320;15.21902;-1.71941;,
 -2.80320;4.33547;-1.71941;,
 -2.80320;4.33547;1.71941;,
 2.80320;15.21902;-1.71941;,
 -2.80320;15.21902;-1.71941;,
 -2.80320;4.33547;-1.71941;,
 2.80320;4.33547;-1.71941;,
 -6.25025;12.36160;-1.00835;,
 -0.50228;12.36160;-1.00835;,
 -0.50228;9.38586;-1.00835;,
 -6.25025;9.38586;-1.00835;,
 -0.50228;12.36160;-1.00835;,
 -0.50228;12.36160;1.00835;,
 -0.50228;9.38586;1.00835;,
 -0.50228;9.38586;-1.00835;,
 -0.50228;12.36160;1.00835;,
 -6.25025;12.36160;1.00835;,
 -6.25025;9.38586;1.00835;,
 -0.50228;9.38586;1.00835;,
 -6.25025;12.36160;1.00835;,
 -6.25025;12.36160;-1.00835;,
 -6.25025;9.38586;-1.00835;,
 -6.25025;9.38586;1.00835;,
 -0.50228;12.36160;-1.00835;,
 -6.25025;12.36160;-1.00835;,
 -6.25025;9.38586;-1.00835;,
 -0.50228;9.38586;-1.00835;,
 0.98971;12.28615;-1.00835;,
 6.73767;12.28615;-1.00835;,
 6.73767;9.31041;-1.00835;,
 0.98971;9.31041;-1.00835;,
 6.73767;12.28615;-1.00835;,
 6.73767;12.28615;1.00835;,
 6.73767;9.31041;1.00835;,
 6.73767;9.31041;-1.00835;,
 6.73767;12.28615;1.00835;,
 0.98971;12.28615;1.00835;,
 0.98971;9.31041;1.00835;,
 6.73767;9.31041;1.00835;,
 0.98971;12.28615;1.00835;,
 0.98971;12.28615;-1.00835;,
 0.98971;9.31041;-1.00835;,
 0.98971;9.31041;1.00835;,
 6.73767;12.28615;-1.00835;,
 0.98971;12.28615;-1.00835;,
 0.98971;9.31041;-1.00835;,
 6.73767;9.31041;-1.00835;,
 -9.29821;11.96586;-0.74014;,
 -3.25628;11.96586;-0.74014;,
 -3.25628;9.63532;-0.74014;,
 -9.29821;9.63532;-0.74014;,
 -3.25628;11.96586;-0.74014;,
 -3.25628;11.96586;0.74014;,
 -3.25628;9.63532;0.74014;,
 -3.25628;9.63532;-0.74014;,
 -3.25628;11.96586;0.74014;,
 -9.29821;11.96586;0.74014;,
 -9.29821;9.63532;0.74014;,
 -3.25628;9.63532;0.74014;,
 -9.29821;11.96586;0.74014;,
 -9.29821;11.96586;-0.74014;,
 -9.29821;9.63532;-0.74014;,
 -9.29821;9.63532;0.74014;,
 -3.25628;11.96586;-0.74014;,
 -9.29821;11.96586;-0.74014;,
 -9.29821;9.63532;-0.74014;,
 -3.25628;9.63532;-0.74014;,
 3.48774;11.89041;-0.74014;,
 9.52966;11.89041;-0.74014;,
 9.52966;9.55987;-0.74014;,
 3.48774;9.55987;-0.74014;,
 9.52966;11.89041;-0.74014;,
 9.52966;11.89041;0.74014;,
 9.52966;9.55987;0.74014;,
 9.52966;9.55987;-0.74014;,
 9.52966;11.89041;0.74014;,
 3.48774;11.89041;0.74014;,
 3.48774;9.55987;0.74014;,
 9.52966;9.55987;0.74014;,
 3.48774;11.89041;0.74014;,
 3.48774;11.89041;-0.74014;,
 3.48774;9.55987;-0.74014;,
 3.48774;9.55987;0.74014;,
 9.52966;11.89041;-0.74014;,
 3.48774;11.89041;-0.74014;,
 3.48774;9.55987;-0.74014;,
 9.52966;9.55987;-0.74014;,
 -2.47759;5.27548;-1.18875;,
 -0.29336;5.27548;-1.18875;,
 -0.29336;1.73219;-1.18875;,
 -2.47759;1.73219;-1.18875;,
 -0.29336;5.27548;-1.18875;,
 -0.29336;5.27548;1.18875;,
 -0.29336;1.73219;1.18875;,
 -0.29336;1.73219;-1.18875;,
 -0.29336;5.27548;1.18875;,
 -2.47759;5.27548;1.18875;,
 -2.47759;1.73219;1.18875;,
 -0.29336;1.73219;1.18875;,
 -2.47759;5.27548;1.18875;,
 -2.47759;5.27548;-1.18875;,
 -2.47759;1.73219;-1.18875;,
 -2.47759;1.73219;1.18875;,
 -0.29336;5.27548;-1.18875;,
 -2.47759;5.27548;-1.18875;,
 -2.47759;1.73219;-1.18875;,
 -0.29336;1.73219;-1.18875;,
 0.29053;5.27548;-1.18875;,
 2.47476;5.27548;-1.18875;,
 2.47476;1.73219;-1.18875;,
 0.29053;1.73219;-1.18875;,
 2.47476;5.27548;-1.18875;,
 2.47476;5.27548;1.18875;,
 2.47476;1.73219;1.18875;,
 2.47476;1.73219;-1.18875;,
 2.47476;5.27548;1.18875;,
 0.29053;5.27548;1.18875;,
 0.29053;1.73219;1.18875;,
 2.47476;1.73219;1.18875;,
 0.29053;5.27548;1.18875;,
 0.29053;5.27548;-1.18875;,
 0.29053;1.73219;-1.18875;,
 0.29053;1.73219;1.18875;,
 2.47476;5.27548;-1.18875;,
 0.29053;5.27548;-1.18875;,
 0.29053;1.73219;-1.18875;,
 2.47476;1.73219;-1.18875;,
 -1.99236;2.62266;-0.61850;,
 -0.77980;2.62266;-0.61850;,
 -0.77980;-0.01737;-0.61850;,
 -1.99236;-0.01737;-0.61850;,
 -0.77980;2.62266;-0.61850;,
 -0.77980;2.62266;0.61850;,
 -0.77980;-0.01737;0.61850;,
 -0.77980;-0.01737;-0.61850;,
 -0.77980;2.62266;0.61850;,
 -1.99236;2.62266;0.61850;,
 -1.99236;-0.01737;0.61850;,
 -0.77980;-0.01737;0.61850;,
 -1.99236;2.62266;0.61850;,
 -1.99236;2.62266;-0.61850;,
 -1.99236;-0.01737;-0.61850;,
 -1.99236;-0.01737;0.61850;,
 -0.77980;2.62266;-0.61850;,
 -1.99236;2.62266;-0.61850;,
 -1.99236;-0.01737;-0.61850;,
 -0.77980;-0.01737;-0.61850;,
 0.86128;2.62266;-0.61850;,
 2.07384;2.62266;-0.61850;,
 2.07384;-0.01737;-0.61850;,
 0.86128;-0.01737;-0.61850;,
 2.07384;2.62266;-0.61850;,
 2.07384;2.62266;0.61850;,
 2.07384;-0.01737;0.61850;,
 2.07384;-0.01737;-0.61850;,
 2.07384;2.62266;0.61850;,
 0.86128;2.62266;0.61850;,
 0.86128;-0.01737;0.61850;,
 2.07384;-0.01737;0.61850;,
 0.86128;2.62266;0.61850;,
 0.86128;2.62266;-0.61850;,
 0.86128;-0.01737;-0.61850;,
 0.86128;-0.01737;0.61850;,
 2.07384;2.62266;-0.61850;,
 0.86128;2.62266;-0.61850;,
 0.86128;-0.01737;-0.61850;,
 2.07384;-0.01737;-0.61850;;
 
 118;
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
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;91,84,95,96;,
 4;97,98,85,94;,
 4;99,100,101,102;,
 4;103,104,105,106;,
 4;107,108,109,110;,
 4;111,112,113,114;,
 4;111,104,115,116;,
 4;117,118,105,114;,
 4;119,120,121,122;,
 4;123,124,125,126;,
 4;127,128,129,130;,
 4;131,132,133,134;,
 4;131,124,135,136;,
 4;137,138,125,134;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;147,148,149,150;,
 4;151,152,153,154;,
 4;151,144,155,156;,
 4;157,158,145,154;,
 4;159,160,161,162;,
 4;163,164,165,166;,
 4;167,168,169,170;,
 4;171,172,173,174;,
 4;171,164,175,176;,
 4;177,178,165,174;,
 4;179,180,181,182;,
 4;183,184,185,186;,
 4;187,188,189,190;,
 4;191,192,193,194;,
 4;191,184,195,196;,
 4;197,198,185,194;,
 4;199,200,201,202;,
 4;203,204,205,206;,
 4;207,208,209,210;,
 4;211,212,213,214;,
 4;211,204,215,216;,
 4;217,218,205,214;,
 4;219,220,221,222;,
 4;223,224,225,226;,
 4;227,228,229,230;,
 4;231,232,233,234;,
 4;231,224,235,236;,
 4;237,238,225,234;,
 4;239,240,241,242;,
 4;243,244,245,246;,
 4;247,248,249,250;,
 4;251,252,253,254;,
 4;251,244,255,256;,
 4;257,258,245,254;;
 
 MeshMaterialList {
  1;
  118;
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
   0.056471;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  112;
  0.000000;1.000000;0.000000;,
  -0.000000;0.924736;-0.380608;,
  0.269131;0.924736;-0.269131;,
  0.380608;0.924736;0.000000;,
  0.269131;0.924736;0.269131;,
  -0.000000;0.924736;0.380608;,
  -0.269131;0.924736;0.269131;,
  -0.380608;0.924736;0.000000;,
  -0.269131;0.924736;-0.269131;,
  -0.000000;0.709231;-0.704976;,
  0.498493;0.709231;-0.498493;,
  0.704976;0.709231;-0.000000;,
  0.498493;0.709231;0.498493;,
  -0.000000;0.709231;0.704976;,
  -0.498493;0.709231;0.498493;,
  -0.704976;0.709231;0.000000;,
  -0.498493;0.709231;-0.498493;,
  -0.000000;0.384550;-0.923104;,
  0.652733;0.384550;-0.652733;,
  0.923104;0.384550;0.000000;,
  0.652733;0.384550;0.652733;,
  -0.000000;0.384550;0.923104;,
  -0.652733;0.384550;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384550;-0.652733;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;-0.384550;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384550;0.000000;,
  0.652733;-0.384550;0.652733;,
  -0.000000;-0.384550;0.923104;,
  -0.652733;-0.384550;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652733;-0.384550;-0.652733;,
  -0.000000;-0.709231;-0.704976;,
  0.498493;-0.709231;-0.498493;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709231;0.498493;,
  -0.000000;-0.709231;0.704976;,
  -0.498493;-0.709231;0.498493;,
  -0.704976;-0.709231;-0.000000;,
  -0.498493;-0.709231;-0.498493;,
  -0.000000;-0.924736;-0.380608;,
  0.269131;-0.924736;-0.269131;,
  0.380609;-0.924736;0.000000;,
  0.269131;-0.924736;0.269131;,
  -0.000000;-0.924736;0.380609;,
  -0.269131;-0.924736;0.269131;,
  -0.380608;-0.924736;-0.000000;,
  -0.269131;-0.924736;-0.269131;,
  -0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  118;
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
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;107,107,107,107;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;111,111,111,111;;
 }
 MeshTextureCoords {
  259;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}