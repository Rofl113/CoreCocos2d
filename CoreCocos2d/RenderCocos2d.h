#pragma once
// Core lib
#include "Core/Render.h"

#include <cocos/base/CCEventListenerCustom.h>


class RenderCocos2d : public Render
{
	using ClassBase = Render;
	RenderCocos2d() = delete;
public:
	explicit RenderCocos2d(const IFactoryScene& factoryScene, const IManagerDescriptionScene& managerDescriptionScene);
	virtual ~RenderCocos2d() override;

	virtual void run(const std::function<void()>& preTick, const std::function<void()>& postTick) override;

private:
	virtual void handleLoadScene(const std::shared_ptr<IScene>& scene) const override;
	virtual void handleShowScene(const std::shared_ptr<IScene>& scene) const override;

private:
	void handleAfterDraw();
	void handleBeforeDraw();

	std::function<void ()> m_preTick;
	std::function<void ()> m_postTick;

	cocos2d::EventListenerCustom* m_eventPreTick = nullptr;
	cocos2d::EventListenerCustom* m_eventPostTick = nullptr;
};
