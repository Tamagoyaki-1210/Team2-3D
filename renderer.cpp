//=============================================================================
//
// �����_���[
// Author : tanimoto kosuke
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "renderer.h"
#include "application.h"
#include "object.h"
//#include "effect.h"
//#include "UI.h"
#include "camera.h"
#include <stdio.h>

#ifdef _DEBUG
#include <tchar.h> // _T
#include "debugproc.h"
#endif // _DEBUG

//****************************************************************************
//�}�N����`
//****************************************************************************
#define TEXT_WIDTH			(10)		//�e�L�X�g�̉���
#define TEXT_HEIGHT			(24)		//�e�L�X�g�̍���

//-----------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------
int GetFPS();		//FPS�擾����

//*****************************************************************************
// �f�o�b�O�p�O���[�o���ϐ�
//*****************************************************************************
#ifdef _DEBUG
LPD3DXFONT pFont;			// �t�H���g�I�u�W�F�N�g
bool g_MeshDebug = false;	// ���b�V���f�o�b�O
bool g_TextDebug = true;	// �e�L�X�g�f�o�b�O
CDebugProc *CRenderer::m_pDebugProc = nullptr;	// �f�o�b�O�t�H���g�|�C���^
#endif // _DEBUG

//=====================================
//�f�t�H���g�R���X�g���N�^
//=====================================
CRenderer::CRenderer() : m_pD3D(nullptr), m_pD3DDevice(nullptr), m_pFont(nullptr)
{
	
}

//=====================================
//�f�X�g���N�^
//=====================================
CRenderer::~CRenderer()
{

}

//=====================================
//����������
//=====================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//�A���t�@�u�����h�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�A���t�@�u�����h�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�A���t�@�u�����h�̐ݒ�

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�e�N�X�`���̑傫���ɍ��킹���Y��ɓ\��
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�e�N�X�`���̑傫���ɍ��킹���Y��ɓ\��
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//�e�N�X�`�����J��Ԃ��ɓ\��
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//�e�N�X�`�����J��Ԃ��ɓ\��

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//�|���S���ƃe�N�X�`���̃A���t�@�l��������
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//�|���S���ƃe�N�X�`���̃A���t�@�l��������(�e�N�X�`���w��)
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//�|���S���ƃe�N�X�`���̃A���t�@�l��������(�|���S���w��)
	
	// ���C���[�t���[���ݒ�
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

#ifdef _DEBUG
																			//�t�H���g
	D3DXCreateFont(
		m_pD3DDevice,				// Direct3D�f�o�C�X
		TEXT_HEIGHT,				// ����
		TEXT_WIDTH,					// ��
		FW_REGULAR,					// �t�H���g�̑��� ����
		NULL,						// ����
		FALSE,						// �Α�
		SHIFTJIS_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x�͕���
		PROOF_QUALITY,				// �����i�����d��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~��
		TEXT("�l�r�o�S�V�b�N"),	// �t�H���g��
		&pFont);					// ID3DXFont�|�C���^

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);

	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif
	return S_OK;
}

//=====================================
//�I������
//=====================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}

	// �f�o�b�O�t�H���g
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

#endif // _DEBUG

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=====================================
//�X�V����
//=====================================
void CRenderer::Update(void)
{
	// �I�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();
	//// �G�t�F�N�g�̍X�V����
	//CEffect::UpdateAll();
	//// UI�̍X�V����
	//CUI::UpdateAll();
}

//=====================================
//�`�揈��
//=====================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CApplication::GetCamera()->SetCamera(m_pD3DDevice);		//�J�����̐ݒ菈��
		//�I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();
		//�G�t�F�N�g�̕`�揈��
		//CEffect::DrawAll();
		////�G�t�F�N�g�̕`�揈��
		//CUI::DrawAll();

#ifdef _DEBUG
		//�f�o�b�O�t�H���g�̕`�揈��
		CDebugProc::Draw();
#endif // _DEBUG
//#ifdef _DEBUG
//		// FPS�\��
//		DrawFPS();
//
//		char aStr[MAX_TEXT][256];	//�e�L�X�g�̕�����
//
//		//sprintf(aStr[0], "<�Q�[�����Ԍo�߃t���[��>\n");
//		//sprintf(aStr[1], "[%d] : f�o��\n", CStage::GetGameTimer());
//
//		for (int nCntText = 0; nCntText < MAX_TEXT; nCntText++)
//		{
//			//�e�L�X�g�ʒu
//			RECT rc = {
//				0,		// �����x���W
//				100 + (TEXT_HEIGHT * nCntText),		// �����y���W
//				SCREEN_WIDTH,	// �E����x���W
//				SCREEN_HEIGHT	// �E����y���W
//			};
//
//			// �e�L�X�g�`��
//			pFont->DrawText(
//				NULL,					// NULL
//				&aStr[nCntText][0],		// �`��e�L�X�g
//				-1,						// �S�ĕ\��
//				&rc,						// �\���͈�
//				DT_LEFT,					// ����
//				D3DCOLOR_XRGB(255, 255, 255)	// ���F
//			);
//		}
//
//#endif // _DEBUG
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=====================================
//FPS�`�揈��
//=====================================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];
	int nCountFPS = GetFPS();

	wsprintf(str, _T("FPS : %d\n"), nCountFPS);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x0f, 0xff, 0xff));
}
#endif // _DEBUG

//=====================================
//�f�o�C�X�擾����
//=====================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}