#include "tyScene.h"

namespace ty
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::END);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
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
	void Scene::Release()
	{
		for (Layer& layer : mLayers)
		{
			layer.Release();
		}
	}
	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer].AddGameObject(obj);
	}
}