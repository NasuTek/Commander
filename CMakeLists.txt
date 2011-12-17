project(nc)
cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)

set(nc_SOURCES QBtAttrDialog.cpp QBtButtonSpace.cpp QBtCanOverwrite.cpp QBtColorDemo.cpp QBtCompareDirsDialog.cpp QBtCompareFileDialog.cpp QBtConfig.cpp QBtConfigApps.cpp QBtConfigButtons.cpp QBtConfigDialog.cpp QBtConfigExtensions.cpp QBtConfigPanels.cpp QBtCopyDialog.cpp QBtDeleteQuest.cpp QBtDeleter.cpp QBtDirCopyDialog.cpp QBtDirModel.cpp QBtDirParser.cpp QBtDirSelector.cpp QBtDirWorkedThread.cpp QBtEditExtensions.cpp QBtEventsController.cpp QBtFileComparator.cpp QBtFileEditor.cpp QBtFileJoiner.cpp QBtFileViewer.cpp QBtFinder.cpp QBtHelp.cpp QBtInfoLabel.cpp QBtMainWindow.cpp QBtPackDialog.cpp QBtPanel.cpp QBtPointsButton.cpp QBtSettings.cpp QBtShared.cpp QBtSyncDirsDialog.cpp QBtSystemCall.cpp QBtSystemInfo.cpp QBtTimeStamp.cpp QBtView.cpp QBtViewDelegate.cpp QBtViewModel.cpp QBtWiper.cpp QBtWorkedThread.cpp QBtWorkspace.cpp bsc.cpp)
set(nc_HEADERS QBtAttrDialog.h QBtButtonSpace.h QBtCanOverwrite.h QBtColorDemo.h QBtCompareDirsDialog.h QBtCompareFileDialog.h QBtConfig.h QBtConfigApps.h QBtConfigButtons.h QBtConfigDialog.h QBtConfigExtensions.h QBtConfigPanels.h QBtCopyDialog.h QBtDeleteQuest.h QBtDeleter.h QBtDirCopyDialog.h QBtDirModel.h QBtDirParser.h QBtDirSelector.h QBtDirWorkedThread.h QBtEditExtensions.h QBtEventsController.h QBtFileComparator.h QBtFileEditor.h QBtFileJoiner.h QBtFileViewer.h QBtFinder.h QBtHelp.h QBtInfoLabel.h QBtMainWindow.h QBtPackDialog.h QBtPanel.h QBtPointsButton.h QBtSettings.h QBtShared.h QBtSyncDirsDialog.h QBtSystemInfo.h QBtTabBar.h QBtTimeStamp.h QBtView.h QBtViewDelegate.h QBtViewModel.h QBtViewStandardItem.h QBtWiper.h QBtWorkedThread.h QBtWorkspace.h)
set(nc_RESOURCES bsc.qrc)

qt4_wrap_cpp(nc_HEADERS_MOC ${nc_HEADERS})
qt4_add_resources(nc_RESOURCES_RCC ${nc_RESOURCES})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

if(WIN32)
	add_executable(nc WIN32 ${nc_SOURCES} ${nc_HEADERS_MOC} ${nc_RESOURCES_RCC} nc.rc)
else()
	add_executable(nc ${nc_SOURCES} ${nc_HEADERS_MOC} ${nc_RESOURCES_RCC})
endif()

target_link_libraries(nc ${QT_LIBRARIES})

include_directories(${CMAKE_CURRENT_BINARY_DIR})