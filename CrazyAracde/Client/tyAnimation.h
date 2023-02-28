#pragma once
#include "tyEntity.h"


namespace ty
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};
	
		Animation();
		~Animation();

		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Create(Image* sheet, Vector2 leftTop, UINT column, UINT row, UINT spriteLength, Vector2 offest, float duration);
		void Reset();

		bool isComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private:
		Animator* mAnimator;
		Image* mSheetImage;
		std::vector<Sprite> mSpriteSheet;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
	};
}
