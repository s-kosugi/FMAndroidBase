#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cGoFont.h													*/
/*  @brief		:	Go�����N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/cSpriteObject.h"

// Go�����N���X
class cGoFont : public cSpriteObject
{
public:
	cGoFont(IBaseObject* parent);

	void Initialize(void);
	void Update(void);
private:

	// �\���D��x
	static const int	PRIORITY;
};
