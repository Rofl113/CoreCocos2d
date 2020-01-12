#include "CoreAppDelegateCocos2d.h"
// CoreCocos
#include "FactorySceneCocos2d.h"
#include "RenderCocos2d.h"
#include "ManagerSceneCocos2d.h"



std::unique_ptr<IFactoryScene> CoreAppDelegateCocos2d::createFactoryScene(const SessionApp& /*sessionApp*/)
{
	// TODO: надо сделать оригинал для Cocos2d
	return std::unique_ptr<IFactoryScene>(new FactorySceneCocos2d());
}

std::unique_ptr<IRender> CoreAppDelegateCocos2d::createRender(const SessionApp& sessionApp, const IFactoryScene& factoryScene, const IManagerDescriptionScene& managerDescriptionScene)
{
	return std::unique_ptr<IRender>(new RenderCocos2d(sessionApp, factoryScene, managerDescriptionScene));
}

std::unique_ptr<IManagerScene> CoreAppDelegateCocos2d::createManagerScene(const SessionApp& /*sessionApp*/, const IRender& render)
{
	return std::unique_ptr<IManagerScene>(new ManagerSceneCocos2d(render));
}
