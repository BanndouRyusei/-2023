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

//グローバル変数
extern int g_Score;

//プリプロセッサ
#define RANDMIZE()		(SRand((unsigned)time(NULL)))
#define DEG2RAD(deg) (deg*3.141592f/180.0f)

const float FRAMETIME_S = 0.016666f;	//=(1.0f/MAX_FPS)
const float FRAMETIME_MS = 16.666f;		//=(1000ms/MAX_FPS)
const float DEG2RAD = 0.0174528f;		//=(2.0f*3.1415f/360.0f)
const float PI = 3.1415f;							//円周率
const float APPER_RAND = 100.0f;		//最大確立(100%)

const int	WINDOW_W = 960;
const int	WINDOW_H = 800;

const int MAX_FPS = 60;					//最大FPS
const float SPF = (WORD)(1000.0 / MAX_FPS + 0.5);	//1フレームの時間[ms]
const bool	WINDOW_SCREEN = true;

const int ALPHA_MAX = 255;
const int ALPHA_STEP = 3;

const int DIGITS = 10; //数字の個数

const float OBJECT_DRAWPRIORITY_MAX = 2.0f;			//オブジェクト(ステージ上に出てくるもの)の描画優先度の最大値
const float OBJECT_DRAWPRIORITY_MIN = OBJECT_DRAWPRIORITY_MAX - 1.0f;			//オブジェクトの描画優先度の最小値
const float OBJECT_Z_MAX = 160.0f;		//オブジェクトのZの最大値

typedef unsigned char BYTE;
typedef unsigned long DWORD;

//タスクの管理
enum class PHASE
{
	START, PLAY, END, NONE
};

//短形同士の当たり判定用構造体
//画像のサイズ(横幅と縦幅)
struct Rect {
	int Width; int Height;
};

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

//短形同士の当たり判定
//短形aと短形bが重なっているかどうかを判定する
bool IsHitBox(float _ax, float _ay, float _bx, float _by, Rect _arect, Rect _brect);

//直線同士の当たり判定
//Z座標同士の当たり判定をする
bool IsHitZLine(float _az, float _bz, float _awidth, float _bwidth);

//オブジェクト同士の当たり判定
//引数　座標 _apos _bpos　オブジェクトの厚さ(Z方向) _awidth _bwidth　画像ハンドル _aghandle _bghandle
bool IsHitObject(const VECTOR& _apos, const VECTOR& _bpos,float _awidth,float _bwidth,int _aghandle,int _bghandle);

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

//判定用情報の作成
void MakePlayerCapsule(const VECTOR& _pos, const VECTOR& _cenpos,
	const float _height, VECTOR* _cap1, VECTOR* _cap2);

//ボックスと2D座標の当たり判定
bool IsHitCheckBox_Point(const int *_x, const int *_y, const int _width, const int _height, const int *_2x, const int *_2y);

//三次元座標情報(VECTOR型)のZの値の引数をもらって描画優先度(float型)を渡す関数
//渡す描画優先度はCHARA_DRAWPRIORITY_MIN〜CHARA_DRAWPRIORITY_MAXの間
float ChangePriority(const float &_z);

//ベルトスクロール用オブジェクト描画関数
//引数 : 座標 _pos 画像ハンドル _Grhandle 　_isturn　反転するか ture する false しない　_rot　回転角度(ラジアン)
void DrawObject(const VECTOR& _pos,const int _Grhandle,const bool _isturn,const float _rot);

#if defined(_DEBUG) | defined(DEBUG)
//デバッグ用コンソール呼び出し
void DebugModeOn(void);
#endif


//CVector2D
//2D座標ベクトルクラス
class CVector2D
{
public:
	float x;
	float y;
	CVector2D() : x(0), y(0) {};
	CVector2D(float x, float y) : x(x), y(y) {};
	CVector2D& operator+=(const CVector2D& ope);
	CVector2D& operator-=(const CVector2D& ope);
	CVector2D& operator=(const CVector2D& ope);
	CVector2D operator+(const CVector2D& ope);
	bool operator==(const CVector2D& ope);
	bool operator!=(const CVector2D& ope);

};

CVector2D VGet2D(float x, float y);

#endif _MYLIB_H_

