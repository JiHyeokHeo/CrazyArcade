#include "tyRigidbody.h"
#include "tyTime.h"
#include "tyGameObject.h"
#include "tyTransform.h"

namespace ty
{
	RigidBody::RigidBody()
		: Component(eComponentType::RigidBody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1000.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 800.0f);
		mFriction = 100.0f;
	}

	RigidBody::~RigidBody()
	{

	}

	void RigidBody::Initialize()
	{

	}

	void RigidBody::Update()
	{
		// 힘은 질량 곱하기 가속도
		// 즉 가속도는 질량분의 힘
		// F = M * A 
		// A = M / F
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해준다.
		mVelocity += mAccelation * Time::DeltaTime();
		if (mbGround)
		{
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else // 땅위에 없으면 그냥 계속해서 더해준다.
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 중력가속도 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity); // 내적 스칼라값 반환 방향은 없고 오직 크기만
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
		if (!(mVelocity == Vector2::Zero))
		{
			//속도에 반대방향으로 마찰력이 적용된다.
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		// 속도에 맞게끔 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();

		if (pos.y > 900.0f)
			mbGround = true;

		tr->SetPos(pos);
		mForce.Clear();
	}

	void RigidBody::Render(HDC hdc)
	{
	}
	void RigidBody::Release()
	{
	}
	void RigidBody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}