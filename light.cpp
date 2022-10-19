//============================================================================
//
//���C�g�̏���[light.cpp] (�t�@�C���w�b�_�R�����g)
//Author:�J�{�N��
//============================================================================
#include "light.h"
#include "input.h"		//�쐬����input.h���C���N���[�h����
#include "application.h"
#include "renderer.h"

//============================================================================
//���C�g�̏���������
//============================================================================
void CLight::Init()
{
	//���C�g���N���A����
	ZeroMemory(&m_light[0], sizeof(m_light));

	//���C�g�̕�����ݒ�
	D3DXVECTOR3 vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	//���K������(�傫��1�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[0].Direction = vecDir;

	m_light[1].Direction = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
	m_light[2].Direction = D3DXVECTOR3(0.0f, 0.8f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	for (int nCnt = 0;nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̎�ނ�ݒ�(���s����)
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;		
		//���C�g�̊g�U����ݒ�(���C�g�̐F)
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_light[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================================
//���C�g�̏I������
//============================================================================
void CLight::Uninit()
{

}

//============================================================================
//���C�g�̍X�V����
//============================================================================
void CLight::Update()
{

}