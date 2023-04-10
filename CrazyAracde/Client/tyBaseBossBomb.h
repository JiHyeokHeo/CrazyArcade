#pragma once

namespace ty
{
	class Animator;
	class BaseBossBomb : public GameObject
	{
	public:
		enum class eBaseBossBombState
		{
			Idle,
			Bombed,
		};
		BaseBossBomb();
		~BaseBossBomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	private:
		void idle();
		void bombed();
		void BombComplete();

	private:
		Animator* mAnimator;
		float mTime;
		eBaseBossBombState mState;

	};
}
