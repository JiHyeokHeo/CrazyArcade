#pragma once

enum class eSceneType
{
	TITLE, // 타이틀
	LOBBY, // 그냥 로비
	GAMELOBBY, // 게임 로비
	PLAY, // 플레이
	REWARD, // 결과창
	END,
};

enum class eLayerType
{
	BG, // 배경
	MONSTER, // 몬스터
	PLAYER, // 플레이어
	EFFECT, // 이펙트
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

