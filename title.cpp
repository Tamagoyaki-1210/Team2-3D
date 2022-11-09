//=============================================================================
//
// title.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "title.h"
#include "Application.h"
#include "meshfield.h"
#include "camera.h"
#include "playerModel.h"
#include "AnimateUI.h"
#include "halfsphere.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CTitle::CTitle()
{
	for (int nCnt = 0; nCnt < MAX_TITLE_MODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_pTitle = nullptr;
}

//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init(void)
{
	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-200.0f, 0.0f, 500.0f), Vec3Null, D3DXVECTOR2(100.0f, 100.0f), 30, 5);
	pField->SetTexture(CObject::TEXTURE_BLOCK);

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 200.0f, -600.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));
	}

	CHalfSphere* pSphere = CHalfSphere::Create(D3DXVECTOR3(0.0f, -8000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(D3DX_PI * -0.15f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);

	pSphere->LoadTexture("data\\TEXTURE\\sky002.jpg");

	m_pModel[0] = CPlayerModel::Create(D3DXVECTOR3(-125.0f, 50.0f, -280.0f), 0, false);
	m_pModel[1] = CPlayerModel::Create(D3DXVECTOR3(-37.5f, 50.0f, -280.0f), 1, false);
	m_pModel[2] = CPlayerModel::Create(D3DXVECTOR3(37.5f, 50.0f, -280.0f), 2, false);
	m_pModel[3] = CPlayerModel::Create(D3DXVECTOR3(125.0f, 50.0f, -280.0f), 3, false);

	CAnimateUI::UIAnimation animInfo;
	animInfo.deltaSize = D3DXVECTOR2(1.0f, 0.5f);
	animInfo.nChangeTime = 60;

	m_pTitle = CAnimateUI::Create(CObject::TEXTURE_TITLE_UI, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR2(320.0f, 160.0f),
		ColorWhite, animInfo);

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{

}

//=====================================
// 更新処理
//=====================================
void CTitle::Update(void)
{

}

//=====================================
// 生成処理
//=====================================
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	return pTitle;
}