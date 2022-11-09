//=============================================================================
//
// effect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _EFFECT_H
#define _EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"


class CEffect : public CBillboard
{
public:
	CEffect();
	~CEffect() override;

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

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