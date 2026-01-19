#pragma once
#include "esphome.h"
#include "esphome/components/i2s_audio/i2s_audio.h"

namespace esphome {
namespace es8311 {

class ES8311Init : public i2s_audio::I2SCodec {
 public:
  void setup() override {
    ESP_LOGD("es8311", "Initializing ES8311 codec...");
    // Add I2C configuration here if needed
    // Set default volume, input/output routing, etc.
  }

  void loop() override {
    // optional: run tasks each loop
  }
};

}  // namespace es8311
}  // namespace esphome
