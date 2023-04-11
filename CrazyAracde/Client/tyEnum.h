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
	AlphaBlender, // ���ĺ���
	BombEffect, // ����Ʈ
	Bomb, // ��ź
	Item,
	Tile, // Ÿ��
	Monster, // ����
	Shadow, // 
	Player, // �÷��̾�
	Effect, // �Ϲ� ����Ʈ
	MapSelectUI,
	UI, // UI
	End, // �ִ� 16���� �̰� �ݸ��� �Ŵ����� �ִ� ����ġ�� 16����Ʈ�� �س��� �����̴�.
};

enum class eItemType
{
	Needle,
	Shield,
	None,
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



