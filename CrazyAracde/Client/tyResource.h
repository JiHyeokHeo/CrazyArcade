#pragma once
#include "tyEntity.h"

namespace ty
{
	class Resource // 추상 클래스 오로지 상속만
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0; // 무조건 오버라이드 받으라는 것이다. 순수가상함수
		

		const std::wstring& GetKey() { return mKey; } // 메모리 절약을 위해 참조 그냥 받아버리면 다 돌아야한다.
		const std::wstring& GetPath() { return mKey; }
		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::wstring mPath;
	};

	//class Image : public Resource
	//{

	//};

	//class Sound : public Resource
	//{

	//};
}
