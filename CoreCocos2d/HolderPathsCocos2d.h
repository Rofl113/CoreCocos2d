#pragma once
#include <vector>
#include <string>



class HolderPathsCocos2d
{
	HolderPathsCocos2d() = delete;
public:
	~HolderPathsCocos2d();
	HolderPathsCocos2d(const std::vector<std::string>& paths);

private:
	const std::vector<std::string> m_pathsOld;
};
