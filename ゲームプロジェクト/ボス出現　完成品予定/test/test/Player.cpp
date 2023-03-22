//---------------------------
//Player.cpp
//---------------------------
#include"Player.h"
#include"Stage.h"
#include"PlayerShot.h"
#include"UI.h"
#include"Effect.h"
#include"Sound.h"
#if defined(_DEBUG) | defined(DEBUG)
#include"Item.h"		//仮でアイテムを出すために読みんでいる
#endif

//定数
const int PLAYER_ATTACKFLAME = 2;			//プレイヤーの攻撃フレーム
const int PLAYER_JUMPFLAME = 1;				//プレイヤーの上昇終了フレーム
const int PLAYER_FALLFLAME = 3;				//プレイヤーの落下終了フレーム
//プレイヤー画像の大きさ
const int PLAYER_H = 200;
const int PLAYER_W = 200;
//プレイヤーの移動可能位置X
const float PLAYER_X_MAX = WINDOW_W / 2 - PLAYER_W;
//プレイヤーのZ軸の厚さ
const float PLAYER_Z_WIDTH = 40.0f;
const float PLAYER_SHOT_POSY = 60.0f;			//プレイヤーショットの高さ(画像の高さに合わせる)
const float GRAVITY = 30.0f;		//重力
const float JUMP_POWER = 920.0f;		//ジャンプ力
const float PLAYER_SHADOW_Y = WINDOW_H - PLAYER_H - 50.0f - OBJECT_Z_MAX;			//プレイヤーの影のYの最大値(50は調整値)
const int PLAYER_POWER_MAX = 2;				//プレイヤーの最大攻撃力
const float PLAYER_POWERUP_TIME = 10 * MAX_FPS;			//攻撃力アップ時間

CPlayer::CPlayer(float _priority) :CCharaBase(_priority, CAST::PLAYER),m_AnimImage() {
	m_Pos = VGet(0.0f, 0.0f, 39.0f);
	m_HP = PLAYER_HP;
	char buf[30];
	for (int i = 0; i < (int)e_PLAYERSTATE::NONE; i++) {
		sprintf_s(buf, "Data\\img\\Player_Anim%d.png", i);
		LoadDivGraph(buf, PLAYER_ANIM, PLAYER_ANIM, 1, PLAYER_W, PLAYER_H, m_AnimImage[i]);
		if (m_AnimImage[i][0] == -1)assert(false);
	}
	m_NowState = e_PLAYERSTATE::NEUTRAL;
	m_Speed = 4.0f;
	m_Power = 1;
	m_PowerUpTimer = 0;
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
	m_Shadow.SetShadow(m_ShadowImage, m_Pos, m_Turn, PLAYER_SHADOW_Y);
}

CPlayer::~CPlayer() {
	CTaskManager::Instance()->EraseTask(CAST::EFFECT);
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
			CControlSound::GetInstance()->CreateSE(e_SE::SHOT);
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

	if (m_Power >= PLAYER_POWER_MAX) {			//攻撃力アップ状態なら
		if (m_PowerUpTimer++ >= PLAYER_POWERUP_TIME) {			//攻撃力アップ時間を過ぎたら
			m_Power = 1;
		}
	}

	m_Shadow.ObjectPosGet(m_Pos, m_Turn);

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
	printfDx("プレイヤーの体力　%d　プレイヤーの攻撃力%d\n", m_HP,m_Power);
	printfDx("操作方法 方向キーで移動(X,Z),Zキーで弾発射,スペースキーでジャンプ,Xキーでダメージ処理\n");
	printfDx("Cキーでアイテム出現\n");
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
			m_Frame = 0;
			m_Timer = 0;
			m_JumpPower = JUMP_POWER;
			CControlSound::GetInstance()->CreateSE(e_SE::JUMP);
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
#if defined(_DEBUG) | defined(DEBUG)
	if (IsKeyTrigger(_key, PAD_INPUT_B)) {			//仮でダメージモーションを流す
		m_NowState = e_PLAYERSTATE::DAMAGE;
		m_Frame = 0;
		m_Timer = 0;
		m_HP--;
		m_Inv = true;
		m_InvTimer = 0;
		CControlSound::GetInstance()->CreateSE(e_SE::HIT);
	}
	if (IsKeyTrigger(_key, PAD_INPUT_C)) {			//仮でアイテムを出現
		float items = (float)CTaskManager::Instance()->GetCount(CAST::ITEM);
		if ((float)GetRand(100) < (APPER_RAND - (float)GetRand(30) - ((float)m_HP + items) / (float)PLAYER_HP * APPER_RAND)) {
			new CItem(0.6f, VGet(m_Pos.x + 200.0f, m_Pos.y, m_Pos.z));
		}
	}
#endif
	if (m_Pos.x > PLAYER_X_MAX) {
		CStage* stage = (CStage*)CTaskManager::Instance()->GetTask(CAST::STAGE);
		stage->MoveScrollX();
		m_Pos.x = PLAYER_X_MAX;
	}
}

