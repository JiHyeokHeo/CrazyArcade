#pragma once

enum class eSceneType
{
	Logo, // 로고
	Login, // 로그인
	Lobby, // 그냥 로비
	Play, // 플레이
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
	Reward, // 결과창
	Tool,
	End,
};

enum class eLayerType
{
	BG, // 배경
	Ground,
	AlphaBlender, // 알파블렌드
	BombEffect, // 이펙트
	Bomb, // 폭탄
	Item,
	Tile, // 타일
	Monster, // 몬스터
	Boss, // 보스
	Shadow, // 
	Player, // 플레이어
	Effect, // 일반 이펙트
	MapSelectUI,
	UI, // UI
	End, // 최대 16까지 이건 콜리전 매니저에 최대 수용치를 16바이트로 해놨기 때문이다.
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



