//---------------------------
//ShadowManager.cpp
//---------------------------
#include"ShadowManager.h"
#include"Stage.h"

CShadowManager* CShadowManager::ms_Instance = nullptr;

//更新タスクの優先度は影を表示するすべてのクラスの更新優先度より大きい値
//描画タスクの優先度はステージの後に描画できるようにする
CShadowManager::CShadowManager(float _priority) : CTask(1.0f,CAST::SHADOW) {
	m_DrawTask.Init(this, std::bind(&CShadowManager::Draw, this), _priority);
	InitShadowList();
	if (ms_Instance == nullptr) {
		ms_Instance = this;
	}
}

CShadowManager::~CShadowManager() {
	InitShadowList();
	if (ms_Instance != nullptr) {
		ms_Instance = nullptr;
	}
}

//影のリストに登録されているアップデートを実行
void CShadowManager::Update() {
}

//影のリストに登録されているDrawを実行
void CShadowManager::Draw()const {
	// 影を背景部分に表示させないようにする
	SetDrawArea(0, WINDOW_H - (int)GROUND_H, WINDOW_W, WINDOW_H);
	for (auto shadow : m_ShadowList) {
		shadow->Draw();
	}
	// 設定を元に戻す
	SetDrawArea(0, 0, WINDOW_W, WINDOW_H);
}

//影のリストに追加
bool CShadowManager::Regist(CShadow* _shadow) {
	assert(_shadow);
	m_ShadowList.push_back(_shadow);
	return true;
}

//影のリストから解除
bool CShadowManager::Remove(CShadow* _shadow) {
	assert(_shadow);
	for (auto it = m_ShadowList.begin(); it != m_ShadowList.end(); ++it) {
		if ((*it) == _shadow) {
			m_ShadowList.erase(it);
		}
		return true;
	}
	return false;
}

//影のリストを空にする
void CShadowManager::InitShadowList() {
	if (!m_ShadowList.empty()) {
		m_ShadowList.clear();
	}
}

//このクラスのインスタンスを取得
CShadowManager* CShadowManager::GetInstance() {
	return ms_Instance;
}