//プレイヤーのアニメーション処理
void CPlayer::AnimPlayer() {
	m_Timer++;
	if (m_Timer % ANIM_TIME == 0) {
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
		//当たり判定を行った後当たったものの種類によって処理を変える
		switch (_hits)
		{
		case e_PLAYERHITS::ITEM_RECOVERY:
			m_HP = min(m_HP++, PLAYER_HP);
			new CEffect(0.7f, (e_EFFECTS)_hits);
			CControlSound::GetInstance()->CreateSE(e_SE::RECOVERY);
			break;
		case e_PLAYERHITS::ITEM_POWERUP:
			//攻撃力アップ
			m_Power = min(m_Power++, PLAYER_POWER_MAX);
			m_PowerUpTimer = 0.0f;
			new CEffect(0.7f, (e_EFFECTS)_hits);
			CControlSound::GetInstance()->CreateSE(e_SE::POWERUP);
			break;
		case e_PLAYERHITS::ENEMYSHOT:
			//無敵状態ならダメージを食らわないようにする
			if (!m_Inv&&m_NowState != e_PLAYERSTATE::DEATH) {
				m_NowState = e_PLAYERSTATE::DAMAGE;
				m_Frame = 0;
				m_Timer = 0;
				m_HP--;
				m_Inv = true;
				m_InvTimer = 0;
				CControlSound::GetInstance()->CreateSE(e_SE::HIT);
			}
			break;
		case e_PLAYERHITS::NONE:
		default:
			assert(false);
			break;
		}
		return true;
	}
	else {
		return false;
	}
}

//プレイヤー死亡時の処理　プレイヤーキャラを徐々に透明にする
void CPlayer::PlayerDeth() {
	static bool seflag = false;
	if (!seflag) {
		CControlSound::GetInstance()->CreateSE(e_SE::DEATH);
		seflag = true;
	}
	m_Alpha -= ALPHA_STEP;
	if (m_Alpha <= 0) {		//完全に透明になったらDelete();
		Delete();
		seflag = false;
	}
}

//プレイヤーのジャンプ中の処理
void CPlayer::PlayerJumping() {
	//ジャンプ中のアニメーションは上昇中と落下中があるので
	//アニメーションのフレームの処理が異なる
	if (m_JumpPower > 0) {				//上昇中は上昇中アニメーションを再生
		m_Timer++;
		if (m_Timer % ANIM_TIME == 0) {
			m_Frame++;
			if (m_Frame >= PLAYER_JUMPFLAME) {
				m_Frame = PLAYER_JUMPFLAME;
				m_Timer = 0;
			}
			m_Timer = 0;
		}
	}
	if (m_JumpPower <= 0) {			//落下中は落下アニメーションに切り替える
		m_Timer++;
		if (m_Timer % ANIM_TIME == 0) {
			m_Frame++;
			if (m_Frame >= PLAYER_FALLFLAME) {
				m_Frame = PLAYER_FALLFLAME;
				m_Timer = 0;
			}
			m_Timer = 0;
		}
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

//プレイヤーの体力を取得
float CPlayer::GetHP() {
	return (float)m_HP;
}

//プレイヤーの座標を取得
const VECTOR& CPlayer::GetPos() {
	return m_Pos;
}

//プレイヤーの攻撃力アップ状態を調べる
//アップ状態ならtrue
bool CPlayer::GetPower() {
	if (m_Power >= PLAYER_POWER_MAX) {
		return true;
	}
	return false;
}