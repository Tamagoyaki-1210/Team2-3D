//============================================================================
//
// ���f���̏���
// Author:�J�{�N��
//
//============================================================================
#include "player.h"		//�쐬����player.h���C���N���[�h����
#include "input.h"		//�쐬����input.h���C���N���[�h����
#include "camera.h"		//�쐬����camera.h���C���N���[�h����
//#include "shadow.h"		//�쐬����shadow.h���C���N���[�h����
#include "model.h"		//�쐬����model.h���C���N���[�h����
#include "meshfield.h"	//�쐬����meshfield.h���C���N���[�h����
//#include "fade.h"		//�쐬����fade.h���C���N���[�h����
#include "game.h"		//�쐬����game.h���C���N���[�h����
#include "application.h"
#include "texture.h"
#include "debugproc.h"

//****************************************************************************
//�O���[�o���ϐ�
//****************************************************************************
int g_nIndxShadowPlayer;				//�e�̃C���f�b�N�X
D3DXVECTOR3 g_rotDestPlayer;

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CPlayer::CPlayer() : CObjectX(OBJECT_PRIORITY_CENTER)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CPlayer::~CPlayer()
{

}

//============================================================================
//�v���C���[�̏���������
//============================================================================
void CPlayer::Init()
{
	CObjectX::Init("Data\\Model\\00_niwamaru_body.x");

	m_pModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 4.0f, -6.0f), "Data\\Model\\01_niwamaru_head.x");
	m_pModel[1] = CModel::Create(D3DXVECTOR3(2.0f, -2.0f, 0.0f), "Data\\Model\\02_niwamaru_legL.x");
	m_pModel[2] = CModel::Create(D3DXVECTOR3(-2.0f, -2.0f, 0.0f), "Data\\Model\\03_niwamaru_legR.x");

	m_nLife = PLAYER_LIFE;
	m_nPower = 0;
	m_fFlame = 0;
	m_fAttack = 0;
	m_bDamege = false;
	m_bLoop = false;
	m_bGround = false;
	m_motion = MOTION_NUTRAL;

	//m_pShadow = CShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//for (int nCntPlayerParts = 0; nCntPlayerParts < MAX_PLAYER_PARTS; nCntPlayerParts++)
	//{
	//	g_aPlayer.aParts[nCntPlayerParts].Worldmtx = D3DXMATRIX();	//���[���h�}�g���b�N�X
	//}

	////��(�e)�̃p�[�c
	//g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[0].nIdxModelParent = -1;

	////��(�q)�̃p�[�c
	//g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[1].nIdxModelParent = 0;

	////����(�q)�̃p�[�c
	//g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[2].nIdxModelParent = 0;

	////�E��(�q)�̃p�[�c
	//g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_aPlayer.aParts[3].nIdxModelParent = 0;

	//g_nIndxShadowPlayer = SetShadow(g_aPlayer.pos, g_aPlayer.rot);
}

//============================================================================
//�v���C���[�̏���������
//============================================================================
void CPlayer::Uninit()
{
	for (int nInd = 0; nInd < MAX_PLAYER_PARTS; nInd++)
	{
		m_pModel[nInd]->Uninit();
	}
	CObjectX::Uninit();
}

