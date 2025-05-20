#pragma once
#include <Windows.h>
#include <string>
using namespace std;
inline wstring ConvertToWString(const string& str)
{
	if (str.empty())
		return L"";
	int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1,NULL, 0); //멀티바이트 현재
	wstring result(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);
	if(!result.empty()&&result.back()==L'\0')//result가 비어있지않고끝에 \0이 있으면 제거함
	result.pop_back();//위험하려나?(null문자제거인데?)
	return result;
}

inline string ConvertToString(const wstring& wstr)
{
	if (wstr.empty())
		return "";
	int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	//위의 코드와 동일하나 맨마지막 2개의 매개변수의경우 utf-8,utf-7의 경우 찾을 수없는경우에는 null로 두어야 파라미터 인자 오류가 생기지않음을 확인
	string result(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], size,NULL,NULL);
	if (!result.empty() && result.back() == '\0')
		result.pop_back();
	return result;
}

//string->wstring
//위코드는 현재 msdn에 이렇게 서술되어있음
//int MultiByteToWideChar(
//	[in]            UINT                              CodePage,
//	[in]            DWORD                             dwFlags,
//	[in]            _In_NLS_string_(cbMultiByte)LPCCH lpMultiByteStr,
//	[in]            int                               cbMultiByte,
//	[out, optional] LPWSTR                            lpWideCharStr,
//	[in]            int                               cchWideChar
//);
// 
// 그아래에 이제 다시 확장으로 바꿀때 wstring->string
//int WideCharToMultiByte(
//	[in]            UINT                               CodePage,
//	[in]            DWORD                              dwFlags,
//	[in]            _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
//	[in]            int                                cchWideChar,
//	[out, optional] LPSTR                              lpMultiByteStr,
//	[in]            int                                cbMultiByte,
//	[in, optional]  LPCCH                              lpDefaultChar,
//	[out, optional] LPBOOL                             lpUsedDefaultChar
//);