//============================================================================
//
// プレイヤーの処理
// Author:谷本康輔
//
//============================================================================
#ifndef _PLAYER_H_		//このマクロ定義がされてなかったら
#define _PLAYER_H_		//2連インクルード防止のマクロ定義

#include "object.h"

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
#define MAX_PLAYER_PARTS	(4)		//プレイヤーのパーツ数
#define MAX_PLAYER_KEY		(4)		//プレイヤーのキー数

//---------------------------
//前方宣言
//---------------------------
class CShadow;
class CModel;

//---------------------------
//クラス
//---------------------------
class CPlayer : CObject
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

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }

	static CPlayer *Create(D3DXVECTOR3 pos);
private:
	//キー要素
	struct KEY {
		float fPosX;
		float fPosY;
		float fPosZ;

		float fRotX;
		float fRotY;
		float fRotZ;
	};

	//キー情報
	struct KEY_SET {
		int m_nFrame;
		KEY aKey[MAX_PLAYER_PARTS];
	};


	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//角度
	D3DXMATRIX m_worldmtx;				//ワールドマトリックス
	float m_fWidth;						//長さ横
	float m_fHeight;					//長さ縦
	float m_fLength;					//長さ(スクウェアルート)
	float m_fAngle;						//角度(アークタンジェント)

	D3DXVECTOR3 m_posOld;		//頂点座標前回位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rotDest;		//向き目的値
	int m_nLife;				//体力
	int m_nPower;				//力
	int m_nMotionFrame;			//フレーム数
	int m_nMotionKey;			//キー数
	int m_nMaxKey;				//最大キー数
	float m_fAttack;			//攻撃待機時間
	bool m_bDamege;				//被弾判定
	bool m_bLoop;				//ループ判定
	bool m_bGround;				//接地判定の場合
	Player_Motion m_motion;		//モーション種類
	CModel *m_apModel[MAX_PLAYER_PARTS];
	CShadow *m_pShadow;
	KEY_SET m_aKeySet[MAX_PLAYER_KEY];
};
#endif// !_PLAYER_H_

