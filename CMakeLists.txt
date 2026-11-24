cmake_minimum_required(VERSION 3.19)
project(LMZ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(LMZ
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    lmz.cpp
    HuffmanTree.h
    LMZ.h
    bitwriteandreadr.h bitwriteandread.cpp
    filewr.h filewr.cpp
)

qt_add_translations(
    TARGETS LMZ
    TS_FILES LMZ_zh_CN.ts
)

target_link_libraries(LMZ
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS LMZ
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET LMZ
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
