//=============================================================================
//
// goal.h
// Author : Kajita Hiromu
//
//=============================================================================

#ifndef _GOAL_H_
#define _GOAL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================

class CGoal : public CObject
{
public:
	CGoal();										//�R���X�g���N�^
	~CGoal() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;		//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����

	static void SetGoal(bool bGoal, int nWinnerIdx);

	static CGoal* Create();	//��������

private:
	LPDIRECT3DTEXTURE9 m_pTexture;					//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_size;								//�T�C�Y
	D3DXVECTOR3 m_rot;								//����
	D3DXMATRIX  m_mtxWorld;							//���[���h�}�g���b�N�X

	static int m_nWinnerIdx;
	static bool m_bGoal;									//�S�[���������ǂ���
};

#endif