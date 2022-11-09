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
 335;
 0.00000;130.91409;0.00000;,
 16.05660;122.96270;-16.05660;,
 0.00000;122.96270;-22.70746;,
 0.00000;130.91409;0.00000;,
 22.70746;122.96270;0.00000;,
 0.00000;130.91409;0.00000;,
 16.05660;122.96270;16.05660;,
 0.00000;130.91409;0.00000;,
 0.00000;122.96270;22.70746;,
 0.00000;130.91409;0.00000;,
 -16.05660;122.96270;16.05660;,
 0.00000;130.91409;0.00000;,
 -22.70746;122.96270;0.00000;,
 0.00000;130.91409;0.00000;,
 -16.05660;122.96270;-16.05660;,
 0.00000;130.91409;0.00000;,
 0.00000;122.96270;-22.70746;,
 25.98014;102.14599;-25.98014;,
 0.00000;102.14599;-36.74148;,
 36.74148;102.14599;0.00000;,
 25.98014;102.14599;25.98014;,
 0.00000;102.14599;36.74148;,
 -25.98016;102.14599;25.98014;,
 -36.74148;102.14599;0.00000;,
 -25.98016;102.14599;-25.98014;,
 0.00000;102.14599;-36.74148;,
 25.98014;76.41520;-25.98014;,
 0.00000;76.41520;-36.74148;,
 36.74148;76.41520;0.00000;,
 25.98014;76.41520;25.98014;,
 0.00000;76.41520;36.74148;,
 -25.98014;76.41520;25.98014;,
 -36.74148;76.41520;0.00000;,
 -25.98014;76.41520;-25.98014;,
 0.00000;76.41520;-36.74148;,
 12.38848;50.59408;-13.89432;,
 0.00000;50.59408;-19.64954;,
 17.51996;50.59408;0.00000;,
 12.38848;50.59408;13.89432;,
 0.00000;50.59408;19.64954;,
 -12.38850;50.59408;13.89432;,
 -17.51996;50.59408;0.00000;,
 -12.38848;50.59408;-13.89432;,
 0.00000;50.59408;-19.64954;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 0.00000;35.76232;0.00000;,
 -14.22000;14.18228;-14.20400;,
 14.19000;14.18228;-14.20400;,
 14.19000;-0.06342;-14.20400;,
 -14.22000;-0.06342;-14.20400;,
 14.19000;14.18228;-14.20400;,
 14.19000;14.18228;14.09000;,
 14.19000;-0.06342;14.09000;,
 14.19000;-0.06342;-14.20400;,
 14.19000;14.18228;14.09000;,
 -14.22000;14.18228;14.09000;,
 -14.22000;-0.06342;14.09000;,
 14.19000;-0.06342;14.09000;,
 -14.22000;14.18228;14.09000;,
 -14.22000;14.18228;-14.20400;,
 -14.22000;-0.06342;-14.20400;,
 -14.22000;-0.06342;14.09000;,
 14.19000;14.18228;-14.20400;,
 -14.22000;14.18228;-14.20400;,
 -14.22000;-0.06342;-14.20400;,
 14.19000;-0.06342;-14.20400;,
 -14.22000;31.03328;11.58774;,
 -11.64624;31.03328;11.58774;,
 -11.64624;8.37964;11.58774;,
 -14.22000;8.37964;11.58774;,
 -11.64624;31.03328;11.58774;,
 -11.64624;31.03328;14.09000;,
 -11.64624;8.37964;14.09000;,
 -11.64624;8.37964;11.58774;,
 -11.64624;31.03328;14.09000;,
 -14.22000;31.03328;14.09000;,
 -14.22000;8.37964;14.09000;,
 -11.64624;8.37964;14.09000;,
 -14.22000;31.03328;14.09000;,
 -14.22000;31.03328;11.58774;,
 -14.22000;8.37964;11.58774;,
 -14.22000;8.37964;14.09000;,
 -11.64624;31.03328;11.58774;,
 -14.22000;31.03328;11.58774;,
 -14.22000;8.37964;11.58774;,
 -11.64624;8.37964;11.58774;,
 11.51338;31.03328;11.31062;,
 14.19000;31.03328;11.31062;,
 14.19000;8.37964;11.31062;,
 11.51338;8.37964;11.31062;,
 14.19000;31.03328;11.31062;,
 14.19000;31.03328;14.09000;,
 14.19000;8.37964;14.09000;,
 14.19000;8.37964;11.31062;,
 14.19000;31.03328;14.09000;,
 11.51338;31.03328;14.09000;,
 11.51338;8.37964;14.09000;,
 14.19000;8.37964;14.09000;,
 11.51338;31.03328;14.09000;,
 11.51338;31.03328;11.31062;,
 11.51338;8.37964;11.31062;,
 11.51338;8.37964;14.09000;,
 14.19000;31.03328;11.31062;,
 11.51338;31.03328;11.31062;,
 11.51338;8.37964;11.31062;,
 14.19000;8.37964;11.31062;,
 11.51338;31.03328;-14.20400;,
 14.19000;31.03328;-14.20400;,
 14.19000;8.37964;-14.20400;,
 11.51338;8.37964;-14.20400;,
 14.19000;31.03328;-14.20400;,
 14.19000;31.03328;-11.54026;,
 14.19000;8.37964;-11.54026;,
 14.19000;8.37964;-14.20400;,
 14.19000;31.03328;-11.54026;,
 11.51338;31.03328;-11.54026;,
 11.51338;8.37964;-11.54026;,
 14.19000;8.37964;-11.54026;,
 11.51338;31.03328;-11.54026;,
 11.51338;31.03328;-14.20400;,
 11.51338;8.37964;-14.20400;,
 11.51338;8.37964;-11.54026;,
 14.19000;31.03328;-14.20400;,
 11.51338;31.03328;-14.20400;,
 11.51338;8.37964;-14.20400;,
 14.19000;8.37964;-14.20400;,
 -14.22000;31.03328;-14.20400;,
 -11.57094;31.03328;-14.20400;,
 -11.57094;8.37964;-14.20400;,
 -14.22000;8.37964;-14.20400;,
 -11.57094;31.03328;-14.20400;,
 -11.57094;31.03328;-11.54026;,
 -11.57094;8.37964;-11.54026;,
 -11.57094;8.37964;-14.20400;,
 -11.57094;31.03328;-11.54026;,
 -14.22000;31.03328;-11.54026;,
 -14.22000;8.37964;-11.54026;,
 -11.57094;8.37964;-11.54026;,
 -14.22000;31.03328;-11.54026;,
 -14.22000;31.03328;-14.20400;,
 -14.22000;8.37964;-14.20400;,
 -14.22000;8.37964;-11.54026;,
 -11.57094;31.03328;-14.20400;,
 -14.22000;31.03328;-14.20400;,
 -14.22000;8.37964;-14.20400;,
 -11.57094;8.37964;-14.20400;,
 15.02072;31.54480;0.00000;,
 15.96262;33.17622;0.00000;,
 11.27272;33.17622;-11.32246;,
 10.60668;31.54480;-10.65644;,
 17.84644;33.17622;0.00000;,
 12.60476;33.17622;-12.65452;,
 18.78834;31.54480;0.00000;,
 13.27080;31.54480;-13.32056;,
 17.84644;29.91338;0.00000;,
 12.60476;29.91338;-12.65452;,
 15.96262;29.91338;0.00000;,
 11.27272;29.91338;-11.32246;,
 15.02072;31.54480;0.00000;,
 10.60668;31.54480;-10.65644;,
 -0.04976;33.17622;-16.01238;,
 -0.04976;31.54480;-15.07048;,
 -0.04976;33.17622;-17.89620;,
 -0.04976;31.54480;-18.83810;,
 -0.04976;29.91338;-17.89620;,
 -0.04976;29.91338;-16.01238;,
 -0.04976;31.54480;-15.07048;,
 -11.37222;33.17622;-11.32246;,
 -10.70620;31.54480;-10.65644;,
 -12.70428;33.17622;-12.65452;,
 -13.37030;31.54480;-13.32056;,
 -12.70428;29.91338;-12.65452;,
 -11.37222;29.91338;-11.32246;,
 -10.70620;31.54480;-10.65644;,
 -16.06214;33.17622;0.00000;,
 -15.12024;31.54480;0.00000;,
 -17.94596;33.17622;0.00000;,
 -18.88786;31.54480;0.00000;,
 -17.94596;29.91338;0.00000;,
 -16.06214;29.91338;0.00000;,
 -15.12024;31.54480;0.00000;,
 -11.37222;33.17622;11.32248;,
 -10.70620;31.54480;10.65644;,
 -12.70428;33.17622;12.65452;,
 -13.37030;31.54480;13.32056;,
 -12.70428;29.91338;12.65452;,
 -11.37222;29.91338;11.32248;,
 -10.70620;31.54480;10.65644;,
 -0.04976;33.17622;16.01238;,
 -0.04976;31.54480;15.07048;,
 -0.04976;33.17622;17.89620;,
 -0.04976;31.54480;18.83810;,
 -0.04976;29.91338;17.89620;,
 -0.04976;29.91338;16.01238;,
 -0.04976;31.54480;15.07048;,
 11.27270;33.17622;11.32246;,
 10.60668;31.54480;10.65644;,
 12.60476;33.17622;12.65452;,
 13.27080;31.54480;13.32056;,
 12.60476;29.91338;12.65452;,
 11.27270;29.91338;11.32246;,
 10.60668;31.54480;10.65644;,
 15.96262;33.17622;0.00000;,
 15.02072;31.54480;0.00000;,
 17.84644;33.17622;0.00000;,
 18.78834;31.54480;0.00000;,
 17.84644;29.91338;0.00000;,
 15.96262;29.91338;0.00000;,
 15.02072;31.54480;0.00000;,
 8.99422;52.87000;-9.06764;,
 9.63118;52.92148;-8.81102;,
 13.41396;28.46039;-13.29220;,
 12.77700;28.40891;-13.54882;,
 9.84038;52.83470;-8.16070;,
 13.62316;28.37360;-12.64188;,
 9.46428;52.67498;-7.60638;,
 13.24708;28.21390;-12.08756;,
 8.78612;52.56260;-7.56548;,
 12.56890;28.10154;-12.04666;,
 8.31654;52.58220;-8.06880;,
 12.09932;28.12112;-12.54998;,
 8.40916;52.71899;-8.73734;,
 12.19194;28.25792;-13.21850;,
 8.99422;52.87000;-9.06764;,
 12.77700;28.40891;-13.54882;,
 9.06312;52.73785;-8.28820;,
 9.06312;52.73785;-8.28820;,
 9.06312;52.73785;-8.28820;,
 9.06312;52.73785;-8.28820;,
 9.06312;52.73785;-8.28820;,
 9.06312;52.73785;-8.28820;,
 9.06312;52.73785;-8.28820;,
 12.84590;28.27678;-12.76938;,
 12.84590;28.27678;-12.76938;,
 12.84590;28.27678;-12.76938;,
 12.84590;28.27678;-12.76938;,
 12.84590;28.27678;-12.76938;,
 12.84590;28.27678;-12.76938;,
 12.84590;28.27678;-12.76938;,
 -8.69054;52.87000;-8.58044;,
 -8.43392;52.92148;-9.21738;,
 -12.91508;28.46039;-13.00016;,
 -13.17170;28.40891;-12.36322;,
 -7.78360;52.83470;-9.42658;,
 -12.26476;28.37360;-13.20936;,
 -7.22928;52.67498;-9.05050;,
 -11.71044;28.21390;-12.83328;,
 -7.18838;52.56260;-8.37232;,
 -11.66954;28.10154;-12.15510;,
 -7.69170;52.58220;-7.90274;,
 -12.17286;28.12112;-11.68552;,
 -8.36022;52.71899;-7.99536;,
 -12.84138;28.25792;-11.77814;,
 -8.69054;52.87000;-8.58044;,
 -13.17170;28.40891;-12.36322;,
 -7.91108;52.73785;-8.64934;,
 -7.91108;52.73785;-8.64934;,
 -7.91108;52.73785;-8.64934;,
 -7.91108;52.73785;-8.64934;,
 -7.91108;52.73785;-8.64934;,
 -7.91108;52.73785;-8.64934;,
 -7.91108;52.73785;-8.64934;,
 -12.39226;28.27678;-12.43212;,
 -12.39226;28.27678;-12.43212;,
 -12.39226;28.27678;-12.43212;,
 -12.39226;28.27678;-12.43212;,
 -12.39226;28.27678;-12.43212;,
 -12.39226;28.27678;-12.43212;,
 -12.39226;28.27678;-12.43212;,
 -9.10998;52.87000;8.95620;,
 -9.74692;52.92148;8.69958;,
 -13.52970;28.46039;13.18074;,
 -12.89276;28.40891;13.43736;,
 -9.95612;52.83470;8.04926;,
 -13.73890;28.37360;12.53042;,
 -9.58004;52.67498;7.49494;,
 -13.36282;28.21390;11.97610;,
 -8.90186;52.56260;7.45404;,
 -12.68464;28.10154;11.93520;,
 -8.43228;52.58220;7.95736;,
 -12.21508;28.12112;12.43852;,
 -8.52490;52.71899;8.62588;,
 -12.30768;28.25792;13.10704;,
 -9.10998;52.87000;8.95620;,
 -12.89276;28.40891;13.43736;,
 -9.17888;52.73785;8.17674;,
 -9.17888;52.73785;8.17674;,
 -9.17888;52.73785;8.17674;,
 -9.17888;52.73785;8.17674;,
 -9.17888;52.73785;8.17674;,
 -9.17888;52.73785;8.17674;,
 -9.17888;52.73785;8.17674;,
 -12.96166;28.27678;12.65792;,
 -12.96166;28.27678;12.65792;,
 -12.96166;28.27678;12.65792;,
 -12.96166;28.27678;12.65792;,
 -12.96166;28.27678;12.65792;,
 -12.96166;28.27678;12.65792;,
 -12.96166;28.27678;12.65792;,
 8.97356;52.87000;8.89906;,
 8.71694;52.92148;9.53602;,
 13.19812;28.46039;13.31880;,
 13.45474;28.40891;12.68184;,
 8.06662;52.83470;9.74520;,
 12.54780;28.37360;13.52800;,
 7.51230;52.67498;9.36912;,
 11.99348;28.21390;13.15192;,
 7.47140;52.56260;8.69096;,
 11.95258;28.10154;12.47374;,
 7.97472;52.58220;8.22138;,
 12.45590;28.12112;12.00416;,
 8.64326;52.71899;8.31400;,
 13.12442;28.25792;12.09678;,
 8.97356;52.87000;8.89906;,
 13.45474;28.40891;12.68184;,
 8.19412;52.73785;8.96796;,
 8.19412;52.73785;8.96796;,
 8.19412;52.73785;8.96796;,
 8.19412;52.73785;8.96796;,
 8.19412;52.73785;8.96796;,
 8.19412;52.73785;8.96796;,
 8.19412;52.73785;8.96796;,
 12.67530;28.27678;12.75074;,
 12.67530;28.27678;12.75074;,
 12.67530;28.27678;12.75074;,
 12.67530;28.27678;12.75074;,
 12.67530;28.27678;12.75074;,
 12.67530;28.27678;12.75074;,
 12.67530;28.27678;12.75074;;
 
 202;
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
 3;36,35,44;,
 3;35,37,45;,
 3;37,38,46;,
 3;38,39,47;,
 3;39,40,48;,
 3;40,41,49;,
 3;41,42,50;,
 3;42,43,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;64,57,68,69;,
 4;70,71,58,67;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;84,77,88,89;,
 4;90,91,78,87;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;104,97,108,109;,
 4;110,111,98,107;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;124,117,128,129;,
 4;130,131,118,127;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;144,137,148,149;,
 4;150,151,138,147;,
 4;152,153,154,155;,
 4;153,156,157,154;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;155,154,166,167;,
 4;154,157,168,166;,
 4;157,159,169,168;,
 4;159,161,170,169;,
 4;161,163,171,170;,
 4;163,165,172,171;,
 4;167,166,173,174;,
 4;166,168,175,173;,
 4;168,169,176,175;,
 4;169,170,177,176;,
 4;170,171,178,177;,
 4;171,172,179,178;,
 4;174,173,180,181;,
 4;173,175,182,180;,
 4;175,176,183,182;,
 4;176,177,184,183;,
 4;177,178,185,184;,
 4;178,179,186,185;,
 4;181,180,187,188;,
 4;180,182,189,187;,
 4;182,183,190,189;,
 4;183,184,191,190;,
 4;184,185,192,191;,
 4;185,186,193,192;,
 4;188,187,194,195;,
 4;187,189,196,194;,
 4;189,190,197,196;,
 4;190,191,198,197;,
 4;191,192,199,198;,
 4;192,193,200,199;,
 4;195,194,201,202;,
 4;194,196,203,201;,
 4;196,197,204,203;,
 4;197,198,205,204;,
 4;198,199,206,205;,
 4;199,200,207,206;,
 4;202,201,208,209;,
 4;201,203,210,208;,
 4;203,204,211,210;,
 4;204,205,212,211;,
 4;205,206,213,212;,
 4;206,207,214,213;,
 4;215,216,217,218;,
 4;216,219,220,217;,
 4;219,221,222,220;,
 4;221,223,224,222;,
 4;223,225,226,224;,
 4;225,227,228,226;,
 4;227,229,230,228;,
 3;231,216,215;,
 3;232,219,216;,
 3;233,221,219;,
 3;234,223,221;,
 3;235,225,223;,
 3;236,227,225;,
 3;237,229,227;,
 3;238,218,217;,
 3;239,217,220;,
 3;240,220,222;,
 3;241,222,224;,
 3;242,224,226;,
 3;243,226,228;,
 3;244,228,230;,
 4;245,246,247,248;,
 4;246,249,250,247;,
 4;249,251,252,250;,
 4;251,253,254,252;,
 4;253,255,256,254;,
 4;255,257,258,256;,
 4;257,259,260,258;,
 3;261,246,245;,
 3;262,249,246;,
 3;263,251,249;,
 3;264,253,251;,
 3;265,255,253;,
 3;266,257,255;,
 3;267,259,257;,
 3;268,248,247;,
 3;269,247,250;,
 3;270,250,252;,
 3;271,252,254;,
 3;272,254,256;,
 3;273,256,258;,
 3;274,258,260;,
 4;275,276,277,278;,
 4;276,279,280,277;,
 4;279,281,282,280;,
 4;281,283,284,282;,
 4;283,285,286,284;,
 4;285,287,288,286;,
 4;287,289,290,288;,
 3;291,276,275;,
 3;292,279,276;,
 3;293,281,279;,
 3;294,283,281;,
 3;295,285,283;,
 3;296,287,285;,
 3;297,289,287;,
 3;298,278,277;,
 3;299,277,280;,
 3;300,280,282;,
 3;301,282,284;,
 3;302,284,286;,
 3;303,286,288;,
 3;304,288,290;,
 4;305,306,307,308;,
 4;306,309,310,307;,
 4;309,311,312,310;,
 4;311,313,314,312;,
 4;313,315,316,314;,
 4;315,317,318,316;,
 4;317,319,320,318;,
 3;321,306,305;,
 3;322,309,306;,
 3;323,311,309;,
 3;324,313,311;,
 3;325,315,313;,
 3;326,317,315;,
 3;327,319,317;,
 3;328,308,307;,
 3;329,307,310;,
 3;330,310,312;,
 3;331,312,314;,
 3;332,314,316;,
 3;333,316,318;,
 3;334,318,320;;
 
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
   0.800000;0.439200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.489600;0.272800;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.690400;0.734400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  201;
  0.000000;1.000000;0.000000;,
  0.000000;0.796379;-0.604797;,
  0.427656;0.796379;-0.427656;,
  0.604797;0.796379;0.000000;,
  0.427656;0.796379;0.427656;,
  0.000000;0.796379;0.604797;,
  -0.427656;0.796379;0.427656;,
  -0.604797;0.796380;0.000000;,
  -0.427656;0.796379;-0.427656;,
  0.000000;0.295681;-0.955287;,
  0.675490;0.295681;-0.675490;,
  0.955287;0.295681;0.000000;,
  0.675490;0.295681;0.675490;,
  0.000000;0.295681;0.955287;,
  -0.675490;0.295681;0.675490;,
  -0.955287;0.295681;0.000000;,
  -0.675490;0.295681;-0.675490;,
  0.000000;-0.294679;-0.955596;,
  0.678472;-0.303356;-0.669067;,
  0.950008;-0.312227;-0.000000;,
  0.678472;-0.303356;0.669067;,
  0.000000;-0.294679;0.955596;,
  -0.678472;-0.303356;0.669067;,
  -0.950008;-0.312227;-0.000000;,
  -0.678472;-0.303356;-0.669067;,
  0.000000;-0.689436;-0.724347;,
  0.531125;-0.684291;-0.499652;,
  0.733123;-0.680096;-0.000000;,
  0.531125;-0.684291;0.499652;,
  0.000000;-0.689436;0.724347;,
  -0.531125;-0.684291;0.499652;,
  -0.733123;-0.680096;-0.000000;,
  -0.531125;-0.684291;-0.499652;,
  0.265779;-0.964034;0.000000;,
  -0.646124;-0.763232;-0.000000;,
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
  -1.000000;0.000000;-0.000001;,
  -0.866025;0.500001;-0.000001;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.866023;-0.500004;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;0.000000;0.707107;,
  -0.612372;0.500002;0.612372;,
  0.707107;0.000000;-0.707107;,
  0.612371;-0.500004;-0.612371;,
  0.000000;0.000000;1.000000;,
  0.000000;0.500000;0.866026;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.500003;-0.866024;,
  0.707107;0.000000;0.707107;,
  0.612373;0.499999;0.612373;,
  -0.707107;0.000000;-0.707107;,
  -0.612372;-0.500001;-0.612372;,
  1.000000;0.000000;0.000000;,
  0.866025;0.500000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.866025;-0.500000;0.000000;,
  0.707107;0.000000;-0.707107;,
  0.612372;0.500002;-0.612372;,
  -0.707107;0.000000;0.707107;,
  -0.612372;-0.500001;0.612372;,
  -0.000001;0.000000;-1.000000;,
  -0.000001;0.500001;-0.866025;,
  -0.000000;0.000000;1.000000;,
  -0.000000;-0.500003;0.866024;,
  -0.707107;0.000000;-0.707107;,
  -0.612373;0.499999;-0.612373;,
  0.707107;0.000000;0.707107;,
  0.612371;-0.500004;0.612371;,
  0.866023;0.500005;0.000000;,
  0.612371;0.500005;-0.612371;,
  -0.866025;-0.500000;-0.000001;,
  -0.612372;-0.500001;0.612372;,
  -0.000000;0.500004;-0.866023;,
  0.000000;-0.499999;0.866026;,
  -0.612372;0.500002;-0.612372;,
  0.612373;-0.499998;0.612373;,
  -0.866025;0.500001;0.000000;,
  0.866026;-0.499999;0.000000;,
  -0.612372;0.500002;0.612372;,
  0.612372;-0.500001;-0.612372;,
  -0.000000;0.500004;0.866023;,
  -0.000001;-0.500000;-0.866025;,
  0.612371;0.500005;0.612371;,
  -0.612373;-0.499998;-0.612373;,
  -0.150391;0.972441;0.178158;,
  -0.086824;0.166510;-0.982210;,
  0.715817;0.231393;-0.658834;,
  0.979437;0.122033;0.160659;,
  0.505518;-0.079221;0.859171;,
  -0.349066;-0.220820;0.910709;,
  -0.940798;-0.196136;0.276461;,
  -0.824085;-0.023758;-0.565967;,
  0.150378;-0.972444;-0.178155;,
  -0.150380;0.972445;0.178148;,
  -0.150388;0.972442;0.178155;,
  -0.150388;0.972443;0.178153;,
  -0.150393;0.972440;0.178166;,
  -0.150393;0.972439;0.178170;,
  -0.150392;0.972441;0.178160;,
  -0.150399;0.972441;0.178152;,
  0.150381;-0.972444;-0.178151;,
  0.150364;-0.972446;-0.178156;,
  0.150358;-0.972447;-0.178158;,
  0.150363;-0.972446;-0.178158;,
  0.150384;-0.972443;-0.178154;,
  0.150399;-0.972441;-0.178152;,
  0.150396;-0.972441;-0.178154;,
  0.178158;0.972442;0.150389;,
  -0.982210;0.166511;0.086818;,
  -0.658831;0.231393;-0.715821;,
  0.160654;0.122034;-0.979438;,
  0.859169;-0.079219;-0.505523;,
  0.910709;-0.220819;0.349067;,
  0.276460;-0.196136;0.940798;,
  -0.565970;-0.023757;0.824084;,
  -0.178154;-0.972444;-0.150378;,
  0.178146;0.972445;0.150381;,
  0.178151;0.972444;0.150386;,
  0.178155;0.972443;0.150387;,
  0.178170;0.972439;0.150391;,
  0.178172;0.972439;0.150391;,
  0.178163;0.972440;0.150392;,
  0.178152;0.972442;0.150395;,
  -0.178151;-0.972444;-0.150381;,
  -0.178156;-0.972445;-0.150368;,
  -0.178157;-0.972446;-0.150362;,
  -0.178154;-0.972446;-0.150365;,
  -0.178151;-0.972444;-0.150383;,
  -0.178151;-0.972442;-0.150395;,
  -0.178154;-0.972442;-0.150391;,
  0.150389;0.972442;-0.178158;,
  0.086818;0.166511;0.982210;,
  -0.715820;0.231393;0.658831;,
  -0.979438;0.122034;-0.160653;,
  -0.505523;-0.079219;-0.859169;,
  0.349072;-0.220820;-0.910707;,
  0.940797;-0.196136;-0.276462;,
  0.824088;-0.023759;0.565964;,
  -0.150379;-0.972444;0.178154;,
  0.150382;0.972445;-0.178146;,
  0.150386;0.972443;-0.178151;,
  0.150387;0.972443;-0.178155;,
  0.150391;0.972439;-0.178170;,
  0.150391;0.972439;-0.178172;,
  0.150392;0.972440;-0.178163;,
  0.150395;0.972442;-0.178152;,
  -0.150381;-0.972444;0.178151;,
  -0.150368;-0.972445;0.178156;,
  -0.150362;-0.972446;0.178157;,
  -0.150365;-0.972446;0.178155;,
  -0.150385;-0.972444;0.178150;,
  -0.150399;-0.972441;0.178152;,
  -0.150393;-0.972441;0.178156;,
  -0.178158;0.972441;-0.150392;,
  0.982210;0.166510;-0.086824;,
  0.658829;0.231393;0.715822;,
  -0.160660;0.122033;0.979437;,
  -0.859169;-0.079220;0.505523;,
  -0.910709;-0.220820;-0.349066;,
  -0.276461;-0.196136;-0.940797;,
  0.565968;-0.023758;-0.824085;,
  0.178155;-0.972444;0.150378;,
  -0.178146;0.972445;-0.150382;,
  -0.178155;0.972442;-0.150388;,
  -0.178152;0.972443;-0.150391;,
  -0.178167;0.972439;-0.150395;,
  -0.178170;0.972439;-0.150393;,
  -0.178160;0.972441;-0.150392;,
  -0.178152;0.972441;-0.150399;,
  0.178151;-0.972444;0.150381;,
  0.178156;-0.972446;0.150363;,
  0.178158;-0.972447;0.150358;,
  0.178158;-0.972446;0.150363;,
  0.178154;-0.972443;0.150384;,
  0.178152;-0.972441;0.150399;,
  0.178154;-0.972441;0.150396;;
  202;
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
  3;25,26,33;,
  3;26,27,33;,
  3;27,28,33;,
  3;28,29,33;,
  3;29,30,33;,
  3;30,31,34;,
  3;31,32,34;,
  3;32,25,33;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,60,66,65;,
  4;61,61,61,61;,
  4;93,62,67,94;,
  4;62,63,68,67;,
  4;64,64,64,64;,
  4;95,59,65,96;,
  4;65,66,70,69;,
  4;61,61,61,61;,
  4;94,67,71,97;,
  4;67,68,72,71;,
  4;64,64,64,64;,
  4;96,65,69,98;,
  4;69,70,74,73;,
  4;61,61,61,61;,
  4;97,71,75,99;,
  4;71,72,76,75;,
  4;64,64,64,64;,
  4;98,69,73,100;,
  4;73,74,78,77;,
  4;61,61,61,61;,
  4;99,75,79,101;,
  4;75,76,80,79;,
  4;64,64,64,64;,
  4;100,73,77,102;,
  4;77,78,82,81;,
  4;61,61,61,61;,
  4;101,79,83,103;,
  4;79,80,84,83;,
  4;64,64,64,64;,
  4;102,77,81,104;,
  4;81,82,86,85;,
  4;61,61,61,61;,
  4;103,83,87,105;,
  4;83,84,88,87;,
  4;64,64,64,64;,
  4;104,81,85,106;,
  4;85,86,90,89;,
  4;61,61,61,61;,
  4;105,87,91,107;,
  4;87,88,92,91;,
  4;64,64,64,64;,
  4;106,85,89,108;,
  4;89,90,60,59;,
  4;61,61,61,61;,
  4;107,91,62,93;,
  4;91,92,63,62;,
  4;64,64,64,64;,
  4;108,89,59,95;,
  4;110,111,111,110;,
  4;111,112,112,111;,
  4;112,113,113,112;,
  4;113,114,114,113;,
  4;114,115,115,114;,
  4;115,116,116,115;,
  4;116,110,110,116;,
  3;109,118,119;,
  3;109,120,118;,
  3;109,121,120;,
  3;109,122,121;,
  3;109,123,122;,
  3;109,124,123;,
  3;109,119,124;,
  3;117,125,126;,
  3;117,126,127;,
  3;117,127,128;,
  3;117,128,129;,
  3;117,129,130;,
  3;117,130,131;,
  3;117,131,125;,
  4;133,134,134,133;,
  4;134,135,135,134;,
  4;135,136,136,135;,
  4;136,137,137,136;,
  4;137,138,138,137;,
  4;138,139,139,138;,
  4;139,133,133,139;,
  3;132,141,142;,
  3;132,143,141;,
  3;132,144,143;,
  3;132,145,144;,
  3;132,146,145;,
  3;132,147,146;,
  3;132,142,147;,
  3;140,148,149;,
  3;140,149,150;,
  3;140,150,151;,
  3;140,151,152;,
  3;140,152,153;,
  3;140,153,154;,
  3;140,154,148;,
  4;156,157,157,156;,
  4;157,158,158,157;,
  4;158,159,159,158;,
  4;159,160,160,159;,
  4;160,161,161,160;,
  4;161,162,162,161;,
  4;162,156,156,162;,
  3;155,164,165;,
  3;155,166,164;,
  3;155,167,166;,
  3;155,168,167;,
  3;155,169,168;,
  3;155,170,169;,
  3;155,165,170;,
  3;163,171,172;,
  3;163,172,173;,
  3;163,173,174;,
  3;163,174,175;,
  3;163,175,176;,
  3;163,176,177;,
  3;163,177,171;,
  4;179,180,180,179;,
  4;180,181,181,180;,
  4;181,182,182,181;,
  4;182,183,183,182;,
  4;183,184,184,183;,
  4;184,185,185,184;,
  4;185,179,179,185;,
  3;178,187,188;,
  3;178,189,187;,
  3;178,190,189;,
  3;178,191,190;,
  3;178,192,191;,
  3;178,193,192;,
  3;178,188,193;,
  3;186,194,195;,
  3;186,195,196;,
  3;186,196,197;,
  3;186,197,198;,
  3;186,198,199;,
  3;186,199,200;,
  3;186,200,194;;
 }
 MeshTextureCoords {
  335;
  0.062500;0.000000;,
  0.125000;0.200000;,
  0.000000;0.200000;,
  0.187500;0.000000;,
  0.250000;0.200000;,
  0.312500;0.000000;,
  0.375000;0.200000;,
  0.437500;0.000000;,
  0.500000;0.200000;,
  0.562500;0.000000;,
  0.625000;0.200000;,
  0.687500;0.000000;,
  0.750000;0.200000;,
  0.812500;0.000000;,
  0.875000;0.200000;,
  0.937500;0.000000;,
  1.000000;0.200000;,
  0.125000;0.400000;,
  0.000000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.125000;0.600000;,
  0.000000;0.600000;,
  0.250000;0.600000;,
  0.375000;0.600000;,
  0.500000;0.600000;,
  0.625000;0.600000;,
  0.750000;0.600000;,
  0.875000;0.600000;,
  1.000000;0.600000;,
  0.125000;0.800000;,
  0.000000;0.800000;,
  0.250000;0.800000;,
  0.375000;0.800000;,
  0.500000;0.800000;,
  0.625000;0.800000;,
  0.750000;0.800000;,
  0.875000;0.800000;,
  1.000000;0.800000;,
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
  0.000000;0.166670;,
  0.125000;0.166670;,
  0.125000;0.000000;,
  0.000000;0.333330;,
  0.125000;0.333330;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.666670;,
  0.125000;0.666670;,
  0.000000;0.833330;,
  0.125000;0.833330;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.166670;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.250000;0.500000;,
  0.250000;0.666670;,
  0.250000;0.833330;,
  0.250000;1.000000;,
  0.375000;0.166670;,
  0.375000;0.000000;,
  0.375000;0.333330;,
  0.375000;0.500000;,
  0.375000;0.666670;,
  0.375000;0.833330;,
  0.375000;1.000000;,
  0.500000;0.166670;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.500000;0.833330;,
  0.500000;1.000000;,
  0.625000;0.166670;,
  0.625000;0.000000;,
  0.625000;0.333330;,
  0.625000;0.500000;,
  0.625000;0.666670;,
  0.625000;0.833330;,
  0.625000;1.000000;,
  0.750000;0.166670;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  0.750000;0.500000;,
  0.750000;0.666670;,
  0.750000;0.833330;,
  0.750000;1.000000;,
  0.875000;0.166670;,
  0.875000;0.000000;,
  0.875000;0.333330;,
  0.875000;0.500000;,
  0.875000;0.666670;,
  0.875000;0.833330;,
  0.875000;1.000000;,
  1.000000;0.166670;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.833330;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.142860;0.000000;,
  0.142860;1.000000;,
  0.000000;1.000000;,
  0.285710;0.000000;,
  0.285710;1.000000;,
  0.428570;0.000000;,
  0.428570;1.000000;,
  0.571430;0.000000;,
  0.571430;1.000000;,
  0.714290;0.000000;,
  0.714290;1.000000;,
  0.857140;0.000000;,
  0.857140;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.071430;0.000000;,
  0.214290;0.000000;,
  0.357140;0.000000;,
  0.500000;0.000000;,
  0.642860;0.000000;,
  0.785710;0.000000;,
  0.928570;0.000000;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;,
  0.000000;0.000000;,
  0.142860;0.000000;,
  0.142860;1.000000;,
  0.000000;1.000000;,
  0.285710;0.000000;,
  0.285710;1.000000;,
  0.428570;0.000000;,
  0.428570;1.000000;,
  0.571430;0.000000;,
  0.571430;1.000000;,
  0.714290;0.000000;,
  0.714290;1.000000;,
  0.857140;0.000000;,
  0.857140;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.071430;0.000000;,
  0.214290;0.000000;,
  0.357140;0.000000;,
  0.500000;0.000000;,
  0.642860;0.000000;,
  0.785710;0.000000;,
  0.928570;0.000000;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;,
  0.000000;0.000000;,
  0.142860;0.000000;,
  0.142860;1.000000;,
  0.000000;1.000000;,
  0.285710;0.000000;,
  0.285710;1.000000;,
  0.428570;0.000000;,
  0.428570;1.000000;,
  0.571430;0.000000;,
  0.571430;1.000000;,
  0.714290;0.000000;,
  0.714290;1.000000;,
  0.857140;0.000000;,
  0.857140;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.071430;0.000000;,
  0.214290;0.000000;,
  0.357140;0.000000;,
  0.500000;0.000000;,
  0.642860;0.000000;,
  0.785710;0.000000;,
  0.928570;0.000000;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;,
  0.000000;0.000000;,
  0.142860;0.000000;,
  0.142860;1.000000;,
  0.000000;1.000000;,
  0.285710;0.000000;,
  0.285710;1.000000;,
  0.428570;0.000000;,
  0.428570;1.000000;,
  0.571430;0.000000;,
  0.571430;1.000000;,
  0.714290;0.000000;,
  0.714290;1.000000;,
  0.857140;0.000000;,
  0.857140;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.071430;0.000000;,
  0.214290;0.000000;,
  0.357140;0.000000;,
  0.500000;0.000000;,
  0.642860;0.000000;,
  0.785710;0.000000;,
  0.928570;0.000000;,
  0.071430;1.000000;,
  0.214290;1.000000;,
  0.357140;1.000000;,
  0.500000;1.000000;,
  0.642860;1.000000;,
  0.785710;1.000000;,
  0.928570;1.000000;;
 }
}
