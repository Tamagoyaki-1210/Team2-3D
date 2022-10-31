//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModel;
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CScore;
class CUIString;

class CPlayer : public CObject
{
public:

	enum Parts
	{
		BODY = 0,
		HEAD,
		LEFT_ARM,
		LEFT_HAND,
		RIGHT_ARM,
		RIGHT_HAND,
		LEFT_LEG,
		LEFT_FOOT,
		RIGHT_LEG,
		RIGHT_FOOT,
		PARTS_MAX
	};

	enum STATE
	{
		STATE_NEUTRAL = 0,
		STATE_RUNNING,
		STATE_MAX
	};

	CPlayer();							//コンストラクタ
	~CPlayer() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; };	//目的の角度の取得処理

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);		//生成処理

	void PlayerController(int nCntPlayer);
	void SetPlayerIdx(int nCntPlayer);

private:

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_move;									//速度
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR3 m_DestRot;								//目的の角度
	D3DXMATRIX  m_mtxWorld;								//ワールドマトリックス

	CModelPart* m_pModel[PARTS_MAX];					//モデルへのポインタ
	CAnimator* m_pAnimator;

	STATE m_State;
	CCylinderHitbox* m_pHitbox;
	CScore* m_pScore;
	CUIString* m_pScoreUI;

	int m_nIdxPlayer;
	//CModel* m_pModel;									//モデル
};

#endif