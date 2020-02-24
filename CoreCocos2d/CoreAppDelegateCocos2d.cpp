#include "CoreAppDelegateCocos2d.h"
// Cocos lib
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>
// Core lib
#include <Core/SessionApp.h>
// CoreCocos
#include "FactorySceneCocos2d.h"
#include "RenderCocos2d.h"
#include "ManagerSceneCocos2d.h"


namespace
{

constexpr auto FRAME_ZOOM_FACTOR = 1.0f;

} // END namespace


std::unique_ptr<IFactoryScene> CoreAppDelegateCocos2d::createFactoryScene(const SessionApp& /*sessionApp*/)
{
	// TODO: надо сделать оригинал для Cocos2d
	return std::unique_ptr<IFactoryScene>(new FactorySceneCocos2d());
}

std::unique_ptr<IRender> CoreAppDelegateCocos2d::createRender(const SessionApp& sessionApp, const IFactoryScene& factoryScene, const IManagerDescriptionScene& managerDescriptionScene)
{
	PtrCocos2d<cocos2d::GLView> glView;
	{
		glView.reset(cocos2d::GLViewImpl::createWithRect(sessionApp.getName(), cocos2d::Rect(0, 0, sessionApp.getSize().first, sessionApp.getSize().second), FRAME_ZOOM_FACTOR, sessionApp.getResizable()));
		glView->setDesignResolutionSize(sessionApp.getSize().first, sessionApp.getSize().second, ResolutionPolicy::SHOW_ALL);
	}
	return std::unique_ptr<IRender>(new RenderCocos2d(std::move(glView), factoryScene, managerDescriptionScene));
}

std::unique_ptr<IManagerScene> CoreAppDelegateCocos2d::createManagerScene(const SessionApp& /*sessionApp*/, const IRender& render)
{
	return std::unique_ptr<IManagerScene>(new ManagerSceneCocos2d(render));
}
