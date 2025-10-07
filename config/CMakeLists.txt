set(CONFIG_LIBRARY mcu_cfg)

add_library(${CONFIG_LIBRARY} INTERFACE)

target_include_directories(
    ${CONFIG_LIBRARY} 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
