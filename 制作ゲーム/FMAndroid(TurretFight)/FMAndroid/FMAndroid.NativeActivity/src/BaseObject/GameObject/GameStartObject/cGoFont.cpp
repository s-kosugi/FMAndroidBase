/*==============================================================================*/
/*																				*/
/*	@file title	:	cGoFont.cpp													*/
/*  @brief		:	Go�����N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cGoFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// �萔
//==========================================================================================
const int	cGoFont::PRIORITY = 1000;
//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cGoFont::cGoFont(IBaseObject * parent)
	: cSpriteObject(parent, "GoFont", "data\\graphic\\go.png")
{
}
//==========================================================================================
// ������
//==========================================================================================
void cGoFont::Initialize(void)
{
	cSpriteObject::Initialize();

	cGame* game = (cGame*)GetRoot();
	m_vPos = game->GetWindowCenter();

	//�g�債�Ȃ�Go�̕����𐶐�����B
	cSpriteObject* sorce = CreateDrawObject<cSpriteObject>(this, "GoFontSorce", m_sFileName);
	sorce->SetPos(m_vPos);
	sorce->SetPriority(PRIORITY - 1);

	cTimer* timer = CreateObject<cTimer>(this, "GoTimer");
	timer->Setup(2.0f);

	SetPriority(PRIORITY);
}

//==========================================================================================
// �X�V
//==========================================================================================
void cGoFont::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("GoTimer");
	if (timer)
	{
		if (timer->Finished())
		{
			DeleteObject();
			return;
		}

		// ���X�ɑ傫������
		m_vScale.x = m_vScale.y = Easing::Linear(timer->GetTime(), timer->GetLimit(), 10.0f, 1.0f);

		// ���X�ɔ�������
		SetAlpha(Easing::Linear(timer->GetTime(), timer->GetLimit(), 0, 255));

		// �g�債�Ȃ�Go�����͍Ō�Ɉ�C�ɔ�������
		cSpriteObject* sorce = (cSpriteObject*)FindChild("GoFontSorce");
		if (sorce)
		{
			sorce->SetAlpha(Easing::InExp(timer->GetTime(), timer->GetLimit(), 0, 255));
		}
	}

	cSpriteObject::Update();
}
