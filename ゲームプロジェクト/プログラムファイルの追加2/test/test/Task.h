#pragma once

class CTaskManager;

//タスクの識別子
enum class CAST
{
	CONTROLPLAYER,PLAYER,PLAYERSHOT, CONTROLZAKOA, ZAKO_A,
	CONTROLZAKOB, ZAKO_B, CONTROLBOSS, BOSS,STAGE,LIFE,HP,UI,TIME,SCORE, CONTROLSOUND, BGM, SE ,GAMECLEAR,GAMEOVER, NONE //タスクを作る事に、識別子をここに登録する
};

class CTask 
{
	friend CTaskManager;

private:
	CTask* m_prev;		//前のタスクへのポインタ
	CTask* m_next;		//次のタスクへのポインタ
	float m_priority;		//優先度(値が小さいほど先に更新)
	bool m_isActive;		//タスクの生死
	CAST m_id;			//タスク識別子
	bool m_guard;		//タスクが死なないようにする変数		true(消さない)
public:
	//コンストラクタ
	CTask(float prio,CAST _id);
	//デストラクタ
	virtual ~CTask();

	//優先度を設定
	void SetPriority(float prio);
	//優先度を取得
	float GetPriority() const;
	//死なないようにする変数を設定
	void IsGuardFlg(const bool _isGuard)
	{
		m_guard = _isGuard;
	}
	//タスクを削除
	void Delete();
	//更新処理
	virtual void Update() = 0;
};