idf_component_register(SRCS "network_controller.c"
                    INCLUDE_DIRS "./include"
                    REQUIRES led_controller
                    PRIV_REQUIRES log esp_http_client esp_netif esp_event protocol_examples_common)
