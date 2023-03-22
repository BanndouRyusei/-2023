//---------------------------
//Item.cpp
//---------------------------
#include"Item.h"
#include"Stage.h"

//定数
const int ITEM_SIZE = 100;			//アイテムの縦横サイズ
const float ITEM_Z_WIDTH = 40;			//アイテムのZ軸の厚さ
const float ITEM_Y = 300.0f;			//アイテムの滞空Y座標
const float ITEM_SPEED = 5.0f;		//アイテムの上昇スピード
const float ITEM_SHADOW_Y = ITEM_Y + 500.0f;			//アイテムの影のY座標の最大値(500.0fは調整値)

CItem::CItem(float _priority, const VECTOR _pos) :CObjectBase(_priority, CAST::ITEM),m_Shadow() {
	m_Pos = _pos;
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	m_Scroll = stage->GetScrollX()*STAGE_SCROLLX;
	m_Type = (e_PLAYERHITS)GetRand((int)e_PLAYERHITS::ITEM_POWERUP);			//ランダムで回復か攻撃upを決める
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

//アイテムのアニメーション
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

//プレイヤーとの当たり判定
void CItem::HitCheck() {
	CPlayer* player = (CPlayer*)CTaskManager::Instance()->GetTask(CAST::PLAYER);
	if (player != nullptr) {
		if (player->HitCheck(m_Pos, ITEM_Z_WIDTH, m_Image[m_Frame], m_Type)) {
			Delete();
		}
	}
}

//画面外に出た時の処理
void CItem::PosCheck() {
	float left = m_Pos.x, right = m_Pos.x + ITEM_SIZE;
	if (left >= WINDOW_W || right <= 0) {		//画面端より外なら消す
		Delete();
	}
}

//アイテムの移動
void CItem::MoveItem() {
	CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
	//現在のスクロール量とアイテムが持っている前回のスクロール量の差だけ移動する
	m_Pos.x -= stage->GetScrollX() * STAGE_SCROLLX - m_Scroll;
	//前回のスクロール量を更新
	m_Scroll = stage->GetScrollX() * STAGE_SCROLLX;
}