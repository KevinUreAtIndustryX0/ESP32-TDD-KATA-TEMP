#ifndef _ESP_HTTP_CLIENT_MOCK_H_
#define _ESP_HTTP_CLIENT_MOCK_H_

#include "fff.h"
#include "esp_err.h"
#include <stdbool.h>

typedef struct esp_http_client *esp_http_client_handle_t;
typedef struct esp_http_client_event *esp_http_client_event_handle_t;


typedef enum {
    HTTP_METHOD_GET = 0,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_PATCH,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_NOTIFY,
    HTTP_METHOD_SUBSCRIBE,
    HTTP_METHOD_UNSUBSCRIBE,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_MAX,
} esp_http_client_method_t;

typedef enum {
    HTTP_AUTH_TYPE_NONE = 0,
    HTTP_AUTH_TYPE_BASIC,
    HTTP_AUTH_TYPE_DIGEST,
} esp_http_client_auth_type_t;

typedef enum {
    HTTP_EVENT_ERROR = 0,
    HTTP_EVENT_ON_CONNECTED,
    HTTP_EVENT_HEADERS_SENT,
    HTTP_EVENT_HEADER_SENT = HTTP_EVENT_HEADERS_SENT, 
    HTTP_EVENT_ON_HEADER,
    HTTP_EVENT_ON_DATA,
    HTTP_EVENT_ON_FINISH,
    HTTP_EVENT_DISCONNECTED,
} esp_http_client_event_id_t;

typedef enum {
    HTTP_TRANSPORT_UNKNOWN = 0x0,
    HTTP_TRANSPORT_OVER_TCP,
    HTTP_TRANSPORT_OVER_SSL,
} esp_http_client_transport_t;

typedef struct esp_http_client_event {
    esp_http_client_event_id_t event_id;
    esp_http_client_handle_t client;
    void *data;
    int data_len;
    void *user_data;
    char *header_key;
    char *header_value;
} esp_http_client_event_t;

typedef esp_err_t (*http_event_handle_cb)(esp_http_client_event_t *evt);

typedef struct {
    const char                  *url;
    const char                  *host;
    int                         port;
    const char                  *username;
    const char                  *password;
    esp_http_client_auth_type_t auth_type;
    const char                  *path;
    const char                  *query;
    const char                  *cert_pem;
    const char                  *client_cert_pem;
    const char                  *client_key_pem;
    esp_http_client_method_t    method;
    int                         timeout_ms;
    bool                        disable_auto_redirect;
    int                         max_redirection_count;
    http_event_handle_cb        event_handler;
    esp_http_client_transport_t transport_type;
    int                         buffer_size;
    int                         buffer_size_tx;
    void                        *user_data;
    bool                        is_async;
    bool                        use_global_ca_store;
    bool                        skip_cert_common_name_check;
} esp_http_client_config_t;

DECLARE_FAKE_VALUE_FUNC(esp_http_client_handle_t, esp_http_client_init, esp_http_client_config_t);
DECLARE_FAKE_VALUE_FUNC(esp_err_t, esp_http_client_open, esp_http_client_handle_t, int);
DECLARE_FAKE_VALUE_FUNC(int, esp_http_client_fetch_headers, esp_http_client_handle_t);
DECLARE_FAKE_VALUE_FUNC(int, esp_http_client_read, esp_http_client_handle_t, char*, int);

#endif 
