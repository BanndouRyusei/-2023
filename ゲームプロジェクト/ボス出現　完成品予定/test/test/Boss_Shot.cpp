//----------
//BossShot.cpp
//----------

#include "EnemyShot.h"
#include "Enemy.h"
#include "Player.h"

//定数
const int SHOT_SPEED = 12;

CBossShot::CBossShot(float _priority, bool _isright, const VECTOR _pos) :CShotBase(_priority, CAST::ZAKOA_SHOT) {
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
	m_Image = LoadGraph("Data\\img\\BossShot.png");
	if (m_Image == -1)assert(false);
	m_ShadowImage = LoadGraph("Data\\img\\BossShotShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, false);
}

CBossShot::~CBossShot() {
	DeleteGraph(m_Image);
}

void CBossShot::Update() {
	HitCheck();
	MoveShot();
	m_Shadow.ObjectPosGet(m_Pos, false);
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CBossShot::Draw()const {
	DrawObject(m_Pos, m_Image, m_Turn, 0.0f);
}

//プレイヤーとの当たり判定
void CBossShot::HitCheck() {
	CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
	if (player != nullptr) {
		if (player->HitCheck(m_Pos, 40.0f, m_Image, e_PLAYERHITS::ENEMYSHOT)) {
			//if (player->HitCheck(m_Pos, 40.0f, m_Image, e_ENEMYHITS::PLAYERSHOT)) {
			Delete();
		}
	}
}

//弾の移動処理
void CBossShot::MoveShot() {
	m_Pos.x -= m_Speed* m_IsRight;
	CheckPos();
}

void CBossShot::CheckPos() {
	float left = m_Pos.x, right = m_Pos.x + BOSS_SHOT_SIZE;
	if (left >= WINDOW_W || right <= 0) {  //画面端より外なら消す
		Delete();
	}
}