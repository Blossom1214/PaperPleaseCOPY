#include "AnimationManager.h"
#include "ResourceManager.h"
#include "ConvertStr.h"
using namespace std;
void AnimationManager::Register(const wstring& name)
{

	if (_resourceRef.count(name)) return;
	auto& resMgr = ResourceManager::GetInstance();
	ImageResource* res = resMgr.GetImageResource(name);
	if (!res)
	{
		
		string skey = ConvertToString(name);
		auto sectionOpt = resMgr.GetSectionKey(name);

		if (!sectionOpt.has_value())
		{
			OutputDebugString((L"[Register Failed] Section not found for: " + name + L"\n").c_str());
			return;
		}

		resMgr.LazyloadingImageJson(sectionOpt.value(), skey);//옵셔널로 해결해서 밸류를통해 키값을 얻어오기에 성공함

		res = resMgr.GetImageResource(name);
		if (!res) {
			OutputDebugString((L"[Register Failed] AnimationResource not found: " + name + L"\n").c_str());
			return;
		}
	}
	_resourceRef[name] = res;
}

const AnimationSequence* AnimationManager::Get(const wstring& name, const wstring& state)
{
	Register(name);
	auto it = _resourceRef.find(name);
	if(it==_resourceRef.end())
		return nullptr;
	auto& aniMap = it->second->animations;
	auto animIt = aniMap.find(state);
	if (animIt != aniMap.end()) {
		return &animIt->second;
	}return nullptr;
}
