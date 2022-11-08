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
 186;
 0.00000;65.20172;0.00000;,
 8.02830;61.22603;-8.02830;,
 0.00000;61.22603;-11.35373;,
 11.35373;61.22603;0.00000;,
 8.02830;61.22603;8.02830;,
 -0.00000;61.22603;11.35373;,
 -8.02830;61.22603;8.02830;,
 -11.35373;61.22603;-0.00000;,
 -8.02830;61.22603;-8.02830;,
 12.99007;50.81769;-12.99007;,
 0.00000;50.81769;-18.37074;,
 18.37074;50.81769;0.00000;,
 12.99007;50.81769;12.99007;,
 -0.00000;50.81769;18.37074;,
 -12.99008;50.81769;12.99007;,
 -18.37074;50.81769;-0.00000;,
 -12.99008;50.81769;-12.99007;,
 12.99007;37.95230;-12.99007;,
 0.00000;37.95230;-18.37074;,
 18.37074;37.95230;0.00000;,
 12.99007;37.95230;12.99007;,
 -0.00000;37.95230;18.37074;,
 -12.99007;37.95230;12.99007;,
 -18.37074;37.95230;-0.00000;,
 -12.99007;37.95230;-12.99007;,
 6.19424;25.04174;-6.94716;,
 0.00000;25.04174;-9.82477;,
 8.75998;25.04174;0.00000;,
 6.19424;25.04174;6.94716;,
 -0.00000;25.04174;9.82477;,
 -6.19425;25.04174;6.94716;,
 -8.75998;25.04174;-0.00000;,
 -6.19424;25.04174;-6.94716;,
 0.00000;17.62586;0.00000;,
 -7.11000;6.83584;-7.10200;,
 7.09500;6.83584;-7.10200;,
 7.09500;-0.28701;-7.10200;,
 -7.11000;-0.28701;-7.10200;,
 7.09500;6.83584;7.04500;,
 7.09500;-0.28701;7.04500;,
 -7.11000;6.83584;7.04500;,
 -7.11000;-0.28701;7.04500;,
 -7.11000;15.26134;5.79387;,
 -5.82312;15.26134;5.79387;,
 -5.82312;3.93452;5.79387;,
 -7.11000;3.93452;5.79387;,
 -5.82312;15.26134;7.04500;,
 -5.82312;3.93452;7.04500;,
 -7.11000;15.26134;7.04500;,
 -7.11000;3.93452;7.04500;,
 5.75669;15.26134;5.65531;,
 7.09500;15.26134;5.65531;,
 7.09500;3.93452;5.65531;,
 5.75669;3.93452;5.65531;,
 7.09500;15.26134;7.04500;,
 7.09500;3.93452;7.04500;,
 5.75669;15.26134;7.04500;,
 5.75669;3.93452;7.04500;,
 5.75669;15.26134;-7.10200;,
 7.09500;15.26134;-7.10200;,
 7.09500;3.93452;-7.10200;,
 5.75669;3.93452;-7.10200;,
 7.09500;15.26134;-5.77013;,
 7.09500;3.93452;-5.77013;,
 5.75669;15.26134;-5.77013;,
 5.75669;3.93452;-5.77013;,
 -7.11000;15.26134;-7.10200;,
 -5.78547;15.26134;-7.10200;,
 -5.78547;3.93452;-7.10200;,
 -7.11000;3.93452;-7.10200;,
 -5.78547;15.26134;-5.77013;,
 -5.78547;3.93452;-5.77013;,
 -7.11000;15.26134;-5.77013;,
 -7.11000;3.93452;-5.77013;,
 7.51036;15.51710;0.00000;,
 7.98131;16.33281;0.00000;,
 5.63636;16.33281;-5.66123;,
 5.30334;15.51710;-5.32822;,
 8.92322;16.33281;0.00000;,
 6.30238;16.33281;-6.32726;,
 9.39417;15.51710;0.00000;,
 6.63540;15.51710;-6.66028;,
 8.92322;14.70139;0.00000;,
 6.30238;14.70139;-6.32726;,
 7.98131;14.70139;0.00000;,
 5.63636;14.70139;-5.66123;,
 -0.02488;16.33281;-8.00619;,
 -0.02488;15.51710;-7.53524;,
 -0.02488;16.33281;-8.94810;,
 -0.02488;15.51710;-9.41905;,
 -0.02488;14.70139;-8.94810;,
 -0.02488;14.70139;-8.00619;,
 -5.68611;16.33281;-5.66123;,
 -5.35310;15.51710;-5.32822;,
 -6.35214;16.33281;-6.32726;,
 -6.68515;15.51710;-6.66028;,
 -6.35214;14.70139;-6.32726;,
 -5.68611;14.70139;-5.66123;,
 -8.03107;16.33281;0.00000;,
 -7.56012;15.51710;0.00000;,
 -8.97298;16.33281;0.00000;,
 -9.44393;15.51710;0.00000;,
 -8.97298;14.70139;0.00000;,
 -8.03107;14.70139;0.00000;,
 -5.68611;16.33281;5.66124;,
 -5.35310;15.51710;5.32822;,
 -6.35214;16.33281;6.32726;,
 -6.68515;15.51710;6.66028;,
 -6.35214;14.70139;6.32726;,
 -5.68611;14.70139;5.66124;,
 -0.02488;16.33281;8.00619;,
 -0.02488;15.51710;7.53524;,
 -0.02488;16.33281;8.94810;,
 -0.02488;15.51710;9.41905;,
 -0.02488;14.70139;8.94810;,
 -0.02488;14.70139;8.00619;,
 5.63635;16.33281;5.66123;,
 5.30334;15.51710;5.32822;,
 6.30238;16.33281;6.32726;,
 6.63540;15.51710;6.66028;,
 6.30238;14.70139;6.32726;,
 5.63635;14.70139;5.66123;,
 4.49711;26.17970;-4.53382;,
 4.81559;26.20544;-4.40551;,
 6.70698;13.97490;-6.64610;,
 6.38850;13.94916;-6.77441;,
 4.92019;26.16205;-4.08035;,
 6.81158;13.93151;-6.32094;,
 4.73214;26.08219;-3.80319;,
 6.62354;13.85165;-6.04378;,
 4.39306;26.02600;-3.78274;,
 6.28445;13.79547;-6.02333;,
 4.15827;26.03580;-4.03440;,
 6.04966;13.80526;-6.27499;,
 4.20458;26.10420;-4.36867;,
 6.09597;13.87366;-6.60925;,
 4.53156;26.11363;-4.14410;,
 6.42295;13.88309;-6.38469;,
 -4.34527;26.17970;-4.29022;,
 -4.21696;26.20544;-4.60869;,
 -6.45754;13.97490;-6.50008;,
 -6.58585;13.94916;-6.18161;,
 -3.89180;26.16205;-4.71329;,
 -6.13238;13.93151;-6.60468;,
 -3.61464;26.08219;-4.52525;,
 -5.85522;13.85165;-6.41664;,
 -3.59419;26.02600;-4.18616;,
 -5.83477;13.79547;-6.07755;,
 -3.84585;26.03580;-3.95137;,
 -6.08643;13.80526;-5.84276;,
 -4.18011;26.10420;-3.99768;,
 -6.42069;13.87366;-5.88907;,
 -3.95554;26.11363;-4.32467;,
 -6.19613;13.88309;-6.21606;,
 -4.55499;26.17970;4.47810;,
 -4.87346;26.20544;4.34979;,
 -6.76485;13.97490;6.59037;,
 -6.44638;13.94916;6.71868;,
 -4.97806;26.16205;4.02463;,
 -6.86945;13.93151;6.26521;,
 -4.79002;26.08219;3.74747;,
 -6.68141;13.85165;5.98805;,
 -4.45093;26.02600;3.72702;,
 -6.34232;13.79547;5.96760;,
 -4.21615;26.03580;3.97868;,
 -6.10754;13.80526;6.21926;,
 -4.26245;26.10420;4.31294;,
 -6.15384;13.87366;6.55352;,
 -4.58944;26.11363;4.08837;,
 -6.48083;13.88309;6.32896;,
 4.48678;26.17970;4.44953;,
 4.35847;26.20544;4.76801;,
 6.59906;13.97490;6.65940;,
 6.72737;13.94916;6.34092;,
 4.03331;26.16205;4.87260;,
 6.27390;13.93151;6.76400;,
 3.75615;26.08219;4.68456;,
 5.99674;13.85165;6.57596;,
 3.73570;26.02600;4.34548;,
 5.97629;13.79547;6.23687;,
 3.98736;26.03580;4.11069;,
 6.22795;13.80526;6.00208;,
 4.32163;26.10420;4.15700;,
 6.56221;13.87366;6.04839;,
 4.09706;26.11363;4.48398;,
 6.33765;13.88309;6.37537;;
 
 202;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 3;26,25,33;,
 3;25,27,33;,
 3;27,28,33;,
 3;28,29,33;,
 3;29,30,33;,
 3;30,31,33;,
 3;31,32,33;,
 3;32,26,33;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,34,37,41;,
 4;40,38,35,34;,
 4;37,36,39,41;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;46,48,49,47;,
 4;48,42,45,49;,
 4;48,46,43,42;,
 4;45,44,47,49;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,50,53,57;,
 4;56,54,51,50;,
 4;53,52,55,57;,
 4;58,59,60,61;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;64,58,61,65;,
 4;64,62,59,58;,
 4;61,60,63,65;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 4;72,66,69,73;,
 4;72,70,67,66;,
 4;69,68,71,73;,
 4;74,75,76,77;,
 4;75,78,79,76;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 4;84,74,77,85;,
 4;77,76,86,87;,
 4;76,79,88,86;,
 4;79,81,89,88;,
 4;81,83,90,89;,
 4;83,85,91,90;,
 4;85,77,87,91;,
 4;87,86,92,93;,
 4;86,88,94,92;,
 4;88,89,95,94;,
 4;89,90,96,95;,
 4;90,91,97,96;,
 4;91,87,93,97;,
 4;93,92,98,99;,
 4;92,94,100,98;,
 4;94,95,101,100;,
 4;95,96,102,101;,
 4;96,97,103,102;,
 4;97,93,99,103;,
 4;99,98,104,105;,
 4;98,100,106,104;,
 4;100,101,107,106;,
 4;101,102,108,107;,
 4;102,103,109,108;,
 4;103,99,105,109;,
 4;105,104,110,111;,
 4;104,106,112,110;,
 4;106,107,113,112;,
 4;107,108,114,113;,
 4;108,109,115,114;,
 4;109,105,111,115;,
 4;111,110,116,117;,
 4;110,112,118,116;,
 4;112,113,119,118;,
 4;113,114,120,119;,
 4;114,115,121,120;,
 4;115,111,117,121;,
 4;117,116,75,74;,
 4;116,118,78,75;,
 4;118,119,80,78;,
 4;119,120,82,80;,
 4;120,121,84,82;,
 4;121,117,74,84;,
 4;122,123,124,125;,
 4;123,126,127,124;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,122,125,135;,
 3;136,123,122;,
 3;136,126,123;,
 3;136,128,126;,
 3;136,130,128;,
 3;136,132,130;,
 3;136,134,132;,
 3;136,122,134;,
 3;137,125,124;,
 3;137,124,127;,
 3;137,127,129;,
 3;137,129,131;,
 3;137,131,133;,
 3;137,133,135;,
 3;137,135,125;,
 4;138,139,140,141;,
 4;139,142,143,140;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,138,141,151;,
 3;152,139,138;,
 3;152,142,139;,
 3;152,144,142;,
 3;152,146,144;,
 3;152,148,146;,
 3;152,150,148;,
 3;152,138,150;,
 3;153,141,140;,
 3;153,140,143;,
 3;153,143,145;,
 3;153,145,147;,
 3;153,147,149;,
 3;153,149,151;,
 3;153,151,141;,
 4;154,155,156,157;,
 4;155,158,159,156;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,154,157,167;,
 3;168,155,154;,
 3;168,158,155;,
 3;168,160,158;,
 3;168,162,160;,
 3;168,164,162;,
 3;168,166,164;,
 3;168,154,166;,
 3;169,157,156;,
 3;169,156,159;,
 3;169,159,161;,
 3;169,161,163;,
 3;169,163,165;,
 3;169,165,167;,
 3;169,167,157;,
 4;170,171,172,173;,
 4;171,174,175,172;,
 4;174,176,177,175;,
 4;176,178,179,177;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,170,173,183;,
 3;184,171,170;,
 3;184,174,171;,
 3;184,176,174;,
 3;184,178,176;,
 3;184,180,178;,
 3;184,182,180;,
 3;184,170,182;,
 3;185,173,172;,
 3;185,172,175;,
 3;185,175,177;,
 3;185,177,179;,
 3;185,179,181;,
 3;185,181,183;,
 3;185,183,173;;
 
 MeshMaterialList {
  4;
  202;
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
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
  }
  Material {
   0.800000;0.439216;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.489412;0.272941;0.109804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.690196;0.734118;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
}
