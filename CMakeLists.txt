idf_component_register(SRC_DIRS src/source
                       INCLUDE_DIRS "src"
                       PRIV_REQUIRES driver
)
target_compile_options(${COMPONENT_LIB} PRIVATE -Wfatal-errors)
