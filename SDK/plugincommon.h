/*
 * SA-MP Plugin SDK
 * Copyright (c) 2016 udan11
 * https://github.com/udan11/samp-plugin-sdk
 */

#ifndef PLUGINCOMMON_H
#define PLUGINCOMMON_H

#ifdef _WIN32
    #define PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
    #define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

#define PLUGIN_CALL

// Plugin data offsets
enum PLUGIN_DATA {
    PLUGIN_DATA_LOGPRINTF,
    PLUGIN_DATA_AMX_EXPORTS
};

// Plugin support flags
enum SUPPORTS_FLAGS {
    SUPPORTS_VERSION = 0x00200,
    SUPPORTS_AMX_NATIVES = 0x10000,
    SUPPORTS_PROCESS_TICK = 0x20000
};

typedef void (*logprintf_t)(const char* format, ...);

#endif // PLUGINCOMMON_H
