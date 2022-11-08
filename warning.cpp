//=============================================================================
//
// warning.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "warning.h"
#include "application.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CWarning::CWarning()
{

}

CWarning::CWarning(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// デストラクタ
//=====================================
CWarning::~CWarning()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CWarning::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_nMaxBlink = 10;

	CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WARNINGS);
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CWarning::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//=====================================
// 更新処理
//=====================================
void CWarning::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	if (m_nLife <= 0)
	{
		BlinkColor();
	}
	else
	{
		m_nLife--;
	}
}

//=====================================
// 描画処理
//=====================================
void CWarning::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

//=====================================
// 描画処理
//=====================================
void CWarning::BlinkColor(void)
{
	if (m_bBlink)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_bBlink = !m_bBlink;
	m_nLife = 20.0f;
	m_nMaxBlink--;

	if (m_nMaxBlink <= 0)
	{
		Release();
	}
}

//=====================================
// 生成処理
//=====================================
CWarning* CWarning::Create(const D3DXVECTOR3 pos)
{
	CWarning* pWarning = new CWarning(5);		//生成(Priority = 5)

										//初期化処理
	if (FAILED(pWarning->Init()))
	{
		return nullptr;
	}

	pWarning->SetPos(pos);									//位置の設定
	pWarning->SetSize(D3DXVECTOR2(50.0f, 50.0f));			//サイズの設定
	pWarning->SetTexture(CObject::TEXTURE_EXCLAMATION);		//テクスチャの設定

	return pWarning;
}