#pragma once
#include "ToryEngine.h"

namespace ty // �̸� Ȯ�ο� ���п� ����� ���ϰ� �ϱ�����
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT id) { mID = id; }
		UINT64 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT64 mID;
	};
}
