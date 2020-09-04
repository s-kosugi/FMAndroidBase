/*==============================================================================*/
/*																				*/
/*	@file title	:	cTitleCursol.cpp											*/
/*  @brief		:	タイトルカーソルクラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cTitleCursol.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cTitleCursol::PRIORITY = 1000;
//==========================================================================================
// コンストラクタ
//==========================================================================================
cTitleCursol::cTitleCursol(IBaseObject * parent)
	: cSpriteObject(parent, "TitleCursol", "data\\graphic\\cursol.png")
{
}
//==========================================================================================
// 初期化
//==========================================================================================
void cTitleCursol::Initialize(void)
{
	cSpriteObject::Initialize();

	cTimer* timer = CreateObject<cTimer>(this, "CursolTimer");
	timer->Setup(1.5f);

	SetPriority(PRIORITY);
}

//==========================================================================================
// 更新
//==========================================================================================
void cTitleCursol::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("CursolTimer");
	if (timer)
	{
		if (timer->Finished()) timer->Reset();

		float addPos;
		addPos = fabs(sin(DEG_TO_RAD(Easing::Linear(timer->GetTime(), timer->GetLimit(), 360.0f, 0.0f))) * 30.0f);
		if (m_fAngle > 0) addPos = -addPos;

		m_vPos.x = m_vOriginPos.x + addPos;
	}

	cSpriteObject::Update();
}

//==========================================================================================
// 初期設定
//==========================================================================================
void cTitleCursol::Setup(const cVector2 & pos, float angle)
{
	m_vOriginPos = m_vPos = pos;
	m_fAngle = angle;
}
