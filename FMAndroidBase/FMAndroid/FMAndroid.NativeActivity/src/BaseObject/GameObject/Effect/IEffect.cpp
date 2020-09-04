/*==============================================================================*/
/*																				*/
/*	@file title	:	IEffect.cpp													*/
/*  @brief		:	エフェクトオブジェクト										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/22													*/
/*																				*/
/*==============================================================================*/

#include "IEffect.h"
#include "cGame.h"
#include "Utility/Timer/cTimer.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif
//==========================================================================================
//  コンストラクタ
//==========================================================================================
IEffect::IEffect(IBaseObject* parent, const std::string object_name, const std::string graphic_file_name) :
	cSpriteObject(parent, object_name, graphic_file_name)
	, m_ptSize({ 64,64 })
	, m_nColNum(1)
	, m_nMaxAnimNum(1)
	, m_nAnimNo(0)
	, m_fFrameTime(0.05f)
{

}

//==========================================================================================
//  初期化
//==========================================================================================
void
IEffect::
Initialize(void)
{
	cSpriteObject::Initialize();
}

//==========================================================================================
//  初期化
//==========================================================================================
void IEffect::Initialize(const cVector2& pos)
{
	m_vPos = pos;

	Initialize();
}

//==========================================================================================
//  更新
//==========================================================================================
void IEffect::Update(void)
{
	cTimer* timer = (cTimer*)FindChild("AnimeTimer");
	if (timer && timer->Finished())
	{
		m_nAnimNo++;
		// アニメーションが最大枚数を超えたら削除
		if (m_nAnimNo >= m_nMaxAnimNum)
		{
			DeleteObject();
			return;
		}
		// アニメーション更新
		UpdateAnime();

		timer->Reset();
	}

	cSpriteObject::Update();
}

//==========================================================================================
//  解放
//==========================================================================================
IBaseObject* IEffect::Finalize(void)
{
	cSpriteObject::Finalize();
	return this;
}
//==========================================================================================
// アニメーション番号のセット
//==========================================================================================
void IEffect::SetAnimNo(short animeNo)
{

	if (m_nMaxAnimNum > animeNo)
	{
		m_nAnimNo = animeNo;
		// アニメーション更新
		UpdateAnime();
		// アニメーションが切り替わったらタイマーをリセット
		cTimer* timer = (cTimer*)FindChild("AnimeTimer");
		if (timer) timer->Reset();
	}
	else
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("error : SetAnime (MaxAnime < animeNo)");
#endif
	}
}
//==========================================================================================
// １フレーム当たりの時間のセット
//==========================================================================================
void IEffect::SetFrameTime(float time)
{
}
//==========================================================================================
//  アニメーション初期設定
//==========================================================================================
void IEffect::SetupAnime(const POINT & size, short col, short maxNum, float frameTime)
{
	m_ptSize = size;
	m_nColNum = col;
	m_nMaxAnimNum = maxNum;
	m_fFrameTime = frameTime;

	m_SrcRect = { 0,0,size.x,size.y };
	m_vCenter.x = size.x / 2.0f;
	m_vCenter.y = size.y / 2.0f;

	// アニメーションタイマー作成
	cTimer* timer = (cTimer*)FindChild("AnimeTimer");
	if (!timer)
	{
		timer = (cTimer*)CreateObject<cTimer>(this, "AnimeTimer");
	}
	timer->Setup(m_fFrameTime);
}

//==========================================================================================
// 現在のアニメーション番号にスプライトをあわせる
//==========================================================================================
void IEffect::UpdateAnime(void)
{
	m_SrcRect.left = (m_nAnimNo * m_ptSize.x) % (m_ptSize.x * m_nColNum);
	m_SrcRect.right = m_SrcRect.left + m_ptSize.x;
	m_SrcRect.top = ((m_nAnimNo * m_ptSize.x) / (m_ptSize.x * m_nColNum)) * m_ptSize.y;
	m_SrcRect.bottom = m_SrcRect.top + m_ptSize.y;
}