//============================================================================
//�v���C���[�̍X�V����
//============================================================================
void CPlayer::Update()
{
	for (int nInd = 0; nInd < MAX_PLAYER_PARTS; nInd++)
	{
		m_pModel[nInd]->Update();
	}
	CObjectX::Update();


	D3DXVECTOR3 pos = CObjectX::GetPos();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//�������畜�A���鏈��
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pos.y <= -100)
	{
		m_nLife--;
		//pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		pos.y = 20.0f;
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//���̑��̏���
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	D3DXVECTOR3 rot = CObjectX::GetRot();

	//�v���C���[�̑O��ʒu�𔽉f
	m_posOld = pos;

	//�d�͂��X�V(����������)
	m_move.y -= 4.0f;

	Input();

	//�ړ��ʂ��X�V(����������)
	m_move -= m_move * 0.1f;

	pos = CObjectX::GetPos();

	Motion();
	Collision();

	pos = CObjectX::GetPos();

	//�v���C���[�̈ʒu�X�V
	pos += m_move * 0.1f;

	SetPos(pos);
	//m_pModel->SetPos(pos);
	//m_pModel->SetRot(rot);

	//m_pShadow->SetShadow(D3DXVECTOR3(pos.x, 2.0f, pos.z));

}
//============================================================================
//�v���C���[�̕`�揈��
//============================================================================
void CPlayer::Draw()
{
	CApplication::GetTexture()->TextureType(CTexture::TYPE_PLAYER);
	CObjectX::Draw();
	for (int nInd = 0; nInd < MAX_PLAYER_PARTS; nInd++)
	{
		m_pModel[nInd]->Draw(GetWorldMtx());
	}
	CApplication::GetTexture()->TextureClear();

	//CDebugProc::Print("���݂̊p�xy : %f\n�ړI�̊p�xy : %f\n", CObjectX::GetRot().y, m_rotDest.y);

	////�p�[�c�̏���
	//for (int nCntPlayerParts = 0; nCntPlayerParts < MAX_PLAYER_PARTS; nCntPlayerParts++)
	//{
	//	//���[���h�}�g���b�N�X�̏�����
	//	D3DXMatrixIdentity(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx);

	//	//�����𔽉f(YaW : y,Pitch : x,Roll : z)
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer.aParts[nCntPlayerParts].rot.y, g_aPlayer.aParts[nCntPlayerParts].rot.x, g_aPlayer.aParts[nCntPlayerParts].rot.z);
	//	D3DXMatrixMultiply(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &mtxRot);

	//	//�ʒu�𔽉f
	//	D3DXMatrixTranslation(&mtxTrans, g_aPlayer.aParts[nCntPlayerParts].pos.x, g_aPlayer.aParts[nCntPlayerParts].pos.y, g_aPlayer.aParts[nCntPlayerParts].pos.z);
	//	D3DXMatrixMultiply(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &mtxTrans);

	//	if (g_aPlayer.aParts[nCntPlayerParts].nIdxModelParent == -1)
	//	{//�e���f���̃C���f�b�N�X��-1�̏ꍇ
	//		mtxParent = g_aPlayer.Worldmtx;				//�v���C���[�}�g���N�X��o�^
	//	}
	//	else
	//	{
	//		mtxParent = g_aPlayer.aParts[g_aPlayer.aParts[nCntPlayerParts].nIdxModelParent].Worldmtx;		//�e�̃}�g���N�X��o�^
	//	}
	//	//�e���f���̃}�g���b�N�X�Ƃ̊|���Z
	//	D3DXMatrixMultiply(&g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx, &mtxParent);

	//	//���[���h�}�g���b�N�X�̐ݒ�
	//	pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer.aParts[nCntPlayerParts].Worldmtx);

	//	//���݂̃}�e���A���̃|�C���^���擾
	//	pMat = (D3DXMATERIAL*)g_aPlayer.aParts[nCntPlayerParts].pBuffMat->GetBufferPointer();

	//	//�e�N�X�`���̓ǂݏo��
	//	for (int nCntMat = 0; nCntMat < (int)g_aPlayer.aParts[nCntPlayerParts].nNumMat; nCntMat++)
	//	{
	//		//�e�N�X�`���̐ݒ�
	//		pDevice->SetTexture(0, g_aPlayer.aParts[nCntPlayerParts].g_pTexture[g_aPlayer.tex]);

	//		//�}�e���A���̐ݒ�
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//		//���f���p�[�c�̕`��
	//		g_aPlayer.aParts[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
	//	}
	//}
}

