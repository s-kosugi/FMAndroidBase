/*==============================================================================*/
/*																				*/
/*	@file title	:	IButton.cpp													*/
/*  @brief		:	�^�b�`�{�^�����N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/07/17													*/
/*																				*/
/*==============================================================================*/

#include"IButton.h"
#include "Input/Touch/cTouch.h"

// �R���X�g���N�^
IButton::IButton(IBaseObject * parent, std::string objectname, std::string filename)
	: cSpriteObject(parent, objectname, filename)
	, m_eButtonState(BUTTON_STATE::NEUTRAL)
{
}

// �f�X�g���N�^
IButton::~IButton(void)
{
}
// ������
void IButton::Initialize(void)
{
	m_vPos = { 0,0 };
	SetPriority(PRIORITY);
	cSpriteObject::Initialize();
}

// ������
void IButton::Initialize(const cVector2& pos)
{
	Initialize();
	m_vPos = pos;
}

// �X�V
void IButton::Update(void)
{
	POINT Size = { GetSpriteSize().x , GetSpriteSize().y };
	cTouch* touch = (cTouch*)GetRoot()->FindChild("Touch");
	if (touch)
	{
		// �^�b�`��Ԃɂ���ă{�^���̏�Ԃ�ύX����
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


// �j��
IBaseObject* IButton::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
