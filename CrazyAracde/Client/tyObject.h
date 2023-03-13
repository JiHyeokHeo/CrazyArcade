#pragma once
#include "tyGameObject.h"
#include "tyScene.h"
#include "tySceneManager.h"
#include "tyTransform.h"

namespace ty::object
{
	template <typename T>
	static inline T* Instantiate(eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		gameObj->Initialize();
		return gameObj;
	}

	static void Destroy(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
	}



}