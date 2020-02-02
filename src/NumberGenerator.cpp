#include <NumberGenerator.hpp>
#include <random>
#include <AppConfig.hpp>

void NumberGenerator::GenerateNumberSlot()
{
    GenerateNumber();
}

uint32_t NumberGenerator::GenerateNumber()
{
    const AppConfig& appCfg = getAppConfig();
    uint32_t result = 0;

    if (appCfg.random == false) {
        result =  (appCfg.end + appCfg.start) / 2;
    } else {
        std::random_device rand_src;
        std::mt19937 mersenne_engine(rand_src());
        std::uniform_int_distribution<uint32_t> dist_interval(appCfg.start, appCfg.end);
        result = dist_interval(mersenne_engine);
    }

    emit FinishedGenerating(result);
    return result;
}