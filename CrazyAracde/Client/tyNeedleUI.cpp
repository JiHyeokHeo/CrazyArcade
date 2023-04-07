#include "tyNeedleUI.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyBazzi.h"
#include "tyObject.h"

namespace ty
{
	NeedleUI::NeedleUI()
	{
	}
	NeedleUI::~NeedleUI()
	{
	}
	void NeedleUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"mNeedleUI", L"..\\Resources\\UI\\needleUI.bmp");
	}
	void NeedleUI::Update()
	{
		if (SceneManager::GetBazzi()->GetItemState() != eItemType::Needle)
		{
			object::Destroy(this);
		}
		
		GameObject::Update();
	}
	void NeedleUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 1015, 741, mImage->GetWidth()* 1.4, mImage->GetHeight()* 1.4, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0 ,255));
		GameObject::Render(hdc);
	}
	void NeedleUI::Release()
	{
	}
}