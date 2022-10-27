//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "font.h"
#include <string>
#include <map>

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CMenu::CMenu()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CMenu::~CMenu()
{

}

//=====================================
// ����������
//=====================================
HRESULT CMenu::Init(void)
{
	CChoice::Create();

	//CFont *pFont[2][20];
	//int nNumFont = 0;

	//// �����[��
	//std::string nStr[4] = { "��", "��", "�[", "��" };
	//for (int i = 0; i < 4; i++)
	//{
	//	pFont[nNumFont][i] = CFont::Create(D3DXVECTOR2(-500.0f, -50.0f), D3DXVECTOR2(30.0f, 30.0f), nStr[i], 5, i, 4);
	//}
	//nNumFont++;

	//// �����
	//int nTex2[3] = { 4, 45, 41 };
	//for (int i = 0; i < 3; i++)
	//{
	//	pFont[nNumFont][i] = CFont::Create(D3DXVECTOR2(0.0f, 60.0f), D3DXVECTOR2(30.0f, 30.0f), nTex2[i], 5, i, 3);
	//}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CMenu::Uninit(void)
{

}

//=====================================
// �X�V����
//=====================================
void CMenu::Update(void)
{

}

//=====================================
// ��������
//=====================================
CMenu* CMenu::Create(void)
{
	CMenu* pMenu = new CMenu;

	if (FAILED(pMenu->Init()))
	{
		return nullptr;
	}

	return pMenu;
}