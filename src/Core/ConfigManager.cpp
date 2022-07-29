#include "pch.h"
#include "Core/ConfigManager.h"

#include "Core/Utils.h"

namespace fs = std::filesystem;

fs::path ConfigManager::s_ConfigFilePath = GetExecDir() /= "OpenNeighborhood.ini";
ConfigManager::ConfigFile ConfigManager::s_ConfigFile = ConfigManager::ConfigFile(ConfigManager::s_ConfigFilePath);
ConfigManager::Config ConfigManager::s_Config;

void ConfigManager::AddXbox(const Xbox &xbox)
{
    if (fs::exists(s_ConfigFilePath))
    {
        s_ConfigFile.read(s_Config);
        s_Config[xbox.GetLabel()]["ip_address"] = xbox.GetIpAddress();
    }
    else
    {
        s_Config[xbox.GetLabel()]["ip_address"] = xbox.GetIpAddress();
        s_ConfigFile.generate(s_Config, true);
    }
}

const ConfigManager::Config &ConfigManager::GetConfig()
{
    if (fs::exists(s_ConfigFilePath))
        s_ConfigFile.read(s_Config);

    return s_Config;
}
