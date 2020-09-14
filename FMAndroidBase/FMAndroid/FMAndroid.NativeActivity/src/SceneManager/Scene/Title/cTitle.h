#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitle.h													*/
/*  @brief		:	タイトルシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/12/02													*/
/*																				*/
/*==============================================================================*/

#include "..\IBaseScene.h"

//================================================================================================
// タイトルシーン
class cTitle : public IBaseScene
{
public:
	cTitle(IBaseObject* parent);
	~cTitle(void);

	void Initialize(void) override;
	void Update(void) override;
	IBaseObject* Finalize(void) override;

};
//================================================================================================