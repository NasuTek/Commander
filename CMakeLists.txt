##############################################################################
#  NasuTek Commander
#  Copyright (C) 2012 NasuTek Enterprises <mmanley@nasutek.com>
#  Copyright (C) 2005-2008 Piotr Pszczolkowski <piotr@beesoft.org>
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
##############################################################################

project(nc)
cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)

include(InstallRequiredSystemLibraries)

##############################################################################
#  CPack Varables
##############################################################################
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NasuTek Commander")
set(CPACK_PACKAGE_VENDOR "NasuTek Enterprises")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/licence.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "5")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "NasuTek Commander")
if(WIN32 AND NOT UNIX)
	#set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
	set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\nc.exe")
	set(CPACK_NSIS_DISPLAY_NAME "NasuTek Commander")
	set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.nasutek.com")
	set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.nasutek.com")
	set(CPACK_NSIS_CONTACT "mmanley@nasutek.com")
	set(CPACK_NSIS_MODIFY_PATH OFF)
	set(CPACK_NSIS_COMPONENT_INSTALL ON)
else(WIN32 AND NOT UNIX)
	set(CPACK_STRIP_FILES "bin/nc")
	set(CPACK_SOURCE_STRIP_FILES "")
endif(WIN32 AND NOT UNIX)
set(CPACK_PACKAGE_EXECUTABLES "nc" "NasuTek Commander")

##############################################################################
#  Source Code Varables (Includes/Headers/Resources/etc.)
##############################################################################
set(nc_SOURCES src/QBtAttrDialog.cpp src/QBtButtonSpace.cpp src/QBtCanOverwrite.cpp src/QBtColorDemo.cpp
    src/QBtCompareDirsDialog.cpp src/QBtCompareFileDialog.cpp src/QBtConfig.cpp src/QBtConfigApps.cpp
    src/QBtConfigButtons.cpp src/QBtConfigDialog.cpp src/QBtConfigExtensions.cpp src/QBtConfigPanels.cpp
    src/QBtCopyDialog.cpp src/QBtDeleteQuest.cpp src/QBtDeleter.cpp src/QBtDirCopyDialog.cpp
    src/QBtDirModel.cpp src/QBtDirParser.cpp src/QBtDirSelector.cpp src/QBtDirWorkedThread.cpp
    src/QBtEditExtensions.cpp src/QBtEventsController.cpp src/QBtFileComparator.cpp src/QBtFileEditor.cpp
    src/QBtFileJoiner.cpp src/QBtFileViewer.cpp src/QBtFinder.cpp src/QBtHelp.cpp
    src/QBtInfoLabel.cpp src/QBtMainWindow.cpp src/QBtPackDialog.cpp src/QBtPanel.cpp
    src/QBtPointsButton.cpp src/QBtSettings.cpp src/QBtShared.cpp src/QBtSyncDirsDialog.cpp
    src/QBtSystemCall.cpp src/QBtSystemInfo.cpp src/QBtTimeStamp.cpp src/QBtView.cpp
    src/QBtViewDelegate.cpp src/QBtViewModel.cpp src/QBtWiper.cpp src/QBtWorkedThread.cpp
    src/QBtWorkspace.cpp src/nc.cpp)

set(nc_HEADERS includes/QBtAttrDialog.h includes/QBtButtonSpace.h includes/QBtCanOverwrite.h includes/QBtColorDemo.h
    includes/QBtCompareDirsDialog.h includes/QBtCompareFileDialog.h includes/QBtConfig.h includes/QBtConfigApps.h
    includes/QBtConfigButtons.h includes/QBtConfigDialog.h includes/QBtConfigExtensions.h includes/QBtConfigPanels.h
    includes/QBtCopyDialog.h includes/QBtDeleteQuest.h includes/QBtDeleter.h includes/QBtDirCopyDialog.h
    includes/QBtDirModel.h includes/QBtDirParser.h includes/QBtDirSelector.h includes/QBtDirWorkedThread.h
    includes/QBtEditExtensions.h includes/QBtEventsController.h includes/QBtFileComparator.h includes/QBtFileEditor.h
    includes/QBtFileJoiner.h includes/QBtFileViewer.h includes/QBtFinder.h includes/QBtHelp.h
    includes/QBtInfoLabel.h includes/QBtMainWindow.h includes/QBtPackDialog.h includes/QBtPanel.h
    includes/QBtPointsButton.h includes/QBtSettings.h includes/QBtShared.h includes/QBtSyncDirsDialog.h
    includes/QBtSystemInfo.h includes/QBtTabBar.h includes/QBtTimeStamp.h includes/QBtView.h
    includes/QBtViewDelegate.h includes/QBtViewModel.h includes/QBtWiper.h includes/QBtWorkedThread.h
    includes/QBtWorkspace.h)

set(nc_RESOURCES rc/nc.qrc)

##############################################################################
#  Include Declerations
##############################################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

##############################################################################
#  QT Generators
##############################################################################
qt4_wrap_cpp(nc_HEADERS_MOC ${nc_HEADERS})
qt4_add_resources(nc_RESOURCES_RCC ${nc_RESOURCES})

##############################################################################
#  QT Includes
##############################################################################
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

##############################################################################
#  NasuTek Commander Executable Target
##############################################################################
if(WIN32)
        add_executable(nc WIN32 ${nc_SOURCES} ${nc_HEADERS_MOC} ${nc_RESOURCES_RCC} rc/nc.rc)
else()
        add_executable(nc ${nc_SOURCES} ${nc_HEADERS_MOC} ${nc_RESOURCES_RCC})
endif()

target_link_libraries(nc ${QT_LIBRARIES})
install(TARGETS nc RUNTIME DESTINATION bin COMPONENT applications)

##############################################################################
#  QT Library Package Inclusion
##############################################################################
if(WIN32)
    install(FILES ${QT_BINARY_DIR}/QtCore4.dll ${QT_BINARY_DIR}/QtGui4.dll ${QT_BINARY_DIR}/mingwm10.dll
        ${QT_BINARY_DIR}/libgcc_s_dw2-1.dll DESTINATION bin COMPONENT qtruntime)
    set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} qtruntime)
    set(CPACK_COMPONENT_QTRUNTIME_DISPLAY_NAME "Qt 4 Runtime")
endif()

##############################################################################
#  Application Package Inclusion
##############################################################################
set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} applications)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "NasuTek Commander Core Application")

##############################################################################
#  CPack Include
##############################################################################
include(CPack)
