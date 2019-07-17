#include "engine/AudioSettings.hpp"

namespace engine {
    float AudioSettings::masterVolume = 0.2f;
    int AudioSettings::sampleRate = 40000;
    int AudioSettings::channels = 2;
    int AudioSettings::bufferSize = 1024;
}