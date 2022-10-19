//=============================================================================
// 
// �T�E���h
// Author : Tanimoto Kosuke
// 
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "xaudio2.h"	// ���y�����ɕK�v

// *****************************************************************************
// �T�E���h�t�@�C��
// *****************************************************************************
enum Sound_Label
{
	SOUND_LABEL_BGM_TITLE = 0,		// BGM�^�C�g��
	SOUND_LABEL_BGM_STAGE1,
	SOUND_LABEL_SE_JUMP,
	SOUND_LABEL_MAX,
};

class CSound
{
public:
	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit();
	static HRESULT PlaySound(Sound_Label label);
	static void StopSound(Sound_Label label);
	static void StopSound(void);

private:
	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
