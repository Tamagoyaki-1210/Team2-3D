//=============================================================================
//
// choice.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "choice.h"
#include "Application.h"

static const int ScaleSpeed = 4;		// ScaleSpeed / 10.0f

//=====================================
// デフォルトコンストラクタ
//=====================================
CChoice::CChoice()
{

}

//=====================================
// デストラクタ
//=====================================
CChoice::~CChoice()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CChoice::Init(void)
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
void CChoice::Uninit(void)
{

}

//=====================================
// 更新処理
//=====================================
void CChoice::Update(void)
{
	SizeScale();
}

//=====================================
// サイズ変更処理
//=====================================
void CChoice::SizeScale(void)
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
void CChoice::SizeReset(void)
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
void CChoice::SetSellect(void)
{
	m_bSellect = true;
}

//=====================================
// 生成処理
//=====================================
CChoice* CChoice::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter)
{
	CChoice* pChoice = new CChoice;
	
	if (FAILED(pChoice->Init()))
	{
		return nullptr;
	}

	// string型の文字数を取得
	int nTex = strlen(letter.c_str());

	int nCnt = 0;
	for (int nLatter = 0; nLatter < nTex; nLatter += 2)
	{
		// 現在位置から1文字進む処理
		std::string sLatter = letter.substr(nLatter , 2);

		// 文字を中央に配置し、string型から*char型を1文字ずつ取り出す
		pChoice->m_pFont[nCnt++] = CFont::Create(D3DXVECTOR3(pos.x + (nLatter * size.x) - (nTex * size.x / 2), pos.y, pos.z), size, sLatter.c_str());
		
		// 最初のサイズを登録する
		pChoice->m_sizeYuan = size;

		// 番号を割り振る
		pChoice->m_nNum++;
	}

	return pChoice;
}