//=============================================================================
//
// �e
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "Object3D.h"

//---------------------------
//�}�N���֐�
//---------------------------
#define MAX_SHADOW				(1)		//�e�̍ő吔
#define SHADOW_WIDTH			(10)	//�e�摜�̉���
#define SHADOW_HEIGHT			(10)	//�e�摜�̏c��

//---------------------------
//�N���X
//---------------------------
class CShadow : public CObject3D
{
public:
	CShadow();
	~CShadow() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetShadow(D3DXVECTOR3 pos);

	static CShadow *Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXMATRIX m_worldmtx;//���[���h�}�g���b�N�X
	float m_fWidth;			//������
	float m_fHeight;		//�����c
};

#endif // !_SHADOW_H_