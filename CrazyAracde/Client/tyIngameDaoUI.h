#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class InGameDaoUI : public GameObject
	{
	public:
		InGameDaoUI();
		~InGameDaoUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		InGameDaoUI* mDaoImage;
		bool isClicked;
	};
};



