//=============================================================================
//
// boundPole.h
// Author : KAJITA HIROMU
//
//=============================================================================
#ifndef _BOUNDPOLE_H
#define _BOUNDPOLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CBoundPole : public CModel
{
public:

	CBoundPole();											//�R���X�g���N�^
	~CBoundPole() override;									//�f�X�g���N�^

	HRESULT Init(void) override;							//����������
	void Uninit(void) override;								//�I������
	void Update(void) override;								//�X�V����
	void Draw(void) override;								//�`�揈��

	static CBoundPole* Create(const D3DXVECTOR3 pos);		//��������

private:

	CCylinderHitbox* m_pHitbox;
};


#endif
#pragma once

