# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += /opt/espadf/esp-adf/components/esp-adf-libs/esp_audio/include /opt/espadf/esp-adf/components/esp-adf-libs/esp_codec/include /opt/espadf/esp-adf/components/esp-adf-libs/esp_codec/wav/include /opt/espadf/esp-adf/components/esp-adf-libs/esp_codec/resample/include /opt/espadf/esp-adf/components/esp-adf-libs/recorder_engine/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/esp-adf-libs -lesp-adf-libs -L/opt/espadf/esp-adf/components/esp-adf-libs/esp_audio/lib -L/opt/espadf/esp-adf/components/esp-adf-libs/esp_codec/lib -L/opt/espadf/esp-adf/components/esp-adf-libs/recorder_engine/lib -lesp_codec -lesp_audio -lesp-aac -lrecorder_engine -lvad 
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += esp-adf-libs
component-esp-adf-libs-build: 
