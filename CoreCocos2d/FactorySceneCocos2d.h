#pragma once
#include <map>
// Core lib
#include "Core/IFactoryScene.h"
// CoreCocos2d
#include "ISceneCreatorCocos2d.h"



class FactorySceneCocos2d : public IFactoryScene
{
public: /// IFactoryScene
	virtual std::shared_ptr<IScene> createScene(const std::shared_ptr<IDescriptionScene>& description) const override;

public:
	template<typename TypeClass>
	void registerScene(const std::string name = std::string(typeid(TypeClass).name()));

private:
	std::map<std::string, std::unique_ptr<ISceneCreatorCocos2d>> m_factory;
};
