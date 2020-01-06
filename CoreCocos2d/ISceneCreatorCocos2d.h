#pragma once
#include <memory>
#include "PtrCocos2d.h"


namespace cocos2d { class Scene; }
class IScene;
class IDescriptionScene;


class ISceneCreatorCocos2d
{
public:
	virtual ~ISceneCreatorCocos2d() = default;
	virtual std::shared_ptr<IScene> create(PtrCocos2d<cocos2d::Scene>&& scene, const std::shared_ptr<IDescriptionScene>& description) const = 0;
};
