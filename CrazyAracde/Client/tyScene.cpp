#include "tyScene.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyBazzi.h"
#include "tyTileBomb.h"
#include "tyTile.h"

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

	void Scene::ChangeGameObjectState()
	{
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>& gameObjects
				= layer.GetGameObject();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin();
				iter != gameObjects.end(); iter++)
			{
				if ((*iter)->GetState() == GameObject::eState::Pause)
				{
					Tile* tile = dynamic_cast<Tile*>(*iter);
					(*iter)->SetState(GameObject::eState::Active);
					Vector2 mPos = (*iter)->GetComponent<Transform>()->GetPos();
					Vector2 mIdx = TileBomb::SetIndex(mPos);
					SceneManager::GetMapIndex()[mIdx.y][mIdx.x] = 2;
					if ((*iter)->GetName() == L"Tile" && tile->Index() == 4)
					{
						SceneManager::GetMapIndex()[mIdx.y][mIdx.x] = 4;
					}
				}
				
			}
		}
	}

	void Scene::ChangeMonsterState()
	{
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*>& gameObjects
				= layer.GetGameObject();

			for (std::vector<GameObject*>::iterator iter = gameObjects.begin();
				iter != gameObjects.end(); iter++)
			{
				if ((*iter)->GetState() == GameObject::eState::Pause)
				{
					(*iter)->SetState(GameObject::eState::Active);
				}

			}
		}
	}

	std::vector<GameObject*>& Scene::GetGameObjects(eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObject();
	}
}