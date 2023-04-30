#include "tyItem.h"
#include "tyBazzi.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyBaseBomb.h"
#include "tyScene.h"
#include "tyObject.h"
#include "tyBombEffect.h"
#include "tyTile.h"
#include "tyTileBomb.h"
#include "tyPlayScene.h"
#include "tyinput.h"
#include "tyBallon.h"

namespace ty
{
	Item::Item()
	{
	}
	Item::Item(ItemType type)
	{
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));

		GameObject::Initialize();
	}
	void Item::Update()
	{
		GameObject::Update();
	}
	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Item::Release()
	{
	}
	void Item::OnCollisionEnter(Collider* other)
	{
		int a = 0;
		
	}
	void Item::OnCollisionStay(Collider* other)
	{
	}
	void Item::OnCollisionExit(Collider* other)
	{
	}
}