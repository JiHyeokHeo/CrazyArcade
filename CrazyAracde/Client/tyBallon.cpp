#include "tyBallon.h"
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

namespace ty
{
	Ballon::Ballon()
	{
	}
	Ballon::~Ballon()
	{
	}
	void Ballon::Initialize()
	{
		GameObject::Initialize();
	}
	void Ballon::Update()
	{
		GameObject::Update();
	}
	void Ballon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ballon::Release()
	{
	}
	void Ballon::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			
		}
	}
	void Ballon::OnCollisionStay(Collider* other)
	{
	}
	void Ballon::OnCollisionExit(Collider* other)
	{
	}
}