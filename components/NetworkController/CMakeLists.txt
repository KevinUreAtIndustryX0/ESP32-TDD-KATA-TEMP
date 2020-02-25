idf_component_register(SRCS "networkController.c"
                    INCLUDE_DIRS "./include"
                    REQUIRES LedController
                    PRIV_REQUIRES protocol_examples_common esp-tls esp_http_client)
