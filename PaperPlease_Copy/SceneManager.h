#pragma once
#include "SceneType.h"
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
class SceneManager
{
public:
	static SceneManager& GetInstance() //�̱���ȭ ��
	{
		static SceneManager instance;
		return instance;
	}
	//�ʱ� �� ���
	void RegisterScene(SceneType type, std::unique_ptr<BaseScene> scene);
	//����ȯ
	void ChangeScene(SceneType next);
	//������� ������Ʈȣ��
	void UpdateScene(float dt);
	//������� ������ ȣ��
	void RenderScene();
	//������� � ��Ÿ������?
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

//�� �Ŵ����� �ؾ��ϴ� ���ҵ�
//���ο� ������ ���� �ʱ�ȭ �Լ��� ȣ����
//�� ��ü
//�ش���� ������Ʈ�� ���� ȣ��
//�ش���� ����������...