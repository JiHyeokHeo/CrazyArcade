#pragma once
#include "ToryEngine.h"

namespace ty // 이름 확인용 구분용 디버깅 편하게 하기위해
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		
		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }

	private:
		std::wstring mName;
	};
}
