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
	AlphaBlender,
	Bomb, // ��ź
	Monster, // ����
	Player, // �÷��̾�
	Effect, // ����Ʈ
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

