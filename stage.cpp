//=============================================================================
//
// stage.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "stage.h"
#include "application.h"
#include "meshfield.h"
#include "model.h"
#include "player.h"
#include "debugProc.h"
#include "halfsphere.h"
#include "CylinderHitbox.h"
#include "BoxHitbox.h"
#include "coin.h"
#include "goal.h"
#include "camera.h"
#include "SpikeBall.h"
#include "lavaFloor.h"
#include "score.h"
#include "message.h"
#include "silhouette.h"
#include "environment.h"
#include "warning.h"
#include <string>

#include "trampoline.h"
#include "bouncePole.h"
#include "stoneSpawner.h"
#include "icePillarSpawner.h"
#include "inputKeyboard.h"

//�A�j���[�V�������̃e�L�X�g�t�@�C���̑��΃p�X
char* CStage::m_pStagePass[STAGE_TYPE_MAX] =
{
	{ "data\\STAGESET\\StageSet1.txt" },
	{ "data\\STAGESET\\StageSet2.txt" },
	{ "data\\STAGESET\\StageSet3.txt" },
};

CMeshfield *CStage::m_pField = nullptr;
CHalfSphere* CStage::m_pSphere[PLAYER_MAX] = {};
CPlayer* CStage::m_pPlayer[PLAYER_MAX] = {};
CMessage* CStage::m_pMessage = nullptr;
bool CStage::m_bResult = false;

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CStage::CStage()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CStage::~CStage()
{

}

//=====================================
// ����������
//=====================================
HRESULT CStage::Init(void)
{
	// �X�t�B�A���b�V��
	m_pSphere[0] = CHalfSphere::Create(D3DXVECTOR3(0.0f, -2000.0f, 1000.0f), D3DXVECTOR3(30000.0f, 0.0f, 30000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CHalfSphere::SPHERE_UP);

	m_pSphere[1] = CHalfSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(35000.0f, 0.0f, 35000.0f), D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI), CHalfSphere::SPHERE_DOWN);

	// �X�e�[�W�ǂݍ��ݏ���
	Load();

	CGoal::Create(D3DXVECTOR3(0.0f, -100.0f, 900.0f));

	//CBouncePole::Create(D3DXVECTOR3(-145.0f, -150.0f, 350.0f));

	// �v���C���[�̐���
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		m_pPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-75.0f + (50 * nCnt), -100.0f, ((m_pField->GetLine() - 20) * -70.0f) - 200.0f), nCnt);
	}

	// ���b�Z�[�W�̐���
	m_pMessage = CMessage::Create();

	// �J�E���g�_�E�����b�Z�[�W�\��
	m_pMessage->SetCountDown(3);

	if (CApplication::GetCamera() != nullptr)
	{
		CApplication::GetCamera()->SetPos(D3DXVECTOR3(0.0f, 0.0f, ((m_pField->GetLine() - 20) * -70.0f) -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));
	}

	//CTrampoline::Create(D3DXVECTOR3(-70.0f, -150.0f, 150.0f));
	//CStoneSpawner::Create(D3DXVECTOR3(0.0f, 400.0f, 150.0f), -149.9f, 135.0f, 100.0f, 30);
	CIcePillarSpawner::Create(D3DXVECTOR3(0.0f, 400.0f, 150.0f), -149.9f, 135.0f, 100.0f, 150);

	CSilhouette::Create();

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CStage::Uninit(void)
{
	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pPlayer[nCnt] != nullptr)
		{
			m_pPlayer[nCnt]->Release();
			m_pPlayer[nCnt] = nullptr;
		}
	}

	if (m_pSphere[0] != nullptr)
	{
		m_pSphere[0]->Release();
		m_pSphere[0] = nullptr;
	}

	if (m_pField != nullptr)
	{
		m_pField->Release();
		m_pField = nullptr;
	}

	if (m_pMessage != nullptr)
	{
		m_pMessage->Uninit();
		delete m_pMessage;
		m_pMessage = nullptr;
	}

	m_bResult = false;
}

//=====================================
// �X�V����
//=====================================
void CStage::Update(void)
{
	if (m_pMessage != nullptr)
	{
		m_pMessage->Update();
	}

	//P�Ń|�[�Y�؂�ւ�
	if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
	{
		CWarning::Create(D3DXVECTOR3(1225.0f, 55.0f, 0.0f));
	}


	GameResult();
}

