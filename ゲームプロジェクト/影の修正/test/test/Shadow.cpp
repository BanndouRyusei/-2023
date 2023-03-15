//---------------------------
//Chara_Shadow.cpp
//---------------------------
#include"Shadow.h"
#include"ShadowManager.h"

CShadow::CShadow() : m_Image(0),m_Pos(VGet(0.0f,0.0f,0.0f)),m_ExtRateX(0.0),m_ExtRateY(0.0),m_SizeX(0),m_SizeY(0),m_MaxY(0),m_Regist(false) {
}

CShadow::~CShadow() {
	RemoveShadow();
	DeleteGraph(m_Image);
}

void CShadow::Update() {}

void CShadow::Draw()const {
	DrawRotaGraph3(m_Pos.x + m_SizeX / 2, WINDOW_H - m_Pos.z - m_SizeY / 2.0f, m_SizeX / 2.0f, m_SizeY / 2.0f, m_ExtRateX, m_ExtRateY, 0.0, m_Image, TRUE, FALSE);
#if defined(_DEBUG) | defined(DEBUG)
	DrawCircle(m_Pos.x + m_SizeX / 2, WINDOW_H - m_Pos.z - m_SizeY / 2.0f, 5.0f, GetColor(0, 0, 255), TRUE);
#endif
}

//影の座標更新この関数を影を出すキャラのアップデートで呼ぶことにより影がキャラについていく
void CShadow::CharaPosGet(const VECTOR& _pos) {
	m_Pos = _pos;
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
}

//影の初期値を設定する。
//引数 : _shadow 影のイメージ画像 : _pos 座標 : _maxy そのオブジェクトのY座標限界値
void CShadow::SetShadow(int _shadow, const VECTOR& _pos,float _maxy) {
	m_Image = _shadow;
	m_Pos = _pos;
	m_ExtRateX = 1.0 - (double)(m_Pos.y / m_MaxY);
	m_ExtRateY = m_ExtRateX;
	m_MaxY = _maxy;
	GetGraphSize(m_Image, &m_SizeX, &m_SizeY);
	//画像変数などが初期化されてなくてバグるかも
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

//影がリストに登録されているかどうか調べる関数
//bool CShadow::IsRegist() {
//	return m_Regist;
//}