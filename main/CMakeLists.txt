idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "." "${PROJECT_BINARY_DIR}/.."
                    REQUIRES AppController
                    PRIV_REQUIRES log)
