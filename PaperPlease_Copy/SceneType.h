#pragma once
#include <memory>
#include <functional>
enum class SceneType
{
	TITLE,
	SINARIO,
	MAINGAME,
	RESULT,
	NEWS,
	ENDING
};
namespace std {//해시테이블덕에 정말 개같이 만듬... 템플릿특수화로 추가함...
	template<>
	struct hash<SceneType> {
		size_t operator()(const SceneType& p) const noexcept
		{
			return static_cast<size_t>(p);
		}
	};
}