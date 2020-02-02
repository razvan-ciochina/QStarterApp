#pragma once

struct AppConfig
{
    uint32_t start;
    uint32_t end;
    bool random;
};

const AppConfig& getAppConfig();