#pragma once


namespace cocos2d { class Scene; }


class ISceneCocos2d
{
public:
	virtual ~ISceneCocos2d() = default;

	virtual cocos2d::Scene* getSceneCocos() const = 0;
	virtual void onLoad() = 0;
	virtual void onActivate() = 0;
	virtual void onDeactivate() = 0;
	virtual void onPause() = 0;
	virtual void onResume() = 0;
};
