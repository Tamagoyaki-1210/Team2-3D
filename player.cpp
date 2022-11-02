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
#include "stage.h"
#include "rendering.h"
#include "silhouette.h"

//�R���X�g���N�^
CPlayer::CPlayer()
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
	m_pAnimator = nullptr;			//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;			//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;				//�X�R�A�ւ̃|�C���^
	m_State = STATE_NEUTRAL;		//�A�j���[�V�������
	m_pScoreUI = nullptr;			//�X�R�A��UI�ւ̃|�C���^
	m_bJump = false;				//�W�����v���Ă��邩�ǂ���

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

	PlayerController(m_nIdxPlayer);

	//m_pModel->SetPos(m_pModel->GetPos() + m_move);

	m_move.x += (0.0f - m_move.x) * 0.1f;				//�ړ��ʂ�X�R���|�l���g�̍X�V
	m_move.y += (0.0f - m_move.y) * 0.1f;				//�ړ��ʂ�Y�R���|�l���g�̍X�V
	m_move.z += (0.0f - m_move.z) * 0.1f;				//�ړ��ʂ�Z�R���|�l���g�̍X�V

	m_pos += m_move;									//�ʒu�̍X�V

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
	
	//�n�ʂƂ̓����蔻��
	if (CMeshfield::FieldInteraction(this))
	{
		m_bJump = false;		//���n���Ă����Ԃɂ���
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera != nullptr)
	{
		D3DXVECTOR3 wallPos = pCamera->GetPos();
		wallPos.z += 150.0f;

		if (m_pos.z <= wallPos.z)
		{
			m_pos.z = wallPos.z;
		}

		if (wallPos.z >= 900.0f || CStage::GetPlayer(0)->m_pos.z >= 900.0f)
		{
			CStage::GetPlayer(0)->m_pos = D3DXVECTOR3(-147.0f,-149.0f,1009.0f);
		}

		if(wallPos.z >= 900.0f || CStage::GetPlayer(1)->m_pos.z >= 900.0f)
		{
			CStage::GetPlayer(1)->m_pos = D3DXVECTOR3(-85.0f, -149.0f, 1009.0f);
		}
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(m_pos);
		m_pHitbox->Update();
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

	CDebugProc::Print("\nRot: %f\nRot Dest: %f\n\nPos: %f, %f, %f", m_pModel[BODY]->GetRot().y, m_DestRot.y, m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("\nPlayer %d score: %d", m_nIdxPlayer, m_pScore->GetScore());
}

//�`�揈��
void CPlayer::Draw(void)
{
	//�f�o�C�X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);


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

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//�ʒu�̐ݒ菈��
void CPlayer::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CPlayer::GetSize(void)
{
	return Vec2Null;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}



//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos,int nCntPlayer)
{
	CPlayer* pModel = new CPlayer;		//�C���X�^���X�𐶐�����
	
	//�v���C���[�̏���������
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 14.0f, 0.0f), Vec3Null);				//�̂̃��f���𐶐�����

	pModel->m_pModel[HEAD] = CModelPart::Create(CModel::MODEL_HEAD, D3DXVECTOR3(0.0f, 13.0f, 0.0f), Vec3Null);				//���̃��f���𐶐�����
	pModel->m_pModel[HEAD]->SetParent(pModel->m_pModel[BODY]);																//���̐e��ݒ肷��

	pModel->m_pModel[LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(5.0f, 12.0f, 0.0f), Vec3Null);		//���r�̃��f���𐶐�����
	pModel->m_pModel[LEFT_ARM]->SetParent(pModel->m_pModel[BODY]);															//���r�̐e��ݒ肷��

	pModel->m_pModel[LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//����̃��f���𐶐�����
	pModel->m_pModel[LEFT_HAND]->SetParent(pModel->m_pModel[LEFT_ARM]);														//����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-5.0f, 12.0f, 0.0f), Vec3Null);	//�E�r�̃��f���𐶐�����
	pModel->m_pModel[RIGHT_ARM]->SetParent(pModel->m_pModel[BODY]);															//�E�r�̐e��ݒ肷��
	
	pModel->m_pModel[RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//�E��̃��f���𐶐�����
	pModel->m_pModel[RIGHT_HAND]->SetParent(pModel->m_pModel[RIGHT_ARM]);													//�E��̐e��ݒ肷��
	
	pModel->m_pModel[LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, 1.0f, 0.0f), Vec3Null);		//�����ڂ̃��f���𐶐�����
	pModel->m_pModel[LEFT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�����ڂ̐e��ݒ肷��
	
	pModel->m_pModel[LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -10.0f, 0.0f), Vec3Null);	//�����̃��f���𐶐�����
	pModel->m_pModel[LEFT_FOOT]->SetParent(pModel->m_pModel[LEFT_LEG]);														//�����̐e��ݒ肷��
	
	pModel->m_pModel[RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, 1.0f, 0.0f), Vec3Null);	//�E���ڂ̃��f���𐶐�����
	pModel->m_pModel[RIGHT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�E���ڂ̐e��ݒ肷��

	pModel->m_pModel[RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -10.0f, 0.0f), Vec3Null);//�E���̃��f���𐶐�����
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

	pModel->SetPlayerIdx(nCntPlayer);

	pModel->m_pScore = CScore::Create(nCntPlayer);

	D3DXCOLOR UIcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	if (nCntPlayer == 1)
	{
		pModel->m_pModel[BODY]->SetModelColor(1, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		pModel->m_pModel[LEFT_ARM]->SetModelColor(1, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		pModel->m_pModel[RIGHT_ARM]->SetModelColor(1, D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));
		UIcol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}

	pModel->m_pScoreUI = CUIString::Create(D3DXVECTOR3(50.0f + 200.0f * nCntPlayer, 50.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), UIcol, "0000", 5);

	CSilhouette::Create();

	return pModel;
}

void CPlayer::PlayerController(int nCntPlayer)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	//�ړ��ʂƖړI�̊p�x�̌v�Z
	if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  < -0.3f)
	{//W�L�[�������ꂽ�ꍇ
		if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f)
		{//A�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f)
		{//D�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(-D3DX_PI * 0.25f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(-D3DX_PI * 0.25f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.75f + fA;
		}
		else
		{//W�L�[�����������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(cameraRot.y);
			}

			m_DestRot.y = D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_S) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  > 0.3f)
	{//S�L�[�������ꂽ�ꍇ
		if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f)
		{//A�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.25f + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.5f)
		{//D�L�[�������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(-D3DX_PI * 0.75f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(-D3DX_PI * 0.75f + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.75f + fA;
		}
		else
		{//S�L�[�����������ꂽ�ꍇ
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.2f * cosf(D3DX_PI + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.2f * sinf(D3DX_PI + cameraRot.y);
			}

			m_DestRot.y = -D3DX_PI * 0.5f + fA;
		}
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_D) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f)
	{//D�L�[���������ꂽ�ꍇ
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.2f * cosf(-D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.2f * sinf(-D3DX_PI * 0.5f + cameraRot.y);
		}

		m_DestRot.y = D3DX_PI + fA;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_A) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f)
	{//A�L�[���������ꂽ�ꍇ
		if (m_move.x <= 4.0f && m_move.x >= -4.0f)
		{
			m_move.x += 0.2f * cosf(D3DX_PI * 0.5f + cameraRot.y);
		}
		if (m_move.z <= 4.0f && m_move.z >= -4.0f)
		{
			m_move.z += 0.2f * sinf(D3DX_PI * 0.5f + cameraRot.y);
		}
		m_DestRot.y = fA;
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && !m_bJump)
	{//�W�����v
		m_move.y = 18.0f;
		m_bJump = true;
	}

	if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputKeyboard::GetKeyboardPress(DIK_S) || CInputKeyboard::GetKeyboardPress(DIK_A) || CInputKeyboard::GetKeyboardPress(DIK_D)
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  > 0.3f)
	{
		m_State = STATE_RUNNING;
	}
	else
	{
		m_State = STATE_NEUTRAL;
	}

	switch (m_State)
	{
	case STATE_NEUTRAL:
		m_pAnimator->SetPresentAnim(0);
		break;

	case STATE_RUNNING:
		m_pAnimator->SetPresentAnim(1);
		break;
	default:
		break;
	}
}

void CPlayer::SetPlayerIdx(int nCntPlayer)
{
	m_nIdxPlayer = nCntPlayer;
}
