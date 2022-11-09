//=============================================================================
//
// AnimateUI.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ANIMATE_UI_H_
#define _ANIMATE_UI_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CAnimateUI : public CObject_2D
{
public:

	struct UIAnimation
	{
		D3DXVECTOR2 deltaSize;				
		int			nChangeTime;			
	};

	CAnimateUI();																//コンストラクタ
	~CAnimateUI() override;														//デストラクタ
																				
	HRESULT Init(void) override;												//初期化処理
	void Uninit(void) override;													//終了処理
	void Update(void) override;													//更新処理

	void AnimateColor(const bool bAnim);
																				
	static CAnimateUI* Create(CObject::TextType texture, const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, UIAnimation animInfo);		//生成処理


private:

	static const D3DXCOLOR targetCol[6];

	UIAnimation m_AnimInfo;
	int			m_nCntAnim;
	int			m_ntargetCol;
	D3DXCOLOR	m_deltaCol;
	bool		m_bAnimateColor;

};







#endif