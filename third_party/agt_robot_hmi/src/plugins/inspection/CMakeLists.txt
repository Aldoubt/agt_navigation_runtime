add_library(agt_inspection
  inspection_types.h
  inspection_point_editor.cpp inspection_point_editor.h
  inspection_task_viewer.cpp inspection_task_viewer.h
  inspection_result_viewer.cpp inspection_result_viewer.h
  inspection_panel.cpp inspection_panel.h)
qt5_wrap_cpp(AGT_INSPECTION_MOC inspection_point_editor.h inspection_task_viewer.h inspection_result_viewer.h inspection_panel.h)
target_sources(agt_inspection PRIVATE ${AGT_INSPECTION_MOC})
target_include_directories(agt_inspection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(agt_inspection PUBLIC Qt5::Core Qt5::Widgets yaml-cpp)
set_target_properties(agt_inspection PROPERTIES AUTOMOC OFF)
