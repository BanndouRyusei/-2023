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
	m_StartTime = GetNowCount();	// �Q�[���X�^�[�g����
	LoadDivGraph("Data\\img\\UI_Num.png", DIGITS, DIGITS, 1, TIME_SIZE, TIME_SIZE, m_TimeImage);
}

CTime::~CTime() {
	for (int i = 0; i < DIGITS; i++) {
		DeleteGraph(m_TimeImage[i]);
	}
}

void CTime::Update() {
	if (m_Time < MAX_TIME) {
		m_Time = (GetNowCount() - m_StartTime) / 1000;		// �o�ߎ��Ԃ̌v�Z
		m_GetDigits(m_Time);
		// �����オ�邲�Ƃɉ摜�̕\���ʒu�����炷
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

// �e���̐��������o��
void CTime::m_GetDigits(int _num) {
	int Num = _num;

	// 1���ڂ̐����i��̈ʁj
	m_OneDgt = Num % 10;

	// 2���ڂ̐����i�\�̈ʁj
	m_TwoDgt = (Num % 100) / 10;

	// 3���ڂ̐����i�S�̈ʁj
	m_ThreeDgt = (Num % 1000) / 100;

	// 4���ڂ̐����i��̈ʁj
	m_FourDgt = Num / 1000;
}