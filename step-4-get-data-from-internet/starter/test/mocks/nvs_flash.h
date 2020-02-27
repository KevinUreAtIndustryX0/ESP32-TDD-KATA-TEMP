#ifndef _NVS_FLASH_MOCK_H_
#define _NVS_FLASH_MOCK_H_

#include "esp_err.h"
#include "fff.h"

#define ESP_ERR_NVS_NO_FREE_PAGES 1
#define ESP_ERR_NVS_NEW_VERSION_FOUND 2

DECLARE_FAKE_VALUE_FUNC(esp_err_t, nvs_flash_init)
DECLARE_FAKE_VALUE_FUNC(esp_err_t, nvs_flash_erase)

#endif