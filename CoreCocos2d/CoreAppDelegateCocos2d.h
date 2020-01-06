#pragma once
// Core lib
#include <Core/CoreAppDelegate.h>


class CoreAppDelegateCocos2d : public CoreAppDelegate
{
public: /// ICoreAppDelegate
	virtual std::unique_ptr<IFactoryScene> createFactoryScene(const SessionApp& sessionApp) override;
	virtual std::unique_ptr<IRender> createRender(const SessionApp& sessionApp, const IFactoryScene& factoryScene, const IManagerDescriptionScene& managerDescriptionScene) override;
	virtual std::unique_ptr<IManagerScene> createManagerScene(const SessionApp& sessionApp, const IRender& render) override;
};
