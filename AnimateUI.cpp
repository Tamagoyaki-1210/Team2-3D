//=============================================================================
//
// AnimateUI.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "AnimateUI.h"


const D3DXCOLOR CAnimateUI::targetCol[6] =
{
	ColorRed,
	ColorYellow,
	ColorGreen,
	ColorCyan,
	ColorBlue,
	ColorMagenta
};

//コンストラクタ
CAnimateUI::CAnimateUI()
{
	ZeroMemory(&m_AnimInfo, sizeof(m_AnimInfo));
	m_nCntAnim = 0;
	m_bAnimateColor = false;
	m_ntargetCol = 0;
	m_deltaCol = ColorNull;
}

//デストラクタ
CAnimateUI::~CAnimateUI()
{

}

//初期化処理
HRESULT CAnimateUI::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	ZeroMemory(&m_AnimInfo, sizeof(m_AnimInfo));
	m_nCntAnim = 0;
	m_bAnimateColor = false;
	m_deltaCol = ColorNull;
	m_ntargetCol = 0;

	return S_OK;
}

//終了処理
void CAnimateUI::Uninit(void)
{
	CObject_2D::Uninit();
}

//更新処理
void CAnimateUI::Update(void)
{
	if (m_AnimInfo.nChangeTime != 0)
	{
		m_nCntAnim++;

		if (m_nCntAnim >= m_AnimInfo.nChangeTime)
		{
			m_AnimInfo.deltaSize.x *= -1.0f;
			m_AnimInfo.deltaSize.y *= -1.0f;
			m_nCntAnim = 0;

			if (m_bAnimateColor)
			{
				m_ntargetCol++;

				if (m_ntargetCol >= 6)
				{
					m_ntargetCol = 0;
				}

				D3DXCOLOR target = targetCol[m_ntargetCol];
				D3DXCOLOR col = GetColor();

				m_deltaCol = target - col;
				m_deltaCol.r /= m_AnimInfo.nChangeTime;
				m_deltaCol.g /= m_AnimInfo.nChangeTime;
				m_deltaCol.b /= m_AnimInfo.nChangeTime;
				m_deltaCol.a /= m_AnimInfo.nChangeTime;
			}
		}

		D3DXVECTOR2 size = GetSize();

		size -= m_AnimInfo.deltaSize;

		if (size.x < 0.0f)
		{
			size.x = 0.0f;
		}
		if (size.y < 0.0f)
		{
			size.y = 0.0f;
		}

		SetSize(size);

		if (m_bAnimateColor)
		{
			D3DXCOLOR col = GetColor();

			col += m_deltaCol;

			SetColor(col);
		}
	}

	CObject_2D::Update();
}







//生成処理
CAnimateUI* CAnimateUI::Create(CObject::TextType texture, const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, UIAnimation animInfo)
{
	CAnimateUI* pUi = new CAnimateUI;

	if (FAILED(pUi->Init()))
	{
		return nullptr;
	}

	pUi->SetTexture(texture);
	pUi->SetPos(pos);
	pUi->SetSize(size);
	pUi->SetColor(col);
	pUi->SetPriority(5);
	pUi->m_AnimInfo = animInfo;

	return pUi;
}