//============================================================================
//
// プレイヤーの処理
// Author:谷本康輔
//
//============================================================================
#ifndef _PLAYER_H_		//このマクロ定義がされてなかったら
#define _PLAYER_H_		//2連インクルード防止のマクロ定義

#include "objectX.h"

//****************************************************************************
//マクロ定義
//****************************************************************************
#define IMAGE_PLAYER		(1)		//プレイヤーの画像数
#define PLAYER_WIDTH		(50)	//プレイヤーの横幅
#define PLAYER_HEIGHT		(70)	//プレイヤーの縦幅
#define MAX_PLAYER_LIFE		(30)	//プレイヤーの最大体力
#define PLAYER_LIFE			(5)		//プレイヤーの体力
#define PLAYER_ATTACK		(2)		//プレイヤーの攻撃判定持続時間
#define PLAYER_SPEAD		(3)		//プレイヤーの移動速度倍率
#define MAX_PLAYER_PARTS	(3)		//プレイヤーのパーツ数

//---------------------------
//前方宣言
//---------------------------
class CShadow;
class CModel;

//---------------------------
//クラス
//---------------------------
class CPlayer : CObjectX
{
public:
	//プレイヤーのモーション種類
	enum Player_Motion
	{
		MOTION_NUTRAL = 0,	//ニュートラルモーション
		MOTION_WARK,		//歩きモーション
		MOTION_JUMP,		//ジャンプモーション
		MOTION_LANDING,		//着地モーション
		MOTION_ATTACK,		//攻撃モーション
		MOTION_DAMEGE,		//被弾モーション
		MOTION_MAX
	};

	CPlayer();
	~CPlayer() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Input();
	void Motion();
	void Collision();
	void RotNormalize();

	static CPlayer *Create(D3DXVECTOR3 pos, float ParentY);
private:
	//****************************************************************************
	//構造体定義
	//****************************************************************************
	//typedef struct
	//{
	//	LPD3DXMESH pMesh;
	//	LPD3DXBUFFER pBuffMat;
	//	DWORD nNumMat;
	//	LPDIRECT3DTEXTURE9 g_pTexture[IMAGE_PLAYER];
	//	D3DXMATRIX Worldmtx;	//ワールドマトリックス
	//	D3DXVECTOR3 pos;		//頂点座標
	//	D3DXVECTOR3 rot;		//向き
	//	float fFrame;			//フレーム数
	//	int nIdxModelParent;	//親モデルのインデックス
	//}PLAYER_PARTS;

	D3DXVECTOR3 m_posOld;		//頂点座標前回位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rotDest;		//向き目的値
	int m_nLife;				//体力
	int m_nPower;				//力
	float m_fFlame;				//フレーム数
	float m_fAttack;			//攻撃待機時間
	bool m_bDamege;				//被弾判定
	bool m_bLoop;				//ループ判定
	bool m_bGround;				//接地判定の場合
	Player_Motion m_motion;		//モーション種類
	//PLAYER_PARTS aParts[MAX_PLAYER_PARTS];
	CModel *m_pModel[MAX_PLAYER_PARTS];
	CShadow *m_pShadow;
};
#endif// !_PLAYER_H_

