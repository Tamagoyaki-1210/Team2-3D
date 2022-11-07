//=============================================================================
//
// boundPole.h
// Author : KAJITA HIROMU
//
//=============================================================================
#ifndef _BOUNDPOLE_H
#define _BOUNDPOLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCylinderHitbox;

class CBoundPole : public CModel
{
public:

	CBoundPole();											//コンストラクタ
	~CBoundPole() override;									//デストラクタ

	HRESULT Init(void) override;							//初期化処理
	void Uninit(void) override;								//終了処理
	void Update(void) override;								//更新処理
	void Draw(void) override;								//描画処理

	static CBoundPole* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	CCylinderHitbox* m_pHitbox;
};


#endif
#pragma once

