/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartFont.cpp												*/
/*  @brief		:	スタートの文字クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/31													*/
/*																				*/
/*==============================================================================*/

#include "cStartFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cStartFont::PRIORITY = 1000;
const float cStartFont::MOVE_TIME = 1.5f;
const float cStartFont::FADE_TIME = 0.5f;
//==========================================================================================
// コンストラクタ
//==========================================================================================
cStartFont::cStartFont(IBaseObject* parent)
	: cSpriteObject(parent, "StartFont", "data\\graphic\\start_font.png")
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
cStartFont::~cStartFont(void)
{
}

//==========================================================================================
// 初期化
//==========================================================================================
void cStartFont::Initialize(void)
{
	SetPriority(PRIORITY);

	cGame* game = (cGame*)GetRoot();

	// 中央左あたりに配置
	SetPos(-GetSpriteSize().x / 2.0f, game->GetWindowCenter().y);

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cStartFont::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("StartFontMoveTimer");
	cGame* game = (cGame*)GetRoot();
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "StartFontMoveTimer");
		timer->Setup(MOVE_TIME);
	}
	if (!timer->Finished())
	{
		float posx = Easing::OutBack(timer->GetTime(), timer->GetLimit(), game->GetWindowCenter().x, -GetSpriteSize().x / 2.0f);
		SetPosX(posx);
	}
	else
	{
		SetPosX(game->GetWindowCenter().x);

		// フェードアウト処理
		timer = (cTimer*)FindChild("StartFontFadeTimer");
		if (!timer)
		{
			timer = CreateObject<cTimer>(this, "StartFontFadeTimer");
			timer->Setup(FADE_TIME);
		}
		if (!timer->Finished())
		{
			SetAlpha((int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 0.0f, 255.0f));
		}
		else
		{
			DeleteObject();
		}
	}

	

	cSpriteObject::Update();
}