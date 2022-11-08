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
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CScore;
class CUIString;
class CBoxHitbox;

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
		STATE_JUMP,
		STATE_PUNCH,
		STATE_DAMAGE,
		STATE_MAX
	};

	enum PlayerColor
	{
		PLAYER_RED = 0,
		PLAYER_GREEN,
		PLAYER_BLUE,
		PLAYER_YELLOW,
		PLAYER_MAGENTA,
		PLAYER_CYAN,
		PLAYER_BLACK,
		PLAYER_WHITE,

		PLAYER_COLOR_MAX
	};

	CPlayer();							//�R���X�g���N�^
	~CPlayer() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ菈��
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override { return Vec2Null; }		//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override { return m_pos; }			//�ʒu�̎擾����

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; }	//�ړI�̊p�x�̎擾����

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);	//��������
	static D3DXCOLOR* GetPlayerColors(void);

	void PlayerController(int nCntPlayer);
	void SetPlayerIdx(int nCntPlayer);
	void SetFriction(const float fFriction);

	bool GetGoal() { return m_bGoal; }

	bool GetRotCmp();

	void MoveWinner();

	void SetWinner(bool bWinner);

	void WinnerAnim();
	void LoserAnim();

	void PlayerRespawn();
private:
	void GoalMove();

	static D3DXCOLOR m_playerColor[PLAYER_COLOR_MAX];
	static const float m_MaxWalkingSpeed;
	static const float m_AccelerationCoeff;

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_move;									//���x
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR3 m_DestRot;								//�ړI�̊p�x
	D3DXMATRIX  m_mtxWorld;								//���[���h�}�g���b�N�X
	bool		m_bJump;								//�W�����v���Ă��邩�ǂ���
	int			m_nInvincibilityCnt;					//���G��Ԃ̃J�E���^�[
	int			m_nCntAttack;
	float		m_fFrictionCoeff;						//���C�W��

	float m_fAngle;
	bool m_bGoal;
	bool m_bMove;
	bool m_bWinner;
	bool m_bPos;
	bool m_bRot;
	bool m_bHit;
	bool m_bPunch;
	bool m_bAttacking;

	int m_nScore[PLAYER_MAX];

	D3DXVECTOR3 m_TargetPos;

	D3DXVECTOR3 GoalPos;

	CModelPart* m_pModel[PARTS_MAX];					//���f���ւ̃|�C���^
	CAnimator* m_pAnimator;

	STATE m_State;
	CCylinderHitbox* m_pHitbox;							//�q�b�g�{�b�N�X
	CBoxHitbox*       m_pAttackHitbox;					//�U���q�b�g�{�b�N�X
	CScore* m_pScore;
	CUIString* m_pScoreUI;

	int m_nIdxPlayer;
	int m_nFrame;
	//CModel* m_pModel;									//���f��
};

#endif