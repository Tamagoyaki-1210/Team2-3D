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
 218;
 -13.56657;-4.26145;-0.00003;,
 -16.69268;1.45346;0.23434;,
 -18.87872;0.40259;0.23434;,
 -17.01390;-3.95993;-0.00003;,
 -17.01407;-3.95978;-0.00003;,
 -18.87872;0.40259;-0.23440;,
 -16.69268;1.45346;-0.23440;,
 -13.56657;-4.26145;-0.00003;,
 -19.63776;-4.37082;-0.00003;,
 -20.38748;-0.42796;-0.23440;,
 -21.66241;-5.39256;-0.00003;,
 -22.14554;-1.95899;-0.23440;,
 -23.18145;-6.97401;-0.00003;,
 -23.43623;-3.88259;-0.23440;,
 -24.67407;-9.01028;-0.00003;,
 -24.07407;-5.92799;-0.23440;,
 -2.76964;0.15029;-0.18106;,
 -4.13367;1.15739;-0.41544;,
 -2.21022;0.78101;-0.41544;,
 -0.13199;0.06202;-0.37737;,
 -5.58781;0.17133;-0.18106;,
 -6.93509;1.62581;-0.41544;,
 -8.62767;-0.50307;-0.18106;,
 -10.19224;2.05044;-0.41544;,
 -11.68066;-1.88273;-0.18106;,
 -13.62466;2.06146;-0.41544;,
 -16.69268;1.45346;-0.23440;,
 -11.68047;-1.88290;-0.18106;,
 -13.62466;2.06146;0.05331;,
 -16.69268;1.45346;0.23434;,
 -8.62750;-0.50324;-0.18106;,
 -10.19224;2.05044;0.05331;,
 -5.58764;0.17116;-0.18106;,
 -6.93509;1.62581;0.05331;,
 -2.76949;0.15012;-0.18106;,
 -4.13367;1.15739;0.05331;,
 -0.13182;0.06187;-0.14300;,
 -2.21022;0.78101;0.05331;,
 -2.21267;0.90567;0.50307;,
 -0.06336;0.19631;0.50307;,
 -0.04341;0.72556;0.71146;,
 -2.36633;1.37853;0.71146;,
 -2.14904;0.70981;-0.00003;,
 0.00028;0.00044;-0.00003;,
 -2.21267;0.90567;-0.50313;,
 -0.13199;0.06202;-0.37737;,
 -2.36633;1.37853;-0.71152;,
 -0.04341;0.72556;-0.71152;,
 -2.51995;1.85137;-0.50313;,
 0.03120;1.27257;-0.50313;,
 -2.58359;2.04723;-0.00003;,
 0.01087;1.34328;-0.00003;,
 -2.51995;1.85137;0.50307;,
 0.03120;1.27257;0.50307;,
 -2.36633;1.37853;0.71146;,
 -0.04341;0.72556;0.71146;,
 -4.14509;1.27867;0.50307;,
 -4.29872;1.75152;0.71146;,
 -4.08145;1.08281;-0.00003;,
 -4.14509;1.27867;-0.50313;,
 -4.29872;1.75152;-0.71152;,
 -4.45236;2.22438;-0.50313;,
 -4.51600;2.42024;-0.00003;,
 -4.45236;2.22438;0.50307;,
 -4.29872;1.75152;0.71146;,
 -6.93874;1.78244;0.50307;,
 -7.09240;2.25530;0.71146;,
 -6.87510;1.58658;-0.00003;,
 -6.93874;1.78244;-0.50313;,
 -7.09240;2.25530;-0.71152;,
 -7.24602;2.72816;-0.50313;,
 -7.30966;2.92402;-0.00003;,
 -7.24602;2.72816;0.50307;,
 -7.09240;2.25530;0.71146;,
 -10.19635;2.15240;0.50307;,
 -10.34999;2.62526;0.71146;,
 -10.13271;1.95654;-0.00003;,
 -10.19635;2.15240;-0.50313;,
 -10.34999;2.62526;-0.71152;,
 -10.50362;3.09809;-0.50313;,
 -10.56726;3.29395;-0.00003;,
 -10.50362;3.09809;0.50307;,
 -10.34999;2.62526;0.71146;,
 -13.65908;2.20796;0.50307;,
 -13.81270;2.68079;0.71146;,
 -13.59544;2.01209;-0.00003;,
 -13.65908;2.20796;-0.50313;,
 -13.81270;2.68079;-0.71152;,
 -13.96635;3.15365;-0.50313;,
 -14.02999;3.34951;-0.00003;,
 -13.96635;3.15365;0.50307;,
 -13.81270;2.68079;0.71146;,
 -16.71743;1.44832;0.50307;,
 -16.87107;1.92117;0.71146;,
 -16.65379;1.25245;-0.00003;,
 -16.71743;1.44832;-0.50313;,
 -16.87107;1.92117;-0.71152;,
 -17.02470;2.39403;-0.50313;,
 -17.08834;2.58989;-0.00003;,
 -17.02470;2.39403;0.50307;,
 -16.87107;1.92117;0.71146;,
 -18.93653;0.50347;0.50307;,
 -19.09017;0.97632;0.71146;,
 -18.87289;0.30761;-0.00003;,
 -18.93653;0.50347;-0.50313;,
 -19.09017;0.97632;-0.71152;,
 -19.24381;1.44916;-0.50313;,
 -19.30744;1.64502;-0.00003;,
 -19.24381;1.44916;0.50307;,
 -19.09017;0.97632;0.71146;,
 -20.49109;-0.35560;0.45276;,
 -20.62937;0.06997;0.64030;,
 -20.43383;-0.53187;-0.00003;,
 -20.49109;-0.35560;-0.45282;,
 -20.62937;0.06997;-0.64036;,
 -20.76765;0.49552;-0.45282;,
 -20.82491;0.67181;-0.00003;,
 -20.76765;0.49552;0.45276;,
 -20.62937;0.06997;0.64030;,
 -22.12628;-1.89638;0.40748;,
 -22.25072;-1.51338;0.57627;,
 -22.07472;-2.05503;-0.00003;,
 -22.12628;-1.89638;-0.40754;,
 -22.25072;-1.51338;-0.57635;,
 -22.37517;-1.13037;-0.40754;,
 -22.42671;-0.97173;-0.00003;,
 -22.37517;-1.13037;0.40748;,
 -22.25072;-1.51338;0.57627;,
 -23.45306;-3.86800;0.32598;,
 -23.55263;-3.56159;0.46101;,
 -23.41184;-3.99492;-0.00003;,
 -23.45306;-3.86800;-0.32604;,
 -23.55263;-3.56159;-0.46107;,
 -23.65219;-3.25518;-0.32604;,
 -23.69342;-3.12826;-0.00003;,
 -23.65219;-3.25518;0.32598;,
 -23.55263;-3.56159;0.46101;,
 -24.10701;-5.81260;0.22818;,
 -24.17668;-5.59812;0.32269;,
 -24.07812;-5.90144;-0.00003;,
 -24.10701;-5.81260;-0.22824;,
 -24.17668;-5.59812;-0.32276;,
 -24.24638;-5.38364;-0.22824;,
 -24.27525;-5.29478;-0.00003;,
 -24.24638;-5.38364;0.22818;,
 -24.17668;-5.59812;0.32269;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 0.13044;0.78204;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -23.18129;-6.97418;-0.00003;,
 -23.43623;-3.88259;0.23434;,
 -24.07407;-5.92799;0.23434;,
 -24.67407;-9.01024;-0.00003;,
 -21.66223;-5.39271;-0.00003;,
 -22.14554;-1.95899;0.23434;,
 -19.63759;-4.37099;-0.00003;,
 -20.38748;-0.42796;0.23434;,
 -24.67407;-9.01024;-0.00003;,
 -24.07407;-5.92799;0.23434;,
 -24.07407;-5.92799;-0.23440;,
 -24.67407;-9.01028;-0.00003;,
 -23.43623;-3.88259;0.23434;,
 -23.43623;-3.88259;-0.23440;,
 -24.07407;-5.92799;0.23434;,
 -22.14554;-1.95899;0.23434;,
 -22.14554;-1.95899;-0.23440;,
 -20.38748;-0.42796;0.23434;,
 -18.87872;0.40259;0.23434;,
 -18.87872;0.40259;-0.23440;,
 -16.69268;1.45346;0.23434;,
 -23.18145;-6.97401;-0.00003;,
 -23.18129;-6.97418;-0.00003;,
 -24.67407;-9.01024;-0.00003;,
 -21.66241;-5.39256;-0.00003;,
 -21.66223;-5.39271;-0.00003;,
 -19.63759;-4.37099;-0.00003;,
 -17.01407;-3.95978;-0.00003;,
 -17.01390;-3.95993;-0.00003;,
 -13.56657;-4.26145;-0.00003;,
 -16.69268;1.45346;-0.23440;,
 -16.69268;1.45346;0.23434;,
 -13.56657;-4.26145;-0.00003;,
 -0.13199;0.06202;-0.37737;,
 -2.21022;0.78101;-0.41544;,
 -2.21022;0.78101;0.05331;,
 -0.13182;0.06187;-0.14300;,
 -4.13367;1.15739;-0.41544;,
 -4.13367;1.15739;0.05331;,
 -2.21022;0.78101;-0.41544;,
 -6.93509;1.62581;-0.41544;,
 -6.93509;1.62581;0.05331;,
 -10.19224;2.05044;-0.41544;,
 -13.62466;2.06146;-0.41544;,
 -13.62466;2.06146;0.05331;,
 -16.69268;1.45346;-0.23440;,
 -2.76949;0.15012;-0.18106;,
 -2.76964;0.15029;-0.18106;,
 -0.13199;0.06202;-0.37737;,
 -5.58764;0.17116;-0.18106;,
 -5.58781;0.17133;-0.18106;,
 -8.62767;-0.50307;-0.18106;,
 -11.68047;-1.88290;-0.18106;,
 -11.68066;-1.88273;-0.18106;,
 -16.69268;1.45346;0.23434;,
 -16.69268;1.45346;-0.23440;;
 
 276;
 3;0,1,2;,
 3;3,0,2;,
 3;4,5,6;,
 3;7,4,6;,
 3;8,9,5;,
 3;4,8,5;,
 3;10,11,9;,
 3;8,10,9;,
 3;12,13,11;,
 3;10,12,11;,
 3;14,15,13;,
 3;12,14,13;,
 3;16,17,18;,
 3;19,16,18;,
 3;20,21,17;,
 3;16,20,17;,
 3;22,23,21;,
 3;20,22,21;,
 3;24,25,23;,
 3;22,24,23;,
 3;0,26,25;,
 3;24,0,25;,
 3;27,28,29;,
 3;7,27,29;,
 3;30,31,28;,
 3;27,30,28;,
 3;32,33,31;,
 3;30,32,31;,
 3;34,35,33;,
 3;32,34,33;,
 3;36,37,35;,
 3;34,36,35;,
 3;38,39,40;,
 3;41,38,40;,
 3;42,43,39;,
 3;38,42,39;,
 3;44,45,43;,
 3;42,44,43;,
 3;46,47,45;,
 3;44,46,45;,
 3;48,49,47;,
 3;46,48,47;,
 3;50,51,49;,
 3;48,50,49;,
 3;52,53,51;,
 3;50,52,51;,
 3;54,55,53;,
 3;52,54,53;,
 3;56,38,41;,
 3;57,56,41;,
 3;58,42,38;,
 3;56,58,38;,
 3;59,44,42;,
 3;58,59,42;,
 3;60,46,44;,
 3;59,60,44;,
 3;61,48,46;,
 3;60,61,46;,
 3;62,50,48;,
 3;61,62,48;,
 3;63,52,50;,
 3;62,63,50;,
 3;64,54,52;,
 3;63,64,52;,
 3;65,56,57;,
 3;66,65,57;,
 3;67,58,56;,
 3;65,67,56;,
 3;68,59,58;,
 3;67,68,58;,
 3;69,60,59;,
 3;68,69,59;,
 3;70,61,60;,
 3;69,70,60;,
 3;71,62,61;,
 3;70,71,61;,
 3;72,63,62;,
 3;71,72,62;,
 3;73,64,63;,
 3;72,73,63;,
 3;74,65,66;,
 3;75,74,66;,
 3;76,67,65;,
 3;74,76,65;,
 3;77,68,67;,
 3;76,77,67;,
 3;78,69,68;,
 3;77,78,68;,
 3;79,70,69;,
 3;78,79,69;,
 3;80,71,70;,
 3;79,80,70;,
 3;81,72,71;,
 3;80,81,71;,
 3;82,73,72;,
 3;81,82,72;,
 3;83,74,75;,
 3;84,83,75;,
 3;85,76,74;,
 3;83,85,74;,
 3;86,77,76;,
 3;85,86,76;,
 3;87,78,77;,
 3;86,87,77;,
 3;88,79,78;,
 3;87,88,78;,
 3;89,80,79;,
 3;88,89,79;,
 3;90,81,80;,
 3;89,90,80;,
 3;91,82,81;,
 3;90,91,81;,
 3;92,83,84;,
 3;93,92,84;,
 3;94,85,83;,
 3;92,94,83;,
 3;95,86,85;,
 3;94,95,85;,
 3;96,87,86;,
 3;95,96,86;,
 3;97,88,87;,
 3;96,97,87;,
 3;98,89,88;,
 3;97,98,88;,
 3;99,90,89;,
 3;98,99,89;,
 3;100,91,90;,
 3;99,100,90;,
 3;101,92,93;,
 3;102,101,93;,
 3;103,94,92;,
 3;101,103,92;,
 3;104,95,94;,
 3;103,104,94;,
 3;105,96,95;,
 3;104,105,95;,
 3;106,97,96;,
 3;105,106,96;,
 3;107,98,97;,
 3;106,107,97;,
 3;108,99,98;,
 3;107,108,98;,
 3;109,100,99;,
 3;108,109,99;,
 3;110,101,102;,
 3;111,110,102;,
 3;112,103,101;,
 3;110,112,101;,
 3;113,104,103;,
 3;112,113,103;,
 3;114,105,104;,
 3;113,114,104;,
 3;115,106,105;,
 3;114,115,105;,
 3;116,107,106;,
 3;115,116,106;,
 3;117,108,107;,
 3;116,117,107;,
 3;118,109,108;,
 3;117,118,108;,
 3;119,110,111;,
 3;120,119,111;,
 3;121,112,110;,
 3;119,121,110;,
 3;122,113,112;,
 3;121,122,112;,
 3;123,114,113;,
 3;122,123,113;,
 3;124,115,114;,
 3;123,124,114;,
 3;125,116,115;,
 3;124,125,115;,
 3;126,117,116;,
 3;125,126,116;,
 3;127,118,117;,
 3;126,127,117;,
 3;128,119,120;,
 3;129,128,120;,
 3;130,121,119;,
 3;128,130,119;,
 3;131,122,121;,
 3;130,131,121;,
 3;132,123,122;,
 3;131,132,122;,
 3;133,124,123;,
 3;132,133,123;,
 3;134,125,124;,
 3;133,134,124;,
 3;135,126,125;,
 3;134,135,125;,
 3;136,127,126;,
 3;135,136,126;,
 3;137,128,129;,
 3;138,137,129;,
 3;139,130,128;,
 3;137,139,128;,
 3;140,131,130;,
 3;139,140,130;,
 3;141,132,131;,
 3;140,141,131;,
 3;142,133,132;,
 3;141,142,132;,
 3;143,134,133;,
 3;142,143,133;,
 3;144,135,134;,
 3;143,144,134;,
 3;145,136,135;,
 3;144,145,135;,
 3;40,39,146;,
 3;39,43,147;,
 3;43,45,148;,
 3;45,47,149;,
 3;47,49,150;,
 3;49,51,151;,
 3;51,53,152;,
 3;53,55,153;,
 3;144,143,154;,
 3;143,142,155;,
 3;142,141,156;,
 3;141,140,157;,
 3;140,139,158;,
 3;139,137,159;,
 3;137,138,160;,
 3;145,144,161;,
 3;162,163,164;,
 3;165,162,164;,
 3;166,167,163;,
 3;162,166,163;,
 3;168,169,167;,
 3;166,168,167;,
 3;3,2,169;,
 3;168,3,169;,
 3;170,171,172;,
 3;173,170,172;,
 3;174,175,172;,
 3;176,174,172;,
 3;177,178,175;,
 3;174,177,175;,
 3;179,9,178;,
 3;177,179,178;,
 3;180,181,9;,
 3;179,180,9;,
 3;182,26,181;,
 3;180,182,181;,
 3;183,184,185;,
 3;173,183,185;,
 3;186,187,184;,
 3;183,186,184;,
 3;8,188,187;,
 3;186,8,187;,
 3;189,190,188;,
 3;8,189,188;,
 3;190,189,191;,
 3;192,193,194;,
 3;195,196,197;,
 3;198,195,197;,
 3;199,200,197;,
 3;201,199,197;,
 3;202,203,200;,
 3;199,202,200;,
 3;204,31,203;,
 3;202,204,203;,
 3;205,206,31;,
 3;204,205,31;,
 3;207,1,206;,
 3;205,207,206;,
 3;208,209,210;,
 3;198,208,210;,
 3;211,212,209;,
 3;208,211,209;,
 3;30,213,212;,
 3;211,30,212;,
 3;214,215,213;,
 3;30,214,213;,
 3;215,214,191;,
 3;216,217,194;;
 
 MeshMaterialList {
  3;
  276;
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\OC\\Desktop\\Ver.3.0\\Ver.3.1\\Ver.3.1\\data\\TEXTURE\\CrobatTex2.png";
   }
  }
  Material {
   0.414118;0.191373;0.492549;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.404706;0.787451;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  187;
  0.032635;-0.027164;0.999098;,
  0.055699;-0.017759;0.998290;,
  0.011547;-0.043876;0.998970;,
  0.009356;-0.052266;0.998589;,
  0.004253;-0.022980;-0.999727;,
  0.019615;-0.049507;-0.998581;,
  -0.009378;-0.051174;-0.998646;,
  0.010799;-0.026367;-0.999594;,
  0.036560;-0.056157;-0.997752;,
  0.023662;-0.029034;-0.999298;,
  0.071496;-0.062334;-0.995491;,
  0.050878;-0.038867;-0.997948;,
  0.249484;-0.103393;-0.962843;,
  0.095573;-0.084717;-0.991811;,
  0.097368;-0.094291;-0.990772;,
  -0.036599;-0.148252;-0.988272;,
  -0.030705;-0.239489;-0.970413;,
  -0.069796;-0.292497;-0.953716;,
  -0.101357;-0.308266;-0.945885;,
  -0.000608;-0.091857;-0.995772;,
  -0.004958;-0.139771;-0.990171;,
  0.008150;-0.050638;-0.998684;,
  0.006420;-0.076799;-0.997026;,
  -0.004101;-0.048270;-0.998826;,
  -0.019634;-0.063675;-0.997778;,
  0.057811;-0.023121;0.998060;,
  0.028674;-0.055930;0.998023;,
  0.013169;-0.073556;0.997204;,
  -0.001977;-0.117568;0.993063;,
  -0.002277;-0.140443;0.990086;,
  -0.024310;-0.209743;0.977454;,
  -0.023974;-0.234819;0.971743;,
  -0.058617;-0.360911;0.930756;,
  -0.063800;-0.397117;0.915548;,
  -0.103550;-0.529172;0.842172;,
  -0.177030;-0.719025;0.672059;,
  -0.259010;-0.784771;0.563070;,
  -0.051612;-0.161174;0.985576;,
  -0.001882;-0.015969;0.999871;,
  -0.252253;-0.967652;-0.004215;,
  -0.334712;-0.942295;-0.006882;,
  -0.211295;-0.750359;-0.626351;,
  -0.007399;-0.001723;-0.999971;,
  0.028544;0.125834;-0.991641;,
  0.153595;0.719685;-0.677098;,
  0.158318;0.697817;-0.698561;,
  0.219326;0.974986;0.036021;,
  0.246631;0.962736;0.110963;,
  0.166423;0.749253;0.641032;,
  0.179795;0.792483;0.582791;,
  -0.135542;-0.729161;0.670785;,
  0.001040;0.000248;0.999999;,
  -0.183499;-0.983020;-0.000354;,
  -0.136641;-0.728902;-0.670843;,
  -0.001039;-0.000247;-0.999999;,
  0.135544;0.729162;-0.670784;,
  0.183504;0.983019;0.000355;,
  0.136645;0.728901;0.670843;,
  -0.104154;-0.729520;0.675982;,
  0.005342;0.001307;0.999985;,
  -0.145293;-0.989387;-0.001744;,
  -0.110123;-0.728419;-0.676223;,
  -0.005343;-0.001307;-0.999985;,
  0.104152;0.729520;-0.675983;,
  0.145290;0.989388;0.001744;,
  0.110122;0.728420;0.676223;,
  -0.042645;-0.726889;0.685430;,
  0.007444;0.001940;0.999970;,
  -0.064636;-0.997907;-0.002141;,
  -0.051770;-0.726108;-0.685629;,
  -0.007444;-0.001933;-0.999970;,
  0.042644;0.726892;-0.685426;,
  0.064633;0.997907;0.002140;,
  0.051768;0.726109;0.685628;,
  0.092589;-0.708382;0.699730;,
  0.018129;0.005275;0.999822;,
  0.112991;-0.993591;-0.003061;,
  0.067749;-0.711076;-0.699843;,
  -0.018127;-0.005284;-0.999822;,
  -0.092586;0.708380;-0.699732;,
  -0.112988;0.993592;0.003061;,
  -0.067747;0.711073;0.699847;,
  0.232610;-0.670560;0.704444;,
  0.010587;0.003455;0.999938;,
  0.317414;-0.948287;0.000083;,
  0.217954;-0.675465;-0.704445;,
  -0.010587;-0.003456;-0.999938;,
  -0.232610;0.670557;-0.704447;,
  -0.317415;0.948287;-0.000082;,
  -0.217954;0.675466;0.704444;,
  0.308825;-0.641378;0.702326;,
  -0.010325;-0.003772;0.999940;,
  0.433183;-0.901306;0.000716;,
  0.297183;-0.646566;-0.702591;,
  -0.027713;-0.009980;-0.999566;,
  -0.344529;0.625262;-0.700248;,
  -0.467598;0.883939;-0.001693;,
  -0.333889;0.631512;0.699793;,
  0.420733;-0.583300;0.694798;,
  -0.015693;-0.005946;0.999859;,
  0.582245;-0.813001;0.004585;,
  0.401938;-0.597063;-0.694235;,
  -0.050655;-0.019354;-0.998529;,
  -0.477849;0.550644;-0.684435;,
  -0.632588;0.774473;-0.004944;,
  -0.460771;0.565211;0.684271;,
  0.563500;-0.485256;0.668577;,
  -0.019582;-0.008824;0.999769;,
  0.756875;-0.653524;0.006922;,
  0.549293;-0.502144;-0.667929;,
  -0.059282;-0.026316;-0.997894;,
  -0.617603;0.442680;-0.650078;,
  -0.795575;0.605796;-0.008467;,
  -0.608228;0.459886;0.646965;,
  0.697562;-0.354354;0.622768;,
  -0.032153;-0.017246;0.999334;,
  0.892192;-0.451497;0.011992;,
  0.689793;-0.377108;-0.618041;,
  -0.094468;-0.049888;-0.994277;,
  -0.761040;0.288109;-0.581215;,
  -0.922787;0.385089;-0.013053;,
  -0.761188;0.308155;0.570643;,
  0.743725;-0.233178;0.626500;,
  0.541809;-0.185278;0.819826;,
  0.960667;-0.273269;0.049423;,
  0.830317;-0.255890;-0.495070;,
  0.527085;-0.193436;-0.827504;,
  -0.825893;0.143701;-0.545207;,
  -0.979129;0.198302;-0.044522;,
  -0.889032;0.167114;0.426257;,
  0.998810;-0.044688;-0.019542;,
  -0.993839;0.110835;0.000000;,
  0.133472;-0.076840;0.988069;,
  0.114982;-0.061545;0.991459;,
  0.163873;-0.080419;0.983198;,
  0.062703;-0.063072;0.996037;,
  0.053363;-0.056875;0.996954;,
  0.028475;-0.057363;0.997947;,
  0.025752;-0.050652;0.998384;,
  -0.020450;-0.043835;-0.998829;,
  -0.207225;-0.978238;-0.010440;,
  0.259837;0.957646;-0.124090;,
  0.096371;0.342835;0.934439;,
  -0.688935;0.092913;-0.718843;,
  -0.667028;0.108107;0.737148;,
  0.969474;-0.084474;0.230184;,
  0.968009;-0.143480;0.205844;,
  0.982850;-0.163680;-0.084943;,
  0.939457;-0.194584;-0.282060;,
  0.964438;-0.139332;-0.224600;,
  0.989988;0.083791;-0.113590;,
  0.978050;0.208370;0.000000;,
  0.989988;0.083791;0.113590;,
  0.934653;-0.197162;-0.295891;,
  0.250922;-0.090968;0.963723;,
  -0.969584;0.244759;0.000000;,
  -0.964929;0.262513;0.000000;,
  -0.185125;0.000000;-0.982715;,
  -0.921754;0.387776;0.000000;,
  -0.879946;0.475074;0.000000;,
  -0.778495;0.627651;0.000000;,
  -0.720161;0.693807;0.000000;,
  -0.601610;0.798790;0.000000;,
  -0.543151;0.839635;0.000000;,
  -0.466073;0.884746;0.000000;,
  -0.449737;0.893161;0.000000;,
  -0.356152;0.934428;0.000000;,
  -0.275965;0.961168;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.877321;0.479904;0.000000;,
  0.326982;0.945030;0.000185;,
  0.260130;0.965574;0.000000;,
  0.260148;0.965569;0.000093;,
  0.327016;0.945019;0.000369;,
  0.183015;0.983110;0.000000;,
  0.173972;0.984751;0.000000;,
  0.153058;0.988217;0.000000;,
  0.141176;0.989985;0.000000;,
  0.087409;0.996172;0.000000;,
  0.045313;0.998973;0.000000;,
  -0.062933;0.998018;0.000000;,
  -0.129092;0.991633;0.000000;,
  -0.038200;-0.033841;-0.998697;,
  -0.033432;-0.999441;-0.000615;,
  -0.013251;-0.014827;-0.999802;,
  -0.877321;-0.479904;0.000000;;
  276;
  3;0,1,2;,
  3;3,0,2;,
  3;4,5,6;,
  3;139,4,6;,
  3;7,8,5;,
  3;4,7,5;,
  3;9,10,8;,
  3;7,9,8;,
  3;11,12,10;,
  3;9,11,10;,
  3;13,14,12;,
  3;11,13,12;,
  3;15,16,17;,
  3;18,15,17;,
  3;19,20,16;,
  3;15,19,16;,
  3;21,22,20;,
  3;19,21,20;,
  3;23,24,22;,
  3;21,23,22;,
  3;139,6,24;,
  3;23,139,24;,
  3;25,26,1;,
  3;0,25,1;,
  3;27,28,26;,
  3;25,27,26;,
  3;29,30,28;,
  3;27,29,28;,
  3;31,32,30;,
  3;29,31,30;,
  3;33,34,32;,
  3;31,33,32;,
  3;35,36,37;,
  3;38,35,37;,
  3;39,40,36;,
  3;35,39,36;,
  3;41,140,40;,
  3;39,41,40;,
  3;42,43,18;,
  3;41,42,18;,
  3;44,45,43;,
  3;42,44,43;,
  3;46,47,141;,
  3;44,46,45;,
  3;48,49,47;,
  3;46,48,47;,
  3;38,37,142;,
  3;48,38,49;,
  3;50,35,38;,
  3;51,50,38;,
  3;52,39,35;,
  3;50,52,35;,
  3;53,41,39;,
  3;52,53,39;,
  3;54,42,41;,
  3;53,54,41;,
  3;55,44,42;,
  3;54,55,42;,
  3;56,46,44;,
  3;55,56,44;,
  3;57,48,46;,
  3;56,57,46;,
  3;51,38,48;,
  3;57,51,48;,
  3;58,50,51;,
  3;59,58,51;,
  3;60,52,50;,
  3;58,60,50;,
  3;61,53,52;,
  3;60,61,52;,
  3;62,54,53;,
  3;61,62,53;,
  3;63,55,54;,
  3;62,63,54;,
  3;64,56,55;,
  3;63,64,55;,
  3;65,57,56;,
  3;64,65,56;,
  3;59,51,57;,
  3;65,59,57;,
  3;66,58,59;,
  3;67,66,59;,
  3;68,60,58;,
  3;66,68,58;,
  3;69,61,60;,
  3;68,69,60;,
  3;70,62,61;,
  3;69,70,61;,
  3;71,63,62;,
  3;70,71,62;,
  3;72,64,63;,
  3;71,72,63;,
  3;73,65,64;,
  3;72,73,64;,
  3;67,59,65;,
  3;73,67,65;,
  3;74,66,67;,
  3;75,74,67;,
  3;76,68,66;,
  3;74,76,66;,
  3;77,69,68;,
  3;76,77,68;,
  3;78,70,69;,
  3;77,78,69;,
  3;79,71,70;,
  3;78,79,70;,
  3;80,72,71;,
  3;79,80,71;,
  3;81,73,72;,
  3;80,81,72;,
  3;75,67,73;,
  3;81,75,73;,
  3;82,74,75;,
  3;83,82,75;,
  3;84,76,74;,
  3;82,84,74;,
  3;85,77,76;,
  3;84,85,76;,
  3;86,78,77;,
  3;85,86,77;,
  3;87,79,78;,
  3;86,87,78;,
  3;88,80,79;,
  3;87,88,79;,
  3;89,81,80;,
  3;88,89,80;,
  3;83,75,81;,
  3;89,83,81;,
  3;90,82,83;,
  3;91,90,83;,
  3;92,84,82;,
  3;90,92,82;,
  3;93,85,84;,
  3;92,93,84;,
  3;94,86,85;,
  3;93,94,85;,
  3;95,87,86;,
  3;94,95,86;,
  3;96,88,87;,
  3;95,96,87;,
  3;97,89,88;,
  3;96,97,88;,
  3;91,83,89;,
  3;97,91,89;,
  3;98,90,91;,
  3;99,98,91;,
  3;100,92,90;,
  3;98,100,90;,
  3;101,93,92;,
  3;100,101,92;,
  3;102,94,93;,
  3;101,102,93;,
  3;103,95,94;,
  3;102,103,94;,
  3;104,96,95;,
  3;103,104,95;,
  3;105,97,96;,
  3;104,105,96;,
  3;99,91,97;,
  3;105,99,97;,
  3;106,98,99;,
  3;107,106,99;,
  3;108,100,98;,
  3;106,108,98;,
  3;109,101,100;,
  3;108,109,100;,
  3;110,102,101;,
  3;109,110,101;,
  3;111,103,102;,
  3;110,111,102;,
  3;112,104,103;,
  3;111,112,103;,
  3;113,105,104;,
  3;112,113,104;,
  3;107,99,105;,
  3;113,107,105;,
  3;114,106,107;,
  3;115,114,107;,
  3;116,108,106;,
  3;114,116,106;,
  3;117,109,108;,
  3;116,117,108;,
  3;118,110,109;,
  3;117,118,109;,
  3;119,111,110;,
  3;118,119,110;,
  3;120,112,111;,
  3;119,120,111;,
  3;121,113,112;,
  3;120,121,112;,
  3;115,107,113;,
  3;121,115,113;,
  3;122,114,115;,
  3;123,122,115;,
  3;124,116,114;,
  3;122,124,114;,
  3;125,117,116;,
  3;124,125,116;,
  3;126,118,117;,
  3;125,126,117;,
  3;127,119,118;,
  3;143,127,118;,
  3;128,120,119;,
  3;127,128,119;,
  3;129,121,120;,
  3;128,129,120;,
  3;144,115,121;,
  3;129,144,121;,
  3;145,146,130;,
  3;146,147,130;,
  3;147,148,130;,
  3;148,149,130;,
  3;149,150,130;,
  3;150,151,130;,
  3;151,152,130;,
  3;152,145,130;,
  3;129,128,131;,
  3;128,127,131;,
  3;127,143,131;,
  3;126,125,153;,
  3;125,124,153;,
  3;124,122,153;,
  3;122,123,154;,
  3;144,129,131;,
  3;132,133,134;,
  3;154,132,134;,
  3;135,136,133;,
  3;132,135,133;,
  3;137,138,136;,
  3;135,137,136;,
  3;3,2,138;,
  3;137,3,138;,
  3;131,155,156;,
  3;13,157,14;,
  3;158,159,156;,
  3;155,158,156;,
  3;160,161,159;,
  3;158,160,159;,
  3;162,163,161;,
  3;160,162,161;,
  3;164,165,163;,
  3;162,164,163;,
  3;166,167,165;,
  3;164,166,165;,
  3;11,168,157;,
  3;169,169,154;,
  3;9,168,168;,
  3;11,9,168;,
  3;7,168,168;,
  3;9,7,168;,
  3;4,168,168;,
  3;7,4,168;,
  3;168,4,139;,
  3;170,170,170;,
  3;171,172,173;,
  3;174,171,173;,
  3;175,176,173;,
  3;172,175,173;,
  3;177,178,176;,
  3;175,177,176;,
  3;179,180,178;,
  3;177,179,178;,
  3;181,182,180;,
  3;179,181,180;,
  3;167,166,182;,
  3;181,167,182;,
  3;183,15,18;,
  3;184,184,140;,
  3;168,19,15;,
  3;183,168,15;,
  3;168,21,19;,
  3;168,168,19;,
  3;185,23,21;,
  3;168,185,21;,
  3;23,185,139;,
  3;186,186,186;;
 }
 MeshTextureCoords {
  218;
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.166670;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.125000;0.916670;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.916670;,
  0.250000;0.916670;,
  0.250000;1.000000;,
  0.375000;0.916670;,
  0.375000;1.000000;,
  0.500000;0.916670;,
  0.500000;1.000000;,
  0.625000;0.916670;,
  0.625000;1.000000;,
  0.750000;0.916670;,
  0.750000;1.000000;,
  0.875000;0.916670;,
  0.875000;1.000000;,
  1.000000;0.916670;,
  1.000000;1.000000;,
  0.125000;0.833330;,
  0.000000;0.833330;,
  0.250000;0.833330;,
  0.375000;0.833330;,
  0.500000;0.833330;,
  0.625000;0.833330;,
  0.750000;0.833330;,
  0.875000;0.833330;,
  1.000000;0.833330;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.666670;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.375000;0.666670;,
  0.500000;0.666670;,
  0.625000;0.666670;,
  0.750000;0.666670;,
  0.875000;0.666670;,
  1.000000;0.666670;,
  0.125000;0.583330;,
  0.000000;0.583330;,
  0.250000;0.583330;,
  0.375000;0.583330;,
  0.500000;0.583330;,
  0.625000;0.583330;,
  0.750000;0.583330;,
  0.875000;0.583330;,
  1.000000;0.583330;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.416670;,
  0.000000;0.416670;,
  0.250000;0.416670;,
  0.375000;0.416670;,
  0.500000;0.416670;,
  0.625000;0.416670;,
  0.750000;0.416670;,
  0.875000;0.416670;,
  1.000000;0.416670;,
  0.125000;0.333330;,
  0.000000;0.333330;,
  0.250000;0.333330;,
  0.375000;0.333330;,
  0.500000;0.333330;,
  0.625000;0.333330;,
  0.750000;0.333330;,
  0.875000;0.333330;,
  1.000000;0.333330;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.166670;,
  0.000000;0.166670;,
  0.250000;0.166670;,
  0.375000;0.166670;,
  0.500000;0.166670;,
  0.625000;0.166670;,
  0.750000;0.166670;,
  0.875000;0.166670;,
  1.000000;0.166670;,
  0.125000;0.083330;,
  0.000000;0.083330;,
  0.250000;0.083330;,
  0.375000;0.083330;,
  0.500000;0.083330;,
  0.625000;0.083330;,
  0.750000;0.083330;,
  0.875000;0.083330;,
  1.000000;0.083330;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.812500;0.000000;,
  0.687500;0.000000;,
  0.562500;0.000000;,
  0.437500;0.000000;,
  0.312500;0.000000;,
  0.187500;0.000000;,
  0.062500;0.000000;,
  0.937500;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}