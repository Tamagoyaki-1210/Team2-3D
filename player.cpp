//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "model.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"
#include "meshfield.h"
#include "modelPart.h"
#include "animator.h"
#include "CylinderHitbox.h"
#include "score.h"
#include "UIString.h"
#include "gamerace.h"
#include "stage.h"
#include "rendering.h"
#include "goal.h"
#include "coin.h"
#include "playerModel.h"
#include "message.h"
#include "BoxHitbox.h"

int CPlayer::m_nRanking;
const float CPlayer::m_MaxWalkingSpeed = 7.0f;
const float CPlayer::m_AccelerationCoeff = 2.0f;
D3DXCOLOR CPlayer::m_playerColor[PLAYER_COLOR_MAX]
{

	{ 1.0f, 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f }
};

//�R���X�g���N�^
CPlayer::CPlayer() : CObject::CObject(1)
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;					//���x�̏���������		
	m_DestRot = Vec3Null;				//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;				//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;				//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;					//�X�R�A�ւ̃|�C���^
	m_State = (STATE)0;					//�A�j���[�V�������
	m_pScoreUI = nullptr;				//�X�R�A��UI�ւ̃|�C���^
	m_bJump = false;					//�W�����v���Ă��邩�ǂ���
	m_nInvincibilityCnt = 0;			//���G��Ԃ̃J�E���^�[
	m_pAttackHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bAttacking = false;
	m_nCntAttack = 0;
	m_fFrictionCoeff = 0.0f;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_move = Vec3Null;				//���x�̏���������
	m_DestRot = Vec3Null;			//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;
	m_pHitbox = nullptr;
	m_pScore = nullptr;
	m_State = STATE_NEUTRAL;
	m_pScoreUI = nullptr;
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_bGoal = false;
	m_bMove = false;
	m_bWinner = false;
	m_bPos = false;
	m_bRot = false;
	m_pAnimator = nullptr;			//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;			//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;				//�X�R�A�ւ̃|�C���^
	m_State = STATE_NEUTRAL;		//�A�j���[�V�������
	m_pScoreUI = nullptr;			//�X�R�A��UI�ւ̃|�C���^
	m_bJump = false;				//�W�����v���Ă��邩�ǂ���
	m_nInvincibilityCnt = 0;		//���G��Ԃ̃J�E���^�[
	m_nFrame = 0;
	m_pAttackHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bAttacking = false;
	m_nCntAttack = 0;
	m_fFrictionCoeff = 0.1f;
	m_nPlayerRanking = 0;
	m_nRanking = 0;

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = nullptr;
		}
	}

	//�A�j���[�^�[�̔j������
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	//�X�R�A�̔j������
	if (m_pScore != nullptr)
	{
		m_pScore->Clear();
		m_pScore = nullptr;
	}
	//�X�R�A��UI�̔j������
	if (m_pScoreUI != nullptr)
	{
		m_pScoreUI->Uninit();
		m_pScoreUI = nullptr;
	}
	if (m_pHeadHitbox != nullptr)
	{
		m_pHeadHitbox->Release();
		m_pHeadHitbox = nullptr;
	}
	if (m_pAttackHitbox != nullptr)
	{
		m_pAttackHitbox->Release();
		m_pAttackHitbox = nullptr;
	}
}

