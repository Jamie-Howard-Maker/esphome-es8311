#include "esphome.h"

using namespace esphome;

class ES8311Init : public Component {
 public:
  void setup() override {
    ESP_LOGI("es8311", "Initializing ES8311 codec");

    auto *bus = i2c::global_i2c;
    if (!bus) return;

    const uint8_t addr = 0x18;

    write(bus, addr, 0x00, 0x80); delay(10); // reset
    write(bus, addr, 0x01, 0x30);
    write(bus, addr, 0x02, 0x00);
    write(bus, addr, 0x03, 0x00); // power up ADC/DAC

    write(bus, addr, 0x09, 0x0C); // mic gain
    write(bus, addr, 0x0A, 0x0C);

    write(bus, addr, 0x11, 0x00); // I2S 16bit
    write(bus, addr, 0x12, 0x00);

    write(bus, addr, 0x31, 0x20); // DAC volume
    write(bus, addr, 0x32, 0x20);

    write(bus, addr, 0x13, 0x00); // unmute

    ESP_LOGI("es8311", "ES8311 initialized");
  }

 private:
  void write(i2c::I2CBus *bus, uint8_t addr, uint8_t reg, uint8_t val) {
    bus->write(addr, {reg, val});
    delay(2);
  }
};
