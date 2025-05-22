idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES ca_cert.pem
                    PRIV_REQUIRES esp_http_client esp_partition nvs_flash app_update esp_timer esp_wifi console)
