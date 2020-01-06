#include "RenderCocos2d.h"
// Cocos lib
#include <cocos/base/CCDirector.h>
#include <cocos/base/CCEventDispatcher.h>
#include <cocos/platform/CCApplication.h>
// Core lib
#include <Core/IScene.h>
// CoreCocos2d
#include "ISceneCocos2d.h"



RenderCocos2d::RenderCocos2d(const IFactoryScene& factoryScene, const IManagerDescriptionScene& managerDescriptionScene)
    : ClassBase(factoryScene, managerDescriptionScene)
    , m_eventPreTick(cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(cocos2d::Director::EVENT_AFTER_DRAW, [this] (cocos2d::EventCustom* /*eventCustom*/)
    {
        this->handleAfterDraw();
    }))
    , m_eventPostTick(cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(cocos2d::Director::EVENT_BEFORE_DRAW, [this] (cocos2d::EventCustom* /*eventCustom*/)
    {
        this->handleBeforeDraw();
    }))
{

}

RenderCocos2d::~RenderCocos2d()
{
	auto eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	eventDispatcher->removeEventListener(m_eventPreTick);
	eventDispatcher->removeEventListener(m_eventPostTick);
}

void RenderCocos2d::run(const std::function<void ()>& preTick, const std::function<void ()>& postTick)
{
	// Save
	m_preTick = preTick;
	m_postTick = postTick;
	// Run
	cocos2d::Application::getInstance()->run();
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
