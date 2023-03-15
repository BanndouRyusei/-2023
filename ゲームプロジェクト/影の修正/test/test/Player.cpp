//---------------------------
//ControlPlayer.cpp
//---------------------------
#include"Player.h"
#include"Stage.h"
#include"PlayerShot.h"
#include"UI.h"

//定数
const float PLAYER_SHOT_POSY = 60.0f;			//プレイヤーショットの高さ(画像の高さに合わせる)
const float GRAVITY = 30.0f;		//重力
const float JUMP_POWER = 920.0f;		//ジャンプ力

CPlayer::CPlayer(float _priority) :CCharaBase(_priority, CAST::PLAYER),m_AnimImage(),m_Shadow() {
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_HP = PLAYER_HP;
	char buf[30];
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Player_Anim%d.png", i);
		LoadDivGraph(buf, PLAYER_ANIM, PLAYER_ANIM, 1, PLAYER_W, PLAYER_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_NowState = e_PLAYERSTATE::NEUTRAL;
	m_Speed = 4.0f;
	m_Turn = false;
	m_Frame = 0;
	m_Timer = 0;
	m_ShotFlag = false;
	m_Alpha = ALPHA_MAX;
	m_JumpPower = 0.0f;
	m_Inv = true;
	m_InvTimer = 0;
	m_DrawFlag = true;
	m_ShadowImage = LoadGraph("Data\\img\\PlayerShadow.png");
	if (m_ShadowImage == -1)assert(false);
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, 228.0f);
}

CPlayer::~CPlayer() {
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		for (int j = 0; j < PLAYER_ANIM; j++) {
			DeleteGraph(m_AnimImage[i][j]);
		}
	}
	DeleteGraph(m_ShadowImage);
}

void CPlayer::Update() {
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	CHP* hp = (CHP*)CTaskManager::Instance()->GetTask(CAST::HP);
	hp->SetPlayerHp(m_HP);
	switch (m_NowState)
	{
	case e_PLAYERSTATE::NEUTRAL:
	case e_PLAYERSTATE::WALK:
		MovePlayer(key);
		//ShotPlayer(key);
		//PlayerJump(key);
		AnimPlayer();
		break;
	case e_PLAYERSTATE::JUMP:
		MovePlayer(key);
		PlayerJumping();
		break;
	case e_PLAYERSTATE::ATTACK:
		if (!m_ShotFlag&&m_Frame == PLAYER_ATTACKFLAME) {			//弾を出していなくて弾を出すフレームだったら弾を出す。
			float shotposx;
			if (m_Turn) {			//向いている方向によってX発射位置を変える
				shotposx = -PLAYER_SHOT_SIZE;
			}
			else {
				shotposx = PLAYER_W;
			}
			//弾生成
			new CPlayerShot(0.5f, m_Turn, VAdd(m_Pos, VGet(shotposx, PLAYER_SHOT_POSY, 0.0f)));
			m_ShotFlag = true;
		}
		if (m_Frame == PLAYER_ANIM - 1) {		//アニメーションがすべて再生されたらニュートラル
			m_NowState = e_PLAYERSTATE::NEUTRAL;
		}
		AnimPlayer();
		break;
	case e_PLAYERSTATE::DAMAGE:
		if (m_Frame == PLAYER_ANIM - 1) {		//アニメーションがすべて再生されたら
			if (m_HP <= 0) {		//体力が0以下なら死亡
				m_NowState = e_PLAYERSTATE::DEATH;
				m_Frame = 0;
				m_Timer = 0;
			}
			else {
				m_NowState = e_PLAYERSTATE::NEUTRAL;
			}
		}
		AnimPlayer();
		break;
	case e_PLAYERSTATE::DEATH:
		if (m_Frame == PLAYER_ANIM - 1) {		//アニメーションがすべて再生されたら
			PlayerDeth();
		}
		else {
			AnimPlayer();
		}
		break;
	case e_PLAYERSTATE::NONE:
		break;
	default:
		break;
	}

	m_JumpPower -= GRAVITY;
	m_Pos.y += (m_JumpPower*FRAMETIME_S);

	if (m_Pos.y <= 0.0f) {		//地面にめり込まないようにする
		m_Pos.y = 0.0f;
	}

	m_Shadow.CharaPosGet(m_Pos);

	BlinkPlayer();
	m_DrawTask.SetPriority(ChangePriority(m_Pos.z));
}

void CPlayer::Draw() const {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);
	if (m_DrawFlag) {
		DrawObject(m_Pos, m_AnimImage[(int)m_NowState][m_Frame], m_Turn, 0.0f);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);
