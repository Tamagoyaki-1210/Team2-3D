//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "playerModel.h"
#include "animator.h"
#include "modelPart.h"
#include "application.h"
#include "rendering.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "object2D.h"

D3DXCOLOR CPlayerModel::m_playersCol[PLAYER_MAX] =
{
	ColorWhite,
	ColorWhite,
	ColorWhite,
	ColorWhite
};

//�R���X�g���N�^
CPlayerModel::CPlayerModel()
{
	//�����o�[�ϐ����N���A����
	m_pAnimator = nullptr;					//�A�j���[�^�[�ւ̃|�C���^
	m_pos = Vec3Null;						//�ʒu
	m_rot = Vec3Null;						//����
	m_nPresentColor = ColorNull;			//���݂̃J�[���[�C���f�b�N�X
	m_nIdx = 0;

	m_pIcon = nullptr;

	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPlayerModel::~CPlayerModel()
{

}

//����������
HRESULT CPlayerModel::Init(void)
{
	m_pAnimator = nullptr;					//�A�j���[�^�[�ւ̃|�C���^
	m_pos = Vec3Null;						//�ʒu
	m_rot = Vec3Null;						//����
	m_nPresentColor = ColorWhite;			//���݂̃J�[���[�C���f�b�N�X
	m_nIdx = 0;

	m_pIcon = nullptr;

	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CPlayerModel::Uninit(void)
{
	m_playersCol[m_nIdx] = m_presentColor;

	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
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
	if (m_pIcon != nullptr)
	{
		m_pIcon->Release();
		m_pIcon = nullptr;
	}
}

//�X�V����
void CPlayerModel::Update(void)
{
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Update();
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_D))
	{
		m_nPresentColor++;

		if (m_nPresentColor >= CPlayer::PLAYER_COLOR_MAX)
		{
			m_nPresentColor = 0;
		}

		m_presentColor = CPlayer::GetPlayerColors()[m_nPresentColor];

		if (m_pModel[CPlayer::BODY] != nullptr)
		{
			m_pModel[CPlayer::BODY]->SetModelColor(2, m_presentColor);
		}
		if (m_pIcon != nullptr)
		{
			m_pIcon->SetColor(m_presentColor);
		}
	}
	else if (CInputKeyboard::GetKeyboardTrigger(DIK_A))
	{
		m_nPresentColor--;

		if (m_nPresentColor < 0)
		{
			m_nPresentColor = CPlayer::PLAYER_COLOR_MAX - 1;
		}

		m_presentColor = CPlayer::GetPlayerColors()[m_nPresentColor];

		if (m_pModel[CPlayer::BODY] != nullptr)
		{
			m_pModel[CPlayer::BODY]->SetModelColor(2, m_presentColor);
		}
		if (m_pIcon != nullptr)
		{
			m_pIcon->SetColor(m_presentColor);
		}
	}

	CDebugProc::Print("\nColor: %d", m_nPresentColor);
}

//�`�揈��
void CPlayerModel::Draw(void)
{
	//�f�o�C�X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxTrans, mtxRot;												//�v�Z�p�̃}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);											//���[���h�}�g���b�N�X�̏���������

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pModel[CPlayer::BODY]->Draw(m_mtxWorld);											//�ŏ��̃��f���̕`�揈��

	for (int nCnt = 1; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//���̃��f���̕`�揈��
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Draw();
		}
	}

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//�ʒu�̐ݒ菈��
void CPlayerModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CPlayerModel::GetSize(void)
{
	return Vec2Null;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CPlayerModel::GetPos(void)
{
	return m_pos;
}

//�J�[���[�̎擾����
const D3DXCOLOR*  CPlayerModel::GetPlayerColors(void)
{
	return m_playersCol;
}






//��������
CPlayerModel* CPlayerModel::Create(const D3DXVECTOR3 pos, int nIdx)
{
	if (nIdx >= PLAYER_MAX)
	{
		return nullptr;
	}

	CPlayerModel* pModel = new CPlayerModel;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_rot = Vec3Null;
	pModel->m_nIdx = nIdx;
	pModel->m_nPresentColor = nIdx;
	pModel->m_presentColor = CPlayer::GetPlayerColors()[nIdx];

	pModel->m_pos = pos;
	pModel->m_pModel[CPlayer::BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 17.0f, 0.0f), Vec3Null);				//�̂̃��f���𐶐�����

	pModel->m_pModel[CPlayer::HEAD] = CModelPart::Create(CModel::MODEL_HEAD, D3DXVECTOR3(0.0f, 7.0f, 0.0f), Vec3Null);				//���̃��f���𐶐�����
	pModel->m_pModel[CPlayer::HEAD]->SetParent(pModel->m_pModel[CPlayer::BODY]);																//���̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(8.0f, 3.0f, 0.0f), Vec3Null);		//���r�̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_ARM]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//���r�̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//����̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_HAND]->SetParent(pModel->m_pModel[CPlayer::LEFT_ARM]);														//����̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-8.0f, 3.0f, 0.0f), Vec3Null);	//�E�r�̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_ARM]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//�E�r�̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//�E��̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_HAND]->SetParent(pModel->m_pModel[CPlayer::RIGHT_ARM]);													//�E��̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, -9.0f, 0.0f), Vec3Null);		//�����ڂ̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_LEG]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//�����ڂ̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -5.0f, 0.0f), Vec3Null);	//�����̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_FOOT]->SetParent(pModel->m_pModel[CPlayer::LEFT_LEG]);														//�����̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, -9.0f, 0.0f), Vec3Null);	//�E���ڂ̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_LEG]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//�E���ڂ̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -5.0f, 0.0f), Vec3Null);//�E���̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_FOOT]->SetParent(pModel->m_pModel[CPlayer::RIGHT_LEG]);													//�E���̐e��ݒ肷��

	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[CPlayer::BODY]);
	vParts.push_back(pModel->m_pModel[CPlayer::HEAD]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_FOOT]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);

	pModel->m_pModel[CPlayer::BODY]->SetModelColor(2, pModel->m_presentColor);

	pModel->m_pIcon = CObject_2D::Create();
	pModel->m_pIcon->SetPos(D3DXVECTOR3(((float)SCREEN_WIDTH / 5.0f) * (nIdx + 1), (float)SCREEN_HEIGHT * 0.75f, 0.0f));
	pModel->m_pIcon->SetSize(D3DXVECTOR2(100.0f, 15.0f));
	pModel->m_pIcon->SetTexture(CObject::TEXTURE_NULL);
	pModel->m_pIcon->SetColor(pModel->m_presentColor);

	return pModel;
}