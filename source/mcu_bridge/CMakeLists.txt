set(TARGET mcu_bridge_headers)

add_library(${TARGET} INTERFACE)

target_include_directories(
    ${TARGET} 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${TARGET}
    INTERFACE mcu_headers
    INTERFACE mcu_cfg
)
