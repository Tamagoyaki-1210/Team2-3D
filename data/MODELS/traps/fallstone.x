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
 130;
 0.73876;21.88526;-4.01421;,
 2.06167;20.40127;-5.53487;,
 0.59574;20.31281;-5.95629;,
 0.73876;21.88526;-4.01421;,
 3.73017;20.61811;-3.85169;,
 0.73876;21.88526;-4.01421;,
 3.62637;21.62055;-2.29274;,
 0.73876;21.88526;-4.01421;,
 2.23460;22.40064;-2.07473;,
 0.73876;21.88526;-4.01421;,
 0.80949;22.78416;-1.67931;,
 0.73876;21.88526;-4.01421;,
 -0.65644;22.69569;-2.10073;,
 0.73876;21.88526;-4.01421;,
 -1.60325;22.16904;-3.17801;,
 0.73876;21.88526;-4.01421;,
 -1.60252;20.64264;-4.92199;,
 0.73876;21.88526;-4.01421;,
 -0.64393;20.18962;-5.88441;,
 0.73876;21.88526;-4.01421;,
 0.59574;20.31281;-5.95629;,
 2.46414;18.21054;-6.38898;,
 0.39444;18.22069;-7.31545;,
 4.98376;19.39072;-4.46475;,
 5.10940;20.84335;-1.95081;,
 3.51174;22.19197;0.06773;,
 0.80103;22.92147;0.81986;,
 -1.46031;23.08781;-0.01932;,
 -3.85945;21.08828;-1.64409;,
 -3.84483;20.54078;-4.38427;,
 -2.25827;18.64043;-6.59166;,
 0.39444;18.22069;-7.31545;,
 3.99243;16.04531;-6.85535;,
 0.15457;15.81371;-7.95864;,
 6.47123;17.42412;-4.03499;,
 6.39427;18.58044;-0.84778;,
 4.40747;20.92845;2.40830;,
 0.66151;21.79284;3.52497;,
 -2.60524;21.97708;1.84263;,
 -5.61663;20.54138;-0.60801;,
 -5.77539;18.67401;-4.14514;,
 -3.57640;16.81779;-6.92342;,
 0.15457;15.81371;-7.95864;,
 4.41127;13.59974;-6.52590;,
 0.59564;13.92718;-7.33475;,
 7.32528;15.22064;-3.21036;,
 7.28977;17.59540;0.85514;,
 4.94351;19.75315;4.12336;,
 -0.34943;20.09957;5.68660;,
 -3.95419;20.66125;4.04333;,
 -6.13671;19.86136;0.40048;,
 -6.66373;17.95340;-2.63883;,
 -4.48642;14.50784;-6.60593;,
 0.59564;13.92718;-7.33475;,
 4.44804;10.99871;-5.78104;,
 -0.63093;11.81582;-7.39669;,
 7.47760;13.28649;-1.51344;,
 7.33345;15.50227;2.20229;,
 5.34539;17.46400;6.10803;,
 0.34623;19.00282;6.91910;,
 -4.39762;18.71655;5.55537;,
 -7.08108;16.81092;1.70506;,
 -7.67534;14.54090;-2.20776;,
 -5.14577;13.18136;-6.11517;,
 -0.63093;11.81582;-7.39669;,
 3.95493;9.34695;-4.04571;,
 -0.21226;9.33687;-5.46922;,
 6.50881;10.50898;-0.20223;,
 7.07223;13.31824;3.33747;,
 4.48716;15.50036;6.60353;,
 0.10113;16.68071;7.82048;,
 -4.75578;16.27098;5.71353;,
 -6.88398;15.33940;3.99988;,
 -7.52783;12.43717;-0.85967;,
 -4.94276;10.25504;-4.12574;,
 -0.21226;9.33687;-5.46922;,
 2.78242;8.57262;-1.56157;,
 -0.23199;7.95088;-3.18569;,
 5.60321;9.33482;0.68260;,
 5.61388;11.48572;3.42923;,
 3.48017;12.31491;6.49955;,
 -0.48279;14.50211;7.83628;,
 -3.99168;13.96288;6.85295;,
 -6.47049;12.58408;4.03260;,
 -6.64342;10.58471;0.57245;,
 -3.55857;8.91294;-2.28917;,
 -0.23199;7.95088;-3.18569;,
 1.98808;7.25499;-0.02066;,
 -0.80029;7.08672;-0.82224;,
 3.78903;8.25675;2.02845;,
 3.91467;9.70938;4.54240;,
 2.31701;11.05800;6.56094;,
 -0.39370;11.78751;7.31305;,
 -3.18207;11.61924;6.51147;,
 -4.86237;11.32973;4.97934;,
 -5.10866;9.16485;1.94842;,
 -3.51100;7.81622;-0.07012;,
 -0.80029;7.08672;-0.82224;,
 0.65718;7.31251;2.09834;,
 -0.80875;7.22404;1.67693;,
 1.60399;7.83917;3.17562;,
 1.67005;8.60285;4.49728;,
 0.80356;9.63246;5.72755;,
 -0.59500;9.69539;5.95390;,
 -2.06093;9.60693;5.53249;,
 -3.00774;9.08027;4.45521;,
 -3.09842;9.01252;2.88171;,
 -2.23386;7.60757;2.07234;,
 -0.80875;7.22404;1.67693;,
 -0.80875;7.22404;1.67693;,
 0.65718;7.31251;2.09834;,
 -0.73801;8.12293;4.01183;,
 1.60399;7.83917;3.17562;,
 -0.73801;8.12293;4.01183;,
 1.67005;8.60285;4.49728;,
 -0.73801;8.12293;4.01183;,
 0.80356;9.63246;5.72755;,
 -0.73801;8.12293;4.01183;,
 -0.59500;9.69539;5.95390;,
 -0.73801;8.12293;4.01183;,
 -2.06093;9.60693;5.53249;,
 -0.73801;8.12293;4.01183;,
 -3.00774;9.08027;4.45521;,
 -0.73801;8.12293;4.01183;,
 -3.09842;9.01252;2.88171;,
 -0.73801;8.12293;4.01183;,
 -2.23386;7.60757;2.07234;,
 -0.73801;8.12293;4.01183;,
 -0.80875;7.22404;1.67693;,
 -0.73801;8.12293;4.01183;;
 
 100;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 4;2,1,21,22;,
 4;1,4,23,21;,
 4;4,6,24,23;,
 4;6,8,25,24;,
 4;8,10,26,25;,
 4;10,12,27,26;,
 4;12,14,28,27;,
 4;14,16,29,28;,
 4;16,18,30,29;,
 4;18,20,31,30;,
 4;22,21,32,33;,
 4;21,23,34,32;,
 4;23,24,35,34;,
 4;24,25,36,35;,
 4;25,26,37,36;,
 4;26,27,38,37;,
 4;27,28,39,38;,
 4;28,29,40,39;,
 4;29,30,41,40;,
 4;30,31,42,41;,
 4;33,32,43,44;,
 4;32,34,45,43;,
 4;34,35,46,45;,
 4;35,36,47,46;,
 4;36,37,48,47;,
 4;37,38,49,48;,
 4;38,39,50,49;,
 4;39,40,51,50;,
 4;40,41,52,51;,
 4;41,42,53,52;,
 4;44,43,54,55;,
 4;43,45,56,54;,
 4;45,46,57,56;,
 4;46,47,58,57;,
 4;47,48,59,58;,
 4;48,49,60,59;,
 4;49,50,61,60;,
 4;50,51,62,61;,
 4;51,52,63,62;,
 4;52,53,64,63;,
 4;55,54,65,66;,
 4;54,56,67,65;,
 4;56,57,68,67;,
 4;57,58,69,68;,
 4;58,59,70,69;,
 4;59,60,71,70;,
 4;60,61,72,71;,
 4;61,62,73,72;,
 4;62,63,74,73;,
 4;63,64,75,74;,
 4;66,65,76,77;,
 4;65,67,78,76;,
 4;67,68,79,78;,
 4;68,69,80,79;,
 4;69,70,81,80;,
 4;70,71,82,81;,
 4;71,72,83,82;,
 4;72,73,84,83;,
 4;73,74,85,84;,
 4;74,75,86,85;,
 4;77,76,87,88;,
 4;76,78,89,87;,
 4;78,79,90,89;,
 4;79,80,91,90;,
 4;80,81,92,91;,
 4;81,82,93,92;,
 4;82,83,94,93;,
 4;83,84,95,94;,
 4;84,85,96,95;,
 4;85,86,97,96;,
 4;88,87,98,99;,
 4;87,89,100,98;,
 4;89,90,101,100;,
 4;90,91,102,101;,
 4;91,92,103,102;,
 4;92,93,104,103;,
 4;93,94,105,104;,
 4;94,95,106,105;,
 4;95,96,107,106;,
 4;96,97,108,107;,
 3;109,110,111;,
 3;110,112,113;,
 3;112,114,115;,
 3;114,116,117;,
 3;116,118,119;,
 3;118,120,121;,
 3;120,122,123;,
 3;122,124,125;,
 3;124,126,127;,
 3;126,128,129;;
 
 MeshMaterialList {
  1;
  100;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\Team2-3D\\data\\TEXTURE\\MeshField001.png";
   }
  }
 }
 MeshNormals {
  92;
  0.096152;0.848402;-0.520547;,
  0.050581;0.651257;-0.757169;,
  0.320655;0.663064;-0.676407;,
  0.423606;0.735938;-0.528160;,
  0.429676;0.805668;-0.407772;,
  0.315930;0.906849;-0.278951;,
  0.123067;0.966257;-0.226279;,
  -0.105097;0.954548;-0.278914;,
  -0.260568;0.862932;-0.432957;,
  -0.249660;0.766106;-0.592242;,
  -0.180341;0.703208;-0.687733;,
  0.077576;0.400959;-0.912806;,
  0.401717;0.426074;-0.810607;,
  0.605838;0.569662;-0.555378;,
  0.680996;0.705694;-0.195554;,
  0.479918;0.875060;0.062843;,
  0.128272;0.978856;0.159333;,
  -0.280512;0.959636;0.020308;,
  -0.492683;0.838260;-0.233632;,
  -0.452253;0.702162;-0.549941;,
  -0.281807;0.501124;-0.818205;,
  0.037298;0.056030;-0.997732;,
  0.479534;0.141946;-0.865967;,
  0.806324;0.338521;-0.485020;,
  0.844613;0.532948;-0.050940;,
  0.571410;0.765281;0.296372;,
  0.086103;0.874837;0.476704;,
  -0.353536;0.891769;0.282417;,
  -0.653259;0.753150;-0.077579;,
  -0.732828;0.484722;-0.477501;,
  -0.463520;0.179625;-0.867689;,
  0.004325;-0.154816;-0.987934;,
  0.541471;-0.153357;-0.826614;,
  0.929793;0.056515;-0.363719;,
  0.930164;0.361152;0.066058;,
  0.598451;0.668937;0.440885;,
  0.041798;0.774479;0.631218;,
  -0.476712;0.734906;0.482348;,
  -0.840757;0.532993;0.095111;,
  -0.890329;0.276644;-0.361638;,
  -0.550202;0.013568;-0.834922;,
  -0.043004;-0.402325;-0.914486;,
  0.561971;-0.443584;-0.698156;,
  0.950620;-0.232297;-0.205813;,
  0.966424;0.045457;0.252901;,
  0.631610;0.356543;0.688437;,
  -0.013113;0.499124;0.866431;,
  -0.580679;0.462726;0.669849;,
  -0.919220;0.300694;0.254199;,
  -0.969086;0.039320;-0.243570;,
  -0.615851;-0.219113;-0.756781;,
  -0.067106;-0.796692;-0.600648;,
  0.462606;-0.771669;-0.436489;,
  0.838621;-0.542917;-0.044222;,
  0.862784;-0.281109;0.420216;,
  0.549504;-0.065351;0.832932;,
  -0.046147;0.165725;0.985092;,
  -0.564759;0.235866;0.790831;,
  -0.908120;0.064232;0.413754;,
  -0.940469;-0.330440;-0.079547;,
  -0.585861;-0.649962;-0.484063;,
  -0.040676;-0.908428;-0.416057;,
  0.398074;-0.865826;-0.303123;,
  0.690209;-0.720847;0.063178;,
  0.722065;-0.465552;0.511746;,
  0.466505;-0.265903;0.843605;,
  -0.031898;-0.062140;0.997558;,
  -0.503950;-0.067049;0.861126;,
  -0.796768;-0.272338;0.539438;,
  -0.814820;-0.576418;0.061729;,
  -0.521496;-0.792622;-0.315899;,
  -0.070722;-0.980679;-0.182392;,
  0.302532;-0.948633;-0.092569;,
  0.516629;-0.829534;0.212055;,
  0.529612;-0.630755;0.567150;,
  0.323583;-0.464584;0.824291;,
  -0.035218;-0.377245;0.925444;,
  -0.403439;-0.412429;0.816786;,
  -0.625799;-0.555979;0.547049;,
  -0.644239;-0.724202;0.245941;,
  -0.466704;-0.883618;-0.037506;,
  -0.101131;-0.972349;0.210498;,
  0.081687;-0.961317;0.263054;,
  0.199766;-0.895637;0.397402;,
  0.195017;-0.787083;0.585208;,
  0.117149;-0.695315;0.709093;,
  -0.046597;-0.668103;0.742608;,
  -0.266007;-0.673566;0.689601;,
  -0.432838;-0.791938;0.430681;,
  -0.500715;-0.793049;0.346925;,
  -0.362829;-0.861734;0.354641;,
  -0.129384;-0.860747;0.492315;;
  100;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,1,10;,
  4;1,2,12,11;,
  4;2,3,13,12;,
  4;3,4,14,13;,
  4;4,5,15,14;,
  4;5,6,16,15;,
  4;6,7,17,16;,
  4;7,8,18,17;,
  4;8,9,19,18;,
  4;9,10,20,19;,
  4;10,1,11,20;,
  4;11,12,22,21;,
  4;12,13,23,22;,
  4;13,14,24,23;,
  4;14,15,25,24;,
  4;15,16,26,25;,
  4;16,17,27,26;,
  4;17,18,28,27;,
  4;18,19,29,28;,
  4;19,20,30,29;,
  4;20,11,21,30;,
  4;21,22,32,31;,
  4;22,23,33,32;,
  4;23,24,34,33;,
  4;24,25,35,34;,
  4;25,26,36,35;,
  4;26,27,37,36;,
  4;27,28,38,37;,
  4;28,29,39,38;,
  4;29,30,40,39;,
  4;30,21,31,40;,
  4;31,32,42,41;,
  4;32,33,43,42;,
  4;33,34,44,43;,
  4;34,35,45,44;,
  4;35,36,46,45;,
  4;36,37,47,46;,
  4;37,38,48,47;,
  4;38,39,49,48;,
  4;39,40,50,49;,
  4;40,31,41,50;,
  4;41,42,52,51;,
  4;42,43,53,52;,
  4;43,44,54,53;,
  4;44,45,55,54;,
  4;45,46,56,55;,
  4;46,47,57,56;,
  4;47,48,58,57;,
  4;48,49,59,58;,
  4;49,50,60,59;,
  4;50,41,51,60;,
  4;51,52,62,61;,
  4;52,53,63,62;,
  4;53,54,64,63;,
  4;54,55,65,64;,
  4;55,56,66,65;,
  4;56,57,67,66;,
  4;57,58,68,67;,
  4;58,59,69,68;,
  4;59,60,70,69;,
  4;60,51,61,70;,
  4;61,62,72,71;,
  4;62,63,73,72;,
  4;63,64,74,73;,
  4;64,65,75,74;,
  4;65,66,76,75;,
  4;66,67,77,76;,
  4;67,68,78,77;,
  4;68,69,79,78;,
  4;69,70,80,79;,
  4;70,61,71,80;,
  4;71,72,82,81;,
  4;72,73,83,82;,
  4;73,74,84,83;,
  4;74,75,85,84;,
  4;75,76,86,85;,
  4;76,77,87,86;,
  4;77,78,88,87;,
  4;78,79,89,88;,
  4;79,80,90,89;,
  4;80,71,81,90;,
  3;81,82,91;,
  3;82,83,91;,
  3;83,84,91;,
  3;84,85,91;,
  3;85,86,91;,
  3;86,87,91;,
  3;87,88,91;,
  3;88,89,91;,
  3;89,90,91;,
  3;90,81,91;;
 }
 MeshTextureCoords {
  130;
  0.050000;0.000000;,
  0.100000;0.100000;,
  0.000000;0.100000;,
  0.150000;0.000000;,
  0.200000;0.100000;,
  0.250000;0.000000;,
  0.300000;0.100000;,
  0.350000;0.000000;,
  0.400000;0.100000;,
  0.450000;0.000000;,
  0.500000;0.100000;,
  0.550000;0.000000;,
  0.600000;0.100000;,
  0.650000;0.000000;,
  0.700000;0.100000;,
  0.750000;0.000000;,
  0.800000;0.100000;,
  0.850000;0.000000;,
  0.900000;0.100000;,
  0.950000;0.000000;,
  1.000000;0.100000;,
  0.100000;0.200000;,
  0.000000;0.200000;,
  0.200000;0.200000;,
  0.300000;0.200000;,
  0.400000;0.200000;,
  0.500000;0.200000;,
  0.600000;0.200000;,
  0.700000;0.200000;,
  0.800000;0.200000;,
  0.900000;0.200000;,
  1.000000;0.200000;,
  0.100000;0.300000;,
  0.000000;0.300000;,
  0.200000;0.300000;,
  0.300000;0.300000;,
  0.400000;0.300000;,
  0.500000;0.300000;,
  0.600000;0.300000;,
  0.700000;0.300000;,
  0.800000;0.300000;,
  0.900000;0.300000;,
  1.000000;0.300000;,
  0.100000;0.400000;,
  0.000000;0.400000;,
  0.200000;0.400000;,
  0.300000;0.400000;,
  0.400000;0.400000;,
  0.500000;0.400000;,
  0.600000;0.400000;,
  0.700000;0.400000;,
  0.800000;0.400000;,
  0.900000;0.400000;,
  1.000000;0.400000;,
  0.100000;0.500000;,
  0.000000;0.500000;,
  0.200000;0.500000;,
  0.300000;0.500000;,
  0.400000;0.500000;,
  0.500000;0.500000;,
  0.600000;0.500000;,
  0.700000;0.500000;,
  0.800000;0.500000;,
  0.900000;0.500000;,
  1.000000;0.500000;,
  0.100000;0.600000;,
  0.000000;0.600000;,
  0.200000;0.600000;,
  0.300000;0.600000;,
  0.400000;0.600000;,
  0.500000;0.600000;,
  0.600000;0.600000;,
  0.700000;0.600000;,
  0.800000;0.600000;,
  0.900000;0.600000;,
  1.000000;0.600000;,
  0.100000;0.700000;,
  0.000000;0.700000;,
  0.200000;0.700000;,
  0.300000;0.700000;,
  0.400000;0.700000;,
  0.500000;0.700000;,
  0.600000;0.700000;,
  0.700000;0.700000;,
  0.800000;0.700000;,
  0.900000;0.700000;,
  1.000000;0.700000;,
  0.100000;0.800000;,
  0.000000;0.800000;,
  0.200000;0.800000;,
  0.300000;0.800000;,
  0.400000;0.800000;,
  0.500000;0.800000;,
  0.600000;0.800000;,
  0.700000;0.800000;,
  0.800000;0.800000;,
  0.900000;0.800000;,
  1.000000;0.800000;,
  0.100000;0.900000;,
  0.000000;0.900000;,
  0.200000;0.900000;,
  0.300000;0.900000;,
  0.400000;0.900000;,
  0.500000;0.900000;,
  0.600000;0.900000;,
  0.700000;0.900000;,
  0.800000;0.900000;,
  0.900000;0.900000;,
  1.000000;0.900000;,
  0.000000;0.900000;,
  0.100000;0.900000;,
  0.050000;1.000000;,
  0.200000;0.900000;,
  0.150000;1.000000;,
  0.300000;0.900000;,
  0.250000;1.000000;,
  0.400000;0.900000;,
  0.350000;1.000000;,
  0.500000;0.900000;,
  0.450000;1.000000;,
  0.600000;0.900000;,
  0.550000;1.000000;,
  0.700000;0.900000;,
  0.650000;1.000000;,
  0.800000;0.900000;,
  0.750000;1.000000;,
  0.900000;0.900000;,
  0.850000;1.000000;,
  1.000000;0.900000;,
  0.950000;1.000000;;
 }
}
