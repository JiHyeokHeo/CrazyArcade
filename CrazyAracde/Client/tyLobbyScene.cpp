#include "tyLobbyScene.h"
#include "tySceneManager.h"
#include "tyInput.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tySealBoss.h"
#include "tyAlphaBlender.h"
#include "tyMapSelect.h"
#include "tyIceSelect.h"
#include "tyIceMapSelect.h"
#include "tyPirateMapSelect.h"
#include "tyPirateSelect.h"
#include "tyCookieSelect.h"
#include "tyCookieMapSelect.h"
#include "tyForestSelect.h"
#include "tyForestMapSelect.h"
#include "tyBazziImage.h"
#include "tyDaoImage.h"
#include "tyBazziLobbyUI.h"
#include "tyDaoLobbyUI.h"
#include "tySound.h"
#include "tyResources.h"


namespace ty
{
	bool LobbyScene::isFirstPicked;
	bool LobbyScene::isSecondPicked;

	LobbyScene::LobbyScene()
	{
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		SetName(L"Lobby");
		Scene::Initialize();

		Lobby = Resources::Load<Sound>(L"LobbbyTheme", L"..\\Resources\\Sound\\lobby_scene.wav");
		Lobby->SetVolume(20);
		object::Instantiate<Lobby_BG>(eLayerType::BG);
		//object::Instantiate<MapSelect>(eLayerType::UI);
	}
	void LobbyScene::Update()
	{
		Scene::Update();
		Vector2 temp = Input::GetMousePos();
		
		// ���� ����
		if (SceneManager::GetIsDuo() == false)
		{
			// ����� ���� �ڵ�
			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			//{
			//	if (isBazziVisited == false)
			//	{
			//		mBazziUIImage = object::Instantiate<BazziImage>(eLayerType::UI); // ���¸� Pause�� ��ȯ��Ű�� ���� BazziImage Ŭ�����ȿ��� ����
			//	}
			//	isBazziVisited = true;
			//}

			if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			{
				if (isFirstPicked == false )
				{
					mBazziUIImage = object::Instantiate<BazziImage>(eLayerType::UI);
					object::Instantiate<BazziLobbyUI>(eLayerType::UI);
					isFirstPicked = true;
				}
				SceneManager::SetFirstCharactorPick(eCharactorPick::Bazzi); // �� �Ŵ������� ĳ���� ���� ����
			}

			if (temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			{
				if (isBazziVisited == true)
				{
					object::Active(mBazziUIImage); // ���⼭ ���¸� �ٽ� Active ��Ŵ
				}
			}

			// �ٿ� ���� ���� �ڵ�
			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			//{
			//	if (isDaoVisited == false)
			//	{
			//		mDaoUIImage = object::Instantiate<DaoImage>(eLayerType::UI);// ���¸� Pause�� ��ȯ��Ű�� ���� BazziImage Ŭ�����ȿ��� ����
			//	}

			//	isDaoVisited = true;
			//}


			if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			{
				if (isFirstPicked == false)
				{
					mDaoUIImage = object::Instantiate<DaoImage>(eLayerType::UI);
					object::Instantiate<DaoLobbyUI>(eLayerType::UI);
					isFirstPicked = true;
				}
				
				SceneManager::SetFirstCharactorPick(eCharactorPick::Dao);  // �� �Ŵ������� ĳ���� ���� ����
			}

			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			//{
			//	if (isDaoVisited == true)
			//	{
			//		object::Active(mDaoUIImage); // ���⼭ ���¸� �ٽ� Active ��Ŵ
			//	}
			//}

		}
		else if (SceneManager::GetIsDuo() == true)
		{
			// ����� ���� �ڵ�
			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			//{
			//	if (isBazziVisited == false)
			//	{
			//		mBazziUIImage = object::Instantiate<BazziImage>(eLayerType::UI); // ���¸� Pause�� ��ȯ��Ű�� ���� BazziImage Ŭ�����ȿ��� ����
			//	}
			//	isBazziVisited = true;
			//}

			if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			{
				if (isFirstPicked == false)
				{
					mBazziUIImage = object::Instantiate<BazziImage>(eLayerType::UI);
					object::Instantiate<BazziLobbyUI>(eLayerType::UI);
					isFirstPicked = true;
				}
				SceneManager::SetFirstCharactorPick(eCharactorPick::Bazzi); // �� �Ŵ������� ĳ���� ���� ����
			}

			if (Input::GetKeyDown(eKeyCode::RBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			{
				if (isSecondPicked == false)
				{
					mBazziUIImage = object::Instantiate<BazziImage>(eLayerType::UI);
					object::Instantiate<BazziLobbyUI>(eLayerType::UI);
					isSecondPicked = true;
				}
				SceneManager::SetSecondCharactorPick(eCharactorPick::Bazzi); // �� �Ŵ������� ĳ���� ���� ���� 2P����
			}

			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
			//{
			//	if (isBazziVisited == true)
			//	{
			//		object::Active(mBazziUIImage); // ���⼭ ���¸� �ٽ� Active ��Ŵ
			//	}
			//}

			// �ٿ� ���� ���� �ڵ�
			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			//{
			//	if (isDaoVisited == false)
			//	{
			//		mDaoUIImage = object::Instantiate<DaoImage>(eLayerType::UI);// ���¸� Pause�� ��ȯ��Ű�� ���� BazziImage Ŭ�����ȿ��� ����
			//	}

			//	isDaoVisited = true;
			//}


			if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			{
				if (isFirstPicked == false)
				{
					mDaoUIImage = object::Instantiate<DaoImage>(eLayerType::UI);
					object::Instantiate<DaoLobbyUI>(eLayerType::UI);
					isFirstPicked = true;
				}

				SceneManager::SetFirstCharactorPick(eCharactorPick::Dao);  // �� �Ŵ������� ĳ���� ���� ����
			}

			if (Input::GetKeyDown(eKeyCode::RBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			{
				if (isSecondPicked == false)
				{
					mDaoUIImage = object::Instantiate<DaoImage>(eLayerType::UI);
					object::Instantiate<DaoLobbyUI>(eLayerType::UI);
					isSecondPicked = true;
				}
				SceneManager::SetSecondCharactorPick(eCharactorPick::Dao); // �� �Ŵ������� ĳ���� ���� ���� 2P����
			}

			//if (temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
			//{
			//	if (isDaoVisited == true)
			//	{
			//		object::Active(mDaoUIImage); // ���⼭ ���¸� �ٽ� Active ��Ŵ
			//	}
			//}
		}



		// �� ����
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 647 && temp.y <= 716 && temp.x >= 970 && temp.x <= 1150 && isMapClicked == false)
		{
			isMapClicked = true;
			MapSelect* MapObj = object::Instantiate<MapSelect>(eLayerType::UI);
			MapObj->GetLobbyScene(this); // �κ���̶� �� ������Ʈ�� ���� // 
		}


		// UI Ű�� �� ����
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 298 && temp.y <= 318 && temp.x >= 525 && temp.x <= 906 && isMapClicked == true)
		{
			object::Instantiate<CookieSelect>(eLayerType::UI);
			object::Instantiate<CookieMapSelect>(eLayerType::MapSelectUI);
			mSceneType = eSceneType::ToyStage3;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 358 && temp.y <= 378 && temp.x >= 525 && temp.x <= 906 && isMapClicked == true)
		{
			object::Instantiate<ForestSelect>(eLayerType::UI);
			object::Instantiate<ForestMapSelect>(eLayerType::MapSelectUI);
			mSceneType = eSceneType::ForestStage3;
		}


		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 378 && temp.y <= 398 && temp.x >= 525 && temp.x <= 906 && isMapClicked == true)
		{
			object::Instantiate<IceSelect>(eLayerType::UI);
			object::Instantiate<IceMapSelect>(eLayerType::MapSelectUI);
			mSceneType = eSceneType::Play;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 458 && temp.y <= 478 && temp.x >= 525 && temp.x <= 906 && isMapClicked == true)
		{
			object::Instantiate<PirateSelect>(eLayerType::UI);
			object::Instantiate<PirateMapSelect>(eLayerType::MapSelectUI);
			mSceneType = eSceneType::PirateStage3;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 877 && temp.y <= 890 && temp.x >= 157 && temp.x <= 191 && isMapClicked == false)
		{
			SceneManager::SetIsDuo(false);
			isFirstPicked = false;
			isSecondPicked = false;
			SceneManager::LoadScene(eSceneType::Login);
		}

		if (Input::GetKey(eKeyCode::Q))
		{
			mSceneType = eSceneType::PlayStage3;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 750 && temp.y <= 820 && temp.x >= 780 && temp.x <= 1050)
		{
			isMapClicked = false;
			SceneManager::LoadScene(mSceneType);
		}
	}
	void LobbyScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void LobbyScene::Release()
	{
		Scene::Release();
	}
	void LobbyScene::OnEnter()
	{
		Lobby->Play(true);
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
	}
	void LobbyScene::OnExit()
	{
		Lobby->Stop(true);
		//object::Destroy(mMapSelect);
		//object::Destroy(mBlender);
	}
}