#pragma once
#include <map>
// Core lib
#include "Core/IFactoryScene.h"
// CoreCocos2d
#include "ISceneCreatorCocos2d.h"
#include "SceneCreatorCocos2d.h"



class FactorySceneCocos2d : public IFactoryScene
{
public: /// IFactoryScene
	virtual std::shared_ptr<IScene> createScene(const std::shared_ptr<IDescriptionScene>& description) const override;

public:
	template<typename TypeClass>
	void registerScene(const std::string name)
	{
		assert(not name.empty());
		assert(m_factory.count(name) == 0);
		if (not name.empty())
		{
			assert(m_factory.count(name) == 0);
			m_factory[name] = std::unique_ptr<ISceneCreatorCocos2d>(new SceneCreatorCocos2d<TypeClass>());
		}
	}

private:
	std::map<std::string, std::unique_ptr<ISceneCreatorCocos2d>> m_factory;
};
