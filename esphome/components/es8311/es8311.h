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

    if (!i2c_bus_) {
      ESP_LOGE("es8311", "I2C bus not set!");
      return;
    }

    // Example register writes
    i2c_bus_->write_byte_data(0x18, 0x00, 0x00);  // reset
    delay(10);
    i2c_bus_->write_byte_data(0x18, 0x1A, 0x30);  // ADC gain
    i2c_bus_->write_byte_data(0x18, 0x1B, 0x0C);  // DAC volume

    ESP_LOGD("es8311", "ES8311 codec initialization complete");
  }

  void loop() override {}

  void set_i2c_bus(i2c::I2CBus *bus) { i2c_bus_ = bus; }

 private:
  i2c::I2CBus *i2c_bus_{nullptr};
};

// **Global instance**
inline ES8311Init es8311_instance;

}  // namespace es8311
}  // namespace esphome
