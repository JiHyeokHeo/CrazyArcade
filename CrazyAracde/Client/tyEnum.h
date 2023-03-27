#pragma once

enum class eSceneType
{
	Logo, // �ΰ�
	Login, // �α���
	Lobby, // �׳� �κ�
	Play, // �÷���
	Reward, // ���â
	Tool,
	End,
};

enum class eLayerType
{
	BG, // ���
	Ground,
	AlphaBlender, // ���ĺ���
	Tile, // Ÿ��
	BombEffect, // ����Ʈ
	Bomb, // ��ź
	Monster, // ����
	Player, // �÷��̾�
	UI, // UI
	End, // �ִ� 16���� �̰� �ݸ��� �Ŵ����� �ִ� ����ġ�� 16����Ʈ�� �س��� �����̴�.
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	RigidBody,
	Audio,
	End,
};

