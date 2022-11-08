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
 153;
 0.00000;21.49170;-1.89000;,
 0.94500;21.49170;-1.63679;,
 1.10000;13.78497;-1.90526;,
 0.00000;13.78497;-2.20000;,
 1.63679;21.49170;-0.94500;,
 1.90526;13.78497;-1.10000;,
 1.89000;21.49170;0.00000;,
 2.20000;13.78497;0.00000;,
 1.63679;21.49170;0.94500;,
 1.90526;13.78497;1.10000;,
 0.94500;21.49170;1.63679;,
 1.10000;13.78497;1.90526;,
 0.00000;21.49170;1.89000;,
 0.00000;13.78497;2.20000;,
 -0.94500;21.49170;1.63679;,
 -1.10000;13.78497;1.90526;,
 -1.63679;21.49170;0.94500;,
 -1.90526;13.78497;1.10000;,
 -1.89000;21.49170;0.00000;,
 -2.20000;13.78497;0.00000;,
 -1.63679;21.49170;-0.94500;,
 -1.90526;13.78497;-1.10000;,
 -0.94500;21.49170;-1.63679;,
 -1.10000;13.78497;-1.90526;,
 0.00000;21.49170;-1.89000;,
 0.00000;13.78497;-2.20000;,
 2.70598;12.49623;-2.70598;,
 0.00000;11.09809;-2.10000;,
 1.81865;11.09809;-1.05000;,
 2.10000;11.09809;0.00000;,
 2.70598;12.49623;2.70598;,
 1.05000;11.09809;1.81865;,
 0.00000;11.09809;2.10000;,
 -2.70598;12.49623;2.70598;,
 -1.81865;11.09809;1.05000;,
 -2.10000;11.09809;0.00000;,
 -2.70598;12.49623;-2.70598;,
 -1.05000;11.09809;-1.81865;,
 0.00000;11.09809;-2.10000;,
 1.00000;8.00000;-1.73205;,
 0.00000;8.00000;-2.00000;,
 1.73205;8.00000;-1.00000;,
 2.00000;8.00000;0.00000;,
 1.73205;8.00000;1.00000;,
 1.00000;8.00000;1.73205;,
 0.00000;8.00000;2.00000;,
 -1.00000;8.00000;1.73205;,
 -1.73205;8.00000;1.00000;,
 -2.00000;8.00000;0.00000;,
 -1.73205;8.00000;-1.00000;,
 -1.00000;8.00000;-1.73205;,
 0.00000;8.00000;-2.00000;,
 1.00000;5.33333;-1.73205;,
 0.00000;5.33333;-2.00000;,
 1.73205;5.33333;-1.00000;,
 2.00000;5.33333;0.00000;,
 1.73205;5.33333;1.00000;,
 1.00000;5.33333;1.73205;,
 0.00000;5.33333;2.00000;,
 -1.00000;5.33333;1.73205;,
 -1.73205;5.33333;1.00000;,
 -2.00000;5.33333;0.00000;,
 -1.73205;5.33333;-1.00000;,
 -1.00000;5.33333;-1.73205;,
 0.00000;5.33333;-2.00000;,
 0.99495;2.80000;-1.80381;,
 0.00000;2.80000;-2.20000;,
 1.90526;2.80000;-1.10000;,
 2.08704;2.80000;0.00000;,
 1.90526;2.80000;1.10000;,
 1.10000;2.80000;1.90526;,
 0.00000;2.80000;2.20000;,
 -1.10000;2.80000;1.90526;,
 -1.90526;2.80000;1.10000;,
 -2.08801;2.80000;0.00000;,
 -1.90526;2.80000;-1.10000;,
 -0.89081;2.80000;-1.71433;,
 0.00000;2.80000;-2.20000;,
 1.12778;-0.13337;-1.81170;,
 0.00000;-0.13333;-2.80278;,
 2.39356;-0.13333;-1.52106;,
 1.93433;-0.13337;0.10931;,
 2.33521;-0.13333;1.32000;,
 1.07564;-0.13337;1.70425;,
 0.00000;-0.13333;3.01608;,
 -0.97992;-0.13337;1.81435;,
 -2.58049;-0.13333;1.59043;,
 -1.99035;-0.13333;0.00000;,
 -2.43422;-0.13333;-1.42762;,
 -1.03714;-0.13333;-1.72201;,
 0.00000;-0.13333;-2.80278;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;21.49170;0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;-0.13333;-0.00000;,
 0.00000;12.34600;-6.50000;,
 0.00000;36.34600;0.00000;,
 3.25000;12.34600;-5.62917;,
 0.00000;36.34600;0.00000;,
 5.62917;12.34600;-3.25000;,
 0.00000;36.34600;0.00000;,
 6.50000;12.34600;0.00000;,
 0.00000;36.34600;0.00000;,
 5.62916;12.34600;3.25000;,
 0.00000;36.34600;0.00000;,
 3.25000;12.34600;5.62916;,
 0.00000;36.34600;0.00000;,
 0.00000;12.34600;6.50000;,
 0.00000;36.34600;0.00000;,
 -3.25000;12.34600;5.62917;,
 0.00000;36.34600;0.00000;,
 -5.62916;12.34600;3.25000;,
 0.00000;36.34600;0.00000;,
 -6.50000;12.34600;0.00000;,
 0.00000;36.34600;0.00000;,
 -5.62917;12.34600;-3.25000;,
 0.00000;36.34600;0.00000;,
 -3.25000;12.34600;-5.62916;,
 0.00000;36.34600;0.00000;,
 0.00000;12.34600;-6.50000;,
 0.00000;12.34600;0.00000;,
 0.00000;12.34600;-6.50000;,
 3.25000;12.34600;-5.62917;,
 5.62917;12.34600;-3.25000;,
 6.50000;12.34600;0.00000;,
 5.62916;12.34600;3.25000;,
 3.25000;12.34600;5.62916;,
 0.00000;12.34600;6.50000;,
 -3.25000;12.34600;5.62917;,
 -5.62916;12.34600;3.25000;,
 -6.50000;12.34600;0.00000;,
 -5.62917;12.34600;-3.25000;,
 -3.25000;12.34600;-5.62916;;
 
 120;
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
 4;3,2,26,27;,
 4;2,5,28,26;,
 4;5,7,29,28;,
 4;7,9,30,29;,
 4;9,11,31,30;,
 4;11,13,32,31;,
 4;13,15,33,32;,
 4;15,17,34,33;,
 4;17,19,35,34;,
 4;19,21,36,35;,
 4;21,23,37,36;,
 4;23,25,38,37;,
 4;27,26,39,40;,
 4;26,28,41,39;,
 4;28,29,42,41;,
 4;29,30,43,42;,
 4;30,31,44,43;,
 4;31,32,45,44;,
 4;32,33,46,45;,
 4;33,34,47,46;,
 4;34,35,48,47;,
 4;35,36,49,48;,
 4;36,37,50,49;,
 4;37,38,51,50;,
 4;40,39,52,53;,
 4;39,41,54,52;,
 4;41,42,55,54;,
 4;42,43,56,55;,
 4;43,44,57,56;,
 4;44,45,58,57;,
 4;45,46,59,58;,
 4;46,47,60,59;,
 4;47,48,61,60;,
 4;48,49,62,61;,
 4;49,50,63,62;,
 4;50,51,64,63;,
 4;53,52,65,66;,
 4;52,54,67,65;,
 4;54,55,68,67;,
 4;55,56,69,68;,
 4;56,57,70,69;,
 4;57,58,71,70;,
 4;58,59,72,71;,
 4;59,60,73,72;,
 4;60,61,74,73;,
 4;61,62,75,74;,
 4;62,63,76,75;,
 4;63,64,77,76;,
 4;66,65,78,79;,
 4;65,67,80,78;,
 4;67,68,81,80;,
 4;68,69,82,81;,
 4;69,70,83,82;,
 4;70,71,84,83;,
 4;71,72,85,84;,
 4;72,73,86,85;,
 4;73,74,87,86;,
 4;74,75,88,87;,
 4;75,76,89,88;,
 4;76,77,90,89;,
 3;91,1,0;,
 3;92,4,1;,
 3;93,6,4;,
 3;94,8,6;,
 3;95,10,8;,
 3;96,12,10;,
 3;97,14,12;,
 3;98,16,14;,
 3;99,18,16;,
 3;100,20,18;,
 3;101,22,20;,
 3;102,24,22;,
 3;103,79,78;,
 3;104,78,80;,
 3;105,80,81;,
 3;106,81,82;,
 3;107,82,83;,
 3;108,83,84;,
 3;109,84,85;,
 3;110,85,86;,
 3;111,86,87;,
 3;112,87,88;,
 3;113,88,89;,
 3;114,89,90;,
 3;115,116,117;,
 3;117,118,119;,
 3;119,120,121;,
 3;121,122,123;,
 3;123,124,125;,
 3;125,126,127;,
 3;127,128,129;,
 3;129,130,131;,
 3;131,132,133;,
 3;133,134,135;,
 3;135,136,137;,
 3;137,138,139;,
 3;140,141,142;,
 3;140,142,143;,
 3;140,143,144;,
 3;140,144,145;,
 3;140,145,146;,
 3;140,146,147;,
 3;140,147,148;,
 3;140,148,149;,
 3;140,149,150;,
 3;140,150,151;,
 3;140,151,152;,
 3;140,152,141;;
 
 MeshMaterialList {
  2;
  120;
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
   0.495686;0.348235;0.181961;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.081569;0.385882;0.141176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  132;
  0.000000;1.000000;0.000000;,
  -0.000000;0.040192;-0.999192;,
  0.499596;0.040192;-0.865326;,
  0.865326;0.040192;-0.499596;,
  0.999192;0.040192;0.000000;,
  0.865326;0.040192;0.499596;,
  0.499596;0.040192;0.865326;,
  0.000000;0.040192;0.999192;,
  -0.499596;0.040192;0.865326;,
  -0.865325;0.040192;0.499596;,
  -0.999192;0.040192;0.000000;,
  -0.865326;0.040192;-0.499596;,
  -0.499596;0.040192;-0.865325;,
  -0.072982;0.031937;-0.996822;,
  0.331427;0.056697;-0.941776;,
  0.935351;0.147168;-0.321654;,
  0.996822;0.031937;-0.072982;,
  0.941776;0.056697;0.331427;,
  0.321654;0.147168;0.935351;,
  0.072982;0.031937;0.996822;,
  -0.331427;0.056697;0.941776;,
  -0.935350;0.147168;0.321654;,
  -0.996822;0.031937;0.072982;,
  -0.941776;0.056697;-0.331426;,
  -0.321654;0.147168;-0.935350;,
  -0.121768;-0.020726;-0.992342;,
  0.018247;-0.007432;-0.999806;,
  0.977565;0.065707;-0.200121;,
  0.992342;-0.020726;-0.121767;,
  0.999806;-0.007432;0.018247;,
  0.200121;0.065707;0.977566;,
  0.121767;-0.020726;0.992342;,
  -0.018247;-0.007432;0.999806;,
  -0.977566;0.065707;0.200121;,
  -0.992342;-0.020726;0.121768;,
  -0.999806;-0.007432;-0.018247;,
  -0.200121;0.065707;-0.977565;,
  -0.050311;-0.033077;-0.998186;,
  0.359694;-0.034188;-0.932444;,
  0.921556;-0.056998;-0.384038;,
  0.998186;-0.033077;-0.050311;,
  0.932444;-0.034188;0.359694;,
  0.384038;-0.056998;0.921556;,
  0.050311;-0.033077;0.998186;,
  -0.359694;-0.034187;0.932444;,
  -0.921556;-0.056998;0.384038;,
  -0.998186;-0.033077;0.050311;,
  -0.932444;-0.034187;-0.359694;,
  -0.384038;-0.056998;-0.921556;,
  -0.014871;0.019930;-0.999691;,
  0.498760;0.024658;-0.866389;,
  0.863906;0.025937;-0.502984;,
  0.999621;0.027542;0.000000;,
  0.871611;0.033663;0.489041;,
  0.499612;0.039386;0.865353;,
  0.000000;0.039386;0.999224;,
  -0.499612;0.039386;0.865354;,
  -0.871557;0.033712;0.489133;,
  -0.999618;0.027643;0.000000;,
  -0.856774;0.020405;-0.515288;,
  -0.499512;0.012758;-0.866213;,
  -0.040032;0.070238;-0.996727;,
  0.485674;0.072833;-0.871101;,
  0.859570;0.066444;-0.506680;,
  0.998998;0.044399;-0.005686;,
  0.881887;0.054213;0.468333;,
  0.513306;0.060723;0.856054;,
  -0.000126;0.076883;0.997040;,
  -0.496350;0.075861;0.864802;,
  -0.874060;0.075462;0.479922;,
  -0.998347;0.057079;-0.006652;,
  -0.845047;0.062829;-0.530987;,
  -0.494796;0.056179;-0.867191;,
  0.519811;0.087357;-0.849803;,
  0.473978;0.096220;-0.875263;,
  0.426806;0.104811;-0.898249;,
  0.999349;0.034265;-0.011256;,
  0.996370;0.035937;-0.077170;,
  0.527372;0.043315;0.848530;,
  0.539476;0.055834;0.840148;,
  -0.494313;0.073110;0.866204;,
  -0.447289;0.075921;0.891161;,
  -0.998161;0.059174;-0.013175;,
  -0.996273;0.054096;0.067183;,
  -0.490157;0.087074;-0.867274;,
  -0.000004;-1.000000;-0.000002;,
  0.860734;0.508621;0.021003;,
  0.975963;0.172044;-0.133778;,
  -0.021003;0.508621;0.860734;,
  0.133778;0.172044;0.975963;,
  -0.860734;0.508621;-0.021004;,
  -0.975963;0.172044;0.133778;,
  0.021004;0.508621;-0.860734;,
  -0.133778;0.172044;-0.975963;,
  0.944291;-0.190430;-0.268423;,
  0.268423;-0.190430;0.944291;,
  -0.944291;-0.190430;0.268423;,
  -0.268423;-0.190430;-0.944291;,
  0.997975;0.032444;0.054706;,
  0.515072;0.030780;0.856594;,
  -0.539931;0.070092;0.838786;,
  -0.993574;0.063867;-0.093448;,
  -0.366677;0.087878;-0.926189;,
  -0.604462;0.084640;-0.792125;,
  -0.000018;-1.000000;0.000000;,
  -0.000006;-1.000000;0.000019;,
  0.000002;-1.000000;0.000003;,
  -0.000021;-1.000000;0.000005;,
  -0.000002;-1.000000;0.000002;,
  -0.000009;-1.000000;-0.000019;,
  0.000002;-1.000000;-0.000000;,
  0.000010;-1.000000;-0.000017;,
  -0.000010;-1.000000;-0.000017;,
  0.000001;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000000;0.261416;-0.965226;,
  0.482613;0.261415;-0.835911;,
  0.835911;0.261415;-0.482613;,
  0.965226;0.261415;0.000000;,
  0.835910;0.261415;0.482613;,
  0.482613;0.261415;0.835910;,
  0.000000;0.261415;0.965226;,
  -0.482613;0.261415;0.835911;,
  -0.835910;0.261415;0.482613;,
  -0.965226;0.261415;0.000000;,
  -0.835911;0.261415;-0.482613;,
  -0.482614;0.261415;-0.835910;,
  0.826549;0.298476;-0.477209;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.298476;0.954417;,
  -0.826550;0.298476;-0.477208;;
  120;
  4;1,2,14,13;,
  4;2,3,15,14;,
  4;3,4,16,15;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;6,7,19,18;,
  4;7,8,20,19;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;11,12,24,23;,
  4;12,1,13,24;,
  4;13,14,26,25;,
  4;86,15,27,87;,
  4;15,16,28,27;,
  4;16,17,29,28;,
  4;88,18,30,89;,
  4;18,19,31,30;,
  4;19,20,32,31;,
  4;90,21,33,91;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;92,24,36,93;,
  4;24,13,25,36;,
  4;25,26,38,37;,
  4;87,27,39,94;,
  4;27,28,40,39;,
  4;28,29,41,40;,
  4;89,30,42,95;,
  4;30,31,43,42;,
  4;31,32,44,43;,
  4;91,33,45,96;,
  4;33,34,46,45;,
  4;34,35,47,46;,
  4;93,36,48,97;,
  4;36,25,37,48;,
  4;37,38,50,49;,
  4;38,39,51,50;,
  4;39,40,52,51;,
  4;40,41,53,52;,
  4;41,42,54,53;,
  4;42,43,55,54;,
  4;43,44,56,55;,
  4;44,45,57,56;,
  4;45,46,58,57;,
  4;46,47,59,58;,
  4;47,48,60,59;,
  4;48,37,49,60;,
  4;49,50,62,61;,
  4;50,51,63,62;,
  4;51,52,64,63;,
  4;52,53,65,64;,
  4;53,54,66,65;,
  4;54,55,67,66;,
  4;55,56,68,67;,
  4;56,57,69,68;,
  4;57,58,70,69;,
  4;58,59,71,70;,
  4;59,60,72,71;,
  4;60,49,61,72;,
  4;61,62,74,73;,
  4;62,63,75,74;,
  4;63,64,76,98;,
  4;64,65,77,76;,
  4;65,66,78,99;,
  4;66,67,79,78;,
  4;67,68,80,100;,
  4;68,69,81,80;,
  4;69,70,82,101;,
  4;70,71,83,82;,
  4;71,72,84,102;,
  4;72,61,103,84;,
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
  3;85,104,105;,
  3;85,105,106;,
  3;85,106,107;,
  3;85,107,108;,
  3;85,108,109;,
  3;85,109,110;,
  3;85,110,111;,
  3;85,111,112;,
  3;85,112,113;,
  3;85,113,114;,
  3;85,114,115;,
  3;85,115,104;,
  3;116,128,117;,
  3;117,128,118;,
  3;118,128,119;,
  3;119,128,120;,
  3;120,130,121;,
  3;121,130,122;,
  3;122,130,123;,
  3;123,130,124;,
  3;124,131,125;,
  3;125,131,126;,
  3;126,131,127;,
  3;127,131,116;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;,
  3;129,129,129;;
 }
 MeshTextureCoords {
  153;
  0.000000;0.000000;,
  0.083333;0.000000;,
  0.083333;0.166667;,
  0.000000;0.166667;,
  0.166667;0.000000;,
  0.166667;0.166667;,
  0.250000;0.000000;,
  0.250000;0.166667;,
  0.333333;0.000000;,
  0.333333;0.166667;,
  0.416667;0.000000;,
  0.416667;0.166667;,
  0.500000;0.000000;,
  0.500000;0.166667;,
  0.583333;0.000000;,
  0.583333;0.166667;,
  0.666667;0.000000;,
  0.666667;0.166667;,
  0.750000;0.000000;,
  0.750000;0.166667;,
  0.833333;0.000000;,
  0.833333;0.166667;,
  0.916667;0.000000;,
  0.916667;0.166667;,
  1.000000;0.000000;,
  1.000000;0.166667;,
  0.083333;0.333333;,
  0.000000;0.333333;,
  0.166667;0.333333;,
  0.250000;0.333333;,
  0.333333;0.333333;,
  0.416667;0.333333;,
  0.500000;0.333333;,
  0.583333;0.333333;,
  0.666667;0.333333;,
  0.750000;0.333333;,
  0.833333;0.333333;,
  0.916667;0.333333;,
  1.000000;0.333333;,
  0.083333;0.500000;,
  0.000000;0.500000;,
  0.166667;0.500000;,
  0.250000;0.500000;,
  0.333333;0.500000;,
  0.416667;0.500000;,
  0.500000;0.500000;,
  0.583333;0.500000;,
  0.666667;0.500000;,
  0.750000;0.500000;,
  0.833333;0.500000;,
  0.916667;0.500000;,
  1.000000;0.500000;,
  0.083333;0.666667;,
  0.000000;0.666667;,
  0.166667;0.666667;,
  0.250000;0.666667;,
  0.333333;0.666667;,
  0.416667;0.666667;,
  0.500000;0.666667;,
  0.583333;0.666667;,
  0.666667;0.666667;,
  0.750000;0.666667;,
  0.833333;0.666667;,
  0.916667;0.666667;,
  1.000000;0.666667;,
  0.083333;0.833333;,
  0.000000;0.833333;,
  0.166667;0.833333;,
  0.250000;0.833333;,
  0.333333;0.833333;,
  0.416667;0.833333;,
  0.500000;0.833333;,
  0.583333;0.833333;,
  0.666667;0.833333;,
  0.750000;0.833333;,
  0.833333;0.833333;,
  0.916667;0.833333;,
  1.000000;0.833333;,
  0.083333;1.000000;,
  0.000000;1.000000;,
  0.166667;1.000000;,
  0.250000;1.000000;,
  0.333333;1.000000;,
  0.416667;1.000000;,
  0.500000;1.000000;,
  0.583333;1.000000;,
  0.666667;1.000000;,
  0.750000;1.000000;,
  0.833333;1.000000;,
  0.916667;1.000000;,
  1.000000;1.000000;,
  0.041667;0.000000;,
  0.125000;0.000000;,
  0.208333;0.000000;,
  0.291667;0.000000;,
  0.375000;0.000000;,
  0.458333;0.000000;,
  0.541667;0.000000;,
  0.625000;0.000000;,
  0.708333;0.000000;,
  0.791667;0.000000;,
  0.875000;0.000000;,
  0.958333;0.000000;,
  0.041667;1.000000;,
  0.125000;1.000000;,
  0.208333;1.000000;,
  0.291667;1.000000;,
  0.375000;1.000000;,
  0.458333;1.000000;,
  0.541667;1.000000;,
  0.625000;1.000000;,
  0.708333;1.000000;,
  0.791667;1.000000;,
  0.875000;1.000000;,
  0.958333;1.000000;,
  0.000000;1.000000;,
  0.041667;0.000000;,
  0.083333;1.000000;,
  0.083333;0.000000;,
  0.166667;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.208333;0.000000;,
  0.416667;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.291667;0.000000;,
  0.583333;1.000000;,
  0.333333;0.000000;,
  0.666667;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.416667;0.000000;,
  0.833333;1.000000;,
  0.458333;0.000000;,
  0.916667;1.000000;,
  0.500000;0.000000;,
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
  0.000000;0.000000;;
 }
}
