idf_component_register(SRCS "appController.c"
                    INCLUDE_DIRS "./include"
                    REQUIRES LedController NetworkController
                    PRIV_REQUIRES log freertos nvs_flash)
