#pragma once
#include"tyScene.h"
#include "tyImage.h"

namespace ty
{
	class Lobby_BG : public GameObject
	{
	public:
		Lobby_BG();
		~Lobby_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}
