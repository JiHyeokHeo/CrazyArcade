#pragma once

enum class eSceneType
{
	Logo, // �ΰ�
	Login, // �α���
	Lobby, // �׳� �κ�
	Play, // �÷���
	PlayStage2, //
	PlayStage3,
	ForestStage1,
	ForestStage2,
	ForestStage3,
	ToyStage1,
	ToyStage2,
	ToyStage3,
	PirateStage1,
	PirateStage2,
	PirateStage3,
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
	Boss, // ����
	Shadow, // 
	Player, // �÷��̾�
	Effect, // �Ϲ� ����Ʈ
	MapSelectUI,
	UI, // UI
	End, // �ִ� 16���� �̰� �ݸ��� �Ŵ����� �ִ� ����ġ�� 16����Ʈ�� �س��� �����̴�.
};


enum class eCharactorPick
{
	Bazzi,
	Dao,
	None,
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