//�X�V����
void CPlayer::Update(void)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����

	//�v���C���[�̖ړI�p�x�̐��K������
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (cR.z < 0.0f)
	{
		fA *= -1.0f;
	}

	if (!m_bGoal && CMessage::GetStart())
	{
		PlayerController(m_nIdxPlayer);
	}

	//m_pModel->SetPos(m_pModel->GetPos() + m_move);

	{
		m_pos += m_move;								//�ʒu�̍X�V
		CDebugProc::Print("\n%f %f %f", m_move.x, m_move.y, m_move.z);
	}

	m_move.x += (0.0f - m_move.x) * m_fFrictionCoeff;				//�ړ��ʂ�X�R���|�l���g�̍X�V
	m_move.y += (0.0f - m_move.y) * m_fFrictionCoeff;				//�ړ��ʂ�Y�R���|�l���g�̍X�V
	m_move.z += (0.0f - m_move.z) * m_fFrictionCoeff;				//�ړ��ʂ�Z�R���|�l���g�̍X�V

	//if (!m_bMove)
	
	PlayerRespawn();

	//�ړI�̊p�x�̐��K������
	if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) > D3DX_PI)
	{
		m_DestRot.y -= 2 * D3DX_PI;
	}
	else if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) < -D3DX_PI)
	{
		m_DestRot.y += 2 * D3DX_PI;
	}

	D3DXVECTOR3 rot = m_pModel[BODY]->GetRot() + ((m_DestRot - m_pModel[BODY]->GetRot()) * 0.1f);		//��]�p�x�̌v�Z

	m_pModel[BODY]->SetRot(rot);		//��]�p�x�̐ݒ菈��

	//��]�p�x�̐��K������
	{
		float fRot = m_pModel[BODY]->GetRot().y;

		if (fRot > D3DX_PI)
		{
			fRot = -D3DX_PI + (fRot - D3DX_PI);
		}
		else if (fRot < -D3DX_PI)
		{
			fRot = D3DX_PI - (D3DX_PI + fRot);
		}

		if (fRot < D3DX_PI * -2.0f)
		{
			fRot += D3DX_PI * 2.0f;
		}
		else if (fRot > D3DX_PI * 2.0f)
		{
			fRot += D3DX_PI * -2.0f;
		}

		//��]�̐ݒ菈��
		m_pModel[BODY]->SetRot(D3DXVECTOR3(m_pModel[BODY]->GetRot().x, fRot, m_pModel[BODY]->GetRot().z));
	}

	//�d�ʂ�ǉ�����
	if (m_move.y >= -10.0f)
	{
		m_move.y -= 0.65f;
	}

	//SetPos(pos);

	{
		float fHeight = 0.0f;

		CMeshfield* pField = CMeshfield::FieldInteraction(this, &fHeight);

			//�n�ʂƂ̓����蔻��
			if (pField != nullptr)
			{
				m_bJump = false;		//���n���Ă����Ԃɂ���
				m_bHit = false;
				m_fFrictionCoeff = pField->GetFriction();

				for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
				{
					if (m_pModel[nCnt] != nullptr)
					{
						m_pModel[nCnt]->SetShadowHeight(fHeight);
					}
				}
			}
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera != nullptr)
	{
		D3DXVECTOR3 wallPos = pCamera->GetPos();
		wallPos.z += 160.0f;

		if (m_pos.z <= wallPos.z)
		{
			m_pos.z = wallPos.z;
		}

		// �v���C���[�ő吔���̃C���X�^���X���쐬
		CPlayer* pPlayer[PLAYER_MAX];

		// �e�v���C���[�̃|�C���^���擾���A�e�C���X�^���X�ɑ��
		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			pPlayer[nCnt] = CStage::GetPlayer(nCnt);
		}

		if (m_pos.z >= 900.0f && m_bGoal == false)
		{
			m_bGoal = true;
			//���ʕt��
			m_nRanking++;
			m_nPlayerRanking = m_nRanking;
			//���ʂɂ���ăX�R�A�̉��Z
			if (m_pScore != nullptr)
			{
				if (m_nPlayerRanking == 1)
				{
					m_pScore->AddScore(30);
				}
				else if (m_nPlayerRanking == 2)
				{
					m_pScore->AddScore(20);
				}
				else if (m_nPlayerRanking == 3)
				{
					m_pScore->AddScore(10);
				}
				else if (m_nPlayerRanking == 4)
				{
					m_pScore->AddScore(5);
				}
			}
		}

		GoalMove();

		if (m_nInvincibilityCnt > 0)
		{
			m_nInvincibilityCnt--;

			if (m_nInvincibilityCnt <= 0)
			{
				if (m_pHitbox != nullptr)
				{
					m_pHitbox->SetInvincibility(false);
				}
			}
		}

		if (m_pHitbox != nullptr)
		{
			int nScore = m_pScore->GetScore();

			m_pHitbox->SetPos(m_pos);
			m_pHitbox->Update();

			CHitbox::INTERACTION_EFFECT effect = m_pHitbox->GetEffect();

			switch (effect)
			{
			case CHitbox::EFFECT_DAMAGE:

			{
				int spawnCoin = (int)((nScore - m_pScore->GetScore()) * 0.1f);

				for (int nCnt = 0; nCnt < spawnCoin; nCnt++)
				{
					CCoin::Create(GetPos(), D3DXVECTOR3((float)random(-5, 5), 10.0f, (float)random(-5, 5)), 180, CCoin::COIN_0);
				}

				m_nInvincibilityCnt = 60;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

				if (m_pHitbox != nullptr)
				{
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
					m_pHitbox->SetInvincibility(true);
				}
			}

			break;

			case CHitbox::EFFECT_LAUNCH:

			{
				m_bHit = true;
				m_pAnimator->SetPresentAnim(4);

				int spawnCoin = (int)((nScore - m_pScore->GetScore()) * 0.1f);

				for (int nCnt = 0; nCnt < spawnCoin; nCnt++)
				{
					CCoin::Create(GetPos(), D3DXVECTOR3((float)random(-5, 5), 10.0f, (float)random(-5, 5)), 180, CCoin::COIN_0);
				}

				D3DXVec3Normalize(&m_move, &m_move);
				m_move.x *= -50.0f;
				m_move.y = 10.0f;
				m_move.z *= -50.f;

				m_nInvincibilityCnt = 60;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

				if (m_pHitbox != nullptr)
				{
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
					m_pHitbox->SetInvincibility(true);
				}
			}

			break;

			case CHitbox::EFFECT_PUSH:

			{
				m_bHit = true;
				m_pAnimator->SetPresentAnim(4);

				m_move = m_pHitbox->GetDirection();
				D3DXVec3Normalize(&m_move, &m_move);
				m_move.x *= 5.0f;
				m_move.y = 10.0f;
				m_move.z *= 5.f;

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

				if (m_pHitbox != nullptr)
				{
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
					m_pHitbox->SetDirection(Vec3Null);
				}
			}

				break;

			case CHitbox::EFFECT_BOUNCE:

			{
				m_bHit = true;
				m_pAnimator->SetPresentAnim(4);

				D3DXVec3Normalize(&m_move, &m_move);
				m_move.x *= -50.0f;
				m_move.y = 10.0f;
				m_move.z *= -50.f;

				if (m_pHitbox != nullptr)
				{
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
					m_pHitbox->SetDirection(Vec3Null);
				}
			}

			break;

			case CHitbox::EFFECT_JUMP:

			{
				m_bHit = true;
				m_bJump = true;
				m_pAnimator->SetPresentAnim(4);

				D3DXVec3Normalize(&m_move, &m_move);
				m_move.y = 30.0f;

				if (m_pHitbox != nullptr)
				{
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);
					m_pHitbox->SetDirection(Vec3Null);
				}
			}

			break;

			default:
				break;
			}
		}
		if (m_nCntAttack > 0)
		{
			m_nCntAttack--;

			if (m_nCntAttack == 49 && m_pAttackHitbox == nullptr)
			{
				D3DXVECTOR3 Rot = Vec3Null;

				if (m_pModel[0] != nullptr)
				{
					Rot = m_pModel[0]->GetRot();
				}
				D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 20.0f, 20.0f);
				D3DXMATRIX mtxOut ,mtxTrans ,mtxRot;
				D3DXMatrixIdentity(&mtxOut);
				D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, 0.0f, 0.0f);
				D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
				/*D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
				D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);*/
				D3DXVec3TransformCoord(&dir, &dir, &mtxOut);

				m_pAttackHitbox = CBoxHitbox::Create(dir + m_pos, Vec3Null, D3DXVECTOR3(14.0f, 14.0f, 14.0f), CHitbox::TYPE_OBSTACLE, this, 0, CHitbox::EFFECT_PUSH);
				
				if (m_pAttackHitbox != nullptr)
				{
					dir.y = 0.0f;
					D3DXVec3Normalize(&dir, &dir);
					m_pAttackHitbox->SetDirection(dir);
				}
			}

			if (m_nCntAttack <= 0)
			{
				m_pAttackHitbox->Release();
				m_pAttackHitbox = nullptr;
				m_nCntAttack = 0;
				m_bAttacking = false;
			}
		}
		if (m_pHeadHitbox != nullptr)
		{
			m_pHeadHitbox->SetPos(m_pos);
			m_pHeadHitbox->Update();
		}
		
		CPlayer *m_pPlayer[PLAYER_MAX] = {};

		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			m_pPlayer[nCnt] = CStage::GetPlayer(nCnt);
		}

		if (m_pPlayer[0]->m_bGoal &&m_pPlayer[1]->m_bGoal &&m_pPlayer[2]->m_bGoal &&m_pPlayer[3]->m_bGoal
			&& m_pPlayer[0]->m_bRot &&m_pPlayer[1]->m_bRot &&m_pPlayer[2]->m_bRot &&m_pPlayer[3]->m_bRot)
		{
			pCamera->SetPos(D3DXVECTOR3(pCamera->GetPos().x, -80.0f, 800.0f), pCamera->GetPos());

			m_nFrame++;

			if (m_nFrame >= 60)
			{
				MoveWinner();
			}
		}

		if (m_pScoreUI != nullptr && m_pScore != nullptr)
		{
			int nScore = m_pScore->GetScore();
			std::string str = std::to_string(nScore);
			std::string begin = {};

			if (str.size() < 4)
			{
				for (int nCnt = 0; nCnt < 4 - (int)str.size(); nCnt++)
				{
					begin += '0';
				}

				begin += str;
			}
			else
			{
				begin = str;
			}

			const char* pStr = begin.c_str();
			m_pScoreUI->ChangeString(pStr);
		}
	}

	CDebugProc::Print("\nRot: %f\nRot Dest: %f\n\nPos: %f, %f, %f", m_pModel[BODY]->GetRot().y, m_DestRot.y, m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("\nPlayer %d score: %d", m_nIdxPlayer, m_pScore->GetScore());
}

