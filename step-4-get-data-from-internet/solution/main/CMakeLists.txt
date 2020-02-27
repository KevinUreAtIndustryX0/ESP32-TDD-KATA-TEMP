idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "./include" "${PROJECT_BINARY_DIR}/.."
                    PRIV_REQUIRES log
                    REQUIRES app_logic)
