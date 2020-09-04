/*==============================================================================*/
/*																				*/
/*	@file title	:	cOverTimer.cpp												*/
/*  @brief		:	ゲームメインタイマーUIクラス								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/26													*/
/*																				*/
/*==============================================================================*/

#include "cOverTimer.h"
#include "Utility/Number/cNumber.h"
#include "SceneManager/Scene/GameMain/cGameMain.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cOverTimer::PRIORITY = 500;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cOverTimer::cOverTimer(IBaseObject* parent)
	: cSpriteObject(parent, "OverTimer", "data\\graphic\\timerFrame.png")
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cOverTimer::~cOverTimer(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cOverTimer::Initialize(void)
{
	// このクラス自身はタイマーのフレームを表示する
	SetPriority(PRIORITY);

	// 分の部分の生成
	cNumber* num = CreateDrawObject<cNumber>(this, "MinuteNumber", "data\\graphic\\Number.png");
	num->CreateNumber(2, 0);
	num->SetPriority(PRIORITY + 10);
	// 秒の部分の生成
	num = CreateDrawObject<cNumber>(this, "SecondNumber", "data\\graphic\\Number.png");
	num->CreateNumber(2, 0);
	num->SetPriority(PRIORITY + 10);

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cOverTimer::Update(void)
{
	cNumber* num = (cNumber*)FindChild("MinuteNumber");
	cGameMain* gm = (cGameMain*)GetParent()->GetParent();
	if (num && gm)
	{
		num->SetValue(gm->GetOverTimeMinute());
		cVector2 vec = m_vPos;
		vec.x -= 25.0f;
		vec.y += 0.0f;
		num->SetPos(vec);
	}
	num = (cNumber*)FindChild("SecondNumber");
	if( num)
	{
		num->SetValue(gm->GetOverTimeSecond());
		cVector2 vec = m_vPos;
		vec.x += 50.0f;
		vec.y += 0.0f;
		num->SetPos(vec);
	}

	cSpriteObject::Update();
}