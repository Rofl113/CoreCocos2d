cmake_minimum_required(VERSION 3.5)

set(HEADERS_CoreCocos2d
    ./PtrCocos2d.h
    ./ISceneCocos2d.h
    ./ManagerSceneCocos2d.h
    ./RenderCocos2d.h
    ./SceneCocos2d.h
    ./FactorySceneCocos2d.h
    ./DescriptionSceneCocos2d.h
    ./HolderPathsCocos2d.h
    ./CoreAppDelegateCocos2d.h
    ./ISceneCreatorCocos2d.h
    ./SceneCreatorCocos2d.h
    )

set(SOURCES_CoreCocos2d
    ./ManagerSceneCocos2d.cpp
    ./RenderCocos2d.cpp
    ./SceneCocos2d.cpp
    ./FactorySceneCocos2d.cpp
    ./DescriptionSceneCocos2d.cpp
    ./HolderPathsCocos2d.cpp
    ./CoreAppDelegateCocos2d.cpp
    )

# Создание статической библиотеки
add_library(CoreCocos2d_LIB STATIC ${SOURCES_CoreCocos2d} ${HEADERS_CoreCocos2d})

find_package(Core_LIB)
target_link_libraries(CoreCocos2d_LIB Core_LIB)

find_package(cocos2d)
target_link_libraries(CoreCocos2d_LIB cocos2d)
