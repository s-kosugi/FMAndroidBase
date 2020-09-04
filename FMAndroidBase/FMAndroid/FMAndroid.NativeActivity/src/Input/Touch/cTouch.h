#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cTouch.h													*/
/*  @brief		:	タッチ入力クラス											*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/07/22													*/
/*																				*/
/*==============================================================================*/

#include "..\..\BaseObject\IBaseObject.h"
#include <DxLib.h>
#include <map>
#include "Utility/Vector/cVector2.h"

class cTouch : public IBaseObject
{
public:

	// タッチ状態
	enum class TOUCH_STATE
	{
		NONE = -1,		// タッチ無し
		TRIGGER = 0,	// 押した瞬間
		BUTTON,			// 押している間
		RELEASE			// 離した瞬間
	};
	// タッチ構造体
	struct TOUCHPTEX
	{
		TOUCHINPUTPOINT pt;				// タッチ構造体
		TOUCH_STATE		state;			// 現在のタッチ状態
	};


	void Initialize(void);
	void Update(void);

	// 特定箇所の範囲がタッチされているかを確認する(円判定)
	// pos   : 指定ポイント
	// state : 調べたいタッチ状態
	// range : 指定ポイントから調べたい範囲
	// ret   : true 指定箇所が該当の状態だった
	bool CheckHitCircle(const cVector2& pos, TOUCH_STATE state, float range);

	// 特定箇所の範囲がタッチされているかを確認する(矩形判定)
	// pos   : 指定ポイント
	// state : 調べたいタッチ状態
	// range : 指定ポイントから調べたい範囲
	// ret   : true 指定箇所が該当の状態だった
	bool CheckHitBox(const cVector2& pos, TOUCH_STATE state, POINT range);

	// タッチ情報配列を取得する
	inline const std::map<int, TOUCHPTEX>& GetMapTouch(void) { return m_mapTouchPoint; };


	// タッチ座標の取得
	// touchID : 取得するタッチID
	// pt      : 取得する座標の参照
	// state   : タッチ状態
	// ret     : true タッチ情報が存在していた。 false タッチ情報が存在していない
	bool GetTouchPos(int touchID, POINT& pt);
	bool GetTouchPos(int touchID, POINT & pt, TOUCH_STATE& state);

	// タッチ数取得
	int GetTouchNum(void);

private:
	std::map<int, TOUCHPTEX> m_mapTouchPoint;		// タッチ情報連想配列　キー値 : タッチID

#ifdef DEBUG
	// デバッグログにタッチのログを表示する
	void DrawTouchDebugLog(void);
#endif // DEBUG

	//-----------------------------------------------------------------------------------------------------
	// シングルトン用
private:
	cTouch(void) { };     //  他からの生成を禁止
	cTouch(IBaseObject* parent) {  };
	cTouch(IBaseObject* parent, const std::string& name) { };
	~cTouch(void) {};   // 他からの削除を禁止(デストラクタをprivateにする事で外部削除不可)
	cTouch(const cTouch& t) {};       // オブジェクトの複製禁止(コピーコンストラクタのオーバライド)
	cTouch& operator = (const cTouch& t) { return *this; };  // オブジェクトの複製禁止(代入演算子のオーバーロード)
public:
	// シングルトンオブジェクトにはDELETEアクセスをさせない。
	IBaseObject* Finalize(void) { IBaseObject::Finalize(); return nullptr; };

	static cTouch& GetInstance(void) {
		static cTouch instance;   // 唯一の実体であるオブジェクト、static変数を使用する事で１つの共有の変数となる
		return instance;    // 常に共通のインスタンスを返す
	};
	//-----------------------------------------------------------------------------------------------------
};