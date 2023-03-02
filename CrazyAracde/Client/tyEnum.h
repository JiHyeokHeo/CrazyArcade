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
	Bomb, // ��ź
	Effect, // ����Ʈ
	UI, // UI
	End,
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	End,
};

