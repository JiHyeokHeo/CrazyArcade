#pragma once
#include "tyEntity.h"

namespace ty
{
	class Resource // �߻� Ŭ���� ������ ��Ӹ�
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0; // ������ �������̵� ������� ���̴�. ���������Լ�
		

		const std::wstring& GetKey() { return mKey; } // �޸� ������ ���� ���� �׳� �޾ƹ����� �� ���ƾ��Ѵ�.
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
