//=========================================
// 
// Title : ���C���ݒ�.h
// Author: Tanimoto Kosuke
// 
//=========================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>
#include "sound.h"

//---------------------------
//�}�N���֐�(�I�u�W�F�N�g2D)
//---------------------------
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//---------------------------
//�I�u�W�F�N�g2D�\����
//---------------------------
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//---------------------------
//�I�u�W�F�N�g3D�\����
//---------------------------
 struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`���W��
};

// �X�N���[���̕�
const int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
const int SCREEN_HEIGHT = 720;

// �X�N���[���̕�
const float F_SCREEN_WIDTH = 1280.0f;
// �X�N���[���̍���
const float F_SCREEN_HEIGHT = 720.0f;
#endif