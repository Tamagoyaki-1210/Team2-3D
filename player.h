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

class CPlayer : public CObject
{
public:

	enum Parts
	{
		BODY = 0,
		LEFT_WING,
		RIGHT_WING,
		LEFT_WING_SMALL,
		RIGHT_WING_SMALL,
		PARTS_MAX
	};


	CPlayer();											//コンストラクタ
	~CPlayer() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; };	//目的の角度の取得処理

	static CPlayer* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_move;									//速度
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR3 m_DestRot;								//目的の角度
	D3DXMATRIX  m_mtxWorld;								//ワールドマトリックス

	CModelPart* m_pModel[PARTS_MAX];					//モデルへのポインタ
	CAnimator* m_pAnimator;
	//CModel* m_pModel;									//モデル
};

#endif