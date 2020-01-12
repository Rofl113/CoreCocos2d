#include "RenderCocos2d.h"
// Cocos lib
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/platform/CCApplication.h>
#include <cocos/platform/CCGLView.h>
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>
// Core lib
#include <Core/IScene.h>
#include <Core/SessionApp.h>
// CoreCocos2d
#include "ISceneCocos2d.h"



namespace
{

} // END namespace



// Делегат для кокоса
class RenderCocos2d::AppDelegateCocos2d : public cocos2d::Application
{
	virtual void initGLContextAttrs() override
	{
		GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
		cocos2d::GLView::setGLContextAttrs(glContextAttrs);
	}
	virtual bool applicationDidFinishLaunching() override
	{
		return true;
	}
	virtual void applicationDidEnterBackground() override
	{
		cocos2d::Director::getInstance()->stopAnimation();
	}
	virtual void applicationWillEnterForeground() override
	{
		cocos2d::Director::getInstance()->startAnimation();
	}
};

RenderCocos2d::RenderCocos2d(const SessionApp& sessionApp, const IFactoryScene& factoryScene, const IManagerDescriptionScene& managerDescriptionScene)
    : ClassBase(sessionApp, factoryScene, managerDescriptionScene)
    , m_appDelegateCocos2d(new AppDelegateCocos2d())
    , m_glView(cocos2d::GLViewImpl::createWithRect(sessionApp.getName(), cocos2d::Rect(0, 0, sessionApp.getSize().first, sessionApp.getSize().second)))
    , m_eventPreTick(cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(cocos2d::Director::EVENT_AFTER_DRAW, [this] (cocos2d::EventCustom* /*eventCustom*/)
    {
        this->handleAfterDraw();
    }))
    , m_eventPostTick(cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(cocos2d::Director::EVENT_BEFORE_DRAW, [this] (cocos2d::EventCustom* /*eventCustom*/)
    {
        this->handleBeforeDraw();
    }))
{
	// Add GlView to Director
	cocos2d::Director::getInstance()->setOpenGLView(m_glView.get());
}

RenderCocos2d::~RenderCocos2d()
{
	auto eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	eventDispatcher->removeEventListener(m_eventPreTick);
	eventDispatcher->removeEventListener(m_eventPostTick);
}

int RenderCocos2d::run(const std::function<void ()>& preTick, const std::function<void ()>& postTick)
{
	// Save
	m_preTick = preTick;
	m_postTick = postTick;
	// Run
	return cocos2d::Application::getInstance()->run();
}

void RenderCocos2d::handleLoadScene(const std::shared_ptr<IScene>& /*scene*/) const
{
}

void RenderCocos2d::handleShowScene(const std::shared_ptr<IScene>& scene) const
{
	if (const auto sceneBase = dynamic_cast<ISceneCocos2d*>(scene.get()))
	{
		if (const auto sceneCocos = sceneBase->getSceneCocos())
		{
			const auto director = cocos2d::Director::getInstance();
			// Устанавливаем сцену
			// TODO: не пользуемся стеком кокоса, отдаем только одну сцену
			// TODO: стек сцен будет на уровне менеджера сцен
			director->replaceScene(sceneCocos);
		}
	}
}

void RenderCocos2d::handleAfterDraw()
{
	if (m_preTick)
	{
		m_preTick();
	}
}

void RenderCocos2d::handleBeforeDraw()
{
	if (m_postTick)
	{
		m_postTick();
	}
}
