#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class BazziLobbyUI : public GameObject
	{
	public:
		BazziLobbyUI();
		~BazziLobbyUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		bool isShown;
	};
};
