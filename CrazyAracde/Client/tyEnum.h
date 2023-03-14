#pragma once

enum class eSceneType
{
	Logo, // 로고
	Login, // 로그인
	Lobby, // 그냥 로비
	Play, // 플레이
	Reward, // 결과창
	End,
};

enum class eLayerType
{
	BG, // 배경
	AlphaBlender,
	Bomb, // 폭탄
	Monster, // 몬스터
	Player, // 플레이어
	Effect, // 이펙트
	UI, // UI
	End, // 최대 16까지 이건 콜리전 매니저에 최대 수용치를 16바이트로 해놨기 때문이다.
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

