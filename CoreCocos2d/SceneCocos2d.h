#pragma once
#include <memory>
// Core lib
#include <Core/IScene.h>
#include "PtrCocos2d.h"
#include "ISceneCocos2d.h"


namespace cocos2d { class Scene; }
class IDescriptionScene;



class SceneCocos2d : public IScene, public ISceneCocos2d
{
	SceneCocos2d() = delete;
public:
	SceneCocos2d(PtrCocos2d<cocos2d::Scene>&& scene, const std::shared_ptr<IDescriptionScene>& description);
	virtual ~SceneCocos2d() override;

public: /// ISceneCocos2d
	virtual void onLoad() override;
	virtual void onActivate() override;
	virtual void onDeactivate() override;
	virtual void onPause() override;
	virtual void onResume() override;

	virtual cocos2d::Scene* getSceneCocos() const override final;

protected:
	std::string fullPathForFilename(const std::string& name) const;

private:
	const PtrCocos2d<cocos2d::Scene> m_scene;
	const std::shared_ptr<IDescriptionScene>& m_description;
};
