deps_config := \
	/opt/espadf/esp-adf/esp-idf/components/app_trace/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/aws_iot/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/bt/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/esp32/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/esp_adc_cal/Kconfig \
	/opt/espadf/esp-adf/components/esp_http_client/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/ethernet/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/fatfs/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/freertos/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/heap/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/libsodium/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/log/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/lwip/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/mbedtls/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/openssl/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/pthread/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/spi_flash/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/spiffs/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/tcpip_adapter/Kconfig \
	/opt/espadf/esp-adf/esp-idf/components/wear_levelling/Kconfig \
	/opt/espadf/esp-adf/components/audio_hal/Kconfig.projbuild \
	/opt/espadf/esp-adf/esp-idf/components/bootloader/Kconfig.projbuild \
	/opt/espadf/esp-adf/esp-idf/components/esptool_py/Kconfig.projbuild \
	/opt/espadf/esp-adf/esp-idf/components/partition_table/Kconfig.projbuild \
	/opt/espadf/esp-adf/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