//�`�揈��
void CPlayer::Draw(void)
{
	if (m_nInvincibilityCnt % 10 <= 5)
	{
		//�f�o�C�X�̎擾����
		//LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		////�X�e���V���o�b�t�@��L���ɂ���
		//pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		////�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
		//pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		////�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
		//pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		////�X�e���V���e�X�g�̔�r���@�̐ݒ�
		//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		////�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
		//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);


		D3DXMATRIX mtxTrans, mtxRot;												//�v�Z�p�̃}�g���b�N�X
		D3DXMatrixIdentity(&m_mtxWorld);											//���[���h�}�g���b�N�X�̏���������

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		m_pModel[BODY]->Draw(m_mtxWorld);											//�ŏ��̃��f���̕`�揈��

		for (int nCnt = 1; nCnt < PARTS_MAX; nCnt++)
		{//���̃��f���̕`�揈��
			if (m_pModel[nCnt] != nullptr)
			{
				m_pModel[nCnt]->Draw();
			}
		}

		////�X�e���V���o�b�t�@�𖳌��ɂ���
		//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}
}

//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, int nCntPlayer)
{
	CPlayer* pModel = new CPlayer;		//�C���X�^���X�𐶐�����

	//�v���C���[�̏���������
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	CModel::ModelType pType = CPlayerModel::GetHeadType(nCntPlayer);

	pModel->m_pos = pos;
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 17.0f, 0.0f), Vec3Null);				//�̂̃��f���𐶐�����

	pModel->m_pModel[HEAD] = CModelPart::Create(pType, D3DXVECTOR3(0.0f, 7.0f, 0.0f), Vec3Null);				//���̃��f���𐶐�����
	pModel->m_pModel[HEAD]->SetParent(pModel->m_pModel[BODY]);																//���̐e��ݒ肷��

	pModel->m_pModel[LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(8.0f, 3.0f, 0.0f), Vec3Null);		//���r�̃��f���𐶐�����
	pModel->m_pModel[LEFT_ARM]->SetParent(pModel->m_pModel[BODY]);															//���r�̐e��ݒ肷��

	pModel->m_pModel[LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//����̃��f���𐶐�����
	pModel->m_pModel[LEFT_HAND]->SetParent(pModel->m_pModel[LEFT_ARM]);														//����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-8.0f, 3.0f, 0.0f), Vec3Null);	//�E�r�̃��f���𐶐�����
	pModel->m_pModel[RIGHT_ARM]->SetParent(pModel->m_pModel[BODY]);															//�E�r�̐e��ݒ肷��

	pModel->m_pModel[RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//�E��̃��f���𐶐�����
	pModel->m_pModel[RIGHT_HAND]->SetParent(pModel->m_pModel[RIGHT_ARM]);													//�E��̐e��ݒ肷��

	pModel->m_pModel[LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, -9.0f, 0.0f), Vec3Null);		//�����ڂ̃��f���𐶐�����
	pModel->m_pModel[LEFT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�����ڂ̐e��ݒ肷��

	pModel->m_pModel[LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -5.0f, 0.0f), Vec3Null);	//�����̃��f���𐶐�����
	pModel->m_pModel[LEFT_FOOT]->SetParent(pModel->m_pModel[LEFT_LEG]);														//�����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, -9.0f, 0.0f), Vec3Null);	//�E���ڂ̃��f���𐶐�����
	pModel->m_pModel[RIGHT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�E���ڂ̐e��ݒ肷��

	pModel->m_pModel[RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -5.0f, 0.0f), Vec3Null);//�E���̃��f���𐶐�����
	pModel->m_pModel[RIGHT_FOOT]->SetParent(pModel->m_pModel[RIGHT_LEG]);													//�E���̐e��ݒ肷��

	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[BODY]);
	vParts.push_back(pModel->m_pModel[HEAD]);
	vParts.push_back(pModel->m_pModel[LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[RIGHT_FOOT]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);

	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(10.0f, 35.0f, 10.0f), CHitbox::TYPE_PLAYER, pModel, nCntPlayer);
	pModel->m_pHeadHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXVECTOR3(1.0f, 2.0f, 1.0f), CHitbox::TYPE_PLAYER, pModel);

	pModel->SetPlayerIdx(nCntPlayer);

	pModel->m_pScore = CScore::Create(nCntPlayer);

	D3DXCOLOR UIcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	D3DXCOLOR col = CPlayerModel::GetPlayerColors()[nCntPlayer];

	pModel->m_pModel[BODY]->SetModelColor(2, col);
	UIcol = col;
	//pModel->m_TargetPos = D3DXVECTOR3(-223.0f + (61.0f * (nCntPlayer + 1)),-149.0f,1009.0f);
	D3DXVECTOR3 fieldPos = CGameRace::GetStage()->GetField()->GetPos();
	pModel->m_TargetPos = D3DXVECTOR3(-75.0f + (50.0f * (nCntPlayer)), -150.0f, fieldPos.z - 100.0f);
	pModel->m_pScoreUI = CUIString::Create(D3DXVECTOR3(100.0f + (320.0f * nCntPlayer), SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), UIcol, "0000", 5);

	//CSilhouette::Create();

	return pModel;
}

