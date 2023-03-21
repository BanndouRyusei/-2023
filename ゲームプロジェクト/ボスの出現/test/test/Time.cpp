//---------------------------
// TIME
//---------------------------
#include"UI.h"

const int TIME_SIZE = 40;

const int TIME_WPOS = 650;
const int TIME_HPOS = 110;

const int MAX_TIME = 9999;

CTime::CTime(float _priority) :CTask(_priority, CAST::TIME){
	m_DrawTask.Init(this, std::bind(&CTime::Draw, this), _priority);
	m_Time = 0;
	m_NextPos = TIME_WPOS;
	m_Digit = 1;
	m_DigitCount = 0;
	m_StartTime = GetNowCount();	// ゲームスタート時間
	LoadDivGraph("Data\\img\\UI_Num.png", DIGITS, DIGITS, 1, TIME_SIZE, TIME_SIZE, m_TimeImage);
}

CTime::~CTime() {
	for (int i = 0; i < DIGITS; i++) {
		DeleteGraph(m_TimeImage[i]);
	}
}

void CTime::Update() {
	if (m_Time < MAX_TIME) {
		m_Time = (GetNowCount() - m_StartTime) / 1000;		// 経過時間の計算
		m_GetDigits(m_Time);
		// 桁が上がるごとに画像の表示位置をずらす
		if (!(m_Time < m_Digit * 10) && m_Time <= 10 || !(m_Time < m_Digit * 10)) {
			m_DigitCount++;
			m_Digit *= 10;
			m_NextPos = TIME_WPOS + (TIME_SIZE * m_DigitCount);
		}
	}
}

void CTime::Draw() const {
	DrawGraph(m_NextPos, TIME_HPOS, m_TimeImage[m_OneDgt], true);
	if (10 <= m_Time)	DrawGraph(m_NextPos - TIME_SIZE, TIME_HPOS, m_TimeImage[m_TwoDgt], true);
	if (100 <= m_Time)	DrawGraph(m_NextPos - TIME_SIZE * 2, TIME_HPOS, m_TimeImage[m_ThreeDgt], true);
	if (1000 <= m_Time)	DrawGraph(m_NextPos - TIME_SIZE * 3, TIME_HPOS, m_TimeImage[m_FourDgt], true);
}

// 各桁の数字を取り出す
void CTime::m_GetDigits(int _num) {
	int Num = _num;

	// 1桁目の数字（一の位）
	m_OneDgt = Num % 10;

	// 2桁目の数字（十の位）
	m_TwoDgt = (Num % 100) / 10;

	// 3桁目の数字（百の位）
	m_ThreeDgt = (Num % 1000) / 100;

	// 4桁目の数字（千の位）
	m_FourDgt = Num / 1000;
}