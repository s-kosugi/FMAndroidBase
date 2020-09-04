#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cEasingTest.h												*/
/*  @brief		:	イージング関数テストオブジェクトクラス						*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/03/18													*/
/*																				*/
/*==============================================================================*/

#include "..\..\cSpriteObject.h"
#include "..\..\..\Utility\Easing\Easing.h"

//================================================================================================
// イージング関数テストオブジェクトクラス
class cEasingTest : public cSpriteObject
{
public:
	cEasingTest(IBaseObject* parent);
	~cEasingTest(void);

	void Initialize(void);
	void Update(void);
	IBaseObject* Finalize(void);

	void SetEasingType(Easing::Type type);

private:
	// 表示優先度
	static const int	PRIORITY = 100;
	static const float	GOAL_POS;

	Easing::Type		m_eEasingType;
	double				m_dTotalTimer;
	double				m_dStartTimer;
};
//================================================================================================