//-----------------
//Shadow.h
//-----------------
#ifndef _SHADOW_H_
#define _SHADOW_H_
#pragma once

//ヘッダーファイル
#include"myLib.h"

//丸影関係

//定数

//丸影クラス
class CShadow {
private:
	int m_Image;
	VECTOR m_Pos;
	float m_MaxY;
	double m_ExtRateX, m_ExtRateY;
	int m_SizeX, m_SizeY;
	bool m_Turn;
	bool m_Regist;
public:
	CShadow();
	~CShadow();
	void Update();
	void Draw();
	void ObjectPosGet(const VECTOR& _pos, bool _turn);							//影の座標更新この関数を影を出すキャラのアップデートで呼ぶことにより影がキャラについていく
	void SetShadow(int _shadow, const VECTOR& _pos, bool _turn, float _maxy = 1.0f);			//影の初期値を設定する。キャラごとに影の画像を指定。_maxyはキャラのY軸の最大値(飛ばないキャラの場合はデフォルト引数を使用する)
	void RegistShadow();		//影のリストに追加
	void RemoveShadow();		//影のリストから解除
};

#endif _SHADOW_H