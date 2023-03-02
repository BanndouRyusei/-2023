//-----------------------
//myLib.cpp
//-----------------------
#include "myLib.h"

//キーリピートを無効化して、キー入力を行う
bool IsKeyTrigger(int key, int key_type) {
	static bool g_key_prev[256] = { false };
	if (key & key_type) {
		if (!g_key_prev[key_type]) {
			g_key_prev[key_type] = true;
			return true;
		}
	}
	else {
		g_key_prev[key_type] = false;
	}
	return false;
}

//二つの座標の符号を返す
int IsSign(float a) {
	return (a > 0) - (a < 0);
}

//指定の範囲からランダムで決定した値を取得する（浮動小数点値）
//		戻り値：ランダムで決定した値
float GetRandomFloat(
	//最大値
	float MaxF,

	//最小値
	float MinF
)
{
	return GetRand(10000)*(MaxF - MinF) / 10000.0f + MinF;
}

//2つのベクトルを受け取り、cからpへのベクトルを求める
//戻り値 : 正規化済みのベクトル(xyz)
VECTOR VectorAngle(const VECTOR &p, const VECTOR &c) {
	VECTOR p1, p2;
	p1 = p;
	p2 = c;
	return VNorm(VSub(p1, p2));
}

//2つのベクトルを受け取り、cからpへのベクトルを求める
//戻り値 : 正規化済みのベクトル(xz)
VECTOR VectorAngle_xz(const VECTOR &p, const VECTOR &c) {
	VECTOR p1, p2;
	p1 = VGet(p.x, 0, p.z);
	p2 = VGet(c.x, 0, c.z);
	return VNorm(VSub(p1, p2));
}

//2つのベクトルを受け取り、cからpへのベクトルを求める
//戻り値 : 正規化済みのベクトル(yz)
VECTOR VectorAngle_yz(const VECTOR &p, const VECTOR &c) {
	VECTOR p1, p2;
	p1 = VGet(0, p.y, p.z);
	p2 = VGet(0, c.y, c.z);
	return VNorm(VSub(p1, p2));
}

//_srcから_distへの回転を_timeで分割した角度を求める
//引数 _dist : 目的角 _src : 初期角
//返却値:分割角
float MovementDirection(const float _dist, const float _src, const int _time) {
	float angle;
	angle = _dist - _src;

	if (angle >= DX_PI_F) angle = -DX_TWO_PI_F + angle;
	else if (angle <= -DX_PI_F) angle = DX_TWO_PI_F + angle;

	return (angle / _time);
}

//2つの座標を受け取り、等しいかどうかを判断する
//戻り値 : bool型
bool VectorEqual(const VECTOR &p, const VECTOR &c) {
	if (
		p.x == c.x&&
		p.y == c.y&&
		p.z == c.z
		) {
		return true;
	}
	else {
		return false;
	}
}

//デバッグ用コンソール呼び出し
void DebugModeOn(void) {
	//デバッグ用にコンソールを呼び出す
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	//デバッグコンソールがアクティブウィンドウになるので
	//ゲーム本体のウィンドウをアクティブにする
	SetForegroundWindow(GetMainWindowHandle());
}

//判定用情報の作成
void MakePlayerCapsule(const VECTOR& _pos, const VECTOR& _cenpos,
	const float _height, VECTOR* _cap1, VECTOR* _cap2) {
	*_cap1 = *_cap2 = VAdd(_pos, _cenpos);
	_cap1->y -= _height / 2.0f;
	_cap2->y += _height / 2.0f;
}

//ボックスと2D座標の当たり判定
bool IsHitCheckBox_Point(const int *_x, const int *_y, const int _width, const int _height, const int *_2x, const int *_2y) {
	const int BOX_UL_X = *_x;		//ボックス左上(X座標)、ボックス左下(X座標)
	const int BOX_UL_Y = *_y;		//ボックス左上(Y座標)、ボックス右上(Y座標)
	const int BOX_UR_X = *_x + _width;		//ボックス右上(X座標)、ボックス右下(X座標)
	const int BOX_UR_Y = *_y + _height;		//ボックス左下(Y座標)、ボックス右下(Y座標)

	if (BOX_UL_X <= *_2x && BOX_UR_X >= *_2x && BOX_UL_Y <= *_2y && BOX_UR_Y >= *_2y) {
		return true;
	}
	else
		return false;
}