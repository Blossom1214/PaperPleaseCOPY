#pragma once
#include<string>
#include<unordered_map>
#include"ImageResource.h"
class AnimationManager
{
public:
	static AnimationManager& GetInstance() //ΩÃ±€≈œ»≠ µ 
	{
		static AnimationManager instance;
		return instance;
	}
	const AnimationSequence* Get(const std::wstring& name  , const std::wstring& state);
private:
	void Register(const std::wstring& name);
	AnimationManager() = default;
	~AnimationManager() = default;
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;
	std::unordered_map<std::wstring, ImageResource*> _resourceRef;
};
