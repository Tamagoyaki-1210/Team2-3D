//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModel;
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CScore;
class CUIString;

class CPlayer : public CObject
{
public:

	enum Parts
	{
		BODY = 0,
		HEAD,
		LEFT_ARM,
		LEFT_HAND,
		RIGHT_ARM,
		RIGHT_HAND,
		LEFT_LEG,
		LEFT_FOOT,
		RIGHT_LEG,
		RIGHT_FOOT,
		PARTS_MAX
	};

	enum STATE
	{
		STATE_NEUTRAL = 0,
		STATE_RUNNING,
		STATE_MAX
	};

	CPlayer();							//�R���X�g���N�^
	~CPlayer() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; };	//�ړI�̊p�x�̎擾����

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);		//��������

	void PlayerController(int nCntPlayer);
	void SetPlayerIdx(int nCntPlayer);

private:

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_move;									//���x
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR3 m_DestRot;								//�ړI�̊p�x
	D3DXMATRIX  m_mtxWorld;								//���[���h�}�g���b�N�X

	CModelPart* m_pModel[PARTS_MAX];					//���f���ւ̃|�C���^
	CAnimator* m_pAnimator;

	STATE m_State;
	CCylinderHitbox* m_pHitbox;
	CScore* m_pScore;
	CUIString* m_pScoreUI;

	int m_nIdxPlayer;
	//CModel* m_pModel;									//���f��
};

#endif