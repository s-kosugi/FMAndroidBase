/*==============================================================================*/
/*																				*/
/*	@file title	:	cTouch.cpp													*/
/*  @brief		:	タッチ入力クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/07/22													*/
/*																				*/
/*==============================================================================*/

#include "cTouch.h"
#include "Utility/Vector/cVector2.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#include <sstream>
#endif

//==========================================================================================
// 初期化
//==========================================================================================
void cTouch::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "Touch";

	m_mapTouchPoint.clear();

	IBaseObject::Initialize();
}

//==========================================================================================
// 更新
//==========================================================================================
void cTouch::Update(void)
{
	//--------------------------------------------------------------------------------------
	// タッチ情報取得前更新
	int touchNum = GetTouchInputNum();
	// タッチされなかった状態を判定するために一旦タッチ状態をダミーにする
	if (!m_mapTouchPoint.empty())
	{
		for (auto it = m_mapTouchPoint.begin(); it != m_mapTouchPoint.end(); it++)
		{
			if ((*it).second.state != TOUCH_STATE::RELEASE)
			{
				(*it).second.state = TOUCH_STATE::NONE;
			}
			else
			{
				// 前フレームでRELEASE状態のタッチは削除する
				it = m_mapTouchPoint.erase(it);
				if (it == m_mapTouchPoint.end()) break;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	// タッチ情報更新
	for (int i = 0; i < touchNum; i++)
	{
		int x, y, id, dev;
		GetTouchInput(i, &x, &y, &id, &dev);

#ifdef DEBUG
		// タッチのポイントを表示する
		cDebugFunc::GetInstance().RegistDrawCircle({ (float)x,(float)y }, 3.0f, 0x77ffffff);
#endif

		auto it = m_mapTouchPoint.find(id);
		// 要素が登録されていない場合は新規タッチを登録する
		if (it == m_mapTouchPoint.end())
		{
			TOUCHPTEX data;
			data.pt.Device = dev;
			data.pt.ID = id;
			data.pt.PositionX = x;
			data.pt.PositionY = y;
			data.state = TOUCH_STATE::TRIGGER;

			// 連想配列にデータを追加する
			//m_mapTouchPoint.insert(std::make_pair(id,data)); // insert関数を使う方法
			m_mapTouchPoint[id] = data;		// 要素番号(キー)を指定する方法
		}
		else
			// 既にあるタッチの場合は連想配列の座標を更新する
		{
			(*it).second.pt.PositionX = x;
			(*it).second.pt.PositionY = y;
			(*it).second.state = TOUCH_STATE::BUTTON;
		}
	}

	//--------------------------------------------------------------------------------------
	// タッチ情報取得後状態更新
	// タッチされてなかったらタッチが離れた判定にする
	for (auto it = m_mapTouchPoint.begin(); it != m_mapTouchPoint.end(); it++)
	{
		if ((*it).second.state == TOUCH_STATE::NONE) (*it).second.state = TOUCH_STATE::RELEASE;
	}
	IBaseObject::Update();
}

//==========================================================================================
// 特定箇所の範囲がタッチされているかを確認する(円判定)
// pos   : 指定ポイント
// state : 調べたいタッチ状態
// range : 指定ポイントから調べたい範囲
// ret : true 指定箇所が該当の状態だった
//==========================================================================================
bool cTouch::CheckHitCircle(const cVector2& pos, TOUCH_STATE state, float range)
{
	if (m_mapTouchPoint.empty()) return false;

	for (auto it : m_mapTouchPoint)
	{
		if (it.second.state != state) continue;

		cVector2 touch((float)it.second.pt.PositionX, (float)it.second.pt.PositionY);
		// タッチが指定範囲内にあった
		if (range >= touch.CalcTwoPointDist(pos)) return true;
	}

	return false;
}

//==========================================================================================
// 特定箇所の範囲がタッチされているかを確認する(矩形判定)
// pos   : 指定ポイントの中心点
// state : 調べたいタッチ状態
// range : 指定ポイントから調べたい範囲
// ret : true 指定箇所が該当の状態だった
//==========================================================================================
bool cTouch::CheckHitBox(const cVector2 & pos, TOUCH_STATE state, POINT range)
{
	if (m_mapTouchPoint.empty()) return false;

	for (auto it : m_mapTouchPoint)
	{
		if (it.second.state != state) continue;

		cVector2 touch((float)it.second.pt.PositionX, (float)it.second.pt.PositionY);
		// タッチが指定範囲内にあった
		if (pos.x - range.x / 2 <= touch.x &&
			pos.x + range.x / 2 >= touch.x &&
			pos.y - range.y / 2 <= touch.y &&
			pos.y + range.y / 2 >= touch.y
			)
		{
			return true;
		}
	}

	return false;
}

//==========================================================================================
// タッチ座標の取得
// touchID : 取得するタッチID
// pt      : 取得する座標の参照
// ret     : true タッチ情報が存在していた。 false タッチ情報が存在していない
//==========================================================================================
bool cTouch::GetTouchPos(int touchID, POINT & pt)
{
	if (m_mapTouchPoint.empty()) return false;

	auto it = m_mapTouchPoint.find(touchID);

	if (it == m_mapTouchPoint.end()) return false;

	pt.x = (*it).second.pt.PositionX;
	pt.y = (*it).second.pt.PositionY;

	return true;
}
//==========================================================================================
// タッチ座標の取得
// touchID : 取得するタッチID
// pt      : 取得する座標の参照
// ret     : true タッチ情報が存在していた。 false タッチ情報が存在していない
//==========================================================================================
bool cTouch::GetTouchPos(int touchID, POINT & pt, cTouch::TOUCH_STATE& state)
{
	if (m_mapTouchPoint.empty()) return false;

	auto it = m_mapTouchPoint.find(touchID);

	if (it != m_mapTouchPoint.end())
	{
		pt.x = it->second.pt.PositionX;
		pt.y = it->second.pt.PositionY;
		state = it->second.state;
		return true;
	}

	return false;
}
//==========================================================================================
// タッチ数取得
//==========================================================================================
int cTouch::GetTouchNum(void)
{
	return GetTouchInputNum();
}

#ifdef DEBUG
//==========================================================================================
// デバッグログにタッチのログを表示する
//==========================================================================================
void cTouch::DrawTouchDebugLog(void)
{
	// タッチされている座標をデバッグログで表示する
	for (auto it : m_mapTouchPoint)
	{
		std::ostringstream oss;
		oss << "Touch" << it.first << "::X : " << it.second.pt.PositionX << " Y :" << it.second.pt.PositionY;
		cDebugFunc::GetInstance().PushDebugLog(oss.str().c_str());
	}
}
#endif // DEBUG
