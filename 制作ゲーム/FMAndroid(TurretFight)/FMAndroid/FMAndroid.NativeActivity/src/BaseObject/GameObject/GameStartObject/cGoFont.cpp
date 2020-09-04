/*==============================================================================*/
/*																				*/
/*	@file title	:	cGoFont.cpp													*/
/*  @brief		:	Go文字クラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cGoFont.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"

//==========================================================================================
// 定数
//==========================================================================================
const int	cGoFont::PRIORITY = 1000;
//==========================================================================================
// コンストラクタ
//==========================================================================================
cGoFont::cGoFont(IBaseObject * parent)
	: cSpriteObject(parent, "GoFont", "data\\graphic\\go.png")
{
}
//==========================================================================================
// 初期化
//==========================================================================================
void cGoFont::Initialize(void)
{
	cSpriteObject::Initialize();

	cGame* game = (cGame*)GetRoot();
	m_vPos = game->GetWindowCenter();

	//拡大しないGoの文字を生成する。
	cSpriteObject* sorce = CreateDrawObject<cSpriteObject>(this, "GoFontSorce", m_sFileName);
	sorce->SetPos(m_vPos);
	sorce->SetPriority(PRIORITY - 1);

	cTimer* timer = CreateObject<cTimer>(this, "GoTimer");
	timer->Setup(2.0f);

	SetPriority(PRIORITY);
}

//==========================================================================================
// 更新
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

		// 徐々に大きくする
		m_vScale.x = m_vScale.y = Easing::Linear(timer->GetTime(), timer->GetLimit(), 10.0f, 1.0f);

		// 徐々に薄くする
		SetAlpha(Easing::Linear(timer->GetTime(), timer->GetLimit(), 0, 255));

		// 拡大しないGo文字は最後に一気に薄くする
		cSpriteObject* sorce = (cSpriteObject*)FindChild("GoFontSorce");
		if (sorce)
		{
			sorce->SetAlpha(Easing::InExp(timer->GetTime(), timer->GetLimit(), 0, 255));
		}
	}

	cSpriteObject::Update();
}
