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
 164;
 -2.01442;-9.41132;-3.84602;,
 -0.15072;-7.12050;-0.33683;,
 -0.71814;-8.76709;-1.37403;,
 -0.15072;-7.12050;-0.33683;,
 0.09680;-9.41043;-4.89354;,
 -0.15072;-7.12050;-0.33683;,
 0.44275;-8.75947;-1.25532;,
 -0.15072;-7.12050;-0.33683;,
 2.03676;-9.43411;-3.41340;,
 -0.15072;-7.12050;-0.33683;,
 0.18402;-8.47405;0.35064;,
 -0.15072;-7.12050;-0.33683;,
 -0.56598;-9.38491;2.03779;,
 -0.15072;-7.12050;-0.33683;,
 -0.90471;-8.44525;0.19774;,
 -0.15072;-7.12050;-0.33683;,
 -2.01442;-9.41132;-3.84602;,
 0.02632;0.27205;-0.12786;,
 -0.70103;0.07405;-0.91204;,
 -1.10635;0.07405;-0.24690;,
 0.02632;0.27205;-0.12786;,
 0.13036;0.07405;-1.11782;,
 0.02632;0.27205;-0.12786;,
 0.90080;0.07405;-0.74368;,
 0.02632;0.27205;-0.12786;,
 1.15898;0.07405;-0.00881;,
 0.02632;0.27205;-0.12786;,
 0.75365;0.07405;0.65633;,
 0.02632;0.27205;-0.12786;,
 -0.07773;0.07405;0.86210;,
 0.02632;0.27205;-0.12786;,
 -0.84818;0.07405;0.48797;,
 0.02632;0.27205;-0.12786;,
 -1.10635;0.07405;-0.24690;,
 -1.31764;-0.48980;-1.57685;,
 -2.06657;-0.48980;-0.34783;,
 0.21857;-0.48980;-1.95706;,
 1.64215;-0.48980;-1.26576;,
 2.11920;-0.48980;0.09211;,
 1.37026;-0.48980;1.32113;,
 -0.16594;-0.48980;1.70135;,
 -1.58953;-0.48980;1.01004;,
 -2.06657;-0.48980;-0.34783;,
 -1.72964;-1.33367;-2.02105;,
 -2.70817;-1.33367;-0.41526;,
 0.27751;-1.33367;-2.51783;,
 2.13751;-1.33367;-1.61459;,
 2.76081;-1.33367;0.15955;,
 1.78226;-1.33367;1.76534;,
 -0.22488;-1.33367;2.26213;,
 -2.08489;-1.33367;1.35889;,
 -2.70817;-1.33367;-0.41526;,
 -1.87431;-2.32908;-2.17703;,
 -2.93348;-2.32908;-0.43894;,
 0.29821;-2.32908;-2.71474;,
 2.31146;-2.32908;-1.73709;,
 2.98610;-2.32908;0.18323;,
 1.92694;-2.32908;1.92132;,
 -0.24558;-2.32908;2.45904;,
 -2.25882;-2.32908;1.48138;,
 -2.93348;-2.32908;-0.43894;,
 -1.72964;-3.32449;-2.02105;,
 -2.70817;-3.32449;-0.41526;,
 0.27751;-3.32449;-2.51783;,
 2.13751;-3.32449;-1.61459;,
 2.76081;-3.32449;0.15955;,
 1.78226;-3.32449;1.76534;,
 -0.22488;-3.32449;2.26213;,
 -2.08489;-3.32449;1.35889;,
 -2.70817;-3.32449;-0.41526;,
 -1.31764;-4.16837;-1.57685;,
 -2.06657;-4.16837;-0.34783;,
 0.21857;-4.16837;-1.95706;,
 1.64215;-4.16837;-1.26576;,
 2.11920;-4.16837;0.09211;,
 1.37026;-4.16837;1.32113;,
 -0.16594;-4.16837;1.70135;,
 -1.58953;-4.16837;1.01004;,
 -2.06657;-4.16837;-0.34783;,
 -0.70103;-4.73222;-0.91204;,
 -1.10635;-4.73222;-0.24690;,
 0.13036;-4.73222;-1.11782;,
 0.90080;-4.73222;-0.74368;,
 1.15898;-4.73222;-0.00881;,
 0.75365;-4.73222;0.65633;,
 -0.07773;-4.73222;0.86210;,
 -0.84818;-4.73222;0.48797;,
 -1.10635;-4.73222;-0.24690;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 0.02632;-4.93022;-0.12786;,
 -0.65124;-4.67078;-0.39850;,
 -0.43528;-4.67078;-0.79625;,
 -0.49757;-6.30573;-0.37549;,
 -0.71353;-6.30573;0.02226;,
 -0.00132;-4.67078;-0.92479;,
 -0.06362;-6.30573;-0.50404;,
 0.39643;-4.67078;-0.70883;,
 0.33414;-6.30573;-0.28808;,
 0.52497;-4.67078;-0.27488;,
 0.46267;-6.30573;0.14588;,
 0.30901;-4.67078;0.12288;,
 0.24672;-6.30573;0.54363;,
 -0.12495;-4.67078;0.25142;,
 -0.18724;-6.30573;0.67217;,
 -0.52269;-4.67078;0.03546;,
 -0.58499;-6.30573;0.45621;,
 -0.65124;-4.67078;-0.39850;,
 -0.71353;-6.30573;0.02226;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.06314;-4.67078;-0.33669;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.12543;-6.30573;0.08407;,
 -0.70896;-6.27762;0.01297;,
 -0.49300;-6.27762;-0.38478;,
 -0.54357;-7.41553;-0.79869;,
 -0.75953;-7.41553;-0.40095;,
 -0.05905;-6.27762;-0.51332;,
 -0.10961;-7.41553;-0.92724;,
 0.33870;-6.27762;-0.29736;,
 0.28814;-7.41553;-0.71128;,
 0.46724;-6.27762;0.13659;,
 0.41669;-7.41553;-0.27732;,
 0.25129;-6.27762;0.53435;,
 0.20073;-7.41553;0.12043;,
 -0.18268;-6.27762;0.66289;,
 -0.23324;-7.41553;0.24898;,
 -0.58042;-6.27762;0.44693;,
 -0.63098;-7.41553;0.03302;,
 -0.70896;-6.27762;0.01297;,
 -0.75953;-7.41553;-0.40095;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.12086;-6.27762;0.07478;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;,
 -0.17142;-7.41553;-0.33913;;
 
 132;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 4;2,0,14,10;,
 4;10,14,16,2;,
 3;6,2,4;,
 3;4,2,6;,
 3;6,10,8;,
 3;8,10,6;,
 3;6,2,10;,
 3;10,2,6;,
 3;14,2,6;,
 3;6,2,14;,
 3;12,10,14;,
 3;14,10,12;,
 3;17,18,19;,
 3;20,21,18;,
 3;22,23,21;,
 3;24,25,23;,
 3;26,27,25;,
 3;28,29,27;,
 3;30,31,29;,
 3;32,33,31;,
 4;19,18,34,35;,
 4;18,21,36,34;,
 4;21,23,37,36;,
 4;23,25,38,37;,
 4;25,27,39,38;,
 4;27,29,40,39;,
 4;29,31,41,40;,
 4;31,33,42,41;,
 4;35,34,43,44;,
 4;34,36,45,43;,
 4;36,37,46,45;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;44,43,52,53;,
 4;43,45,54,52;,
 4;45,46,55,54;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;53,52,61,62;,
 4;52,54,63,61;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;62,61,70,71;,
 4;61,63,72,70;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;71,70,79,80;,
 4;70,72,81,79;,
 4;72,73,82,81;,
 4;73,74,83,82;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 3;80,79,88;,
 3;79,81,89;,
 3;81,82,90;,
 3;82,83,91;,
 3;83,84,92;,
 3;84,85,93;,
 3;85,86,94;,
 3;86,87,95;,
 4;96,97,98,99;,
 4;97,100,101,98;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 3;114,97,96;,
 3;115,100,97;,
 3;116,102,100;,
 3;117,104,102;,
 3;118,106,104;,
 3;119,108,106;,
 3;120,110,108;,
 3;121,112,110;,
 3;122,99,98;,
 3;123,98,101;,
 3;124,101,103;,
 3;125,103,105;,
 3;126,105,107;,
 3;127,107,109;,
 3;128,109,111;,
 3;129,111,113;,
 4;130,131,132,133;,
 4;131,134,135,132;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 3;148,131,130;,
 3;149,134,131;,
 3;150,136,134;,
 3;151,138,136;,
 3;152,140,138;,
 3;153,142,140;,
 3;154,144,142;,
 3;155,146,144;,
 3;156,133,132;,
 3;157,132,135;,
 3;158,135,137;,
 3;159,137,139;,
 3;160,139,141;,
 3;161,141,143;,
 3;162,143,145;,
 3;163,145,147;;
 
 MeshMaterialList {
  7;
  132;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.768800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.765490;0.351373;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\Texture\\Player\\mofu.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.012549;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\Texture\\Player\\mofu.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data\\Texture\\Player\\mofu.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  101;
  0.887139;-0.015163;-0.461253;,
  -0.839765;0.465464;-0.279530;,
  0.318837;0.929511;-0.185342;,
  -0.795830;0.050008;-0.603452;,
  0.418310;0.874198;0.246566;,
  0.363183;0.742787;0.562465;,
  -0.583409;0.726794;0.362499;,
  0.935694;0.345062;0.073552;,
  0.000000;1.000000;0.000000;,
  -0.339284;0.940008;-0.035660;,
  -0.209810;0.932192;-0.294955;,
  0.039835;0.924539;-0.378999;,
  0.266550;0.932191;-0.244889;,
  0.339283;0.940008;0.035660;,
  0.209810;0.932191;0.294957;,
  -0.039834;0.924539;0.379000;,
  -0.266550;0.932191;0.244889;,
  -0.655418;0.752118;-0.068887;,
  -0.399567;0.729755;-0.554801;,
  0.073741;0.708761;-0.701584;,
  0.506184;0.729755;-0.459604;,
  0.655416;0.752120;0.068887;,
  0.399565;0.729757;0.554799;,
  -0.073739;0.708765;0.701580;,
  -0.506184;0.729757;0.459600;,
  -0.899131;0.427355;-0.094503;,
  -0.538756;0.404532;-0.738983;,
  0.096508;0.384152;-0.918212;,
  0.680625;0.404533;-0.610822;,
  0.899131;0.427355;0.094502;,
  0.538756;0.404534;0.738981;,
  -0.096508;0.384156;0.918210;,
  -0.680627;0.404535;0.610818;,
  -0.994522;-0.000000;-0.104529;,
  -0.591036;0.000000;-0.806645;,
  0.104528;0.000000;-0.994522;,
  0.745831;0.000000;-0.666135;,
  0.994522;0.000000;0.104528;,
  0.591038;0.000000;0.806643;,
  -0.104528;0.000000;0.994522;,
  -0.745834;0.000000;0.666132;,
  -0.899132;-0.427352;-0.094503;,
  -0.538756;-0.404530;-0.738984;,
  0.096508;-0.384149;-0.918213;,
  0.680626;-0.404530;-0.610822;,
  0.899132;-0.427353;0.094502;,
  0.538757;-0.404531;0.738983;,
  -0.096508;-0.384153;0.918212;,
  -0.680628;-0.404532;0.610819;,
  -0.655420;-0.752117;-0.068887;,
  -0.399568;-0.729753;-0.554802;,
  0.073741;-0.708759;-0.701586;,
  0.506186;-0.729753;-0.459605;,
  0.655418;-0.752118;0.068887;,
  0.399566;-0.729755;0.554801;,
  -0.073739;-0.708764;0.701581;,
  -0.506185;-0.729756;0.459601;,
  -0.339284;-0.940008;-0.035660;,
  -0.209810;-0.932192;-0.294955;,
  0.039835;-0.924539;-0.378998;,
  0.266550;-0.932191;-0.244889;,
  0.339282;-0.940008;0.035660;,
  0.209810;-0.932191;0.294957;,
  -0.039834;-0.924539;0.378999;,
  -0.266550;-0.932192;0.244888;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.994420;0.010883;-0.104933;,
  -0.623548;-0.172478;-0.762521;,
  0.100783;-0.251560;-0.962580;,
  0.766329;-0.187346;-0.614525;,
  0.994420;-0.010883;0.104935;,
  0.623551;0.172477;0.762519;,
  -0.100790;0.251560;0.962579;,
  -0.766325;0.187347;0.614530;,
  0.000000;-1.000000;-0.000000;,
  -0.991726;0.080453;-0.100031;,
  -0.607278;0.295277;-0.737580;,
  0.102074;0.336042;-0.936300;,
  0.768440;0.188321;-0.611584;,
  0.991728;-0.080444;0.100024;,
  0.607283;-0.295273;0.737578;,
  -0.102082;-0.336041;0.936299;,
  -0.768441;-0.188317;0.611584;,
  -0.178495;0.957904;-0.224854;,
  -0.888031;0.449006;-0.098965;,
  0.896321;0.413813;-0.159270;,
  0.625533;0.772272;0.110924;,
  -0.704581;0.571022;0.421306;,
  -0.845008;0.523999;0.106707;,
  -0.015738;0.979182;-0.202371;,
  -0.000910;0.979651;-0.200707;,
  -0.047028;-0.998807;0.013179;,
  0.015113;-0.999671;-0.020743;,
  0.015738;-0.979182;0.202371;,
  -0.005273;-0.982160;0.187974;,
  -0.065844;-0.982906;0.171930;,
  -0.011660;-0.984108;0.177187;,
  0.011660;0.984108;-0.177187;,
  -0.225346;-0.964855;0.135178;,
  0.041204;-0.886745;-0.460420;;
  132;
  3;0,7,0;,
  3;84,85,1;,
  3;86,7,2;,
  3;3,85,3;,
  3;87,7,4;,
  3;4,7,5;,
  3;88,85,6;,
  3;6,85,89;,
  4;84,90,91,90;,
  4;92,93,94,95;,
  3;96,95,97;,
  3;98,84,98;,
  3;2,4,87;,
  3;99,92,96;,
  3;2,84,4;,
  3;92,95,96;,
  3;93,95,96;,
  3;2,84,91;,
  3;5,4,6;,
  3;93,92,100;,
  3;8,10,9;,
  3;8,11,10;,
  3;8,12,11;,
  3;8,13,12;,
  3;8,14,13;,
  3;8,15,14;,
  3;8,16,15;,
  3;8,9,16;,
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
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  3;57,58,65;,
  3;58,59,65;,
  3;59,60,65;,
  3;60,61,65;,
  3;61,62,65;,
  3;62,63,65;,
  3;63,64,65;,
  3;64,57,65;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,67,67,74;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,83,83,82;,
  4;83,76,76,83;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;;
 }
 MeshTextureCoords {
  164;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
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
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
  0.937500;1.000000;;
 }
}
