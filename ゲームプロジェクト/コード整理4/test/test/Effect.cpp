//---------------------------
//Effect.cpp
//---------------------------
#include"Effect.h"
#include"Player.h"

//定数
const int EFFECT_SIZE = 200;
const int EFFECT_ANIM_SPEED = MAX_FPS / 6;

CEffect::CEffect(float _priority,e_EFFECTS _type) :CObjectBase(_priority, CAST::EFFECT) {
	CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
	if (player != nullptr) {
		m_Pos = player->GetPos();
	}
	m_Type = _type;
	m_Frame = 0;
	m_Timer = 0;
	char buf[30];
	sprintf_s(buf, "Data\\img\\Effect%d.png", (int)m_Type);
	LoadDivGraph(buf, EFFECT_ANIM, EFFECT_ANIM / 2, 2, EFFECT_SIZE, EFFECT_SIZE, m_Image);
	if (m_Image[0] == -1)assert(false);
}

CEffect::~CEffect() {
	for (int i = 0; i < EFFECT_ANIM; i++) {
		DeleteGraph(m_Image[i]);
	}
}

void CEffect::Update() {
	CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
	if (player != nullptr) {			//プレイヤーがいる場所に座標更新
		m_Pos = player->GetPos();
	}
	switch (m_Type)
	{
	case e_EFFECTS::RECOVERY:
		m_Timer++;
		if (m_Timer % EFFECT_ANIM_SPEED == 0) {
			m_Frame++;
			if (m_Frame >= EFFECT_ANIM) {
				Delete();			//再生が終わったら削除
			}
			m_Timer = 0;
		}
		break;
	case e_EFFECTS::POWERUP:
		m_Timer++;
		if (m_Timer % EFFECT_ANIM_SPEED == 0) {
			m_Frame++;
			if (m_Frame >= EFFECT_ANIM) {
				m_Frame = 0;
			}
			m_Timer = 0;
		}
		if (!player->GetPower()) {			//攻撃力アップ状態が終わったら削除
			Delete();
		}
		break;
	case e_EFFECTS::NONE:
	default:
		assert(false);
		break;
	}

	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CEffect::Draw() const {
	DrawObject(m_Pos, m_Image[m_Frame], false, 0.0f);
}

void CEffect::AnimEffect() {

}