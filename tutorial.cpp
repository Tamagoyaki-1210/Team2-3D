//=============================================================================
//
// tutorial.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "tutorial.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "application.h"
#include "meshfield.h"
#include "coin.h"
#include "SpikeBall.h"
#include "lavaFloor.h"
#include "score.h"
#include "trampoline.h"
#include "bouncePole.h"
#include "stoneSpawner.h"
#include "icePillarSpawner.h"
#include "stage.h"

CStage* CTutorial::m_pStage = nullptr;
bool CTutorial::m_bEndTutorial = false;

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CTutorial::CTutorial()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CTutorial::~CTutorial()
{

}

//=====================================
// ����������
//=====================================
HRESULT CTutorial::Init(void)
{
	m_pStage = CStage::Create();

	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -150.0f, -1800.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), 20, 10, 3);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(0.33f);

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CTutorial::Uninit(void)
{
	if (m_pStage != nullptr)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}

	m_bEndTutorial = false;
}

//=====================================
// �X�V����
//=====================================
void CTutorial::Update(void)
{
	if (m_pStage != nullptr)
	{
		m_pStage->Update();
	}
	//�Q�[�����̏���
	if (m_bEndTutorial == false)
	{
		//P�Ń|�[�Y�؂�ւ�
		if (CInputKeyboard::GetKeyboardTrigger(DIK_P) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0))
		{
			CApplication::SetMode(CApplication::Mode_Title);
		}
	}
}

//=====================================
// �X�V����
//=====================================
void CTutorial::SetEndTutorial(void)
{
	m_bEndTutorial = true;
}

//=====================================
// ��������
//=====================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial;

	if (FAILED(pTutorial->Init()))
	{
		return nullptr;
	}

	return pTutorial;
}