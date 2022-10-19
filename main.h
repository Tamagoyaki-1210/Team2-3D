//=========================================
// 
// Title : メイン設定.h
// Author: Tanimoto Kosuke
// 
//=========================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <d3dx9.h>
#include "sound.h"

//---------------------------
//マクロ関数(オブジェクト2D)
//---------------------------
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//---------------------------
//オブジェクト2D構造体
//---------------------------
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//---------------------------
//オブジェクト3D構造体
//---------------------------
 struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ標準
};

// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;

// スクリーンの幅
const float F_SCREEN_WIDTH = 1280.0f;
// スクリーンの高さ
const float F_SCREEN_HEIGHT = 720.0f;
#endif