#pragma once
#include "esphome.h"
#include "esphome/components/i2s_audio/i2s_audio.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace es8311 {

class ES8311Init : public i2s_audio::I2SCodec {
 public:
  ES8311Init() {
    // Automatically register with I2S audio system
    i2s_audio::I2SCodec::register_codec(this);
  }

  void setup() override {
    ESP_LOGD("es8311", "Initializing ES8311 codec...");

    if (!i2c_bus_) {
      ESP_LOGE("es8311", "I2C bus not set!");
      return;
    }

    // Reset
    write_register(0x00, 0x80);  // Software reset
    delay(50);

    // Power configuration
    write_register(0x01, 0x01);  // Enable DAC
    write_register(0x02, 0x01);  // Enable ADC
    write_register(0x0F, 0x00);  // Clock source: MCLK from ESP32
    write_register(0x10, 0x00);  // DAC LRCK = 32x BCLK
    write_register(0x11, 0x00);  // ADC LRCK = 32x BCLK

    // ADC setup
    write_register(0x1A, 0x30);  // L/R ADC gain
    write_register(0x1B, 0x30);  // L/R ADC boost

    // DAC setup
    write_register(0x1C, 0x00);  // DAC volume left
    write_register(0x1D, 0x00);  // DAC volume right

    // Power management
    write_register(0x2F, 0xC0);  // Enable all power modules

    // Optional: fine-tune ADC/DAC, mic bias
    write_register(0x33, 0x0C);  // Mic bias 2.0V
    write_register(0x34, 0x08);  // Headphone output enabled

    ESP_LOGD("es8311", "ES8311 codec initialization complete");
  }

  void loop() override {}

  void set_i2c_bus(i2c::I2CBus *bus) { i2c_bus_ = bus; }

 private:
  i2c::I2CBus *i2c_bus_{nullptr};

  void write_register(uint8_t reg, uint8_t value) {
    i2c_bus_->write_byte_data(0x18, reg, value);  // ES8311 default I2C address
  }
};

// Global instance so setup() runs automatically
static ES8311Init es8311_instance;

}  // namespace es8311
}  // namespace esphome
