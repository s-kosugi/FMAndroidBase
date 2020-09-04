/*==============================================================================*/
/*																				*/
/*	@file title	:	IButton.cpp													*/
/*  @brief		:	タッチボタン基底クラス										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/17													*/
/*																				*/
/*==============================================================================*/

#include"IButton.h"
#include "Input/Touch/cTouch.h"

// コンストラクタ
IButton::IButton(IBaseObject * parent, std::string objectname, std::string filename)
	: cSpriteObject(parent, objectname, filename)
	, m_eButtonState(BUTTON_STATE::NEUTRAL)
{
}

// デストラクタ
IButton::~IButton(void)
{
}
// 初期化
void IButton::Initialize(void)
{
	m_vPos = { 0,0 };
	SetPriority(PRIORITY);
	cSpriteObject::Initialize();
}

// 初期化
void IButton::Initialize(const cVector2& pos)
{
	Initialize();
	m_vPos = pos;
}

// 更新
void IButton::Update(void)
{
	POINT Size = { GetSpriteSize().x , GetSpriteSize().y };
	cTouch* touch = (cTouch*)GetRoot()->FindChild("Touch");
	if (touch)
	{
		// タッチ状態によってボタンの状態を変更する
		if (touch->CheckHitBox(m_vPos, cTouch::TOUCH_STATE::TRIGGER, Size))
		{
			m_eButtonState = BUTTON_STATE::TRIGGER;
			Trigger();
		}
		else if (touch->CheckHitBox(m_vPos, cTouch::TOUCH_STATE::RELEASE, Size))
		{
			m_eButtonState = BUTTON_STATE::RELEASE;
			Release();
		}
		else if (touch->CheckHitBox(m_vPos, cTouch::TOUCH_STATE::BUTTON, Size))
		{
			m_eButtonState = BUTTON_STATE::PRESSED;
			Pressed();
		}
		else
		{
			m_eButtonState = BUTTON_STATE::NEUTRAL;
			Neutral();
		}
	}	cSpriteObject::Update();
}


// 破棄
IBaseObject* IButton::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
