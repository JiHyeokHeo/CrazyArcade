#include "tyComponent.h"

namespace ty
{
	Component::Component(eComponentType type)
		: mType(type)
	{
	}
	Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
	void Component::Release()
	{
	}
}