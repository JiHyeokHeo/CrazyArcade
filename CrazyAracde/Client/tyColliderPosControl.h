#pragma once
#include "tyGameObject.h"
#include "tyRigidBody.h"
#include "tyScene.h"
#include "tySceneManager.h"
#include "tyTransform.h"
#include "tyCollider.h"
#include "tyRigidBody.h"

namespace ty::colposctr
{
	template <typename T>
	void ColPosControl(Collider* other, T* col)
	{
		GameObject* gameobj = dynamic_cast<GameObject*>(other->GetOwner());
		if (gameobj == nullptr)
			return;

		//RigidBody* rb = gameobj->GetComponent<RigidBody>();
		//rb->SetGround(true);  //이쪽은 내 입맛 대로 고쳐쓰자. 이 함수는 어떠한 물체에 enter할때 사용하도록 만든 함수이다.*/

		Collider* gameobjCol = gameobj->GetComponent<Collider>();
		Vector2 gameobjPos = gameobjCol->GetPos();

		Collider* thisCol = col->GetComponent<Collider>();
		Vector2 thisPos = thisCol->GetPos();


		float fLen = fabs(gameobjPos.y - thisPos.y);
		float fSize = (gameobjCol->GetSize().y / 2.0f) + (thisCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* gameobjTr = gameobj->GetComponent<Transform>();
			Transform* colTr = col->GetComponent<Transform>();

			Vector2 gameobjPos = gameobjTr->GetPos();
			Vector2 colPos = colTr->GetPos();

			gameobjPos -= (fSize - fLen); //- 1.0f;
			gameobjTr->SetPos(gameobjPos);
		}
	}
}
