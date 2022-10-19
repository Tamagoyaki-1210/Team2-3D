//============================================================================
//
//
// �J�����̏���
// Author:�J�{�N��
//
//============================================================================
#ifndef _CAMERA_H_						//���̃}�N����`������ĂȂ�������
#define _CAMERA_H_						//2�A�C���N���[�h�h�~�̃}�N����`

#include <d3dx9.h>

//****************************************************************************
//�}�N����`
//****************************************************************************
#define CAMERA_NEAR				(10)	//�J�����̃j�A�[
#define CAMERA_FAR				(3000)	//�J�����̃t�@�[
#define CAMERA_SPEAD			(2)		//�J�����̈ړ����x

class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init();
	void Uninit();
	void Update();
	void Input();
	void SetCamera(LPDIRECT3DDEVICE9 device);
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXVECTOR3 GetRotDest() { return m_rotDest; }
private:
	//****************************************************************************
	//�\���̒�`
	//****************************************************************************
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_vecU;			//������x�N�g��
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_posVDest;		//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;		//�ړI�̒����_
	D3DXVECTOR3 m_rotDest;		//�ړI�̕���
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	float m_fDistance;			//���_���璍���_�̋���
	bool m_bFollowUse;			//�Ǐ]�@�\����
};
#endif #pragma once
