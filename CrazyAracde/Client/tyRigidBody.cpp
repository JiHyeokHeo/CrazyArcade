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
		// ���� ���� ���ϱ� ���ӵ�
		// �� ���ӵ��� �������� ��
		// F = M * A 
		// A = M / F
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += mAccelation * Time::DeltaTime();
		if (mbGround)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else // ������ ������ �׳� ����ؼ� �����ش�.
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �߷°��ӵ� �ִ� �ӵ� ����
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity); // ���� ��Į�� ��ȯ ������ ���� ���� ũ�⸸
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

		// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		if (!(mVelocity == Vector2::Zero))
		{
			//�ӵ��� �ݴ�������� �������� ����ȴ�.
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
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