#pragma once

enum class eSceneType
{
	TITLE, // Ÿ��Ʋ
	LOBBY, // �׳� �κ�
	GAMELOBBY, // ���� �κ�
	PLAY, // �÷���
	REWARD, // ���â
	END,
};

enum class eLayerType
{
	BG, // ���
	MONSTER, // ����
	PLAYER, // �÷��̾�
	EFFECT, // ����Ʈ
	UI, // UI
	END,
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