#if defined(_DEBUG) | defined(DEBUG)
	DrawCircle(m_Pos.x + PLAYER_W / 2, WINDOW_H - m_Pos.y - m_Pos.z - PLAYER_H / 2.0f, 5.0f,GetColor(0, 0, 255), TRUE);
	printfDx("プレイヤー座標　X%f,Y%f,Z%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
	printfDx("プレイヤーの体力　%d\n", m_HP);
	printfDx("操作方法 方向キーで移動(X,Z),Zキーで弾発射,スペースキーでジャンプ,Xキーでダメージ処理\n");
	printf("プレイヤー座標　X%f,Y%f,Z%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
#endif
}

//プレイヤーの移動処理
void CPlayer::MovePlayer(int _key) {
	VECTOR temp = m_Pos;
	if (m_NowState <= e_PLAYERSTATE::WALK) {
		if (_key&PAD_INPUT_A) {			//Zキーだったら
			m_NowState = e_PLAYERSTATE::ATTACK;
			m_Frame = 0;
			m_Timer = 0;
			m_ShotFlag = false;
		}
		if (_key&PAD_INPUT_10) {	//ジャンプ状態へ
			m_NowState = e_PLAYERSTATE::JUMP;
			m_Frame = 1;			//上昇中アニメーションフレームにする
			m_Timer = 0;
			m_JumpPower = JUMP_POWER;
		}
	}
	if (_key & PAD_INPUT_RIGHT) {
		temp.x += m_Speed;
		m_Pos.x = min(temp.x, PLAYER_X_MAX + 1.0f);		//移動可能位置より先にいるなら画面スクロール判定のために移動可能位置より少し先に座標を設定する
		m_Turn = false;
	}
	if (_key & PAD_INPUT_LEFT) {
		temp.x -= m_Speed;
		m_Pos.x = max(temp.x, 0);
		m_Turn = true;
	}
	if (_key & PAD_INPUT_UP) {
		temp.z += m_Speed;
		m_Pos.z = min(temp.z, OBJECT_Z_MAX);
	}
	if (_key & PAD_INPUT_DOWN) {
		temp.z -= m_Speed;
		m_Pos.z = max(temp.z, 0);
	}
	if (_key == 0) {
		if (m_NowState == e_PLAYERSTATE::WALK){
			m_NowState = e_PLAYERSTATE::NEUTRAL;
			m_Frame = 0;
			m_Timer = 0;
		}
	}
	else {
		if (m_NowState == e_PLAYERSTATE::NEUTRAL) {
			m_NowState = e_PLAYERSTATE::WALK;
			m_Frame = 0;
			m_Timer = 0;
		}
	}
	if (IsKeyTrigger(_key, PAD_INPUT_B)) {			//仮でダメージモーションを流す
		m_NowState = e_PLAYERSTATE::DAMAGE;
		m_Frame = 0;
		m_Timer = 0;
		m_HP--;
		m_Inv = true;
		m_InvTimer = 0;
	}
	if (m_Pos.x > PLAYER_X_MAX) {
		CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
		stage->MoveScrollX();
		m_Pos.x = PLAYER_X_MAX;
	}
}

//プレイヤーの弾発射処理
/*void CPlayer::ShotPlayer(int _key) {
	if (_key&PAD_INPUT_A) {			//Zキーだったら
		m_NowState = e_PLAYERSTATE::ATTACK;
		m_Frame = 0;
		m_Timer = 0;
		m_ShotFlag = false;
	}
}*/

//プレイヤーのアニメーション処理
void CPlayer::AnimPlayer() {
	m_Timer++;
	if (m_Timer % (MAX_FPS / 3) == 0) {
		m_Frame++;
		if (m_Frame >= PLAYER_ANIM) {
			m_Frame = 0;
		}
		m_Timer = 0;
	}
}

//プレイヤーの当たり判定
bool CPlayer::HitCheck(const VECTOR &_pos, float _zwidth, int _ghandle, e_PLAYERHITS _hits) {
	if (IsHitObject(m_Pos, _pos, PLAYER_Z_WIDTH, _zwidth, m_AnimImage[(int)m_NowState][m_Frame], _ghandle)) {
		printfDx("Hit\n");
		return true;
	}
	else {
		return false;
	}

	//当たり判定を行った後当たったものの種類によって処理を変える
	/*switch (_hits)
	{
	case e_PLAYERHITS::ENEMYSHOT:
		//無敵状態ならダメージを食らわないようにする
		m_NowState = e_PLAYERSTATE::DAMAGE;
		m_Frame = 0;
		m_Timer = 0;
		m_HP--;
		break;
	case e_PLAYERHITS::ITEM_RECOVERY:
		m_HP++;
		break;
	case e_PLAYERHITS::ITEM_POWERUP:
		break;
	case e_PLAYERHITS::NONE:
	default:
		assert(false);
		break;
	}*/
}

//プレイヤー死亡時の処理　プレイヤーキャラを徐々に透明にする
void CPlayer::PlayerDeth() {
	m_Alpha -= ALPHA_STEP;
	if (m_Alpha <= 0)			//完全に透明になったらDelete();
		Delete();
}

//プレイヤーのジャンプ
/*void CPlayer::PlayerJump(int _key) {
	if (_key&PAD_INPUT_10) {	//ジャンプ状態へ
		m_NowState = e_PLAYERSTATE::JUMP;
		m_Frame = 1;			//上昇中アニメーションフレームにする
		m_Timer = 0;
		m_JumpPower = JUMP_POWER;
	}
}*/

//プレイヤーのジャンプ中の処理
void CPlayer::PlayerJumping() {
	//ジャンプ中のアニメーションは上昇中と落下中があるので
	//アニメーションのフレームの処理が異なる
	if (m_JumpPower <= 0) {			//落下中は落下フレームに切り替える
		m_Frame = 2;
	}
	if (m_Pos.y <= 0) {			//地面より下なら
		m_NowState = e_PLAYERSTATE::NEUTRAL;
	}
}

//無敵状態の点滅
void CPlayer::BlinkPlayer() {
	const float INV_TIME = 2 * MAX_FPS;		//無敵時間(秒数×最大FPS)
	const float RATE = 30;
	if (m_Inv) {		//無敵状態なら
		m_InvTimer++;
		m_DrawFlag = (sinf(DEG2RAD*(m_InvTimer  * RATE)) >= 0.0f) ? true : false;
		if (m_InvTimer >= INV_TIME) {		//無敵時間を超えたら
			m_Inv = false;
			m_DrawFlag = true;
		}
	}
}