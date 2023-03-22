//----------
//Zako.cpp
//----------

#include "Player.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "Stage.h"
#include "Item.h"

const int ZAKOB_HP = 4;  //雑魚AのHP
const int ZAKOB_W = 200; //幅
const int ZAKOB_H = 200; //高さ
const int ZAKOB_ATTACKFLAME = 2;  //雑魚Aの攻撃タイミングフレーム数
const float ZAKOB_SHOT_POSY = 60.0f; //エネミーショットの高さ
const int SHOT_WAIT = 120;     //エネミーのSHOT間隔
const float ZAKOB_SHADOW_Y = WINDOW_H - ZAKOB_H - 50.0f - OBJECT_Z_MAX;


CZakoB::CZakoB(float _ex, float _ey, float _ez, float _priortiy) :CCharaBase(_priortiy, CAST::ZAKO_B) {
	
	m_Pos = VGet(_ex, _ey, _ez);
	m_HP = ZAKOB_HP;
	m_Speed = 4.0f;
	char buf[30];
	for (int i = 0; i < (int)e_ENEMYSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Enemy2_Anim%d.png", i);
		LoadDivGraph(buf, ENEMY_ANIM, ENEMY_ANIM, 1, ZAKOB_W, ZAKOB_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_NowState = e_ENEMYSTATE::NEUTRAL;
	m_ShotFlag = true;

	m_ShadowImage = LoadGraph("Data\\img\\ZakoBShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, m_Turn, ZAKOB_SHADOW_Y);
}

CZakoB::~CZakoB() {
	for (int i = 0; i < (int)e_ENEMYSTATE::NONE; i++) {
		for (int j = 0; j < ENEMY_ANIM; j++) {
			DeleteGraph(m_AnimImage[i][j]);
		}
	}
	DeleteGraph(m_ShadowImage);
}

void CZakoB::Update() {
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	m_Pos.x -= stage->GetScrollX()*STAGE_SCROLLX - m_ScrollX;
	m_ScrollX = stage->GetScrollX()*STAGE_SCROLLX;

	switch (m_NowState)
	{
	case e_ENEMYSTATE::NEUTRAL:
		if (m_AttackTimer++ >= SHOT_WAIT) {
			m_NowState = e_ENEMYSTATE::ATTACK;
			m_AttackTimer = 0;
			m_ShotFlag = true;
			m_Frame = 0;
			m_Timer = 0;
		}
	case e_ENEMYSTATE::ATTACK:
			if (m_ShotFlag && m_Frame == ZAKOB_ATTACKFLAME) {
				if (m_Turn) {
					m_ShotPosX = ZAKOB_W;
				}
				else {
					m_ShotPosX = -ZAKOB_SHOT_SIZE / 2;
				}
				m_AttackTimer = 0;
				new CZakoBShot(0.6f, false, VAdd(m_Pos, VGet(m_ShotPosX, ZAKOB_SHOT_POSY, 0.0f)));
				m_ShotFlag = false;
			}
		if (m_Frame == ENEMY_ANIM - 1) {		//アニメーションがすべて再生されたらニュートラル
			m_NowState = e_ENEMYSTATE::NEUTRAL;
		}
		AnimEnemy();
		break;
	case e_ENEMYSTATE::DAMAGE:
		if (m_Frame == ENEMY_ANIM - 1) {		//アニメーションがすべて再生されたら
			if (m_HP <= 0) {		//体力が0以下なら死亡
				m_NowState = e_ENEMYSTATE::DEATH;
				m_Frame = 0;
				m_Timer = 0;
			}
			else {
				m_NowState = e_ENEMYSTATE::NEUTRAL;
			}
		}
		AnimEnemy();
		break;
	case e_ENEMYSTATE::DEATH:
		if (m_Frame == ENEMY_ANIM - 1) {		//アニメーションがすべて再生されたら
			EnemyDeth();
			CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
			float items = (float)CTaskManager::Instance()->GetCount(CAST::ITEM);
			if ((float)GetRand(100) < (APPER_RAND - (float)GetRand(30) - (player->GetHP() + items) / (float)PLAYER_HP * APPER_RAND)) {
				new CItem(0.6f, VGet(m_Pos.x, m_Pos.y, m_Pos.z));
			}
		}
		else {
			AnimEnemy();
		}
		break;
	case e_ENEMYSTATE::NONE:
		break;
	default:
		break;
	}
	m_Shadow.ObjectPosGet(m_Pos, m_Turn);
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
	CheckPos();
}

//エネミーのアニメーション処理
void CZakoB::AnimEnemy() {
	m_Timer++;
	if (m_Timer % (MAX_FPS / 3) == 0) {
		m_Frame++;
		if (m_Frame >= ENEMY_ANIM) {
			m_Frame = 0;
		}
		m_Timer = 0;
	}
}

void CZakoB::Draw()const {
	DrawObject(m_Pos, m_AnimImage[(int)m_NowState][m_Frame], false, 0.0f);
}

bool CZakoB::HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle) {
	if (IsHitObject(m_Pos, _pos, 40.0f, _zwidth, m_AnimImage[(int)m_NowState][0], _ghandle)) {
		if (m_NowState != e_ENEMYSTATE::DEATH) {
			m_NowState = e_ENEMYSTATE::DAMAGE;
			m_Frame = 0;
			m_Timer = 0;
			CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
			if (true == player->GetPower()) {
				m_HP -= 2;
			}
			else {
				m_HP--;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

//エネミー死亡時の処理　プレイヤーキャラを徐々に透明にする
void CZakoB::EnemyDeth() {
	m_Alpha -= ALPHA_STEP;
	if (m_Alpha <= 0)			//完全に透明になったらDelete();
		Delete();
}

void CZakoB::CheckPos() {
	float right = m_Pos.x + ZAKOB_W;
	if (right <= 0) {  //画面端より外なら消す
		Delete();
	}
}