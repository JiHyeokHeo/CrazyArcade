#include "tyScene.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyBazzi.h"

namespace ty
{
	Scene::Scene()
	{
		mLayers.reserve(5);
		mLayers.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		SceneManager::SetActiveScene(this);
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}
	void Scene::Destroy()
	{
		std::vector<GameObject*> deleteGameObjects = {};
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>& gameObjects
				= layer.GetGameObject();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin();
				iter != gameObjects.end();)
			{
				if ((*iter)->GetState() == GameObject::eState::Death)
				{
					deleteGameObjects.push_back((*iter)); // * ��������ν� ���� ����
					iter = gameObjects.erase(iter); // erase �Լ��� ����ϸ� �������� ���ÿ� iter�� �ٷ� ���� ���� ��ȯ�ϰ� �ȴ�.
				}
				else
				{
					iter++;
					// �׷��� else �� �߰��ؼ� iter++�� ���ִ� ���̴�.
				}
			}
		}

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}
	}
	void Scene::Release()
	{
	
	}
	void Scene::OnEnter()
	{

	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
	std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObject();
	}
}