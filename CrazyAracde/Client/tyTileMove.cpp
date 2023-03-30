#include "tyTileMove.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyRigidbody.h"
#include "tyTransform.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyPlayScene.h"
#include "tyColliderPosControl.h"
#include "tyTime.h"

namespace ty
{
	TileMove::TileMove()
	{
	}
	TileMove::~TileMove()
	{
	}
	void TileMove::Initialize()
	{
		SetName(L"TileMove");
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(TILE_SIZE_X, TILE_SIZE_Y));

		GameObject::Initialize();
	}
	void TileMove::Update()
	{
	}
	void TileMove::Render(HDC hdc)
	{
	}
	void TileMove::Release()
	{
	}
	void TileMove::OnCollisionEnter(Collider* other)
	{
	}
	void TileMove::OnCollisionStay(Collider* other)
	{
	}
	void TileMove::OnCollisionExit(Collider* other)
	{
	}
}