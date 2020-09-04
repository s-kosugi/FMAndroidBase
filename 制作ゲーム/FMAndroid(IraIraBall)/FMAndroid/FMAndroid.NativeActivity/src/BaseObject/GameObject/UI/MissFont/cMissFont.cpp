/*==============================================================================*/
/*																				*/
/*	@file title	:	cMissFont.cpp												*/
/*  @brief		:	�~�X�̕����N���X											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/08/31													*/
/*																				*/
/*==============================================================================*/

#include "cMissFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cMissFont::PRIORITY = 1000;
const float cMissFont::FALL_TIME = 1.5f;

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cMissFont::cMissFont(IBaseObject* parent)
	: cSpriteObject(parent, "MissFont", "data\\graphic\\miss_font.png")
{
}

//==========================================================================================
// �f�X�g���N�^
//==========================================================================================
cMissFont::~cMissFont(void)
{
}

//==========================================================================================
// ������
//==========================================================================================
void cMissFont::Initialize(void)
{
	SetPriority(PRIORITY);

	cGame* game = (cGame*)GetRoot();
	// �����゠����ɔz�u
	SetPos(game->GetWindowCenter().x, -GetSpriteSize().y / 2.0f);

	cSpriteObject::Initialize();
}

//==========================================================================================
// �X�V
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