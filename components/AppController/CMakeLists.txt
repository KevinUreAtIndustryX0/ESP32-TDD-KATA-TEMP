idf_component_register(SRCS "appController.c"
                    INCLUDE_DIRS "./include"
                    REQUIRES LedController
                    PRIV_REQUIRES log freertos)
