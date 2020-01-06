#include "SceneCocos2d.h"
// Cocos lib
#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCFileUtils.h>
// CoreCocos2d
#include "HolderPathsCocos2d.h"
#include "DescriptionSceneCocos2d.h"



SceneCocos2d::SceneCocos2d(PtrCocos2d<cocos2d::Scene>&& scene, const std::shared_ptr<IDescriptionScene>& description)
    : m_scene(std::move(scene))
    , m_description(description)
{
}

cocos2d::Scene* SceneCocos2d::getSceneCocos() const
{
	return m_scene.get();
}

std::string SceneCocos2d::fullPathForFilename(const std::string& name) const
{
	if (const auto descriptionCocos2d = dynamic_cast<const DescriptionSceneCocos2d*>(m_description.get()))
	{
		const HolderPathsCocos2d pathsHolder (descriptionCocos2d->getPaths());
		auto fu = cocos2d::FileUtils::getInstance();
		return fu->fullPathForFilename(name);
	}
	assert(false);
	return {};
}

void SceneCocos2d::onLoad()
{

}

SceneCocos2d::~SceneCocos2d()
{

}

void SceneCocos2d::onActivate()
{

}

void SceneCocos2d::onDeactivate()
{

}

void SceneCocos2d::onPause()
{
	if (const auto sceneCocos = this->getSceneCocos())
	{
		sceneCocos->pause();
	}
}

void SceneCocos2d::onResume()
{
	if (const auto sceneCocos = this->getSceneCocos())
	{
		sceneCocos->resume();
	}
}
