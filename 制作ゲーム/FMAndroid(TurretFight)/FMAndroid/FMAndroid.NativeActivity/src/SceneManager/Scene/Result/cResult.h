#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cResult.h													*/
/*  @brief		:	リザルトシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/20													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// リザルトシーン
class cResult : public IBaseScene
{
public:
	cResult(IBaseObject* parent);
	~cResult(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);
private:
	static const int RANK_B_BORDER;
	static const int RANK_A_BORDER;
	static const int RANK_S_BORDER;
};
//================================================================================================