//---------------------------
//Chara_Shadow.cpp
//---------------------------
#include"Shadow.h"
#include"ShadowManager.h"

CShadow::CShadow() : m_Image(0),m_Pos(VGet(0.0f,0.0f,0.0f)), m_MaxY(0),m_ExtRateX(0.0),m_ExtRateY(0.0),m_SizeX(0),m_SizeY(0),m_Turn(false),m_Regist(false) {
}

CShadow::~CShadow() {
	RemoveShadow();
	DeleteGraph(m_Image);
}

void CShadow::Update() {}

void CShadow::Draw() {

	//画像の自由変形のための座標
	CVector2D LD, RD, LU, RU;		//左下、右下、左上、右上座標

	//画像の４つの角を指定して変形している		
	//影の画像を下側の中央に向かって縮小するように変形させる
	//高さを変えたくないため下側のY座標には拡縮率を反映させていない
	//左側のX座標はm_Pos.x、右側のX座標はm_Pos.x+m_SizeX
	//下側のY座標はWINDOW_H-m_Pos.z、上側のY座標はWINDOW_H-m_Pos.z-m_SizeY（影なのでオブジェクトのY座標要素は考慮しない）
	//拡大縮小のために(m_SizeX / 2 - m_SizeX / 2 * m_ExtRateX)を左側のX座標に足している。右側の場合は引いている
	//引く値の画像サイズをすべて2で割っているのは画像の横サイズの半分のX座標を超えないようにするため
	//Yの拡縮は上側のみ行うので(m_SizeY - m_SizeY * m_ExtRateY)を上側のY座標に足している
	//Y座標の足す値の画像サイズを2で割っていないのは画像本体の下側に影があるため
	LD = VGet2D(m_Pos.x + (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), WINDOW_H - m_Pos.z);
	RD = VGet2D((m_Pos.x + m_SizeX) - (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), WINDOW_H - m_Pos.z);
	LU = VGet2D(m_Pos.x + (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), (WINDOW_H - m_Pos.z - m_SizeY) + (m_SizeY - m_SizeY * (float)m_ExtRateY));
	RU = VGet2D((m_Pos.x + m_SizeX) - (m_SizeX / 2 - m_SizeX / 2 * (float)m_ExtRateX), (WINDOW_H - m_Pos.z - m_SizeY) + (m_SizeY - m_SizeY * (float)m_ExtRateY));

	//画像をY軸反転処理
	//画像の横幅×横拡縮率をかけて足す(左右のX座標を入れ替える)
	if (m_Turn) {
		LD.x += m_SizeX * (float)m_ExtRateX;
		LU.x += m_SizeX * (float)m_ExtRateX;
		RD.x -= m_SizeX * (float)m_ExtRateX;
		RU.x -= m_SizeX * (float)m_ExtRateX;
	}

	DrawModiGraphF(LU.x, LU.y, RU.x, RU.y, RD.x, RD.y, LD.x, LD.y, m_Image, TRUE);
}

//影の座標更新この関数を影を出すキャラのアップデートで呼ぶことにより影がキャラについていく
void CShadow::ObjectPosGet(const VECTOR& _pos, bool _turn) {
	m_Pos = _pos;
	m_Turn = _turn;
	if (m_MaxY == 1.0f) {
		m_Pos.y = 0.0f;
	}
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
}

//影の初期値を設定する。
//引数 : _shadow 影のイメージ画像 : _pos  座標 : _turn 座標 : _maxy そのオブジェクトのY座標限界値(指定しなければ拡大縮小はしない)
void CShadow::SetShadow(int _shadow, const VECTOR& _pos, bool _turn, float _maxy) {
	m_Image = _shadow;
	m_Pos = _pos;
	m_MaxY = _maxy;
	if (m_MaxY == 1.0f) {			//デフォルト引数が使われていたらY座標を考慮しない
		m_Pos.y = 0.0f;
	}
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
	GetGraphSize(m_Image, &m_SizeX, &m_SizeY);
	m_Turn = _turn;
	m_Regist = false;
	RegistShadow();
}

//影のリストに追加
void CShadow::RegistShadow() {
	//登録されているかどうかを先に調べる
	assert(!m_Regist);
	m_Regist = CShadowManager::GetInstance()->Regist(this);
}

//影のリストから解除
void CShadow::RemoveShadow() {
	//登録されているかどうかを先に調べる
	assert(m_Regist);
	m_Regist = CShadowManager::GetInstance()->Remove(this);
}