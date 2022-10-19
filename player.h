//============================================================================
//
// �v���C���[�̏���
// Author:�J�{�N��
//
//============================================================================
#ifndef _PLAYER_H_		//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_		//2�A�C���N���[�h�h�~�̃}�N����`

#include "objectX.h"

//****************************************************************************
//�}�N����`
//****************************************************************************
#define IMAGE_PLAYER		(1)		//�v���C���[�̉摜��
#define PLAYER_WIDTH		(50)	//�v���C���[�̉���
#define PLAYER_HEIGHT		(70)	//�v���C���[�̏c��
#define MAX_PLAYER_LIFE		(30)	//�v���C���[�̍ő�̗�
#define PLAYER_LIFE			(5)		//�v���C���[�̗̑�
#define PLAYER_ATTACK		(2)		//�v���C���[�̍U�����莝������
#define PLAYER_SPEAD		(3)		//�v���C���[�̈ړ����x�{��
#define MAX_PLAYER_PARTS	(3)		//�v���C���[�̃p�[�c��

//---------------------------
//�O���錾
//---------------------------
class CShadow;
class CModel;

//---------------------------
//�N���X
//---------------------------
class CPlayer : CObjectX
{
public:
	//�v���C���[�̃��[�V�������
	enum Player_Motion
	{
		MOTION_NUTRAL = 0,	//�j���[�g�������[�V����
		MOTION_WARK,		//�������[�V����
		MOTION_JUMP,		//�W�����v���[�V����
		MOTION_LANDING,		//���n���[�V����
		MOTION_ATTACK,		//�U�����[�V����
		MOTION_DAMEGE,		//��e���[�V����
		MOTION_MAX
	};

	CPlayer();
	~CPlayer() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Input();
	void Motion();
	void Collision();
	void RotNormalize();

	static CPlayer *Create(D3DXVECTOR3 pos, float ParentY);
private:
	//****************************************************************************
	//�\���̒�`
	//****************************************************************************
	//typedef struct
	//{
	//	LPD3DXMESH pMesh;
	//	LPD3DXBUFFER pBuffMat;
	//	DWORD nNumMat;
	//	LPDIRECT3DTEXTURE9 g_pTexture[IMAGE_PLAYER];
	//	D3DXMATRIX Worldmtx;	//���[���h�}�g���b�N�X
	//	D3DXVECTOR3 pos;		//���_���W
	//	D3DXVECTOR3 rot;		//����
	//	float fFrame;			//�t���[����
	//	int nIdxModelParent;	//�e���f���̃C���f�b�N�X
	//}PLAYER_PARTS;

	D3DXVECTOR3 m_posOld;		//���_���W�O��ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rotDest;		//�����ړI�l
	int m_nLife;				//�̗�
	int m_nPower;				//��
	float m_fFlame;				//�t���[����
	float m_fAttack;			//�U���ҋ@����
	bool m_bDamege;				//��e����
	bool m_bLoop;				//���[�v����
	bool m_bGround;				//�ڒn����̏ꍇ
	Player_Motion m_motion;		//���[�V�������
	//PLAYER_PARTS aParts[MAX_PLAYER_PARTS];
	CModel *m_pModel[MAX_PLAYER_PARTS];
	CShadow *m_pShadow;
};
#endif// !_PLAYER_H_

