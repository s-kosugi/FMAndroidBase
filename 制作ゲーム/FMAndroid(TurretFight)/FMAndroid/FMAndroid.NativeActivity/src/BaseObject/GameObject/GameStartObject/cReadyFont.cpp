/*==============================================================================*/
/*																				*/
/*	@file title	:	cReadyFont.cpp												*/
/*  @brief		:	Ready�����N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cReadyFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"
#include "cGoFont.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cReadyFont::PRIORITY = 1000;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cReadyFont::cReadyFont(IBaseObject * parent)
	: cSpriteObject(parent, "ReadyFont", "data\\graphic\\ready.png")
	, m_eState(STATE::APPEAR)
{
}
//==========================================================================================
// ������
//==========================================================================================
void cReadyFont::Initialize(void)
{
	cSpriteObject::Initialize();

	cGame* game = (cGame*)GetRoot();
	m_vPos = game->GetWindowCenter();

	cTimer* timer = CreateObject<cTimer>(this,"ReadyTimer");
	timer->Setup(1.5f);


	SetPriority(PRIORITY);
}

//==========================================================================================
// �X�V
//==========================================================================================
void cReadyFont::Update(void)
{
	switch (m_eState)
	{
	case STATE::APPEAR: Appear(); break;
	case STATE::DISAPPEAR: Disappear(); break;
	default: break;
	}
	
	cSpriteObject::Update();
}

void cReadyFont::Appear(void)
{
	cTimer* timer = (cTimer*)FindChild("ReadyTimer");
	if (timer)
	{
		// �^�C�}�[�I������GoFont���Q�[�����C����e�Ƃ��Đ�������
		if (timer->Finished())
		{
			timer->Setup(0.5f);
			m_eState = STATE::DISAPPEAR;
			m_SrcRect.top = 0;
			return;
		}

		// ���X�ɏo��������
		m_SrcRect.top = (int)Easing::OutSine(timer->GetTime(), timer->GetLimit(), 0.0f, GetGraphichSize().y);
	}
}

void cReadyFont::Disappear(void)
{
	cTimer* timer = (cTimer*)FindChild("ReadyTimer");
	if (timer)
	{
		// �^�C�}�[�I������GoFont���Q�[�����C����e�Ƃ��Đ�������
		if (timer->Finished())
		{
			CreateObject<cGoFont>(GetParent())->Initialize();
			DeleteObject();
			return;
		}
		SetAlpha((int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 0.0f, 255));
	}
}
