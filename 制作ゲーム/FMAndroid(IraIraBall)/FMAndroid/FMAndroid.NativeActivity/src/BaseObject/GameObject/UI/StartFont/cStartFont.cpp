/*==============================================================================*/
/*																				*/
/*	@file title	:	cStartFont.cpp												*/
/*  @brief		:	�X�^�[�g�̕����N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/31													*/
/*																				*/
/*==============================================================================*/

#include "cStartFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cStartFont::PRIORITY = 1000;
const float cStartFont::MOVE_TIME = 1.5f;
const float cStartFont::FADE_TIME = 0.5f;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cStartFont::cStartFont(IBaseObject* parent)
	: cSpriteObject(parent, "StartFont", "data\\graphic\\start_font.png")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cStartFont::~cStartFont(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cStartFont::Initialize(void)
{
	SetPriority(PRIORITY);

	cGame* game = (cGame*)GetRoot();

	// ������������ɔz�u
	SetPos(-GetSpriteSize().x / 2.0f, game->GetWindowCenter().y);

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
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

		// �t�F�[�h�A�E�g����
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