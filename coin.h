//=============================================================================
//
// coin.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _COIN_H
#define _COIN_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;

class CCoin : public CModel
{
public:

	//コインの種類
	enum COIN_TYPE
	{
		COIN_0 = 0,
		COIN_1,
		COIN_2,
		COIN_3,
		COIN_MAX
	};

	CCoin();									//コンストラクタ
	~CCoin() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理


	static CCoin* Create(const D3DXVECTOR3 pos, const COIN_TYPE type);		//生成処理

private:

	static const D3DXVECTOR3 m_hitboxSize[COIN_MAX];		//ヒットボックスの大きさ

	CBoxHitbox* m_pHitbox;			//ヒットボックスへのポインタ

};





#endif