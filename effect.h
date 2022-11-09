//=============================================================================
//
// effect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _EFFECT_H
#define _EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "billboard.h"


class CEffect : public CBillboard
{
public:
	CEffect();
	~CEffect() override;

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rotSpeed, const D3DXVECTOR3 move
		, const D3DXCOLOR col, const D3DXCOLOR deltaCol, const float fSize, const float fdeltaSize, const int nLife);

private:

	D3DXVECTOR3 m_rotSpeed;
	D3DXVECTOR3 m_move;
	D3DXCOLOR   m_deltaCol;
	float		m_fDeltaSize;
	int			m_nLife;


};



#endif