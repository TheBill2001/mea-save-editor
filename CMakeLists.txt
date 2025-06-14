cmake_minimum_required(VERSION 3.21)

project(mea-save-editor VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT6_MIN_VERSION 6.8.0)
set(KF6_MIN_VERSION 6.13.0)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(FeatureSummary)

include(ECMSetupVersion)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEGitCommitHooks)
include(KDEClangFormat)

find_package(Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS Widgets)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX MEA_SAVE_EDITOR
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/utils/version.h"
)

qt_add_executable(mea-save-editor
    src/main.cpp

    src/mainwindow.cpp src/mainwindow.hpp
    src/landingwidget.hpp src/landingwidget.cpp
)

qt_add_ui(mea-save-editor INCLUDE_PREFIX forms SOURCES
    forms/mainwindow.ui
    forms/landingwidget.ui
)

target_include_directories(mea-save-editor PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/src")

target_link_libraries(mea-save-editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(mea-save-editor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.mea-save-editor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS mea-save-editor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(LINUX OR (UNIX AND NOT APPLE))
    configure_file(io.github.thebill2001.mea-save-editor.desktop.in io.github.thebill2001.mea-save-editor.desktop @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/io.github.thebill2001.mea-save-editor.desktop" DESTINATION ${KDE_INSTALL_APPDIR})
    install(FILES io.github.thebill2001.mea-save-editor.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.hpp)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
