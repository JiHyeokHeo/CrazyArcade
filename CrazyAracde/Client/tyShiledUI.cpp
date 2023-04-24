#include "tyShiledUI.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyBazzi.h"
#include "tyObject.h"
#include "tyDao.h"

namespace ty
{
	ShieldUI::ShieldUI()
	{
	}
	ShieldUI::~ShieldUI()
	{
	}
	void ShieldUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"mShieldUI", L"..\\Resources\\UI\\shieldUI.bmp");
	}
	void ShieldUI::Update()
	{
		if (SceneManager::GetBazzi() != NULL)
		{
			if (SceneManager::GetBazzi()->GetItemState() != eItemType::Shield)
			{
				object::Pause(this);
			}
		}
		else if (SceneManager::GetDao() != NULL)
		{
			if (SceneManager::GetDao()->GetItemState() != eItemType::Shield)
			{
				object::Pause(this);
			}
		}


		GameObject::Update();
	}
	void ShieldUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 1015, 741, mImage->GetWidth() * 1.4, mImage->GetHeight() * 1.4, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		GameObject::Render(hdc);
	}
	void ShieldUI::Release()
	{
	}
}