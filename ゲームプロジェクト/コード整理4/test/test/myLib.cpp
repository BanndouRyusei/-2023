//-----------------------
//myLib.cpp
//-----------------------
#include "myLib.h"

//グローバル変数
int g_Score = 0;

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

//長方形同士の当たり判定
//a=長方形a　b=長方形b
//l=左端t=上端r=右端b=下端
bool IsHitBox(float _ax, float _ay, float _bx, float _by, Rect _arect, Rect _brect) {
	float al = _ax;
	float at = _ay + _arect.Height;
	float ar = al + _arect.Width;
	float ab = at + _arect.Height;

	float bl = _bx;
	float bt = _by + _arect.Height;
	float br = bl + _brect.Width;
	float bb = bt + _brect.Height;

	if (al < br&&bl < ar&&at < bb&&bt < ab) {
		return true;
	}
	else {
		return false;
	}
}

//直線同士の当たり判定
//Z座標同士の当たり判定をする
bool IsHitZLine(float _az, float _bz, float _awidth, float _bwidth) {
	float at = _az + _awidth / 2;
	float au = _az - _awidth / 2;
	
	float bt = _bz + _bwidth / 2;
	float bu = _bz - _bwidth / 2;

	if (at >= bu && au <= bt) {
		return true;
	}
	else {
		return false;
	}
}

//オブジェクト同士の当たり判定
//引数　座標 _apos _bpos　オブジェクトの厚さ(Z方向) _awidth _bwidth　画像ハンドル _aghandle _bghandle
bool IsHitObject(const VECTOR& _apos, const VECTOR& _bpos, float _awidth, float _bwidth, int _aghandle, int _bghandle) {
	//画像サイズを取得
	int aSizeX, aSizeY;
	int bSizeX, bSizeY;
	GetGraphSize(_aghandle, &aSizeX, &aSizeY);
	GetGraphSize(_bghandle, &bSizeX, &bSizeY);

	Rect arect, brect;
	arect.Width = aSizeX; arect.Height = aSizeY;
	brect.Width = bSizeX; brect.Height = bSizeY;

	if (IsHitBox(_apos.x, _apos.y, _bpos.x, _bpos.y, arect, brect) && IsHitZLine(_apos.z, _bpos.z, _awidth, _bwidth)) {
		return true;
	}
	else {
		return false;
	}
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

//三次元座標情報(VECTOR型)のZの値の引数をもらって描画優先度(float型)を渡す関数
//渡す描画優先度はOBJECT_DRAWPRIORITY_MINからOBJECT_DRAWPRIORITY_MAXの間
float ChangePriority(const float &_z) {
	return OBJECT_DRAWPRIORITY_MAX - _z / OBJECT_Z_MAX;
}

//ベルトスクロール用オブジェクト描画関数
void DrawObject(const VECTOR& _pos, const int _Grhandle, const bool _isturn,const float _rot) {
	//画像サイズを取得
	float SizeX, SizeY;
	GetGraphSizeF(_Grhandle, &SizeX, &SizeY);
	DrawRotaGraph2F(_pos.x + SizeX / 2, WINDOW_H - _pos.y - _pos.z - SizeY / 2.0f, SizeX / 2.0f, SizeY / 2.0f, 1.0, DEG2RAD(_rot), _Grhandle, TRUE, _isturn);
}

#if defined(_DEBUG) | defined(DEBUG)
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
#endif

//CVector2D
CVector2D& CVector2D::operator+=(const CVector2D& ope) {
	x += ope.x;
	y += ope.y;
	return *this;
}

CVector2D& CVector2D::operator-=(const CVector2D& ope) {
	x -= ope.x;
	y -= ope.y;
	return *this;
}
CVector2D& CVector2D::operator=(const CVector2D& ope) {
	x = ope.x;
	y = ope.y;
	return *this;
}
CVector2D CVector2D::operator+(const CVector2D& ope) {
	float tempX, tempY;
	tempX = x + ope.x;
	tempY = y + ope.y;
	return CVector2D(tempX, tempY);
}
bool CVector2D::operator==(const CVector2D& ope) {
	if ((x == ope.x) && (y == ope.y))
		return true;
	else
		return false;
}
bool CVector2D::operator!=(const CVector2D& ope) {
	if ((x != ope.x) && (y != ope.y))
		return true;
	else
		return false;
}

//2D座標を取得
CVector2D VGet2D(float x, float y) {
	return CVector2D(x, y);
}