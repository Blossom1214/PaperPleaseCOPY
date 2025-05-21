#pragma once
#include "SceneType.h"
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
class SceneManager
{
public:
	static SceneManager& GetInstance() //싱글턴화 됨
	{
		static SceneManager instance;
		return instance;
	}
	//초기 씬 등록
	void RegisterScene(SceneType type, std::unique_ptr<BaseScene> scene);
	//씬전환
	void ChangeScene(SceneType next);
	//현재씬의 업데이트호출
	void UpdateScene(float dt);
	//현재씬의 렌더를 호출
	void RenderScene();
	//현재씬이 어떤 씬타입인지?
	SceneType GetCurrentSceneType() const;
	void Release();
private:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
private:
	std::unordered_map<SceneType, std::unique_ptr<BaseScene>> _sceneMap;
	BaseScene* _currentScene = nullptr;
	SceneType _currentSceneType= SceneType::TITLE;
	bool _isChanging = false;
};

//씬 매니저가 해야하는 역할들
//새로운 씬으로 들어가면 초기화 함수를 호출함
//씬 교체
//해당씬의 업데이트와 렌더 호출
//해당씬의 정보날리기...