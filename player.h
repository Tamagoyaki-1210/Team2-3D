//============================================================================
//
// �v���C���[�̏���
// Author:�J�{�N��
//
//============================================================================
#ifndef _PLAYER_H_		//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_		//2�A�C���N���[�h�h�~�̃}�N����`

#include "object.h"

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
#define MAX_PLAYER_PARTS	(4)		//�v���C���[�̃p�[�c��
#define MAX_PLAYER_KEY		(4)		//�v���C���[�̃L�[��

//---------------------------
//�O���錾
//---------------------------
class CShadow;
class CModel;

//---------------------------
//�N���X
//---------------------------
class CPlayer : CObject
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

	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetWorldMtx(D3DXMATRIX worldmtx) { m_worldmtx = worldmtx; }
	virtual void SetWidth(float fWidth) { m_fWidth = fWidth; }
	virtual void SetHeight(float fHeight) { m_fHeight = fHeight; }

	const D3DXVECTOR3& GetPos() const { return m_pos; }
	const D3DXVECTOR3& GetRot() const { return m_rot; }
	const D3DXMATRIX& GetWorldMtx() const { return m_worldmtx; }
	const float GetWidth() const { return m_fWidth; }
	const float GetHeight() const { return m_fHeight; }
	const float GetLength() const { return m_fLength; }

	static CPlayer *Create(D3DXVECTOR3 pos);
private:
	//�L�[�v�f
	struct KEY {
		float fPosX;
		float fPosY;
		float fPosZ;

		float fRotX;
		float fRotY;
		float fRotZ;
	};

	//�L�[���
	struct KEY_SET {
		int m_nFrame;
		KEY aKey[MAX_PLAYER_PARTS];
	};


	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//�p�x
	D3DXMATRIX m_worldmtx;				//���[���h�}�g���b�N�X
	float m_fWidth;						//������
	float m_fHeight;					//�����c
	float m_fLength;					//����(�X�N�E�F�A���[�g)
	float m_fAngle;						//�p�x(�A�[�N�^���W�F���g)

	D3DXVECTOR3 m_posOld;		//���_���W�O��ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rotDest;		//�����ړI�l
	int m_nLife;				//�̗�
	int m_nPower;				//��
	int m_nMotionFrame;			//�t���[����
	int m_nMotionKey;			//�L�[��
	int m_nMaxKey;				//�ő�L�[��
	float m_fAttack;			//�U���ҋ@����
	bool m_bDamege;				//��e����
	bool m_bLoop;				//���[�v����
	bool m_bGround;				//�ڒn����̏ꍇ
	Player_Motion m_motion;		//���[�V�������
	CModel *m_apModel[MAX_PLAYER_PARTS];
	CShadow *m_pShadow;
	KEY_SET m_aKeySet[MAX_PLAYER_KEY];
};
#endif// !_PLAYER_H_

