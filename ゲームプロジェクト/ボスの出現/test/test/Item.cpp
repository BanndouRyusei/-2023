//---------------------------
//Item.cpp
//---------------------------
#include"Item.h"
#include"Stage.h"

//�萔
const int ITEM_SIZE = 100;			//�A�C�e���̏c���T�C�Y
const float ITEM_Z_WIDTH = 40;			//�A�C�e����Z���̌���
const float ITEM_Y = 300.0f;			//�A�C�e���̑؋�Y���W
const float ITEM_SPEED = 5.0f;		//�A�C�e���̏㏸�X�s�[�h
const float ITEM_SHADOW_Y = ITEM_Y + 500.0f;			//�A�C�e���̉e��Y���W�̍ő�l(500.0f�͒����l)

CItem::CItem(float _priority, const VECTOR _pos) :CObjectBase(_priority, CAST::ITEM),m_Shadow() {
	m_Pos = _pos;
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	m_Scroll = stage->GetScrollX()*STAGE_SCROLLX;
	m_Type = (e_PLAYERHITS)GetRand((int)e_PLAYERHITS::ITEM_POWERUP);			//�����_���ŉ񕜂��U��up�����߂�
	m_Frame = 0;
	m_Timer = 0;
	char buf[30];
	sprintf_s(buf, "Data\\img\\Item%d.png", (int)m_Type);
	LoadDivGraph(buf, ITEM_ANIM, ITEM_ANIM, 1, ITEM_SIZE, ITEM_SIZE, m_Image);
	if (m_Image[0] == -1)assert(false);
	m_ShadowImage = LoadGraph("Data\\img\\ItemShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, false, ITEM_SHADOW_Y);
}

CItem::~CItem() {
	for (int i = 0; i < ITEM_ANIM; i++) {
		DeleteGraph(m_Image[i]);
	}
}

void CItem::Update() {
	m_Pos.y += ITEM_SPEED;
	if (m_Pos.y >= ITEM_Y) {
		m_Pos.y = ITEM_Y;
	}
	MoveItem();
	m_Shadow.ObjectPosGet(m_Pos, false);
	AnimItem();
	HitCheck();
	PosCheck();
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CItem::Draw() const {
	DrawObject(m_Pos, m_Image[m_Frame], false, 0.0f);
}

//�A�C�e���̃A�j���[�V����
void CItem::AnimItem() {
	m_Timer++;
	if (m_Timer % ANIM_TIME == 0) {
		m_Frame++;
		if (m_Frame >= ITEM_ANIM) {
			m_Frame = 0;
		}
		m_Timer = 0;
	}
}

//�v���C���[�Ƃ̓����蔻��
void CItem::HitCheck() {
	CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
	if (player != nullptr) {
		if (player->HitCheck(m_Pos, ITEM_Z_WIDTH, m_Image[m_Frame], m_Type)) {
			Delete();
		}
	}
}

//��ʊO�ɏo�����̏���
void CItem::PosCheck() {
	float left = m_Pos.x, right = m_Pos.x + ITEM_SIZE;
	if (left >= WINDOW_W || right <= 0) {		//��ʒ[���O�Ȃ����
		Delete();
	}
}

//�A�C�e���̈ړ�
void CItem::MoveItem() {
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	//���݂̃X�N���[���ʂƃA�C�e���������Ă���O��̃X�N���[���ʂ̍������ړ�����
	m_Pos.x -= stage->GetScrollX() * STAGE_SCROLLX - m_Scroll;
	//�O��̃X�N���[���ʂ��X�V
	m_Scroll = stage->GetScrollX() * STAGE_SCROLLX;
}