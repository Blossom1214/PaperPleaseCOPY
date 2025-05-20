#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "ImageResource.h"
namespace Gdiplus {
	class Graphics;
	class Image;
}

class ResourceManager
{
public:
	//singleton
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}
	//preloading
	void PreloadingImageJson();
	//lazy loading
	void LazyloadingImageJson(std::string& strkey, std::string& strimg);
	//resource memory clear
	void Clear();
	//initial
	void InitImgJson();
	//get rootsegmention section key (value use)
	std::optional<std::string>GetSectionKey(const std::wstring& name);
	//get image
	ImageResource* GetImageResource(const std::wstring& key);
private:
	//file load
	Gdiplus::Image* LoadImageFromFile(const std::wstring& path); 
private:
	ResourceManager() = default;
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	std::unordered_map<std::wstring, ImageResource> _images;
	nlohmann::json _jsonImgData;
	
};

//초기 이미지 로드할 것들을 정확하게 가져와주기!
//그뒤에 실시간으로 로드를 할 때는 음.... 실시간 추가 파일로 만들어 줘야할듯?
//그럼 함수가 3개여야하는거같은데? 


//1)선로딩
//2)로딩파일
//3)실시간로딩

//4 파일열기
//5 파일닫기필요
//6 해당파일을 저장할 공간도 필요

