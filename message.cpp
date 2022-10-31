//=============================================================================
//
// message.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "message.h"

//=====================================
// デフォルトコンストラクタ
//=====================================
CMessage::CMessage()
{

}

//=====================================
// デストラクタ
//=====================================
CMessage::~CMessage()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CMessage::Init(void)
{
	m_nMessageCounter = 0;
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CMessage::Uninit(void)
{
	if (m_pObj2D != nullptr)
	{
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}
}

//=====================================
// 更新処理
//=====================================
void CMessage::Update(void)
{
	// メッセージ表示時間をカウント
	if (m_nMessageCounter > 0)
	{
		m_nMessageCounter--;
	}
	else
	{
		m_nMessageCounter = 0;
		Uninit();
	}
}

//=====================================
// ゴールメッセージ表示処理
//=====================================
void CMessage::GoalMessage(void)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_GOAL);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_nMessageCounter = 120;
	}
}

//=====================================
// 生成処理
//=====================================
CMessage* CMessage::Create()
{
	CMessage* pMessage = new CMessage;

	//初期化処理
	if (FAILED(pMessage->Init()))
	{
		return nullptr;
	}

	return pMessage;
}