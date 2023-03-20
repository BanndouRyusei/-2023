//----------
//Zako.cpp
//----------
#include "Task.h"
#include "Enemy.h"

const int ZAKOA_HP = 3;  //éGãõAÇÃHP
const int ZAKOA_W = 200; //ïù
const int ZAKOA_H = 200; //çÇÇ≥


CEnemyBoss::CEnemyBoss(float _ex, float _ez, float _speed, float _priortiy) :CTask(_priortiy, CAST::ZAKO_A) {
	m_DrawTask.Init(this, std::bind(&CEnemyBoss::Draw, this), OBJECT_DRAWPRIORITY_MIN);
	//m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Pos = VGet(_ex, 0.0f, _ez);
	m_HP = ZAKOA_HP;
	m_Speed = _speed;
	char buf[30];
	for (int i = 0; i < (int)e_ENEMYSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Boss_Anim%d.png", i);
		LoadDivGraph(buf, ENEMY_ANIM, ENEMY_ANIM, 1, ZAKOA_W, ZAKOA_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_Phase = e_ENEMYSTATE::NEUTRAL;
}

CEnemyBoss::~CEnemyBoss() {
	for (int i = 0; i < (int)e_ENEMYSTATE::NONE; i++) {
		for (int j = 0; j < ENEMY_ANIM; j++) {
			DeleteGraph(m_AnimImage[i][j]);
		}
	}
}

void CEnemyBoss::Update() {
	if (m_Pos.x > 0) {
		m_Pos.x -= m_Speed;
	}
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CEnemyBoss::Draw()const {
	DrawObject(m_Pos, m_AnimImage[(int)m_Phase][0], false, 0.0f);
}

bool CEnemyBoss::HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle) {
	if (IsHitObject(m_Pos, _pos, 40.0f, _zwidth, m_AnimImage[(int)m_Phase][0], _ghandle)) {
		printfDx("Hit\n");
		return true;
	}
	else {
		return false;
	}
}