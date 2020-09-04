/*==============================================================================*/
/*																				*/
/*	@file title	:	IEnemy.cpp													*/
/*  @brief		:	敵ベースクラス												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/06/16													*/
/*																				*/
/*==============================================================================*/

#include "IEnemy.h"
#include "cGame.h"
#include "ScoreManager/cScoreManager.h"
#include "..\Effect\cEffectManager.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif
//==========================================================================================
// 定数
//==========================================================================================
const int  IEnemy::AREAOUT_ADJUST = 100; // エリアアウト距離

//==========================================================================================
// コンストラクタ
//==========================================================================================
IEnemy::IEnemy(IBaseObject * parent, const std::string object_name, const std::string graphic_file_name)
	: cSpriteObject(parent, object_name, graphic_file_name)
	, m_vPosUp(0.0f, 0.0f)
	, m_fDist(0.0f)
	, m_eState(STATE::NORMAL)
	, m_nHp(1)
	, m_nScore(1)
{
}

//==========================================================================================
// デストラクタ
//==========================================================================================
IEnemy::~IEnemy(void)
{
}
//==========================================================================================
// 初期化
//==========================================================================================
void IEnemy::Initialize(void)
{
	Initialize({ 0.0f,0.0f });
}
//==========================================================================================
// 初期化
//==========================================================================================
void IEnemy::Initialize(const cVector2 & pos)
{
	m_vPos = pos;

	cSpriteObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void IEnemy::Update(void)
{
	// 状態別処理
	switch (m_eState)
	{
	case STATE::NORMAL:
		Normal();
		break;
	case STATE::DEAD:
		Dead();
		break;
	}

	// 移動処理
	m_vPos += m_vPosUp;

	// エリアアウトしたら敵を削除する
	AreaOutAllProc();

#ifdef DEBUG
	// 当たり判定の描画
	cDebugFunc::GetInstance().RegistDrawCircle(m_vPos, m_fDist, 0x77ff0000);
#endif

	cSpriteObject::Update();
}

//==========================================================================================
// 破棄
//==========================================================================================
IBaseObject* IEnemy::Finalize(void)
{
	cSpriteObject::Finalize();

	return this;
}

//=================================================================
// 通常状態
//=================================================================
void IEnemy::Normal(void)
{
}
//=================================================================
// 死亡状態
//=================================================================
void IEnemy::Dead(void)
{
	m_vPosUp = {0.0f,0.0f};
	int alpha = GetAlpha();
	alpha -= 8;
	if (alpha <= 0)
	{
		DeleteObject();
	}
	else
	{
		SetAlpha((unsigned int)alpha);
	}

}

//=================================================================
// 画面外配置処理
//=================================================================
IEnemy::DIRECTION IEnemy::ArrangeOffScreen(void)
{
	DIRECTION direction = DIRECTION::LEFT;

	cGame* game = (cGame*)GetRoot();

	// 画面端から出すようにする為どの方向から出現するかをランダムで決定する
	switch (cGame::Random(0, 3))
	{
	case 0:
		// 左側の場合
		m_vPos.x = -GetSpriteSize().x / 2.0f;
		direction = DIRECTION::LEFT;
		break;
	case 1:
		// 右側の場合
		m_vPos.x = game->GetWindowWidth() + GetSpriteSize().x;
		direction = DIRECTION::RIGHT;
		break;
	case 2:
		// 上側の場合
		m_vPos.y = -GetSpriteSize().y / 2.0f;
		direction = DIRECTION::TOP;
		break;
	case 3:
		// 下側の場合
		m_vPos.y = game->GetWindowHeight() + GetSpriteSize().y;
		direction = DIRECTION::BOTTOM;
		break;
	}
	return direction;
}

//==========================================================================================
// プレイヤーへ向かう移動量を設定する
// speed : 基本移動力
//==========================================================================================
void IEnemy::GotoPlayer(float speed)
{
	// プレイヤーに向かって移動
	cSpriteObject* pc = (cSpriteObject*)GetParent()->FindSibling("Player");
	if (pc)
	{
		cVector2 pcPos = pc->GetPos();
		float angle = m_vPos.CalcTwoPointAngle(pcPos);

		// 移動量を決定
		m_vPosUp.x = cos(DEG_TO_RAD(angle)) * speed;
		m_vPosUp.y = sin(DEG_TO_RAD(angle)) * speed;
	}
}

//==========================================================================================
// ダメージ処理
//==========================================================================================
void IEnemy::Damage(void)
{
	m_nHp--;
	if (m_nHp <= 0)
	{
		m_eState = STATE::DEAD;
		m_vPosUp.x = m_vPosUp.y = 0.0f;

		// 加点処理
		cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
		sm->AddScore(m_nScore);

		// エフェクト再生
		cEffectManager* ef = (cEffectManager*)GetRoot()->FindChild("EffectManager");
		ef->Create(EFFECT_ID::BOM,m_vPos);
	}
}

//==========================================================================================
// 左エリアアウト処理
//==========================================================================================
void IEnemy::AreaOutLeftProc(void)
{
	if (m_vPos.x + GetSpriteSize().x / 2 < ((cGame*)GetRoot())->GetPlayArea().left - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 上エリアアウト処理
//==========================================================================================
void IEnemy::AreaOutUpProc(void)
{
	if (m_vPos.y + GetSpriteSize().y / 2 < ((cGame*)GetRoot())->GetPlayArea().top - AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 右エリアアウト処理
//==========================================================================================
void IEnemy::AreaOutRightProc(void)
{
	if (m_vPos.x - GetSpriteSize().x / 2 > ((cGame*)GetRoot())->GetPlayArea().right + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 下エリアアウト処理
//==========================================================================================
void IEnemy::AreaOutBottomProc(void)
{
	if (m_vPos.y - GetSpriteSize().y / 2 > ((cGame*)GetRoot())->GetPlayArea().bottom + AREAOUT_ADJUST)
	{
		DeleteObject();
	}
}

//==========================================================================================
// 全方向エリアアウト処理
//==========================================================================================
void IEnemy::AreaOutAllProc(void)
{
	AreaOutLeftProc();
	AreaOutUpProc();
	AreaOutRightProc();
	AreaOutBottomProc();
}