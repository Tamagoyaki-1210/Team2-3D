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
 113;
 -0.00423;-0.00398;-0.83000;,
 -0.00423;-6.38054;-0.83000;,
 -0.59113;-6.38054;-0.58690;,
 -0.59113;-0.00398;-0.58690;,
 -0.83423;-6.38054;0.00000;,
 -0.83423;-0.00398;0.00000;,
 -0.59113;-6.38054;0.58690;,
 -0.59113;-0.00398;0.58690;,
 -0.00423;-6.38054;0.83000;,
 -0.00423;-0.00398;0.83000;,
 0.58267;-6.38054;0.58690;,
 0.58267;-0.00398;0.58690;,
 0.82577;-6.38054;-0.00000;,
 0.82577;-0.00398;-0.00000;,
 0.58267;-6.38054;-0.58690;,
 0.58267;-0.00398;-0.58690;,
 -0.00423;-6.38054;-0.83000;,
 -0.00423;-0.00398;-0.83000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-0.00398;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00423;-6.38054;0.00000;,
 -0.00105;1.72753;0.00000;,
 -0.00105;1.59612;-0.66064;,
 -0.46820;1.59612;-0.46715;,
 -0.00105;1.72753;0.00000;,
 -0.66170;1.59612;0.00000;,
 -0.00105;1.72753;0.00000;,
 -0.46820;1.59612;0.46715;,
 -0.00105;1.72753;0.00000;,
 -0.00105;1.59612;0.66064;,
 -0.00105;1.72753;0.00000;,
 0.46609;1.59612;0.46715;,
 -0.00105;1.72753;0.00000;,
 0.65959;1.59612;0.00000;,
 -0.00105;1.72753;0.00000;,
 0.46609;1.59612;-0.46715;,
 -0.00105;1.72753;0.00000;,
 -0.00105;1.59612;-0.66064;,
 -0.00105;1.22190;-1.22071;,
 -0.86423;1.22190;-0.86317;,
 -1.22176;1.22190;0.00000;,
 -0.86423;1.22190;0.86317;,
 -0.00105;1.22190;1.22071;,
 0.86211;1.22190;0.86317;,
 1.21966;1.22190;0.00000;,
 0.86211;1.22190;-0.86317;,
 -0.00105;1.22190;-1.22071;,
 -0.00105;0.66184;-1.59493;,
 -1.12884;0.66184;-1.12779;,
 -1.59599;0.66184;0.00000;,
 -1.12884;0.66184;1.12779;,
 -0.00105;0.66184;1.59493;,
 1.12673;0.66184;1.12779;,
 1.59388;0.66184;0.00000;,
 1.12673;0.66184;-1.12779;,
 -0.00105;0.66184;-1.59493;,
 -0.00105;0.00119;-1.72634;,
 -1.22176;0.00119;-1.22071;,
 -1.72740;0.00119;0.00000;,
 -1.22176;0.00119;1.22071;,
 -0.00105;0.00119;1.72634;,
 1.21966;0.00119;1.22071;,
 1.72529;0.00119;0.00000;,
 1.21966;0.00119;-1.22071;,
 -0.00105;0.00119;-1.72634;,
 -0.00105;-0.65946;-1.59493;,
 -1.12884;-0.65946;-1.12779;,
 -1.59599;-0.65946;0.00000;,
 -1.12884;-0.65946;1.12779;,
 -0.00105;-0.65946;1.59493;,
 1.12673;-0.65946;1.12779;,
 1.59388;-0.65946;-0.00000;,
 1.12673;-0.65946;-1.12779;,
 -0.00105;-0.65946;-1.59493;,
 -0.00105;-1.21952;-1.22071;,
 -0.86423;-1.21952;-0.86317;,
 -1.22176;-1.21952;0.00000;,
 -0.86423;-1.21952;0.86317;,
 -0.00105;-1.21952;1.22071;,
 0.86211;-1.21952;0.86317;,
 1.21966;-1.21952;-0.00000;,
 0.86211;-1.21952;-0.86317;,
 -0.00105;-1.21952;-1.22071;,
 -0.00105;-1.59375;-0.66064;,
 -0.46820;-1.59375;-0.46715;,
 -0.66170;-1.59375;0.00000;,
 -0.46820;-1.59375;0.46715;,
 -0.00105;-1.59375;0.66064;,
 0.46609;-1.59375;0.46715;,
 0.65959;-1.59375;-0.00000;,
 0.46609;-1.59375;-0.46715;,
 -0.00105;-1.59375;-0.66064;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;,
 -0.00105;-1.72515;0.00000;;
 
 88;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 3;18,0,3;,
 3;19,3,5;,
 3;20,5,7;,
 3;21,7,9;,
 3;22,9,11;,
 3;23,11,13;,
 3;24,13,15;,
 3;25,15,17;,
 3;26,2,1;,
 3;27,4,2;,
 3;28,6,4;,
 3;29,8,6;,
 3;30,10,8;,
 3;31,12,10;,
 3;32,14,12;,
 3;33,16,14;,
 3;34,35,36;,
 3;37,36,38;,
 3;39,38,40;,
 3;41,40,42;,
 3;43,42,44;,
 3;45,44,46;,
 3;47,46,48;,
 3;49,48,50;,
 4;35,51,52,36;,
 4;36,52,53,38;,
 4;38,53,54,40;,
 4;40,54,55,42;,
 4;42,55,56,44;,
 4;44,56,57,46;,
 4;46,57,58,48;,
 4;48,58,59,50;,
 4;51,60,61,52;,
 4;52,61,62,53;,
 4;53,62,63,54;,
 4;54,63,64,55;,
 4;55,64,65,56;,
 4;56,65,66,57;,
 4;57,66,67,58;,
 4;58,67,68,59;,
 4;60,69,70,61;,
 4;61,70,71,62;,
 4;62,71,72,63;,
 4;63,72,73,64;,
 4;64,73,74,65;,
 4;65,74,75,66;,
 4;66,75,76,67;,
 4;67,76,77,68;,
 4;69,78,79,70;,
 4;70,79,80,71;,
 4;71,80,81,72;,
 4;72,81,82,73;,
 4;73,82,83,74;,
 4;74,83,84,75;,
 4;75,84,85,76;,
 4;76,85,86,77;,
 4;78,87,88,79;,
 4;79,88,89,80;,
 4;80,89,90,81;,
 4;81,90,91,82;,
 4;82,91,92,83;,
 4;83,92,93,84;,
 4;84,93,94,85;,
 4;85,94,95,86;,
 4;87,96,97,88;,
 4;88,97,98,89;,
 4;89,98,99,90;,
 4;90,99,100,91;,
 4;91,100,101,92;,
 4;92,101,102,93;,
 4;93,102,103,94;,
 4;94,103,104,95;,
 3;96,105,97;,
 3;97,106,98;,
 3;98,107,99;,
 3;99,108,100;,
 3;100,109,101;,
 3;101,110,102;,
 3;102,111,103;,
 3;103,112,104;;
 
 MeshMaterialList {
  2;
  88;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   6.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  68;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.707107;0.000000;-0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  0.707106;0.000000;0.707107;,
  1.000000;0.000000;0.000000;,
  0.707106;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000001;1.000000;0.000000;,
  0.000002;0.924736;-0.380609;,
  -0.269129;0.924737;-0.269131;,
  -0.380609;0.924736;0.000000;,
  -0.269129;0.924737;0.269131;,
  0.000002;0.924736;0.380609;,
  0.269130;0.924736;0.269132;,
  0.380608;0.924736;0.000000;,
  0.269130;0.924736;-0.269132;,
  0.000002;0.709234;-0.704973;,
  -0.498490;0.709234;-0.498492;,
  -0.704974;0.709234;0.000000;,
  -0.498490;0.709234;0.498492;,
  0.000002;0.709234;0.704973;,
  0.498490;0.709234;0.498493;,
  0.704972;0.709235;0.000000;,
  0.498490;0.709234;-0.498493;,
  0.000001;0.384552;-0.923103;,
  -0.652731;0.384552;-0.652734;,
  -0.923103;0.384553;0.000000;,
  -0.652731;0.384552;0.652734;,
  0.000001;0.384552;0.923103;,
  0.652731;0.384554;0.652733;,
  0.923102;0.384556;0.000000;,
  0.652731;0.384554;-0.652733;,
  0.000000;0.000000;-1.000000;,
  -0.707104;0.000000;-0.707109;,
  -1.000000;0.000000;0.000000;,
  -0.707104;0.000000;0.707109;,
  0.000000;0.000000;1.000000;,
  0.707106;0.000000;0.707108;,
  1.000000;0.000000;0.000000;,
  0.707106;0.000000;-0.707108;,
  0.000001;-0.384552;-0.923103;,
  -0.652731;-0.384552;-0.652734;,
  -0.923103;-0.384553;0.000000;,
  -0.652731;-0.384552;0.652734;,
  0.000001;-0.384552;0.923103;,
  0.652731;-0.384554;0.652733;,
  0.923102;-0.384555;-0.000000;,
  0.652731;-0.384554;-0.652733;,
  0.000002;-0.709229;-0.704978;,
  -0.498494;-0.709229;-0.498495;,
  -0.704979;-0.709228;0.000000;,
  -0.498494;-0.709229;0.498495;,
  0.000002;-0.709229;0.704978;,
  0.498493;-0.709229;0.498497;,
  0.704977;-0.709230;-0.000000;,
  0.498493;-0.709229;-0.498497;,
  0.000002;-0.924737;-0.380608;,
  -0.269128;-0.924737;-0.269130;,
  -0.380608;-0.924736;0.000000;,
  -0.269128;-0.924737;0.269130;,
  0.000002;-0.924737;0.380608;,
  0.269129;-0.924737;0.269131;,
  0.380607;-0.924737;-0.000000;,
  0.269129;-0.924737;-0.269131;,
  0.000001;-1.000000;-0.000000;;
  88;
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,1,1;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;10,11,12;,
  3;10,12,13;,
  3;10,13,14;,
  3;10,14,15;,
  3;10,15,16;,
  3;10,16,17;,
  3;10,17,18;,
  3;10,18,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,19,11;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,27,19;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,35,27;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,43,35;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,57,49;,
  4;49,57,58,50;,
  4;50,58,51,43;,
  4;51,59,60,52;,
  4;52,60,61,53;,
  4;53,61,62,54;,
  4;54,62,63,55;,
  4;55,63,64,56;,
  4;56,64,65,57;,
  4;57,65,66,58;,
  4;58,66,59,51;,
  3;59,67,60;,
  3;60,67,61;,
  3;61,67,62;,
  3;62,67,63;,
  3;63,67,64;,
  3;64,67,65;,
  3;65,67,66;,
  3;66,67,59;;
 }
 MeshTextureCoords {
  113;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
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
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
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
  0.937500;1.000000;;
 }
}
