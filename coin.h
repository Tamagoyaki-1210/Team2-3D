//=============================================================================
//
// coin.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _COIN_H
#define _COIN_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;

class CCoin : public CModel
{
public:

	//�R�C���̎��
	enum COIN_TYPE
	{
		COIN_0 = 0,
		COIN_1,
		COIN_2,
		COIN_3,
		COIN_MAX
	};

	CCoin();									//�R���X�g���N�^
	~CCoin() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����


	static CCoin* Create(const D3DXVECTOR3 pos, const COIN_TYPE type);		//��������

private:

	static const D3DXVECTOR3 m_hitboxSize[COIN_MAX];		//�q�b�g�{�b�N�X�̑傫��

	CBoxHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^

};





#endif