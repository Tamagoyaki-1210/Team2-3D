//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _LAVA_FLOOR_H
#define _LAVA_FLOOR_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object3D.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;

class CLavaFloor : public CObject_3D

{
public:
	CLavaFloor();										//コンストラクタ
	~CLavaFloor();										//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
														
	static CLavaFloor* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);	//生成処理

private:

	CBoxHitbox* m_pHitbox;								//ヒットボックス
};





#endif