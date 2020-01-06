#include "DescriptionSceneCocos2d.h"



DescriptionSceneCocos2d::DescriptionSceneCocos2d(const std::string& name, const std::string& type, const std::vector<std::string>& paths, const std::string& ccbName)
    : m_name(name)
    , m_type(type)
    , m_paths(paths)
    , m_ccbName(ccbName)
{

}

const std::string& DescriptionSceneCocos2d::getName() const
{
	return m_name;
}

const std::string& DescriptionSceneCocos2d::getType() const
{
	return m_type;
}

const std::vector<std::string>& DescriptionSceneCocos2d::getPaths() const
{
	return m_paths;
}

const std::string& DescriptionSceneCocos2d::getCcbName() const
{
	return m_ccbName;
}
