#pragma once
// Core lib
#include <Core/ManagerScene.h>


class ManagerSceneCocos2d : public ManagerScene
{
	using ClassBase = ManagerScene;
	ManagerSceneCocos2d() = delete;
public:
	ManagerSceneCocos2d(const IRender& render);
	virtual ~ManagerSceneCocos2d() override;
	// Получить сцену по имени
	virtual std::shared_ptr<IScene> loadScene(const std::string& name) override;
	// Текущая сцена на экране
	virtual const std::shared_ptr<IScene>& top() override;
	// Добавления сцены на экран
	virtual bool push(const std::shared_ptr<IScene>& scene) override;
	// Удаление сцены с экрана
	virtual bool pop(const std::shared_ptr<IScene>& scene) override;
};
