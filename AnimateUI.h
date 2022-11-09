//=============================================================================
//
// AnimateUI.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ANIMATE_UI_H_
#define _ANIMATE_UI_H_

//=============================================================================
//�C���N���[�h�t�@�C��
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

	CAnimateUI();																//�R���X�g���N�^
	~CAnimateUI() override;														//�f�X�g���N�^
																				
	HRESULT Init(void) override;												//����������
	void Uninit(void) override;													//�I������
	void Update(void) override;													//�X�V����

	void AnimateColor(const bool bAnim);
																				
	static CAnimateUI* Create(CObject::TextType texture, const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, UIAnimation animInfo);		//��������


private:

	static const D3DXCOLOR targetCol[6];

	UIAnimation m_AnimInfo;
	int			m_nCntAnim;
	int			m_ntargetCol;
	D3DXCOLOR	m_deltaCol;
	bool		m_bAnimateColor;

};







#endif