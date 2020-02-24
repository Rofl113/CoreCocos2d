#include "RenderCocos2d.h"
// Cocos lib
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/platform/CCApplication.h>
#include <cocos/platform/CCGLView.h>
#include <cocos/platform/desktop/CCGLViewImpl-desktop.h>
// Core lib
#include <Core/IScene.h>
// CoreCocos2d
#include "ISceneCocos2d.h"

namespace
{

constexpr auto FRAME_ZOOM_FACTOR = 1.0f;

PtrCocos2d<cocos2d::GLView> createGlView(const std::string& name
                                         , const std::pair<size_t, size_t>& sizeView
                                         , const std::pair<size_t, size_t>& sizeDesignResolution
                                         , const bool isResizable)
{
	PtrCocos2d<cocos2d::GLView> glView;
	{
		glView.reset(cocos2d::GLViewImpl::createWithRect(name, cocos2d::Rect(0, 0, sizeView.first, sizeView.second), FRAME_ZOOM_FACTOR, isResizable));
		glView->setDesignResolutionSize(sizeDesignResolution.first, sizeDesignResolution.second, ResolutionPolicy::SHOW_ALL);
	}
	return glView;
}

} // END namespace



// Делегат для кокоса
class RenderCocos2d::AppDelegateCocos2d : public cocos2d::Application
{
public:
	virtual ~AppDelegateCocos2d() override
	{

	}
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

RenderCocos2d::RenderCocos2d(PtrCocos2d<cocos2d::GLView>&& glView
                             , const IFactoryScene& factoryScene
                             , const IManagerDescriptionScene& managerDescriptionScene)
    : ClassBase(factoryScene, managerDescriptionScene)
    , m_appDelegateCocos2d(new AppDelegateCocos2d())
    , m_glView(std::move(glView))
    , m_eventPreTick(cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(cocos2d::Director::EVENT_AFTER_DRAW, [this] (cocos2d::EventCustom* /*eventCustom*/)
    {
        this->handleAfterDraw();
    }))
    , m_eventPostTick(cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(cocos2d::Director::EVENT_BEFORE_DRAW, [this] (cocos2d::EventCustom* /*eventCustom*/)
    {
        this->handleBeforeDraw();
    }))
{
	auto director = cocos2d::Director::getInstance();
	// Add GlView to Director
	director->setOpenGLView(m_glView.get());
	// Setting Director
	director->setProjection(cocos2d::Director::Projection::_2D);
	director->setContentScaleFactor(1.0f);
	director->setDisplayStats(true);
	const auto fps = 60;
	director->setAnimationInterval(1.0f / static_cast<float>(fps));
	director->resume();
	director->runWithScene(cocos2d::Scene::create());
}

RenderCocos2d::RenderCocos2d(const std::string& name,
                             const std::pair<size_t, size_t>& sizeView
                             , const std::pair<size_t, size_t>& sizeDesignResolution
                             , const bool isResizable
                             , const IFactoryScene& factoryScene
                             , const IManagerDescriptionScene& managerDescriptionScene)
    : RenderCocos2d(createGlView(name, sizeView, sizeDesignResolution, isResizable)
                    , factoryScene
                    , managerDescriptionScene)
{

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
