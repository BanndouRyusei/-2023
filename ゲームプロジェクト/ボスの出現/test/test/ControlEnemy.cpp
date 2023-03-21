//----------
//CControlEnemy.cpp
//----------
#include "Enemy.h"
#include "Stage.h"

using namespace std;

const float BOSS_Z = 60.0f;			//ボスの出現位置Z

CControlEnemy::CControlEnemy(float _priority) :CTask(_priority, CAST::CONTROLENEMY) {
	m_BossFlag = true;
	m_ScrollX = 0;
	LoadEnemy();
}

CControlEnemy::~CControlEnemy() {};

void CControlEnemy::Update() {
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	m_ScrollX = stage->GetScrollX();
	MakeBoss();
}

void CControlEnemy::LoadEnemy()
{
	//エネミー配置情報読み込み
	fopen_s(&fp, "Data\\txt\\Data.txt", "r");
	fscanf_s(fp, "%d", &enemynum);  //配置エネミー数
	for (int i = 1; i <= enemynum; i++) {
		fscanf_s(fp, "%d,%f,%f,%f", &EnemyNo, &temp.Pos.x,
			&temp.Pos.y, &temp.Pos.z);

		switch (EnemyNo)
		{
		case 1:
			new CZakoA(temp.Pos.x, temp.Pos.y, temp.Pos.z, 0.5f);
			break;
		case 2:
			new CZakoB(temp.Pos.x, temp.Pos.y, temp.Pos.z, 0.5f);
			break;
		case 3:
			new CBoss(temp.Pos.x, temp.Pos.y, temp.Pos.z, 0.5f);
			break;
		default:
			break;
		}
	}
	fclose(fp);

}

void CControlEnemy::MakeBoss() {
	int zakoa, zakob;
	zakoa = CTaskManager::Instance()->GetCount(CAST::ZAKO_A);
	zakob = CTaskManager::Instance()->GetCount(CAST::ZAKO_B);
	if ((zakoa + zakob) == 0 && m_BossFlag) {			//ボス出現フラグが立っていて雑魚敵がすべて死んでいたら
		new CBoss((float)WINDOW_W, 0.0f, BOSS_Z, 0.5f);
		m_BossFlag = false;
	}
}