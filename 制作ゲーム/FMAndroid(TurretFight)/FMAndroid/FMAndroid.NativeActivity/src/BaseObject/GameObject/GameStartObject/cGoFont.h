#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cGoFont.h													*/
/*  @brief		:	Go文字クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/
#include "BaseObject/cSpriteObject.h"

// Go文字クラス
class cGoFont : public cSpriteObject
{
public:
	cGoFont(IBaseObject* parent);

	void Initialize(void);
	void Update(void);
private:

	// 表示優先度
	static const int	PRIORITY;
};
