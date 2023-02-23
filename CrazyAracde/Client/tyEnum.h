#pragma once

enum class eSceneType
{
	Logo, // �ΰ�
	Login, // �α���
	Lobby, // �׳� �κ�
	Play, // �÷���
	Reward, // ���â
	End,
};

enum class eLayerType
{
	BG, // ���
	Monster, // ����
	Player, // �÷��̾�
	Effect, // ����Ʈ
	UI, // UI
	End,
};

//enum class ePlayerType
//{
//	Bazzi,
//	Uni,
//	End,
//};

//enum class eItemType
//{
//	Shield,
//	Dart,
//	Spring,
//	End,
//};

enum class eComponentType
{
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	End,
};

