/*==============================================================================*/
/*																				*/
/*	@file title	:	cClearFont.cpp												*/
/*  @brief		:	�N���A�̕����N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/31													*/
/*																				*/
/*==============================================================================*/

#include "cClearFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cClearFont::PRIORITY = 1000;
const float cClearFont::MOVE_TIME = 1.5f;
const float cClearFont::FADE_TIME = 0.5f;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cClearFont::cClearFont(IBaseObject* parent)
	: cSpriteObject(parent, "ClearFont", "data\\graphic\\clearfont.png")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cClearFont::~cClearFont(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cClearFont::Initialize(void)
{
	SetPriority(PRIORITY);

	cGame* game = (cGame*)GetRoot();

	// �����E������ɔz�u
	SetPos(game->GetWindowWidth() + GetSpriteSize().x / 2.0f, game->GetWindowCenter().y);

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
//==========================================================================================
void cClearFont::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("ClearFontMoveTimer");
	cGame* game = (cGame*)GetRoot();
	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "ClearFontMoveTimer");
		timer->Setup(MOVE_TIME);
	}
	if (!timer->Finished())
	{
		float posx = Easing::OutBack(timer->GetTime(), timer->GetLimit(), game->GetWindowCenter().x, game->GetWindowWidth() + GetSpriteSize().x / 2.0f);
		SetPosX(posx);
	}
	else
	{
		SetPosX(game->GetWindowCenter().x);

		// �t�F�[�h�A�E�g����
		timer = (cTimer*)FindChild("ClearFontFadeTimer");
		if (!timer)
		{
			timer = CreateObject<cTimer>(this, "ClearFontFadeTimer");
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