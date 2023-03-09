//---------------------------
//ControlPlayer.cpp
//---------------------------
#include"Player.h"


CPlayer::CPlayer(float _priority) :Task(_priority, CAST::PLAYER) {
	m_drawTask.Init(this, std::bind(&CPlayer::Draw, this), OBJECT_DRAWPRIORITY_MIN);
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_HP = PLAYER_HP;
	char buf[30];
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Player_Anim%d.png", i);
		LoadDivGraph(buf, PLAYER_ANIM, PLAYER_ANIM, 1, PLAYER_W, PLAYER_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_Phase = e_PLAYERSTATE::NEUTRAL;
	m_Speed = 5.0f;
}

CPlayer::~CPlayer() {
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		for (int j = 0; j < PLAYER_ANIM; j++) {
			DeleteGraph(m_AnimImage[i][j]);
		}
	}
}

void CPlayer::Update() {
	MovePlayer();
}

void CPlayer::Draw() const {
	//DrawRotaGraph2F(m_Pos.x, m_Pos.y - m_Pos.z, PLAYER_W / 2.0f, PLAYER_H / 2.0f, 1.0, 0.0f, m_AnimImage[(int)m_Phase][0], TRUE);
	DrawObject(m_Pos, m_AnimImage[(int)m_Phase][0], true);
}

void CPlayer::MovePlayer() {
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	VECTOR temp = m_Pos;
	if (key & PAD_INPUT_RIGHT) {
		temp.x += m_Speed;
		m_Pos.x = min(temp.x, PLAYER_X_MAX);
	}
	if (key & PAD_INPUT_LEFT) {
		temp.x -= m_Speed;
		m_Pos.x = max(temp.x, 0);
	}
	if (key & PAD_INPUT_UP) {
		temp.z += m_Speed;
		m_Pos.z = min(temp.z, OBJECT_Z_MAX);
	}
	if (key & PAD_INPUT_DOWN) {
		temp.z -= m_Speed;
		m_Pos.z = max(temp.z, 0);
	}
}