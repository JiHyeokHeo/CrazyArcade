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
	Monster, // 몬스터
	Player, // 플레이어
	Effect, // 이펙트
	UI, // UI
	End,
};

//enum class ePlayerType
//{
//	Bazzi,
//	Uni,
//	End,
//};

//enum class eItemType
//{
//	Shield,
//	Dart,
//	Spring,
//	End,
//};

enum class eComponentType
{
	Transform,
	Collider,
	SpriteRenderer,
	Animator,
	Audio,
	End,
};

