project(nc)
cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)

include(InstallRequiredSystemLibraries)

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

set(nc_SOURCES QBtAttrDialog.cpp QBtButtonSpace.cpp QBtCanOverwrite.cpp QBtColorDemo.cpp QBtCompareDirsDialog.cpp QBtCompareFileDialog.cpp QBtConfig.cpp QBtConfigApps.cpp QBtConfigButtons.cpp QBtConfigDialog.cpp QBtConfigExtensions.cpp QBtConfigPanels.cpp QBtCopyDialog.cpp QBtDeleteQuest.cpp QBtDeleter.cpp QBtDirCopyDialog.cpp QBtDirModel.cpp QBtDirParser.cpp QBtDirSelector.cpp QBtDirWorkedThread.cpp QBtEditExtensions.cpp QBtEventsController.cpp QBtFileComparator.cpp QBtFileEditor.cpp QBtFileJoiner.cpp QBtFileViewer.cpp QBtFinder.cpp QBtHelp.cpp QBtInfoLabel.cpp QBtMainWindow.cpp QBtPackDialog.cpp QBtPanel.cpp QBtPointsButton.cpp QBtSettings.cpp QBtShared.cpp QBtSyncDirsDialog.cpp QBtSystemCall.cpp QBtSystemInfo.cpp QBtTimeStamp.cpp QBtView.cpp QBtViewDelegate.cpp QBtViewModel.cpp QBtWiper.cpp QBtWorkedThread.cpp QBtWorkspace.cpp bsc.cpp)
set(nc_HEADERS QBtAttrDialog.h QBtButtonSpace.h QBtCanOverwrite.h QBtColorDemo.h QBtCompareDirsDialog.h QBtCompareFileDialog.h QBtConfig.h QBtConfigApps.h QBtConfigButtons.h QBtConfigDialog.h QBtConfigExtensions.h QBtConfigPanels.h QBtCopyDialog.h QBtDeleteQuest.h QBtDeleter.h QBtDirCopyDialog.h QBtDirModel.h QBtDirParser.h QBtDirSelector.h QBtDirWorkedThread.h QBtEditExtensions.h QBtEventsController.h QBtFileComparator.h QBtFileEditor.h QBtFileJoiner.h QBtFileViewer.h QBtFinder.h QBtHelp.h QBtInfoLabel.h QBtMainWindow.h QBtPackDialog.h QBtPanel.h QBtPointsButton.h QBtSettings.h QBtShared.h QBtSyncDirsDialog.h QBtSystemInfo.h QBtTabBar.h QBtTimeStamp.h QBtView.h QBtViewDelegate.h QBtViewModel.h QBtWiper.h QBtWorkedThread.h QBtWorkspace.h)
set(nc_RESOURCES bsc.qrc)

qt4_wrap_cpp(nc_HEADERS_MOC ${nc_HEADERS})
qt4_add_resources(nc_RESOURCES_RCC ${nc_RESOURCES})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
	add_executable(nc WIN32 ${nc_SOURCES} ${nc_HEADERS_MOC} ${nc_RESOURCES_RCC} nc.rc)
else()
	add_executable(nc ${nc_SOURCES} ${nc_HEADERS_MOC} ${nc_RESOURCES_RCC})
endif()

target_link_libraries(nc ${QT_LIBRARIES})
install(TARGETS nc RUNTIME DESTINATION bin COMPONENT applications)

set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} applications)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "NasuTek Commander Core Application")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(CPack)