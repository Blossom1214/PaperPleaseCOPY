#include "ResourceManager.h"
#include "framework.h"
#include <fstream>
#include "ConvertStr.h"
using namespace std;
using namespace Gdiplus;
void ResourceManager::PreloadingImageJson()
{
    for (const auto& [key, value] : _jsonImgData["images"].items()) {
        wstring wkey = ConvertToWString(key);
        wstring wpath = ConvertToWString(value["path"]);
        auto img = LoadImageFromFile(wpath); 
        if (!img) continue;
        ImageResource r;
        r.img = unique_ptr<Image>(img);
        if (value.contains("rect") && value["rect"].is_object()) {

            for (auto& [motionName, frameList] : value["rect"].items())
            {
                AnimationSequence sequence;
                if (frameList.contains("playback"))
                {
                    string typeStr = frameList["playback"].get<string>();
                    if (typeStr == "loop") sequence.playback = PlaybackType::LOOP;
                    else if (typeStr == "once") sequence.playback = PlaybackType::ONCE;
                    else if (typeStr == "pingpong") sequence.playback = PlaybackType::PINGPONG;
                }

                if (frameList.contains("frames")) {
                    for (auto& f : frameList["frames"])
                    {
                        Frame frame;
                        frame.rect.left = f["x"];
                        frame.rect.top = f["y"];
                        frame.rect.right = frame.rect.left + f["w"];
                        frame.rect.bottom = frame.rect.top + f["h"];
                        if (f.contains("duration")) {
                            frame.duration = f["duration"];
                        }
                        sequence.frames.push_back(frame);
                    }

                }
                r.animations[ConvertToWString(motionName)] = move(sequence);
            }


        }
        
        if (value.contains("position")) {
            r.pos.x = value["position"]["x"];
            r.pos.y = value["position"]["y"];
        }

        
        if (value.contains("scale")) {
            r.scaleX = value["scale"]["x"];
            r.scaleY = value["scale"]["y"];
        }

        
        if (value.contains("originalResolution")) {
            r.originalResolution.cx = value["originalResolution"]["w"];
            r.originalResolution.cy = value["originalResolution"]["h"];
        }
        _images[wkey] = move(r);
    }
}
Image* ResourceManager::LoadImageFromFile(const wstring& path)
{
    Image* img = new Image(path.c_str());
    if (img->GetLastStatus() != Gdiplus::Ok)
    {
        delete img;
        return nullptr;
    }

	return img;
}

void ResourceManager::LazyloadingImageJson(string& strkey,string& strimg)
{
       
    const auto& value = _jsonImgData[strkey][strimg];
    wstring wkey = ConvertToWString(strimg);
    wstring wpath = ConvertToWString(value["path"]);
    
    auto img = LoadImageFromFile(wpath);
    if (!img) return;
    ImageResource ir;
    ir.img = unique_ptr<Image>(img);
    
    if (value.contains("rect")&& value["rect"].is_object()) {
        
        for (auto& [motionName, frameList] : value["rect"].items())
        {
            AnimationSequence sequence;
            if (frameList.contains("playback"))
            {
                string typeStr = frameList["playback"].get<string>();
                if (typeStr == "loop") sequence.playback = PlaybackType::LOOP;
                else if (typeStr == "once") sequence.playback = PlaybackType::ONCE;
                else if (typeStr == "pingpong") sequence.playback = PlaybackType::PINGPONG;
            }
            if (frameList.contains("frames")) {
                for (auto& f : frameList["frames"])
                {
                    Frame frame;
                    frame.rect.left = f["x"];
                    frame.rect.top = f["y"];
                    frame.rect.right = frame.rect.left + f["w"];
                    frame.rect.bottom = frame.rect.top + f["h"];
                    if (f.contains("duration")) {
                        frame.duration = f["duration"];
                    }
                    sequence.frames.push_back(frame);
                }
                
            }
            ir.animations[ConvertToWString(motionName)] = move(sequence);
        }


    }
    if (value.contains("position") &&
        value["position"].contains("x") &&
        value["position"].contains("y") &&
        value["position"]["x"].is_number() &&
        value["position"]["y"].is_number()) 
    {
        ir.pos.x = value["position"]["x"];
        ir.pos.y = value["position"]["y"];
    }
    else
    {
        OutputDebugString(L"[ResourceManager] JSON의 position이 비어 있음 → 기존 값 유지\n");
    }


    if (value.contains("scale")) {
        ir.scaleX = value["scale"]["x"];
        ir.scaleY = value["scale"]["y"];
    }


    if (value.contains("originalResolution")) {
        ir.originalResolution.cx = value["originalResolution"]["w"];
        ir.originalResolution.cy = value["originalResolution"]["h"];
    }
    _images[wkey] = move(ir);
 
}

void ResourceManager::Clear()
{
    _images.clear();
}

void ResourceManager::InitImgJson()
{
    ifstream InitFile("../assets/resource_table.json");
    if (!InitFile.is_open())
    {
        return;
    }
    InitFile >> _jsonImgData;
    InitFile.close();
}

optional<string> ResourceManager::GetSectionKey(const wstring& name)
{
    string targetKey = ConvertToString(name);
    for (const auto& [sectionName, entries] : _jsonImgData.items())
    {
        if (entries.contains(targetKey))
        {
            return sectionName;
        }
    }
    return nullopt;
}

ImageResource* ResourceManager::GetImageResource(const wstring& key)
{
    auto it = _images.find(key);
    if (it != _images.end() && it->second.img)
        return &(it->second);
    return nullptr;
}

