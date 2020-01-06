#include "HolderPathsCocos2d.h"
// Cocos lib
#include <cocos/platform/CCFileUtils.h>


HolderPathsCocos2d::~HolderPathsCocos2d()
{
	cocos2d::FileUtils::getInstance()->setSearchPaths(m_pathsOld);
}

HolderPathsCocos2d::HolderPathsCocos2d(const std::vector<std::string>& paths)
    : m_pathsOld(cocos2d::FileUtils::getInstance()->getSearchPaths())
{
	cocos2d::FileUtils::getInstance()->setSearchPaths(paths);
}
