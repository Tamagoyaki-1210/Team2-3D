//=============================================================================
//
// fontString.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "fontString.h"
#include "Application.h"

static const int ScaleSpeed = 4;		// ScaleSpeed / 10.0f

//=====================================
// デフォルトコンストラクタ
//=====================================
CFontString::CFontString()
{

}

//=====================================
// デストラクタ
//=====================================
CFontString::~CFontString()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CFontString::Init(void)
{
	m_nNum = 0;
	m_fScale = 0.0f;
	m_bScale = false;
	m_bSellect = false;
	
	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CFontString::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		if (m_pFont[nCnt] != nullptr)
		{
			m_pFont[nCnt]->Release();
			m_pFont[nCnt] = nullptr;
		}
	}
}

//=====================================
// 更新処理
//=====================================
void CFontString::Update(void)
{
	SizeScale();
}

//=====================================
// サイズ変更処理
//=====================================
void CFontString::SizeScale(void)
{
	// 現在その選択肢が選択されている場合
	if (m_bSellect == true)
	{
		if (m_bScale == false)
		{
			m_fScale += ScaleSpeed / 10.0f;
			if (m_fScale > 5.0f)
			{
				m_bScale = true;
			}
		}
		else
		{
			m_fScale -= ScaleSpeed / 10.0f;
			if (m_fScale < -5.0f)
			{
				m_bScale = false;
			}
		}

		for (int nCnt = 0; nCnt < m_nNum; nCnt++)
		{
			m_pFont[nCnt]->SetSize(D3DXVECTOR2(m_sizeYuan.x + m_fScale, m_sizeYuan.y + m_fScale));
		}
	}
}

//=====================================
// サイズリセット処理
//=====================================
void CFontString::SizeReset(void)
{
	m_bSellect = false;
	m_fScale = 0.0f;
	m_bScale = false;
	for (int nCnt = 0; nCnt < m_nNum; nCnt++)
	{
		m_pFont[nCnt]->SetSize(D3DXVECTOR2(m_sizeYuan.x + m_fScale, m_sizeYuan.y + m_fScale));
	}
}

//=====================================
// サイズ変更処理
//=====================================
void CFontString::SetSellect(void)
{
	m_bSellect = true;
}

//=====================================
// 生成処理
//=====================================
CFontString* CFontString::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter)
{
	CFontString* pFontString = new CFontString;
	
	if (FAILED(pFontString->Init()))
	{
		return nullptr;
	}

	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		pFontString->m_pFont[nCnt]  = nullptr;
	}

	// string型の文字数を取得
	int nTex = strlen(letter.c_str());

	int nCnt = 0;
	float maxSizeX = size.x * 2;
	for (int nLatter = 0; nLatter < nTex; nLatter += 2)
	{
		// 現在位置から1文字進む処理
		std::string sLatter = letter.substr(nLatter , 2);

		// 文字を中央に配置し、string型から*char型を1文字ずつ取り出す
		if (nTex / 2 % 2 == 1)
		{
			pFontString->m_pFont[nCnt++] = CFont::Create(D3DXVECTOR3(pos.x - (maxSizeX * (nTex / 4)) + ((maxSizeX * nCnt)), pos.y, pos.z), size, sLatter.c_str());
		}
		else
		{
			pFontString->m_pFont[nCnt++] = CFont::Create(D3DXVECTOR3(pos.x - (maxSizeX * ((nTex / 4) - 1)) + (maxSizeX * nCnt) - (maxSizeX / 2), pos.y, pos.z), size, sLatter.c_str());
		}

		// 最初のサイズを登録する
		pFontString->m_sizeYuan = size;

		// 番号を割り振る
		pFontString->m_nNum++;
	}

	return pFontString;
}