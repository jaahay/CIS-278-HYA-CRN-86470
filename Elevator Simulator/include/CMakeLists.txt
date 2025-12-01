add_library(include INTERFACE)
target_include_directories(include INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)