# SPDX-FileCopyrightText: 2025 Trần Nam Tuấn <tuantran1632001@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.24)

project(mea-save-editor VERSION 0.0.1)

include(FeatureSummary)

set(QT6_MIN_VERSION 6.8.0)
set(KF6_MIN_VERSION 6.13.0)
set(KIRIGAMI_ADDONS_MIN_VERSION 1.6.0)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMSetupVersion)
include(ECMFindQmlModule)
include(ECMQmlModule)

include(KDEGitCommitHooks)
include(KDEClangFormat)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX MEASAVEEDITOR
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/measaveeditor-version.hpp"
)

find_package(Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Gui
    Qml
    QuickControls2
    Svg
    Widgets
)

find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS
    Kirigami
    CoreAddons
    Config
    I18n
    IconThemes
)

find_package(KF6KirigamiAddons ${KIRIGAMI_ADDONS_MIN_VERSION} REQUIRED)
set_package_properties(KF6KirigamiAddons PROPERTIES
    TYPE REQUIRED
    PURPOSE "Required application components and runtime dependency"
)

find_package(ZLIB REQUIRED)

qt_policy(SET QTP0004 NEW)

ecm_find_qmlmodule(org.kde.kirigamiaddons.formcard)
ecm_find_qmlmodule(org.kde.kirigamiaddons.statefulapp)
ecm_find_qmlmodule(org.kde.kirigamiaddons.components)

add_subdirectory(src)

if(LINUX OR (UNIX AND NOT APPLE))
    configure_file(thebill2001.mea-save-editor.desktop.in thebill2001.mea-save-editor.desktop @ONLY)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/thebill2001.mea-save-editor.desktop" DESTINATION ${KDE_INSTALL_APPDIR})
    install(FILES thebill2001.mea-save-editor.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
endif()

ki18n_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.hpp)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
