#include "FactorySceneCocos2d.h"
#include <cassert>
// Cocos lib
#include <cocos/2d/CCScene.h>
#include <cocos/base/CCDirector.h>
#include <cocosbuilder/CCNodeLoaderLibrary.h>
// Core lib
#include <Core/IDescriptionScene.h>
// CoreCocos2d
#include "PtrCocos2d.h"
#include "DescriptionSceneCocos2d.h"
#include "HolderPathsCocos2d.h"
#include "SceneCreatorCocos2d.h"



std::shared_ptr<IScene> FactorySceneCocos2d::createScene(const std::shared_ptr<IDescriptionScene>& description) const
{
	const auto& itFind = m_factory.find(description->getType());
	if (itFind != m_factory.cend())
	{
		if (const auto& creatorScene = itFind->second)
		{
			if (const auto& dataCocos2d = dynamic_cast<const DescriptionSceneCocos2d*>(description.get()))
			{
				const HolderPathsCocos2d pathsHolder(dataCocos2d->getPaths());
				// Create SceneCocos2d
				auto sceneCocos = PtrCocos2d<cocos2d::Scene>::create();
				// Load SceneCocos2d
				{
					auto nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

//					sceneCocos->registerLoaders(nodeLoaderLibrary);

					cocosbuilder::CCBReader ccbReader(nodeLoaderLibrary, nullptr, nullptr, nullptr);
					// cocosbuilder::CCBReader ccbReader(nodeLoaderLibrary, nullptr, scene->m_resolver.get(), nullptr);
					auto root = ccbReader.readNodeGraphFromFile(dataCocos2d->getCcbName().c_str(), sceneCocos.get());
					sceneCocos->addChild(root);
				}
				// Create Scene
				return creatorScene->create(std::move(sceneCocos), description);
			}
		}
	}
	// Not Found
	return {};
}

template<typename TypeClass>
void FactorySceneCocos2d::registerScene(const std::string name)
{
	assert(not name.empty());
	assert(m_factory.count(name) == 0);
	if (not name.empty())
	{
		assert(m_factory.count(name) == 0);
		m_factory[name] = new SceneCreatorCocos2d<TypeClass>();
	}
}
