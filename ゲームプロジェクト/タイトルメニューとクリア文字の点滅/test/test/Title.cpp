//----------------------
//Title.cpp
//----------------------

//�w�b�_�[�t�@�C��
#include"Title.h"
#include"Sound.h"

CTitle::CTitle(float _priority) :CTask(_priority, CAST::TITLE) {
	m_DrawTask.Init(this, std::bind(&CTitle::Draw, this), _priority);
	m_Timer = 0;
	m_Phase = PHASE::START;
	m_Alpha = 0;
	m_Image = LoadGraph("Data\\img\\Title.png");
	if (m_Image == -1)assert(false);
}

CTitle::~CTitle() {
	DeleteGraph(m_Image);
}

void CTitle::Update() {
	int key;

	m_Timer++;

	switch (m_Phase)
	{
	case PHASE::START:
		m_Alpha = m_Timer * ALPHA_STEP;
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key || m_Alpha >= ALPHA_MAX) {
			m_Phase = PHASE::PLAY;
			m_Alpha = ALPHA_MAX;
		}
		break;
	case PHASE::PLAY:
		new CTitleMenu(0.5f);			//���j���[�Ăяo��
		m_Phase = PHASE::END;
		break;
	case PHASE::END:
		if (!CTaskManager::Instance()->GetCount(CAST::TITLEMENU)) {
			Delete();
		}
		break;
	case PHASE::NONE:
	default:
		assert(false);
	}
}

void CTitle::Draw() const {
	SetDrawBright(m_Alpha, m_Alpha, m_Alpha);
	DrawGraph(0, 0, m_Image, TRUE);
	SetDrawBright(ALPHA_MAX, ALPHA_MAX, ALPHA_MAX);
}

CTitleMenu::CTitleMenu(float _priority) : CTask(_priority,CAST::TITLEMENU), m_MenuImage() {
	m_DrawTask.Init(this, std::bind(&CTitleMenu::Draw, this), _priority);
	m_Item = 0;
	m_SelectMenu = TITLE_MENU;
	m_Alpha = ALPHA_MAX;
	m_AlphaTurn = -1;
	m_IsDecide = false;			//false=������
	m_CusorImage = LoadGraph("Data\\img\\MenuCursor.png");
	if (m_CusorImage == -1)assert(false);
	char buf[30];
	for (int i = 0; i < TITLE_MENU; i++) {
		sprintf_s(buf, "Data\\img\\TitleMenu%d.png", i);
		m_MenuImage[i] = LoadGraph(buf);
		if (m_MenuImage[i] == -1)assert(false);
	}
}

CTitleMenu::~CTitleMenu() {
	DeleteGraph(m_CusorImage);
	for (int i = 0; i < TITLE_MENU; i++) {
		DeleteGraph(m_MenuImage[i]);
	}
}

void CTitleMenu::Update(void) {
	CBGM* bgm = (CBGM*)CTaskManager::Instance()->GetTask(CAST::BGM);

	if (!m_IsDecide) {			//�܂����j���[�����߂Ă��Ȃ�������
		//�I�΂�Ă��郁�j���[������_�ł�����
		m_Alpha += TITLE_SELECTMENU_ALPHA_STEP * m_AlphaTurn;
		if (m_Alpha > ALPHA_MAX || m_Alpha < 0) {
			m_Alpha = ALPHA_MAX * m_AlphaTurn;			//�l�̏�����(ALPHA_MAX���傫���ꍇ��ALPHA_MAX)
			if (m_Alpha < 0) {			//0��菬�����ꍇ��0
				m_Alpha = 0;
			}
			m_AlphaTurn *= -1;			//�����l�̔��]
		}
	}

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (!m_IsDecide&&IsKeyTrigger(key, PAD_INPUT_UP)) {
		//CControlSound::GetInstance()->CreateSE(e_SE::SELECT);		//���j���[�ړ����Đ�
		m_Alpha = ALPHA_MAX;
		m_AlphaTurn = -1;
		m_Item--;
	}
	if (!m_IsDecide&&IsKeyTrigger(key, PAD_INPUT_DOWN)) {
		//CControlSound::GetInstance()->CreateSE(e_SE::SELECT);		//���j���[�ړ����Đ�
		m_Alpha = ALPHA_MAX;
		m_AlphaTurn = -1;
		m_Item++;
	}
	if (m_Item < MENU_MIN)m_Item = MENU_MAX;
	if (m_Item > MENU_MAX)m_Item = MENU_MIN;

	if (!m_IsDecide&&IsKeyTrigger(key, PAD_INPUT_A)) {			//�܂����j���[�����肵�Ă��Ȃ��Č���L�[�������ꂽ��
		//CControlSound::GetInstance()->CreateSE(e_SE::SELECT);		//���艹�Đ�
		m_SelectMenu = m_Item;		//�I�񂾔ԍ����Z�b�g
		m_Alpha = ALPHA_MAX;
		//bgm->ChangePhase(PHASE::END);			//BGM���~�߂�
		m_IsDecide = true;
	}
	if (m_IsDecide) {		//���肳��Ă�����
		//if (!CTaskManager::Instance()->GetCount(CAST::BGM)) {			//BGM�����񂾂�
			throw(m_SelectMenu);		//�I�񂾔ԍ��𓊂���	
			Delete();
	//	}
	}
}

void CTitleMenu::Draw(void) const {
	for (int i = 0; i < TITLE_MENU; i++) {
		if (i == m_Item) {
			DrawGraph(TITLE_MENU_X - TITLE_CORSOR_SIZE, TITLE_MENU_Y + TITLE_MENU_SPECE * i, m_CusorImage, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);
			DrawGraph(TITLE_MENU_X, TITLE_MENU_Y + TITLE_MENU_SPECE * i, m_MenuImage[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);
			continue;
		}
		DrawGraph(TITLE_MENU_X, TITLE_MENU_Y + TITLE_MENU_SPECE * i, m_MenuImage[i], TRUE);
	}
}