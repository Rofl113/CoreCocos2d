#pragma once
#include <vector>
// Core lib
#include <Core/IDescriptionScene.h>



class DescriptionSceneCocos2d : public IDescriptionScene
{
	DescriptionSceneCocos2d() = delete;
public:
	DescriptionSceneCocos2d(const std::string& name, const std::string& type, const std::vector<std::string>& paths, const std::string& ccbName);
	// Имя сцены
	virtual const std::string& getName() const override;
	// Тип сцены (логический класс)
	virtual const std::string& getType() const override;
	// Абсолютные пути поиска
	const std::vector<std::string>& getPaths() const;
	// Файл с которого начинается вся сцена
	const std::string& getCcbName() const;

private:
	const std::string m_name;
	const std::string m_type;
	// Абсолютные пути поиска
	const std::vector<std::string> m_paths;
	// Файл с которого начинается вся сцена
	const std::string m_ccbName;
};
