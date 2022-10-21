//=============================================================================
//
// light.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "light.h"
#include "application.h"
#include "rendering.h"

CLight* CLight::m_pLight[CLight::MaxLight] = {};

//�R���X�g���N�^
CLight::CLight()
{
	for (int nCnt = 0; nCnt < CLight::MaxLight; nCnt++)
	{
		if (m_pLight[nCnt] == nullptr)
		{
			m_pLight[nCnt] = this;
			m_nIdx = nCnt;
			break;
		}
	}
}

//�f�X�g���N�^
CLight::~CLight()
{

}

//���C�g�̏���������
HRESULT CLight::Init(void)
{
	return S_OK;
}

//���C�g�̏I������
void CLight::Uninit(void)
{

}

//���C�g�̍X�V����
void CLight::Update(void)
{

}

void CLight::Release(void)
{
	int nIdx = m_nIdx;

	delete m_pLight[nIdx];
	m_pLight[nIdx] = nullptr;
}

const int CLight::GetLightIdx(void)
{
	return m_nIdx;
}




void CLight::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < CLight::MaxLight; nCnt++)
	{
		if (m_pLight[nCnt] != nullptr)
		{
			m_pLight[nCnt]->Release();
		}
	}
}