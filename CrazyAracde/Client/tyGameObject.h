#pragma once
#include "tyEntity.h"
#include "tyComponent.h"

namespace ty
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Death
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);


		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents )
			{
				if (dynamic_cast<T*>(comp))
				{
					return dynamic_cast<T*> (comp);
				}
			}

			return nullptr;
		}

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }


	private:
		std::vector<Component*> mComponents; // 스프라이트 렌더러, 중력 , 콜라이더 캐릭터
		eState mState;
	};
}


