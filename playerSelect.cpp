//=============================================================================
//
// title.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "playerSelect.h"
#include "Application.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "fade.h"
#include "playerModel.h"
#include "camera.h"
#include "halfsphere.h"

CFontString* CPlayerSelect::m_pStr = nullptr;
int CPlayerSelect::m_nPlayerCount = 0;
//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CPlayerSelect::CPlayerSelect()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CPlayerSelect::~CPlayerSelect()
{

}

//=====================================
// ����������
//=====================================
HRESULT CPlayerSelect::Init(void)
{
	CHalfSphere* m_pSphere = CHalfSphere::Create(D3DXVECTOR3(0.0f, -8000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);
	
	m_pSphere->BindTexture(CObject_2D::GetTexturePointer(CObject::TEXTURE_BACKGROUND));

	CObject_2D* pObj2D = CObject_2D::Create();
	pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	pObj2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	pObj2D->SetTexture(CObject::TEXTURE_CHARASET_FRAM);
	pObj2D->SetPriority(5);

	m_pStr = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), "�L�����N�^�[�Z���N�g");

	CCamera* pCamera = CApplication::GetCamera();
	pCamera->SetPos(D3DXVECTOR3(50.0f, 230.0f, -200.0f), D3DXVECTOR3(50.0f, 220.0f, 100.0f));

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CPlayerSelect::Uninit(void)
{
	if (m_pStr != nullptr)
	{
		m_pStr->Uninit();
		m_pStr = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void CPlayerSelect::Update(void)
{
	if (m_pStr != nullptr)
	{
		m_pStr->Update();
	}
	Input();
}

//=====================================
// ���͏���
//=====================================
void CPlayerSelect::Input(void)
{
	CSound *pSound = CApplication::GetSound();

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
#ifdef _DEBUG
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{
			CApplication::SetMode(CApplication::Mode_StageSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_YES);
		}
#endif // !DEBUG
		if (m_nPlayerCount >= 4)
		{//�S��������������������
			CApplication::SetMode(CApplication::Mode_StageSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_YES);
		}
	}
}

//=====================================
// ��������
//=====================================
CPlayerSelect* CPlayerSelect::Create(void)
{
	CPlayerSelect* pPlayerSelect = new CPlayerSelect;

	if (FAILED(pPlayerSelect->Init()))
	{
		return nullptr;
	}

	CPlayerModel* pModel = CPlayerModel::Create(D3DXVECTOR3(-85.0f, 200.0f, 100.0f), 0);
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.125f, 0.0f));
	pModel = CPlayerModel::Create(D3DXVECTOR3(5.0f, 200.0f, 100.0f), 1);
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.025f, 0.0f));
	pModel = CPlayerModel::Create(D3DXVECTOR3(92.0f, 200.0f, 100.0f), 2);
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.025f, 0.0f));
	pModel = CPlayerModel::Create(D3DXVECTOR3(182.0f, 200.0f, 100.0f), 3);
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.125f, 0.0f));

	return pPlayerSelect;
}