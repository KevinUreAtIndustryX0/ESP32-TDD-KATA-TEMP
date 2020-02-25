idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "." "${PROJECT_BINARY_DIR}/.."
                    REQUIRES board led_controller
                    PRIV_REQUIRES log)
