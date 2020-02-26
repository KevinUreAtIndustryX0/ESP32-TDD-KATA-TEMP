idf_component_register(SRCS "network_controller.c"
                    INCLUDE_DIRS "./include"
                    PRIV_REQUIRES esp_netif esp_event)
