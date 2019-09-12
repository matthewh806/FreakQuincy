#include <memory>

#include "catch.hpp"
#include "engine/WaveForm.hpp"


TEST_CASE("WAVE FORM GETTERS") {
    std::unique_ptr<engine::WaveForm> wForm = std::unique_ptr<engine::WaveForm>(new engine::WaveForm());
    wForm->setFrequency(440);
    wForm->setWaveType(engine::WaveTypes::SINE);

    REQUIRE(wForm->getFrequency() == 440.0);
    REQUIRE(wForm->getWaveType() == engine::WaveTypes::SINE);
}
