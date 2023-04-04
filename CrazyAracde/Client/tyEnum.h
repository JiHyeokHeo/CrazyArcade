#pragma once

enum class eSceneType
{
	Logo, // �ΰ�
	Login, // �α���
	Lobby, // �׳� �κ�
	Play, // �÷���
	Stage2, //
	Reward, // ���â
	Tool,
	End,
};

enum class eLayerType
{
	BG, // ���
	Ground,
	Tile, // Ÿ��
	AlphaBlender, // ���ĺ���
	Item,
	BombEffect, // ����Ʈ
	Bomb, // ��ź
	Monster, // ����
	Shadow, // 
	Player, // �÷��̾�
	MapSelectUI,
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