//=====================================
//���͏���
//=====================================
void CPlayer::Input()
{
	//�L�[�{�[�h�擾
	CInput *pInput = CApplication::GetInput();

	//�J�����擾����
	CCamera *pCamera = CApplication::GetCamera();

	D3DXVECTOR3 rotPlayer = GetRot();
	D3DXVECTOR3 rotCamera = pCamera->GetRot();

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//�v���C���[�ړ�����
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pInput->GetKeyboardPress(DIK_W) == true)
	{//��O�ړ�
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}
		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			m_move.x += sinf(rotCamera.y - D3DX_PI / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y - D3DX_PI / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y + D3DX_PI * 3 / 4;
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			m_move.x += sinf(rotCamera.y + D3DX_PI / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y + D3DX_PI / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y - D3DX_PI * 3 / 4;
		}
		else
		{
			m_move.x += sinf(rotCamera.y) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y) * PLAYER_SPEAD;

			if (rotPlayer.y >= rotCamera.y)
			{
				m_rotDest.y = rotCamera.y + D3DX_PI;
			}
			else if (rotPlayer.y < rotCamera.y)
			{
				m_rotDest.y = rotCamera.y - D3DX_PI;
			}
		}
	}
	else if (pInput->GetKeyboardPress(DIK_S) == true)
	{//���ړ�
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}

		if (pInput->GetKeyboardPress(DIK_A) == true)
		{
			m_move.x += sinf(rotCamera.y - D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y - D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y + D3DX_PI / 4;
		}
		else if (pInput->GetKeyboardPress(DIK_D) == true)
		{
			m_move.x += sinf(rotCamera.y + D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y + D3DX_PI * 3 / 4) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y - D3DX_PI / 4;
		}
		else
		{
			m_move.x += sinf(rotCamera.y - D3DX_PI) * PLAYER_SPEAD;
			m_move.z += cosf(rotCamera.y - D3DX_PI) * PLAYER_SPEAD;
			m_rotDest.y = rotCamera.y;
		}
	}
	else if (pInput->GetKeyboardPress(DIK_A) == true)
	{//���ړ�
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}

		m_move.x += sinf(rotCamera.y - D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_move.z += cosf(rotCamera.y - D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_rotDest.y = rotCamera.y + D3DX_PI / 2;
	}
	else if (pInput->GetKeyboardPress(DIK_D) == true)
	{//�E�ړ�
		rotPlayer.y += (m_rotDest.y - rotPlayer.y) / 10;
		if (m_bLoop == false && m_bGround == true)
		{
			m_fFlame = 0;
			m_motion = MOTION_WARK;
			m_bLoop = true;
		}

		m_move.x += sinf(rotCamera.y + D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_move.z += cosf(rotCamera.y + D3DX_PI / 2.0f) * PLAYER_SPEAD;
		m_rotDest.y = rotCamera.y - D3DX_PI / 2;
	}

	if (m_bGround == true)
	{//�ڒn���̏���
		if (pInput->GetKeyboardTrigger(DIK_SPACE) == true)
		{//�W�����v
			m_motion = MOTION_JUMP;
			m_bLoop = true;
			m_fFlame = 0;
			m_move.y += 100.0f;
			m_bGround = false;		//���n������U�ɂ���
		}
	}

	//if (m_nPower < 3)
	//{
	//	if (pInput->GetKeyboardTrigger(DIK_RETURN) == true)
	//	{//�U�����[�V����
	//		m_motion = MOTION_ATTACK;
	//		m_bLoop = true;
	//		m_fFlame = 0;
	//	}
	//}
	//else if (m_fFlame >= 6.0f)
	//{
	//	if (pInput->GetKeyboardPress(DIK_RETURN) == true)
	//	{//�U�����[�V����
	//		m_motion = MOTION_ATTACK;
	//		m_bLoop = true;
	//		m_fFlame = 0;
	//	}
	//}
	//else
	//{
	//	m_fFlame++;
	//}
	SetRot(rotPlayer);
	RotNormalize();
}

//=====================================
//���[�V��������
//=====================================
void CPlayer::Motion()
{
	////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////�v���C���[���[�V��������
	////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	////�ʏ���
	//if (m_motion == MOTION_NUTRAL)
	//{
	//	m_fFlame++;

	//	if (m_fFlame <= 40)
	//	{
	//		//��(�e)�̃p�[�c
	//		g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.002f, 0.0f, 0.0f);
	//		//��(�q)�̃p�[�c
	//		g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.002f, 0.0f, 0.0f);
	//		//����(�q)�̃p�[�c
	//		g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//		//�E��(�q)�̃p�[�c
	//		g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//	}
	//	else if (g_aPlayer.fFlame <= 80)
	//	{
	//		//��(�e)�̃p�[�c
	//		g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.002f, 0.0f, 0.0f);
	//		//��(�q)�̃p�[�c
	//		g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.002f, 0.0f, 0.0f);
	//		//����(�q)�̃p�[�c
	//		g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//		//�E��(�q)�̃p�[�c
	//		g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.003f, 0.0f, 0.0f);
	//	}
	//	else
	//	{//���[�V�������Z�b�g
	//		g_aPlayer.fFlame = 0;
	//		//��(�e)�̃p�[�c
	//		g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//		g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		//��(�q)�̃p�[�c
	//		g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//		g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		//����(�q)�̃p�[�c
	//		g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//		g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		//�E��(�q)�̃p�[�c
	//		g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//		g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	}
	//}
	////�ʏ��ԈȊO�̏���
	//else if (g_aPlayer.bLoop == true)
	//{
	//	//���s���
	//	if (g_aPlayer.motion == MOTION_WARK)
	//	{
	//		g_aPlayer.fFlame++;

	//		if (g_aPlayer.fFlame <= 5)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 10)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 15)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 20)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.01f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.01f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//		}
	//		else
	//		{//���[�V�������Z�b�g
	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//	}
	//	//�W�����v���
	//	if (g_aPlayer.motion == MOTION_JUMP)
	//	{
	//		if (g_aPlayer.fFlame == 0)
	//		{
	//			g_aPlayer.fFlame++;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 2)
	//		{
	//			g_aPlayer.fFlame++;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 4)
	//		{
	//			g_aPlayer.fFlame++;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 6)
	//		{
	//			g_aPlayer.fFlame++;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(0.1f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(-0.1f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos += D3DXVECTOR3(0.0f, -0.6f, 0.0f);
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(-0.6f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos += D3DXVECTOR3(0.0f, -0.6f, 0.0f);
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(-0.6f, 0.0f, 0.0f);
	//		}
	//	}
	//	//���n���
	//	if (g_aPlayer.motion == MOTION_LANDING)
	//	{
	//		g_aPlayer.fFlame++;

	//		if (g_aPlayer.move.x >= 1.0f || g_aPlayer.move.z >= 1.0f)
	//		{
	//			//���[�V�������Z�b�g
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//			g_aPlayer.motion = MOTION_WARK;
	//		}
	//		else if (g_aPlayer.fFlame == 1)
	//		{//���[�V�������Z�b�g
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 5)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos += D3DXVECTOR3(0.0f, -0.4f, 0.0f);
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.08f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos += D3DXVECTOR3(0.0f, 0.4f, 0.0f);
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.10f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos += D3DXVECTOR3(0.0f, 0.4f, 0.0f);
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.10f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 15)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos -= D3DXVECTOR3(0.0f, -0.2f, 0.0f);
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.04f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos -= D3DXVECTOR3(0.0f, 0.2f, 0.0f);
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.05f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos -= D3DXVECTOR3(0.0f, 0.2f, 0.0f);
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.05f, 0.0f, 0.0f);
	//		}
	//		else
	//		{
	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//		}
	//	}
	//	//�U�����
	//	if (g_aPlayer.motion == MOTION_ATTACK)
	//	{
	//		if (g_aPlayer.fFlame == 0)
	//		{//�U������쐬(�ʒu, �ړ���, ��������, ���)
	//			//SetAttack
	//			//(
	//			//	D3DXVECTOR3(g_aPlayer.pos.x - sinf(g_aPlayer.rot.y) * 12.0f, (g_aPlayer.pos.y + 10.0f), g_aPlayer.pos.z - cosf(g_aPlayer.rot.y) * 12.0f),
	//			//	D3DXVECTOR3(0.0f, -10.0f, 0.0f),
	//			//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//			//	PLAYER_ATTACK,
	//			//	ATTACK_TYPE_PLAYER
	//			//);
	//		}
	//		g_aPlayer.fFlame++;
	//		if (g_aPlayer.fFlame <= 4)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot += D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot += D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 8)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].rot -= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].rot -= D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	//		}
	//		else
	//		{//���[�V�������Z�b�g
	//			g_aPlayer.fFlame = 0;
	//			g_aPlayer.bLoop = false;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�e���I��������
	//			pAttack->bUse = false;
	//		}
	//	}
	//	//��e���
	//	if (g_aPlayer.motion == MOTION_DAMEGE)
	//	{
	//		if (g_aPlayer.fFlame <= 0)
	//		{//���[�V�������Z�b�g
	//			g_aPlayer.fFlame = 0;
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//		g_aPlayer.fFlame++;

	//		if (g_aPlayer.fFlame <= 5)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.08f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 10)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot -= D3DXVECTOR3(-0.28f, 0.0f, 0.0f);
	//		}
	//		else if (g_aPlayer.fFlame <= 20)
	//		{
	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].rot += D3DXVECTOR3(-0.14f, 0.0f, 0.0f);
	//		}
	//		else
	//		{//���[�V�������Z�b�g
	//			g_aPlayer.bLoop = false;
	//			g_aPlayer.fFlame = 0;

	//			//��(�e)�̃p�[�c
	//			g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//			g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//��(�q)�̃p�[�c
	//			g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//			g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//����(�q)�̃p�[�c
	//			g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//			//�E��(�q)�̃p�[�c
	//			g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//			g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		}
	//	}
	//}
	//else
	//{//�ʏ��ԈȊO�̃��[�V�������I�������ꍇ
	//	g_aPlayer.fFlame = 0;
	//	//��(�e)�̃p�[�c
	//	g_aPlayer.aParts[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//	g_aPlayer.aParts[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//��(�q)�̃p�[�c
	//	g_aPlayer.aParts[1].pos = D3DXVECTOR3(0.0f, 4.0f, -6.0f);
	//	g_aPlayer.aParts[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//����(�q)�̃p�[�c
	//	g_aPlayer.aParts[2].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	//	g_aPlayer.aParts[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//�E��(�q)�̃p�[�c
	//	g_aPlayer.aParts[3].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	//	g_aPlayer.aParts[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPlayer.motion = MOTION_NUTRAL;		//�ʏ��Ԃɖ߂�
	//}