//=====================================
// ���f���ݒ菈��
//=====================================
void CStage::SetModelType(D3DXVECTOR3 pos, ModelType type)
{
	switch (type)
	{
	case CStage::MODEL_SPIKEBALL:
	{
		// �S��
		CSpikeBall::Create(pos);
	}
	break;
	case CStage::MODEL_BOUNCEPOLE:
	{
		// ���˕Ԃ�~��
		CBouncePole::Create(pos);
	}
	break;
	case CStage::MODEL_TRAMPOLINE:
	{
		// ���˕Ԃ�~��
		CTrampoline::Create(pos);
	}
	break;
	default:
		break;
	}
}

//=====================================
// ���ݒ菈��
//=====================================
void CStage::SetFloorType(D3DXVECTOR3 pos, FloorType type)
{
	switch (type)
	{
	case CStage::FLOOR_LAVA:
	{
		// �n�⏰
		CLavaFloor::Create(pos);
	}
	break;
	default:
		break;
	}
}

//=====================================
// �Q�[���̃��U���g����
//=====================================
void CStage::GameResult()
{
	// ���U���g�������s���Ă��Ȃ��ꍇ
	if (!m_bResult)
	{
		bool bGoal[PLAYER_MAX] = {};
		bool bRot[PLAYER_MAX] = {};

		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			bGoal[nCnt] = m_pPlayer[nCnt]->GetGoal();
			bRot[nCnt] = m_pPlayer[nCnt]->GetRotCmp();
		}

		// �S�����S�[�� & �S�����U��������������ꍇ
		if (bGoal[0] && bGoal[1] && bGoal[2] && bGoal[3]
			&& bRot[0] && bRot[1] && bRot[2] && bRot[3])
		{
			m_bResult = true;
			ScoreComparison();
		}
	}
}

//=====================================
// �X�R�A��r����
//=====================================
void CStage::ScoreComparison()
{
	D3DXVECTOR2 PlayerScore[PLAYER_MAX] = {};
	D3DXVECTOR2 nChange;

	for (int nCount = 0; nCount < PLAYER_MAX; nCount++)
	{
		PlayerScore[nCount].x = (float)CScore::GetScore(nCount);
		PlayerScore[nCount].y = (float)nCount;
	}

	// 2�̃v���C���[�X�R�A���\�[�g����(�~��)
	for (int nCount = 0; nCount < PLAYER_MAX - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < PLAYER_MAX; nCount2++)
		{
			if (PlayerScore[nCount].x < PlayerScore[nCount2].x)
			{
				// �X�R�A�̓���ւ�
				nChange = PlayerScore[nCount2];
				PlayerScore[nCount2] = PlayerScore[nCount];
				PlayerScore[nCount] = nChange;
			}
		}
	}

	// �����l�������߂�
	if ((int)PlayerScore[3].x == (int)PlayerScore[0].x)
	{
		m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[2].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[3].y]->SetWinner(true);

		m_pMessage->GoalMessage(0);
	}
	else if ((int)PlayerScore[2].x == (int)PlayerScore[0].x)
	{
		m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[2].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[3].y]->SetWinner(false);

		m_pMessage->GoalMessage(0);
	}
	else if ((int)PlayerScore[1].x == (int)PlayerScore[0].x)
	{
		m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[1].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[2].y]->SetWinner(false);
		m_pPlayer[(int)PlayerScore[3].y]->SetWinner(false);

		m_pMessage->GoalMessage(0);
	}
	else
	{
		m_pPlayer[(int)PlayerScore[0].y]->SetWinner(true);
		m_pPlayer[(int)PlayerScore[1].y]->SetWinner(false);
		m_pPlayer[(int)PlayerScore[2].y]->SetWinner(false);
		m_pPlayer[(int)PlayerScore[3].y]->SetWinner(false);

		m_pMessage->GoalMessage((int)PlayerScore[0].y + 1);
	}
}

//=====================================
// ��������
//=====================================
CStage* CStage::Create(void)
{
	CStage* pStage = new CStage;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}