D3DXCOLOR* CPlayer::GetPlayerColors(void)
{
	return m_playerColor;
}






void CPlayer::PlayerController(int nCntPlayer)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (!m_bAttacking)
	{
		//�ړ��ʂƖړI�̊p�x�̌v�Z
		if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y < -0.3f)
		{//W�L�[�������ꂽ�ꍇ
			if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x < -0.3f)
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.75f + fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x > 0.3f)
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.25f + fA;
			}
			else
			{//W�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_S) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y > 0.3f)
		{//S�L�[�������ꂽ�ꍇ
			if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x < -0.3f)
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.75f + fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x > 0.5f)
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.25f + fA;
			}
			else
			{//S�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x > 0.3f)
		{//D�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}

			m_DestRot.y = fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x < -0.3f)
		{//A�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			m_DestRot.y = D3DX_PI + fA;
		}
	}

	if ((CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) || (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A,nCntPlayer))) && !m_bJump && !m_bAttacking)
	{//�W�����v
		m_move.y = 18.0f;
 		m_bJump = true;
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		m_pAnimator->SetPresentAnim(2);
	}

	if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputKeyboard::GetKeyboardPress(DIK_S) || CInputKeyboard::GetKeyboardPress(DIK_A) || CInputKeyboard::GetKeyboardPress(DIK_D)
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  > 0.3f)
	{
		if (!m_bJump && !m_bHit && !m_bAttacking)
		{
			m_pAnimator->SetLoopingAnim(1);
		}
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_V) || (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, nCntPlayer)) &&  !m_bJump && !m_bHit && !m_bAttacking)
	{
		m_pAnimator->SetPresentAnim(3);

		m_bAttacking = true;
		m_nCntAttack = 50;
	}
}

