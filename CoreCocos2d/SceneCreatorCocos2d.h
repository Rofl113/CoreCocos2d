#pragma once
#include <cassert>
// Core lib
#include <Core/IDescriptionScene.h>
// CoreCocos2d
#include "ISceneCreatorCocos2d.h"


template<typename TypeClass>
class SceneCreatorCocos2d : public ISceneCreatorCocos2d
{
public:
	virtual std::shared_ptr<IScene> create(PtrCocos2d<cocos2d::Scene>&& scene, const std::shared_ptr<IDescriptionScene>& description) const override
	{
		assert(description->getType() == std::string(typeid(TypeClass).name()));
		return new TypeClass(std::move(scene), description);
	}
};