//=====================================
//�ǂݍ��ݏ���
//=====================================
void CStage::Load()
{
	char aStr[256] = {};		//�ǂݍ��ޗp������
								//�t�@�C�����J��
	FILE* pFile = fopen(m_pStagePass[(StageType)CApplication::GetStageSelect()], "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", aStr);

		while (strncmp(aStr, "END_SCRIPT", 10) != 0)
		{//������̏������Ɠǂݍ���
			fscanf(pFile, "%s", aStr);

			if (strncmp(aStr, "FIELDSET", 8) == 0)
			{// ���b�V���t�B�[���h�ǂݍ���
				while (strncmp(aStr, "END_FIELDSET", 12) != 0)
				{
					fscanf(pFile, "%s", aStr);

					if (strncmp(aStr, "LINE", 3) == 0)
					{//���̌�ɃR�����g
						fscanf(pFile, "%s", aStr);
						fscanf(pFile, "%s", aStr);

						std::string s = aStr;			// std::string�ɕϊ�����
						int nLine = std::stoi(s);		//int�ɕϊ�����

						// ���b�V���t�B�[���h�̐���
						m_pField = CMeshfield::Create(D3DXVECTOR3(-135.0f, -150.0f, 1100.0f), Vec3Null, D3DXVECTOR2(30.0f, 70.0f), nLine, 10, 3);
					}
					else if (strncmp(aStr, "TEXTURE_NAME", 12) == 0)
					{//���̌�ɃR�����g
						fscanf(pFile, "%s", aStr);
						fscanf(pFile, "%s", aStr);
						m_pField->LoadTexture(aStr);
					}
					else if (strncmp(aStr, "TEXTURE_TILING", 14) == 0)
					{//���̌�ɃR�����g
						fscanf(pFile, "%s", aStr);
						fscanf(pFile, "%s", aStr);			// ���b�V���t�B�[���h�̃^�C�����O��ǂݍ��ޏ���
						std::string s = aStr;				// std::string�ɕϊ�����
						float fTaling = std::stof(s);		//float�ɕϊ�����
						m_pField->SetTextureTiling(fTaling);
					}
				}
			}
			else if (strncmp(aStr, "SPHERESET", 9) == 0)
			{// �n�[�t�X�t�B�A���b�V���ǂݍ���
				int nSphere = 0;
				while (strncmp(aStr, "END_SPHERESET", 13) != 0)
				{
					fscanf(pFile, "%s", aStr);
					while (strncmp(aStr, "END_SPHERE", 10) != 0)
					{
						fscanf(pFile, "%s", aStr);
						if (strncmp(aStr, "SPHERE", 6) == 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "TEXTURE_NAME", 12) == 0)
							{
								fscanf(pFile, "%s", aStr);
								fscanf(pFile, "%s", aStr);
								m_pSphere[nSphere]->LoadTexture(aStr);
							}
						}
					}
					nSphere++;
				}
			}
			else if (strncmp(aStr, "COINALLSET", 10) == 0)
			{// �R�C���ǂݍ���
				int nCoinType = 0;
				while (strncmp(aStr, "END_COINALLSET", 14) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "COINTYPESET", 11) == 0)
					{
						fscanf(pFile, "%s", aStr);
						while (strncmp(aStr, "END_COINTYPESET", 15) != 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "COINSET", 7) == 0)
							{
								while (strncmp(aStr, "END_COINSET", 11) != 0)
								{
									fscanf(pFile, "%s", aStr);
									if (strncmp(aStr, "COIN", 4) == 0)
									{
										while (strncmp(aStr, "END_COIN", 8) != 0)
										{
											fscanf(pFile, "%s", aStr);
											if (strncmp(aStr, "POS", 3) == 0)
											{
												fscanf(pFile, "%s", aStr);
												fscanf(pFile, "%s", aStr);	//X���W�̓ǂݍ��ޏ���
												std::string s = aStr;		//std::string�ɕϊ�����
												float x = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Y���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float y = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Z���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float z = std::stof(s);		//float�ɕϊ�����

												CCoin::Create(D3DXVECTOR3(x, y, z), (CCoin::COIN_TYPE)nCoinType);
											}
										}
									}
								}
							}
						}
						nCoinType++;
					}
				}
			}
			else if (strncmp(aStr, "MODELALLSET", 11) == 0)
			{// ��Q�����f���ǂݍ���
				int nModelType = 0;
				while (strncmp(aStr, "END_MODELALLSET", 15) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "MODELTYPESET", 12) == 0)
					{
						fscanf(pFile, "%s", aStr);
						while (strncmp(aStr, "END_MODELTYPESET", 16) != 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "MODELSET", 8) == 0)
							{
								while (strncmp(aStr, "END_MODELSET", 12) != 0)
								{
									fscanf(pFile, "%s", aStr);
									if (strncmp(aStr, "MODEL", 5) == 0)
									{
										while (strncmp(aStr, "END_MODEL", 9) != 0)
										{
											fscanf(pFile, "%s", aStr);
											if (strncmp(aStr, "POS", 3) == 0)
											{
												fscanf(pFile, "%s", aStr);
												fscanf(pFile, "%s", aStr);	//X���W�̓ǂݍ��ޏ���
												std::string s = aStr;		//std::string�ɕϊ�����
												float x = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Y���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float y = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Z���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float z = std::stof(s);		//float�ɕϊ�����

												SetModelType(D3DXVECTOR3(x, y, z), (ModelType)nModelType);
											}
										}
									}
								}
							}
						}
						nModelType++;
					}
				}
			}
			else if (strncmp(aStr, "FLOORALLSET", 11) == 0)
			{// �����f���ǂݍ���
				int nFloorType = 0;
				while (strncmp(aStr, "END_FLOORALLSET", 15) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "FLOORTYPESET", 12) == 0)
					{
						fscanf(pFile, "%s", aStr);
						while (strncmp(aStr, "END_FLOORTYPESET", 16) != 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "FLOORSET", 8) == 0)
							{
								while (strncmp(aStr, "END_FLOORSET", 12) != 0)
								{
									fscanf(pFile, "%s", aStr);
									if (strncmp(aStr, "FLOOR", 5) == 0)
									{
										while (strncmp(aStr, "END_FLOOR", 9) != 0)
										{
											fscanf(pFile, "%s", aStr);
											if (strncmp(aStr, "POS", 3) == 0)
											{
												fscanf(pFile, "%s", aStr);
												fscanf(pFile, "%s", aStr);	//X���W�̓ǂݍ��ޏ���
												std::string s = aStr;		//std::string�ɕϊ�����
												float x = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Y���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float y = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Z���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float z = std::stof(s);		//float�ɕϊ�����

												SetFloorType(D3DXVECTOR3(x, y, z), (FloorType)nFloorType);
											}
										}
									}
								}
							}
						}
						nFloorType++;
					}
				}
			}
			else if (strncmp(aStr, "ENVIRONMENTALLSET", 17) == 0)
			{// �����f���ǂݍ���
				int nEnvironmentType = 0;
				while (strncmp(aStr, "END_ENVIRONMENTALLSET", 21) != 0)
				{
					fscanf(pFile, "%s", aStr);
					if (strncmp(aStr, "ENVIRONMENTTYPESET", 18) == 0)
					{
						fscanf(pFile, "%s", aStr);
						while (strncmp(aStr, "END_ENVIRONMENTTYPESET", 22) != 0)
						{
							fscanf(pFile, "%s", aStr);
							if (strncmp(aStr, "ENVIRONMENTSET", 14) == 0)
							{
								while (strncmp(aStr, "END_ENVIRONMENTSET", 18) != 0)
								{
									fscanf(pFile, "%s", aStr);
									if (strncmp(aStr, "ENVIRONMENT", 11) == 0)
									{
										while (strncmp(aStr, "END_ENVIRONMENT", 15) != 0)
										{
											fscanf(pFile, "%s", aStr);
											if (strncmp(aStr, "POS", 3) == 0)
											{
												fscanf(pFile, "%s", aStr);
												fscanf(pFile, "%s", aStr);	//X���W�̓ǂݍ��ޏ���
												std::string s = aStr;		//std::string�ɕϊ�����
												float x = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Y���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float y = std::stof(s);		//float�ɕϊ�����

												fscanf(pFile, "%s", aStr);	//Z���W�̓ǂݍ��ޏ���
												s = aStr;					//std::string�ɕϊ�����
												float z = std::stof(s);		//float�ɕϊ�����

												CEnvironment::Create(D3DXVECTOR3(x, y, z), (CEnvironment::EnvironmentType)nEnvironmentType);
											}
										}
									}
								}
							}
						}
						nEnvironmentType++;
					}
				}
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);
}