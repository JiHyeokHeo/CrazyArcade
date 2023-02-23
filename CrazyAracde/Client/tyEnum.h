#pragma once

enum class eSceneType
{
	Title, // Ÿ��Ʋ
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

enum class ePlayerType
{
	Bazzi,
	Uni,
	End,
};

enum class eComponentType
{
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	End,
};

