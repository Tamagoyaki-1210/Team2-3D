//=============================================================================
//
// gamedebug.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "gamedebug.h"
#include "input.h"
#include "application.h"
#include "meshfield.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"
#include "model.h"
#include "player.h"
#include "UIString.h"
#include "Letter.h"
//#include "fade.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "font.h"
#include "halfsphere.h"
#include "CylinderHitbox.h"
#include "BoxHitbox.h"
#include "coin.h"

CMeshfield *CGameDebug::m_pField = nullptr;
CHalfSphere* CGameDebug::m_pSphere[PLAYER_MAX] = {};
CPlayer* CGameDebug::m_pPlayer[PLAYER_MAX] = {};

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CGameDebug::CGameDebug()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CGameDebug::~CGameDebug()
{

}

//=====================================
// ����������
//=====================================
HRESULT CGameDebug::Init(void)
{
	CGame::Init();

	// ���b�V���t�B�[���h�̐���
	m_pField = CMeshfield::Create(D3DXVECTOR3(-1000.0f, -150.0f, 1000.0f), Vec3Null, D3DXVECTOR2(50.0f, 50.0f), 30, 30, 3);
	m_pField->SetTexture(CObject::TEXTURE_BLOCK);
	m_pField->SetTextureTiling(0.33f);

	CObject_2D* pObj2D = CObject_2D::Create();
	pObj2D->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	pObj2D->SetSize(D3DXVECTOR2(20.0f, 20.0f));
	pObj2D->SetTexture(CObject::TEXTURE_LETTERS);
	pObj2D->SetTextureParameter(5, 13, 2, 60);
	pObj2D->SetAnimPattern(15);
	pObj2D->SetAnimationBase(15);

	//// �I�u�W�F�N�g3D�̐���
	//CObject_3D* pObj = CObject_3D::Create();
	//pObj->SetPos(D3DXVECTOR3(0.0f, -200.0f, 300.0f));
	//pObj->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	//pObj->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//pObj->SetStartingRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//pObj->SetTexture(CObject::TEXTURE_BLOCK);
	//pObj->SetTextureParameter(1, 1, 1, INT_MAX);

	// ���f���̐���
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, -150.0f));
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, 150.0f));

	// �r���{�[�h�̐���
	CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f), D3DXVECTOR2(50.0f, 50.0f), 3);
	pBillboard->SetTexture(CObject::TEXTURE_BLOCK);

	// �v���C���[�̐���
	m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f), 0);
	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(-100.0f, -100.0f, -100.0f), 1);

	m_pSphere[0] = CHalfSphere::Create(D3DXVECTOR3(0.0f, -1000.0f, 1000.0f), D3DXVECTOR3(15000.0f, 0.0f, 15000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHalfSphere::SPHERE_UP);
	m_pSphere[0]->LoadTexture("data\\TEXTURE\\sky001.jpg");

	m_pSphere[1] = CHalfSphere::Create(D3DXVECTOR3(0.0f, -1000.0f, 1000.0f), D3DXVECTOR3(15000.0f, 0.0f, 15000.0f), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), CHalfSphere::SPHERE_DOWN);
	m_pSphere[1]->LoadTexture("data\\TEXTURE\\9_m.jpg");

	// UIString�̐���
	CUIString::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR2(250.0f, 25.0f), D3DXCOLOR(0.2f, 1.0f, 0.5f, 1.0f), "Sentence A, 125 $%&");

	CLetter::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 'r', 5);

	CLetter::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 4, 5);

	CBoxHitbox::Create(D3DXVECTOR3(-200.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(50.0f, 300.0f, 50.0f), CHitbox::TYPE_NEUTRAL, nullptr);
	CCylinderHitbox::Create(D3DXVECTOR3(350.0f, -150.0f, 200.0f), Vec3Null, D3DXVECTOR3(150.0f, 300.0f, 150.0f), CHitbox::TYPE_NEUTRAL, nullptr);

	CCoin::Create(D3DXVECTOR3(-100.0f, -125.0f, 200.0f), CCoin::COIN_0);
	CCoin::Create(D3DXVECTOR3(0.0f, -125.0f, 200.0f), CCoin::COIN_1);
	CCoin::Create(D3DXVECTOR3(100.0f, -125.0f, 200.0f), CCoin::COIN_2);
	CCoin::Create(D3DXVECTOR3(200.0f, -125.0f, 200.0f), CCoin::COIN_3);
	//UI
	//m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 140.0f, 50.0f, 0.0f));

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CGameDebug::Uninit(void)
{
	CGame::Uninit();

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pPlayer[nCnt] != nullptr)
		{
			m_pPlayer[nCnt]->Release();
			m_pPlayer[nCnt] = nullptr;
		}
	}

	if (m_pSphere[0] != nullptr)
	{
		m_pSphere[0]->Release();
		m_pSphere[0] = nullptr;
	}
	
	if (m_pField != nullptr)
	{
		m_pField->Release();
		m_pField = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void CGameDebug::Update(void)
{
	CGame::Update();
	CDebugProc::Print("\n[F2] : �f�o�b�O���[�h���I��\n");

	if (CInputKeyboard::GetKeyboardTrigger(DIK_F2))
	{//�G���^�[�L�[����������
		CApplication::SetMode(CApplication::Mode_Game_Race);
	}
}

//=====================================
// ��������
//=====================================
CGameDebug* CGameDebug::Create(void)
{
	CGameDebug* pGameDebug = new CGameDebug;

	if (FAILED(pGameDebug->Init()))
	{
		return nullptr;
	}

	return pGameDebug;
}