//--------------
//myLib.h
//--------------
#ifndef _MYLIB_H_
#define _MYLIB_H_
#pragma once

#define _CRT_SECURE_NO_DEPRECATE
//ヘッダーファイル
#include"DxLib.h"
#include"resource.h"
#include"assert.h"
#include<stdlib.h>
#include<time.h>
#include <list>
#include<math.h>
#include"TaskManager.h"

using namespace std;

//プリプロセッサ
#define RANDMIZE()		(srand((unsigned)time(NULL)))
#define DEG2RAD(deg) (deg*3.141592f/180.0f)

const float FRAMETIME_S = 0.016666f;	//=(1.0f/MAX_FPS)
const float FRAMETIME_MS = 16.666f;		//=(1000ms/MAX_FPS)
const float DEG2RAD = 0.0174528f;		//=(2.0f*3.1415f/360.0f)
const float PI = 3.1415f;							//円周率

const int	WINDOW_W = 960;
const int	WINDOW_H = 800;

const int MAX_FPS = 60;					//最大FPS
const float SPF = (WORD)(1000.0 / MAX_FPS + 0.5);	//1フレームの時間[ms]
const bool	WINDOW_SCREEN = true;

const int ALPHA_MAX = 255;
const int ALPHA_STEP = 5;

const int DIGITS = 10; //数字の個数

const float OBJECT_DRAWPRIORITY_MAX = 2.0f;
const float OBJECT_DRAWPRIORITY_MIN = OBJECT_DRAWPRIORITY_MAX - 1.0f;
const float OBJECT_Z_MAX = 200.0f;

typedef unsigned char BYTE;
typedef unsigned long DWORD;

//キーリピートを無効化して、キー入力を行う
bool IsKeyTrigger(int key, int key_type);

//与えられた数値の符号を返す
int IsSign(float a);

//指定の範囲からランダムで決定した値を取得する（浮動小数点値）
//		戻り値：ランダムで決定した値
float GetRandomFloat(
	//最大値
	float MaxF,

	//最小値
	float MinF
);

//2つのベクトルを受け取り、cからpへのベクトルを求める
//戻り値 : 正規化済みのベクトル(xyz)
VECTOR VectorAngle(const VECTOR &p, const VECTOR &c);

//2つのベクトルを受け取り、cからpへのベクトルを求める
//戻り値 : 正規化済みのベクトル(xz)
VECTOR VectorAngle_xz(const VECTOR &p, const VECTOR &c);

//2つのベクトルを受け取り、cからpへのベクトルを求める
//戻り値 : 正規化済みのベクトル(yz)
VECTOR VectorAngle_yz(const VECTOR &p, const VECTOR &c);

//_srcから_distへの回転を_timeで分割した角度を求める
//引数 _dist : 目的角 _src : 初期角
//返却値:分割角
float MovementDirection(const float _dist, const float _src, const int _time);

//2つの座標を受け取り、等しいかどうかを判断する
//戻り値 : bool型
bool VectorEqual(const VECTOR &p, const VECTOR &c);

//デバッグ用コンソール呼び出し
void DebugModeOn(void);

//判定用情報の作成
void MakePlayerCapsule(const VECTOR& _pos, const VECTOR& _cenpos,
	const float _height, VECTOR* _cap1, VECTOR* _cap2);

//ボックスと2D座標の当たり判定
bool IsHitCheckBox_Point(const int *_x, const int *_y, const int _width, const int _height, const int *_2x, const int *_2y);

//三次元座標情報(VECTOR型)のZの値の引数をもらって描画優先度(float型)を渡す関数
//渡す描画優先度はCHARA_DRAWPRIORITY_MIN～CHARA_DRAWPRIORITY_MAXの間
float ChangePriority(const float* _z);

#endif _MYLIB_H_

