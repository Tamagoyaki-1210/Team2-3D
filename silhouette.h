//=============================================================================
//
// silhouette.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _SILHOUETTE_H_
#define _SILHOUETTE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CSilhouette : public CObject_2D
{
public:
	CSilhouette();
	~CSilhouette() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Draw(void) override;

	static CSilhouette* Create(void);

private:

};




#endif
#pragma once
