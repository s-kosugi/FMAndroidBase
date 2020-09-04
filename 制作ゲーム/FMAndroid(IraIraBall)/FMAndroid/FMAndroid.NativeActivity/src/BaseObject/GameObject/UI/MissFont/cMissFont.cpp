/*==============================================================================*/
/*																				*/
/*	@file title	:	cMissFont.cpp												*/
/*  @brief		:	ミスの文字クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/31													*/
/*																				*/
/*==============================================================================*/

#include "cMissFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cMissFont::PRIORITY = 1000;
const float cMissFont::FALL_TIME = 1.5f;

//==========================================================================================
// コンストラクタ
//==========================================================================================
cMissFont::cMissFont(IBaseObject* parent)
	: cSpriteObject(parent, "MissFont", "data\\graphic\\miss_font.png")
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cMissFont::~cMissFont(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cMissFont::Initialize(void)
{
	SetPriority(PRIORITY);

	cGame* game = (cGame*)GetRoot();
	// 中央上あたりに配置
	SetPos(game->GetWindowCenter().x, -GetSpriteSize().y / 2.0f);

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cMissFont::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("MissFontFallTimer");
	cGame* game = (cGame*)GetRoot();
	if (!timer)
	{
		timer = CreateObject<cTimer>(this,"MissFontFallTimer");
		timer->Setup(FALL_TIME);
	}
	if (!timer->Finished())
	{
		float posy = Easing::OutBounce(timer->GetTime(), timer->GetLimit(), game->GetWindowCenter().y, -GetSpriteSize().y / 2.0f);
		SetPosY(posy);
	}
	else
	{
		SetPosY(game->GetWindowCenter().y);
	}

	cSpriteObject::Update();
}