//----------
//ControlZakoA.cpp
//Ç±ÇÃÉNÉâÉXÇ≈ÅAéGãõÇÃê∂ê¨ÅAîjâÛó\íË
//----------
#include "Enemy.h"
#include "myLib.h"

const int APPEAR_WAIT = 10;
const int APPEAR_RAND = 33;

const int ZAKOA_CX = 800;
const int ZAKOA_SPEED = 1;
const int ZAKOA_HP = 3;
const int ZAKOA_COUNT = 20;

CControlZakoA::CControlZakoA(BYTE _MaxEnemy, float _priority):CTask(_priority,CAST::CONTROLZAKOA) {
	m_Timer = 0;
	m_EnemyCount = 0;
	//m_Hp = 0;
}

CControlZakoA::~CControlZakoA() {}

void CControlZakoA::Update() {
	if (m_Timer++ < APPEAR_WAIT) return;
	m_Timer = 0;
	if (rand() % 100 < APPEAR_RAND && CTaskManager::Instance()->GetCount(CAST::ZAKO_A) < m_MaxEnemy) {
		new CEnemyZakoA((float)(rand()%WINDOW_W),ZAKOA_CX,ZAKOA_SPEED,0.5f);
		m_EnemyCount += 1;
		//m_Hp++;
	}
}

