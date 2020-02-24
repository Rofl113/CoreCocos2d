#pragma once
// Core lib
#include "Core/Render.h"
// Cocos2d lib
#include <cocos/base/CCEventListenerCustom.h>
// CoreCocos2d
#include "CoreCocos2d/PtrCocos2d.h"


namespace cocos2d { class GLView; }



class RenderCocos2d : public Render
{
	using ClassBase = Render;
	class AppDelegateCocos2d;
	RenderCocos2d() = delete;
public:
	explicit RenderCocos2d(PtrCocos2d<cocos2d::GLView>&& glView
	                       , const IFactoryScene& factoryScene
	                       , const IManagerDescriptionScene& managerDescriptionScene);
	explicit RenderCocos2d(const std::string& name
	                       , const std::pair<size_t, size_t>& sizeView
	                       , const std::pair<size_t, size_t>& sizeDesignResolution
	                       , const bool isResizable
	                       , const IFactoryScene& factoryScene
	                       , const IManagerDescriptionScene& managerDescriptionScene);
	virtual ~RenderCocos2d() override;

	virtual int run(const std::function<void()>& preTick, const std::function<void()>& postTick) override;

private:
	virtual void handleLoadScene(const std::shared_ptr<IScene>& scene) const override;
	virtual void handleShowScene(const std::shared_ptr<IScene>& scene) const override;

private:
	void handleAfterDraw();
	void handleBeforeDraw();

	std::unique_ptr<AppDelegateCocos2d> m_appDelegateCocos2d;
	PtrCocos2d<cocos2d::GLView> m_glView;

	std::function<void ()> m_preTick;
	std::function<void ()> m_postTick;

	cocos2d::EventListenerCustom* m_eventPreTick = nullptr;
	cocos2d::EventListenerCustom* m_eventPostTick = nullptr;
};
