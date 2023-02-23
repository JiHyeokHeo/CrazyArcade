#pragma once

enum class eSceneType
{
	Title, // 타이틀
	Lobby, // 그냥 로비
	Play, // 플레이
	Reward, // 결과창
	End,
};

enum class eLayerType
{
	BG, // 배경
	Monster, // 몬스터
	Player, // 플레이어
	Effect, // 이펙트
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

