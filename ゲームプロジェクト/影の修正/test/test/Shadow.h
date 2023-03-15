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
	double m_ExtRateX, m_ExtRateY;
	int m_SizeX, m_SizeY;
	float m_MaxY;
	bool m_Regist;
public:
	CShadow();
	~CShadow();
	void Update();
	void Draw()const;
	void CharaPosGet(const VECTOR& _pos);							//影の座標更新この関数を影を出すキャラのアップデートで呼ぶことにより影がキャラについていく
	void SetShadow(int _shadow, const VECTOR& _pos, float _maxy = 0.0f);			//影の初期値を設定する。キャラごとに影の画像を指定できたらいいなと思い引数に入れている
	void RegistShadow();		//影のリストに追加
	void RemoveShadow();		//影のリストから解除
	//bool IsRegist();				//影がリストに登録されているかどうか調べる関数
};

#endif _SHADOW_H