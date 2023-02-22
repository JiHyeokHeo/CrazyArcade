#pragma once
#include "tyResource.h"

namespace ty
{
	class Resources
	{
	public:
		
		template <typename T>
		static T* Find(const std::wstring& key) // �ּ� ��ȯ�ϴ� �Լ�
		{
			//���ҽ��ʿ��� �����͸� Ž���Ѵ�. �����Ͱ� �ִٸ� �ش� �����͸� ��ȯ�ϰ�
			//�����Ͱ� ���ٸ� end�� ��ȯ���ش�.
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);

			//ã���� �ϴ� �����Ͱ� �����Ѵٸ�
			//�ش�Ÿ������ ����ȯ�Ͽ� ��ȯ
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			//������ ���ٸ� ���� ��ȯ
			return nullptr;
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			// Ű������ Ž��
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// �ش� ���ҽ��� ���ٸ�
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};


}
