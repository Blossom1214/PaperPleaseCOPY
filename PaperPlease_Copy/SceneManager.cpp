#include "SceneManager.h"
using namespace std;
void SceneManager::RegisterScene(SceneType type, unique_ptr<BaseScene> scene)
{
	_sceneMap[type] = move(scene);
}

void SceneManager::ChangeScene(SceneType next)
{
	if (_currentSceneType == next || _isChanging)
		return;
	_isChanging = true;
	
	if (_currentScene)
		_currentScene->Release();
	//해시맵에서 다음 타입에 해당하는 씬을 찾아줘
	auto it = _sceneMap.find(next);
	//찾으면 밸류를 겟해온걸 현재 씬으로 전환해
	if (it != _sceneMap.end()) {
		_currentScene = it->second.get();
	}
	else//아니면 nullptr 
	{
		_currentScene = nullptr; // 또는 예외 처리
	}
	//그거의 초기화를 불러봐
	if (_currentScene)
		_currentScene->Init();
	//그리고 내가 입력한 타입을 넥스트로 불러
	_currentSceneType = next;
	//그리고 안바꾼다고 알려
	_isChanging = false;
}

void SceneManager::UpdateScene(float dt)
{
	if (_currentScene)
		_currentScene->Update(dt);
}

void SceneManager::RenderScene()
{
	if (_currentScene)
		_currentScene->Render();
}

SceneType SceneManager::GetCurrentSceneType() const
{
	return _currentSceneType;
}
void SceneManager::Release()
{
	//처음 씬을 등록자체를 make_unique로 하기때문에 릴리즈가 따로 필요가있지는않음
}