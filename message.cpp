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
#include "game.h"
#include "application.h"

//静的メンバー変数宣言
bool CMessage::m_bStart;

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
	m_nNum = 0;
	m_bCountDown = false;
	m_bEndGame = false;
	m_bStart = false;
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
	m_nMessageCounter = 0;
	m_nNum = 0;
	m_bCountDown = false;
	m_bEndGame = false;
}

//=====================================
// 更新処理
//=====================================
void CMessage::Update(void)
{
	// ポーズ中でない場合のみ更新
	if (CApplication::GetPause() == false)
	{
		// カウントダウン処理でなければ
		if (m_bCountDown == false)
		{
			// メッセージ表示時間をカウント
			if (m_nMessageCounter > 0)
			{
				m_nMessageCounter--;
			}
			else
			{	// ゲーム終了判定
				if (m_bEndGame == true)
				{
					CGame::SetEndGame();
				}
				m_nMessageCounter = 0;
				m_bStart = true;
				Uninit();
			}
		}
		else
		{
			CountDown();
		}
	}
}

//=====================================
// カウントダウンメッセージ表示処理
//=====================================
void CMessage::SetCountDown(int nNum)
{
	if (m_bCountDown == false && m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NUMBERS);
		m_pObj2D->SetTextureParameter(1, 5, 3, INT_MAX);
		m_pObj2D->SetPriority(3);
		m_nNum = nNum;
		m_pObj2D->SetAnimPattern(nNum);
		m_nMessageCounter = CountDownLife;
		m_bCountDown = true;
	}
}

//=====================================
// カウントダウンメッセージ表示処理
//=====================================
void CMessage::CountDown()
{
	m_nMessageCounter--;
	if (m_nMessageCounter <= 0)
	{
		m_nNum--;
		// 現在位置が0より大きい場合
		if (m_nNum > 0)
		{
			m_nMessageCounter = CountDownLife;
			m_pObj2D->SetAnimPattern(m_nNum);
		}
		else
		{
			Uninit();
			StartMessage();
		}
	}
}

//=====================================
// スタートメッセージ表示処理
//=====================================
void CMessage::StartMessage(void)
{
	if (m_pObj2D == nullptr)
	{
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_START);
		m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObj2D->SetPriority(4);
		m_nMessageCounter = 120;
	}
}

//=====================================
// ゴールメッセージ表示処理
//=====================================
void CMessage::GoalMessage(int nMessageIdx)
{
	if (m_pObj2D == nullptr)
	{
		if (nMessageIdx == 0)
		{
			m_pObj2D = CObject_2D::Create();
			m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
			m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
			m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_GOAL);
			m_pObj2D->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pObj2D->SetPriority(4);
			m_nMessageCounter = 120;
			m_bEndGame = true;
		}
	}

	if (nMessageIdx == 1)
	{
		CObject_2D *m_pObject2D = CObject_2D::Create();
		m_pObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObject2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObject2D->SetTexture(CObject::TEXTURE_1P_WIN);
		m_pObject2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObject2D->SetPriority(4);
	}
	else if (nMessageIdx == 2)
	{
		CObject_2D *m_pObject2D = CObject_2D::Create();
		m_pObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObject2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObject2D->SetTexture(CObject::TEXTURE_2P_WIN);
		m_pObject2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObject2D->SetPriority(4);
	}
	else if (nMessageIdx == 3)
	{
		CObject_2D *m_pObject2D = CObject_2D::Create();
		m_pObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObject2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObject2D->SetTexture(CObject::TEXTURE_3P_WIN);
		m_pObject2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObject2D->SetPriority(4);
	}
	else if (nMessageIdx == 4)
	{
		CObject_2D *m_pObject2D = CObject_2D::Create();
		m_pObject2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObject2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObject2D->SetTexture(CObject::TEXTURE_4P_WIN);
		m_pObject2D->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pObject2D->SetPriority(4);
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