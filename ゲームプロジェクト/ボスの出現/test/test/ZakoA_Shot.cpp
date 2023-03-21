//----------
//ZakoAShot.cpp
//----------

#include "EnemyShot.h"
#include "Enemy.h"
#include "Player.h"

//定数
const int SHOT_SPEED = 8;

CZakoAShot::CZakoAShot(float _priority, bool _isright, const VECTOR _pos) :CShotBase(_priority, CAST::ZAKOA_SHOT) {
	m_Pos = _pos;
	m_Frame = 0, m_Timer = 0;
	m_Turn = _isright;
	m_Speed = SHOT_SPEED;
	if (_isright) {
		m_IsRight = -1.0f;
	}
	else {
		m_IsRight = 1.0f;
	}
	m_Image = LoadGraph("Data\\img\\ZakoAShot.png");
	if (m_Image == -1)assert(false);
}

CZakoAShot::~CZakoAShot() {
	DeleteGraph(m_Image);
}

void CZakoAShot::Update() {
	HitCheck();
	MoveShot();
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CZakoAShot::Draw()const {
	DrawObject(m_Pos, m_Image, m_Turn, 0.0f);
}

//プレイヤーとの当たり判定
void CZakoAShot::HitCheck() {
	CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
	if (player != nullptr) {
		if (player->HitCheck(m_Pos, 40.0f, m_Image, e_PLAYERHITS::ENEMYSHOT)) {
			//if (player->HitCheck(m_Pos, 40.0f, m_Image, e_ENEMYHITS::PLAYERSHOT)) {
			Delete();
		}
	}
}

//弾の移動処理
void CZakoAShot::MoveShot() {
	m_Pos.x -= /*m_Speed*/0 * m_IsRight;
	CheckPos();
}

void CZakoAShot::CheckPos() {
	float left = m_Pos.x, right = m_Pos.x + ZAKOA_SHOT_SIZE;
	if (left >= WINDOW_W || right <= 0) {  //画面端より外なら消す
		Delete();
	}
}