void CPlayer::SetPlayerIdx(int nCntPlayer)
{
	m_nIdxPlayer = nCntPlayer;
}

void CPlayer::SetFriction(const float fFriction)
{
	m_fFrictionCoeff = fFriction;
}

bool CPlayer::GetRotCmp()
{
	return m_bRot;
}

//=====================================
// ���҂̈ړ�����
//=====================================
void CPlayer::MoveWinner()
{
	if (m_bWinner && GetRotCmp())
	{
		if (!m_bPos)
		{
			GoalPos = m_pos - D3DXVECTOR3(0.0f, 0.0f, 50.0f);
			m_bPos = true;
		}

		m_fAngle = sqrtf((float)(pow(GoalPos.x - m_pos.x, 2) + pow(GoalPos.z - m_pos.z, 2)));
		m_move.x = (GoalPos.x - m_pos.x) / (m_fAngle / 1.0f);
		m_move.z = (GoalPos.z - m_pos.z) / (m_fAngle / 1.0f);

		if (m_pos.z <= GoalPos.z)
		{
			m_move = Vec3Null;
			m_bMove = true;
		}

		WinnerAnim();
	}
	else if(GetRotCmp())
	{
		LoserAnim();
	}
}

void CPlayer::SetWinner(bool bWinner)
{
	m_bWinner = bWinner;
}

