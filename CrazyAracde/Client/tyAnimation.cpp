#include "tyAnimation.h"
#include "tyTime.h"
#include "tyImage.h"
#include "tyAnimator.h"
#include "tyTransform.h"
#include "tyGameObject.h"
#include "tyCamera.h"

namespace ty
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mSheetImage(nullptr)
		, mTime(0.0f)
		, mbComplete(false)
		, mSpriteIndex(0)
		, mAnimationName(L"")
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Initialize()
	{
	}
	void Animation::Update()
	{
		if (mbComplete == true)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime) // 이쪽을 좀 더 알아보자
		{
			mTime = 0.0f;

			if (mSpriteSheet.size() <= mSpriteIndex + 1)
			{
				mbComplete = true;
			}
			else
			{
				mSpriteIndex++;
			}
		}
	}
	void Animation::Render(HDC hdc)
	{
		Transform* tr
			= mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 scale = tr->GetScale();

		// 이미지가 그려질 좌표는 오브젝트 좌표의 위쪽 중간에 그려진다.
		// 캐릭터의 발을 기준으로 포지션을 계산
		Vector2 pos = tr->GetPos();
		//pos = Camera::CalculatePos(pos);
		pos += mSpriteSheet[mSpriteIndex].offset;
		//pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
		//pos.y -= mSpriteSheet[mSpriteIndex].size.y;

		TransparentBlt(hdc, pos.x, pos.y
			, mSpriteSheet[mSpriteIndex].size.x * scale.x
			, mSpriteSheet[mSpriteIndex].size.y * scale.y
			, mSheetImage->GetHdc()
			, mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
			, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
			, RGB(255, 0, 255));
	}
	void Animation::Create(Image* sheet, Vector2 leftTop, 
		UINT column, UINT row, UINT spriteLength,
		Vector2 offset, float duration)
	{
		mSheetImage = sheet;

		//UINT coulm = mSheetImage->GetWidth() / size.x;
		Vector2 size = Vector2::One;
		size.x = mSheetImage->GetWidth() / (float)column;
		size.y = mSheetImage->GetHeight() / (float)row;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite spriteinfo;

			spriteinfo.leftTop.x = leftTop.x + (size.x * i);
			spriteinfo.leftTop.y = leftTop.y;
			spriteinfo.size = size;
			spriteinfo.offset = offset;
			spriteinfo.duration = duration;

			mSpriteSheet.push_back(spriteinfo);
		}
	}
	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}
}