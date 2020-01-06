#include "ManagerSceneCocos2d.h"
// Core lib
#include <Core/IScene.h>
#include "ISceneCocos2d.h"



ManagerSceneCocos2d::ManagerSceneCocos2d(const IRender& render)
    : ClassBase(render)
{

}

ManagerSceneCocos2d::~ManagerSceneCocos2d()
{

}

std::shared_ptr<IScene> ManagerSceneCocos2d::loadScene(const std::string& name)
{
	auto scene = ClassBase::loadScene(name);
	if (const auto sceneBase = dynamic_cast<ISceneCocos2d*>(scene.get()))
	{
		sceneBase->onLoad();
	}
	return scene;
}

const std::shared_ptr<IScene>& ManagerSceneCocos2d::top()
{
	return ClassBase::top();
}

bool ManagerSceneCocos2d::push(const std::shared_ptr<IScene>& scene)
{
	const auto& sceneOld = this->top();
	const bool result = ClassBase::push(scene);
	if (result)
	{
		const auto& sceneNew = this->top();
		if (sceneOld != sceneNew)
		{
			if (const auto sceneBaseOld = dynamic_cast<ISceneCocos2d*>(sceneOld.get()))
			{
				sceneBaseOld->onPause();
			}
		}
		if (const auto sceneBaseNew = dynamic_cast<ISceneCocos2d*>(sceneNew.get()))
		{
			sceneBaseNew->onActivate();
		}
	}
	return result;
}

bool ManagerSceneCocos2d::pop(const std::shared_ptr<IScene>& scene)
{
	const auto& sceneOld = this->top();
	const bool result = ClassBase::pop(scene);
	if (result)
	{
		if (const auto sceneBaseOld = dynamic_cast<ISceneCocos2d*>(sceneOld.get()))
		{
			sceneBaseOld->onDeactivate();
		}
		const auto& sceneNew = this->top();
		if (sceneOld != sceneNew)
		{
			if (const auto sceneBaseNew = dynamic_cast<ISceneCocos2d*>(sceneNew.get()))
			{
				sceneBaseNew->onResume();
			}
		}
	}
	return result;
}
