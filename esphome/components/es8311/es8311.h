#pragma once
#include "esphome.h"
#include "esphome/components/i2s_audio/i2s_audio.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace es8311 {

class ES8311Init : public i2s_audio::I2SCodec {
 public:
  void setup() override {
    ESP_LOGD("es8311", "Initializing ES8311 codec...");

    // Make sure I2C bus exists
    if (!i2c_bus_) {
      ESP_LOGE("es8311", "I2C bus not set!");
      return;
    }

    // Reset ES8311 (if needed)
    write_register(0x00, 0x00);  // dummy reset example
    delay(10);

    // Basic ADC/DAC configuration
    write_register(0x1A, 0x30);  // example: set ADC gain
    write_register(0x1B, 0x0C);  // example: set DAC volume

    ESP_LOGD("es8311", "ES8311 codec initialization complete");
  }

  void loop() override {
    // Optional runtime updates can go here
  }

  void set_i2c_bus(i2c::I2CBus *bus) { i2c_bus_ = bus; }

 private:
  i2c::I2CBus *i2c_bus_{nullptr};

  void write_register(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    i2c_bus_->write_byte_data(0x18, reg, value);  // ES8311 default I2C addr = 0x18
  }
};
extern ES8311Init es8311_instance;
}  // namespace es8311
}  // namespace esphome
