//---------------------------
// TIME
//---------------------------
#include"UI.h"

CTime::CTime(float _priority) :CTask(_priority, CAST::TIME){
	m_DrawTask.Init(this, std::bind(&CTime::Draw, this), _priority);
	m_Time = 0;

	m_StartTime = GetNowCount();	// ゲームスタート時間
//	LoadDivGraph("Data\\img\\UI_Num.png", WIDTH * HEIGHT, WIDTH, HEIGHT, CHIPSIZE, CHIPSIZE, m_TimeImage);
}

CTime::~CTime() {
//	for (int i = 0; i < WIDTH * HEIGHT; i++)
//		DeleteGraph(m_TimeImage[i]);
}

void CTime::Update() {
//	m_Time = (GetNowCount() - m_StartTime) / 1000;
}

void CTime::Draw() const {

}