//CObjectX::SetPos(pos);
//CObjectX::SetRot(rot);
}

//=====================================
//�v���C���[�����蔻�菈��
//=====================================
void CPlayer::Collision()
{
	//�t�B�[���h�|�C���^����
	CMeshField *pField = CGame::GetField();

	//�v���C���[�̃T�C�Y�����߂鏈��
	D3DXVECTOR3 size = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	//�v���C���[�̃T�C�Y�̔��a�����߂鏈��
	D3DXVECTOR3 r_size = size / 2;

	D3DXVECTOR3 pos = CObjectX::GetPos();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//���̔��菈��
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//���b�V���t�B�[���h�����蔻��̏���
	//bool bIsGroundField = pField->FieldCollision(pos, m_posOld);

	////�G�L���������蔻��̏���
	//bool bIsGroundEnemy = EnemyCollision(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &r_size);

	////���f�������蔻��̏���
	//bool bIsGroundModel = ModelCollision(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &r_size);

	//���ڒn��
	if (pField->FieldCollision(pos, m_posOld) == true)
	{

		//�ڒn���Ă���Ȃ�
		//if (pField->GetVecNor() == pos.y)
		//{
		float f = pField->GetVecNor();
			//�v���C���[�̈ʒu.y�������グ�鏈��
			SetPos(D3DXVECTOR3(pos.x, f, pos.z));
				//m_move.y = 0.0f;

				if (m_bGround == false)
				{
					m_bGround = true;	//���n�����^�ɂ���
					m_bLoop = true;
					m_fFlame = 0;
					m_motion = MOTION_LANDING;
				}
			
		//}
	}
	////�e�̑傫���������Őݒ�
	//SetpositionShadow(g_nIndxShadowPlayer, D3DXVECTOR3(g_aPlayer.pos.x, -2.0f, g_aPlayer.pos.z),
	//	SHADOW_WIDTH + (g_aPlayer.pos.y / 2), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1 - (g_aPlayer.pos.y / 100)));
}