void CPlayer::WinnerAnim()
{
	m_pAnimator->SetPresentAnim(5);
}

void CPlayer::LoserAnim()
{
	m_pAnimator->SetPresentAnim(6);
}

//��������
void CPlayer::PlayerRespawn()
{
	if (m_pos.y <= -500.0f)
	{
		D3DXVECTOR3 posCamera = CApplication::GetCamera()->GetPos();
		m_pos = D3DXVECTOR3(posCamera.x, posCamera.y + 100.0f, posCamera.z + 100.0f);

		if (m_pHitbox != nullptr)
		{
			m_pHitbox->SetInvincibility(true);
		}

		if (m_pScore != nullptr)
		{
			m_pScore->AddScore(-30);
		}

		m_nInvincibilityCnt = 180;
	}
}

void CPlayer::GoalMove()
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (!m_bGoal)
	{
		return;
	}

	// �Ώۂ܂ł̊p�x�̎Z�o
	m_fAngle = sqrtf((float)(pow(m_TargetPos.x - m_pos.x, 2) + pow(m_TargetPos.z - m_pos.z, 2)));
	m_move.x = (m_TargetPos.x - m_pos.x) / (m_fAngle / 1.0f);
	m_move.z = (m_TargetPos.z - m_pos.z) / (m_fAngle / 1.0f);

	if (m_pos.z >= m_TargetPos.z)
	{
		m_move = Vec3Null;
		m_DestRot.y = D3DX_PI * 0.5f + fA;
	}
	
	if(m_rot.y <= m_DestRot.y * 2.0f)
	{
		m_bRot = true;
	}
}
