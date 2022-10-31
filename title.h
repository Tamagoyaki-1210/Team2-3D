//=============================================================================
//
// title.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//---------------------------
//�N���X�錾
//---------------------------
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CTitle* Create(void);
private:
};

#endif // !_TITLE_H_