//=====================================
//���͏���
//=====================================
void CPlayer::RotNormalize()
{
	D3DXVECTOR3 rotPlayer = GetRot();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//�p�x�̐��K������
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (rotPlayer.y > D3DX_PI)
	{//���݂̊p�x��(PI)���傫���ꍇ
		rotPlayer.y -= D3DX_PI * 2;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{//���݂̊p�x��(-PI)��菬�����ꍇ
		rotPlayer.y += D3DX_PI * 2;
	}

	if (m_rotDest.y - rotPlayer.y > D3DX_PI)
	{//���݂̖ړI�l��(PI)���傫���ꍇ
		m_rotDest.y -= 2 * D3DX_PI;
	}
	else if (m_rotDest.y - rotPlayer.y < -D3DX_PI)
	{//���݂̖ړI�n��(-PI)��菬�����ꍇ
		m_rotDest.y += 2 * D3DX_PI;
	}
	SetRot(rotPlayer);
}

//=====================================
//�v���C���[��������
//=====================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float ParentY)
{
	CPlayer *pPlayer = new CPlayer;		//�v���C���[�|�C���^

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
		pPlayer->SetPos(pos);
		pPlayer->SetType(TYPE_PLAYER);
		pPlayer->SetPalentY(ParentY);
	}
	return pPlayer;
}