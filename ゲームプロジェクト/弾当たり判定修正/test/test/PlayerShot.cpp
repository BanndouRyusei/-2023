//---------------------------
//Stage.cpp
//---------------------------
#include"PlayerShot.h"
#include"Player.h"
#include"Enemy.h"

//定数
const int SHOT_SPEED = 8;
const float SHOT_Z_WIDTH = 40.0f;

CPlayerShot::CPlayerShot(float _priority,bool _isright,const VECTOR _pos) :CShotBase(_priority, CAST::PLAYERSHOT) {
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
	m_Image = LoadGraph("Data\\img\\PlayerShot.png");
	if (m_Image == -1)assert(false);
	m_ShadowImage = LoadGraph("Data\\img\\PlayerShotShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, m_Turn);
}

CPlayerShot::~CPlayerShot() {
	DeleteGraph(m_Image);
}

void CPlayerShot::Update() {
	//当たり判定を敵の数だけ行う関数を働かせて当たったらDelete();
	HitCheck();

	MoveShot();
	m_Shadow.ObjectPosGet(m_Pos, m_Turn);
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CPlayerShot::Draw() const {
	DrawObject(m_Pos, m_Image, m_Turn, 0.0f);
#if defined(_DEBUG) | defined(DEBUG)
	DrawCircle(m_Pos.x + 50 / 2, WINDOW_H - m_Pos.y - m_Pos.z - 50 / 2.0f, 5.0f, GetColor(0, 0, 255), TRUE);
#endif
}

//敵との当たり判定
void CPlayerShot::HitCheck() {
	int zakoas, zakobs, bosss;			//それぞれの敵の数
	CEnemyZakoA* zakoa;
	CEnemyZakoB* zakob;
	CEnemyBoss* boss;
	zakoas = CTaskManager::Instance()->GetCount(CAST::ZAKO_A);
	for (int i = 0; i < zakoas; i++) {		//敵の数だけ繰り返す
		zakoa = (CEnemyZakoA*)CTaskManager::Instance()->GetTask(CAST::ZAKO_A, i);
		if (zakoa->HitCheck(m_Pos, SHOT_Z_WIDTH, m_Image)) {
			Delete();
		}
	}
	zakobs = CTaskManager::Instance()->GetCount(CAST::ZAKO_B);
	for (int i = 0; i < zakobs; i++) {		//敵の数だけ繰り返す
		zakob = (CEnemyZakoB*)CTaskManager::Instance()->GetTask(CAST::ZAKO_B, i);
		if (zakob->HitCheck(m_Pos, SHOT_Z_WIDTH, m_Image)) {
			Delete();
		}
	}
	bosss = CTaskManager::Instance()->GetCount(CAST::BOSS);
	for (int i = 0; i < bosss; i++) {		//敵の数だけ繰り返す
		boss = (CEnemyBoss*)CTaskManager::Instance()->GetTask(CAST::BOSS, i);
		if (boss->HitCheck(m_Pos, SHOT_Z_WIDTH, m_Image)) {
			Delete();
		}
	}
}

//弾の移動処理
void CPlayerShot::MoveShot() {
	m_Pos.x += m_Speed * m_IsRight;
	CheckPos();
}

//画面外に出ていたら消す
void CPlayerShot::CheckPos() {
	float left = m_Pos.x, right = m_Pos.x + PLAYER_SHOT_SIZE;
	if (left >= WINDOW_W || right <= 0) {		//画面端より外なら消す
		Delete();
	}
}