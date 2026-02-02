/*
 * TD Animation Plugin - Main File
 * SA-MP Plugin for smooth textdraw animations
 * 
 * Author: Claude
 * Version: 1.0.0
 */

#include "SDK/plugin.h"
#include "TDAnimation.h"
#include <thread>
#include <atomic>

typedef void (*logprintf_t)(const char* format, ...);
logprintf_t logprintf;

extern void *pAMXFunctions;

// Global manager
TDAnimationManager* g_AnimManager = nullptr;

// Animation thread
std::atomic<bool> g_Running(false);
std::thread g_AnimThread;

// Native functions from SA-MP
extern "C" {
    // These are SA-MP native functions we'll call
    // Note: Actual implementation depends on SA-MP SDK version
}

// Animation update loop (60 FPS)
void AnimationUpdateLoop() {
    const int targetFPS = 60;
    const int frameTimeMS = 1000 / targetFPS;
    
    while (g_Running) {
        auto frameStart = std::chrono::steady_clock::now();
        
        if (g_AnimManager) {
            // Update all animations
            // Note: Actual SA-MP native calls would go here
            // This is a placeholder for the update logic
        }
        
        // Sleep to maintain target FPS
        auto frameEnd = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();
        int sleepTime = frameTimeMS - elapsed;
        
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
}

// AMX Native: TD_FadeIn
// native TD_FadeIn(playerid, PlayerText:textdraw, duration = 300, baseColor = 0xFFFFFFFF, easing = EASE_OUT);
static cell AMX_NATIVE_CALL n_TD_FadeIn(AMX* amx, cell* params) {
    // params[1] = playerid
    // params[2] = textdraw
    // params[3] = duration
    // params[4] = baseColor
    // params[5] = easing
    
    int playerid = params[1];
    int textdraw = params[2];
    int duration = (params[0] >= 3 * sizeof(cell)) ? params[3] : 300;
    int baseColor = (params[0] >= 4 * sizeof(cell)) ? params[4] : 0xFFFFFFFF;
    int easing = (params[0] >= 5 * sizeof(cell)) ? params[5] : 2; // EASE_OUT
    
    if (g_AnimManager) {
        int animID = g_AnimManager->fadeIn(playerid, textdraw, true, duration, baseColor, (EasingType)easing);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_FadeOut
// native TD_FadeOut(playerid, PlayerText:textdraw, duration = 300, baseColor = 0xFFFFFFFF, easing = EASE_IN);
static cell AMX_NATIVE_CALL n_TD_FadeOut(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    int duration = (params[0] >= 3 * sizeof(cell)) ? params[3] : 300;
    int baseColor = (params[0] >= 4 * sizeof(cell)) ? params[4] : 0xFFFFFFFF;
    int easing = (params[0] >= 5 * sizeof(cell)) ? params[5] : 1; // EASE_IN
    
    if (g_AnimManager) {
        int animID = g_AnimManager->fadeOut(playerid, textdraw, true, duration, baseColor, (EasingType)easing);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_SlideFromRight
// native TD_SlideFromRight(playerid, PlayerText:textdraw, Float:toX, Float:toY, duration = 500, easing = EASE_OUT);
static cell AMX_NATIVE_CALL n_TD_SlideFromRight(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    float toX = amx_ctof(params[3]);
    float toY = amx_ctof(params[4]);
    int duration = (params[0] >= 5 * sizeof(cell)) ? params[5] : 500;
    int easing = (params[0] >= 6 * sizeof(cell)) ? params[6] : 2; // EASE_OUT
    
    if (g_AnimManager) {
        int animID = g_AnimManager->slideFromRight(playerid, textdraw, true, toX, toY, duration, (EasingType)easing);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_SlideFromLeft
static cell AMX_NATIVE_CALL n_TD_SlideFromLeft(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    float toX = amx_ctof(params[3]);
    float toY = amx_ctof(params[4]);
    int duration = (params[0] >= 5 * sizeof(cell)) ? params[5] : 500;
    int easing = (params[0] >= 6 * sizeof(cell)) ? params[6] : 2;
    
    if (g_AnimManager) {
        int animID = g_AnimManager->slideFromLeft(playerid, textdraw, true, toX, toY, duration, (EasingType)easing);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_SlideFromTop
static cell AMX_NATIVE_CALL n_TD_SlideFromTop(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    float toX = amx_ctof(params[3]);
    float toY = amx_ctof(params[4]);
    int duration = (params[0] >= 5 * sizeof(cell)) ? params[5] : 500;
    int easing = (params[0] >= 6 * sizeof(cell)) ? params[6] : 2;
    
    if (g_AnimManager) {
        int animID = g_AnimManager->slideFromTop(playerid, textdraw, true, toX, toY, duration, (EasingType)easing);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_SlideFromBottom
static cell AMX_NATIVE_CALL n_TD_SlideFromBottom(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    float toX = amx_ctof(params[3]);
    float toY = amx_ctof(params[4]);
    int duration = (params[0] >= 5 * sizeof(cell)) ? params[5] : 500;
    int easing = (params[0] >= 6 * sizeof(cell)) ? params[6] : 2;
    
    if (g_AnimManager) {
        int animID = g_AnimManager->slideFromBottom(playerid, textdraw, true, toX, toY, duration, (EasingType)easing);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_Pulse
// native TD_Pulse(playerid, PlayerText:textdraw, duration = 1000, pulseCount = 2, baseColor = 0xFFFFFFFF);
static cell AMX_NATIVE_CALL n_TD_Pulse(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    int duration = (params[0] >= 3 * sizeof(cell)) ? params[3] : 1000;
    int pulseCount = (params[0] >= 4 * sizeof(cell)) ? params[4] : 2;
    int baseColor = (params[0] >= 5 * sizeof(cell)) ? params[5] : 0xFFFFFFFF;
    
    if (g_AnimManager) {
        int animID = g_AnimManager->pulse(playerid, textdraw, true, duration, pulseCount, baseColor);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_Blink
// native TD_Blink(playerid, PlayerText:textdraw, duration = 1000, blinkCount = 3);
static cell AMX_NATIVE_CALL n_TD_Blink(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    int duration = (params[0] >= 3 * sizeof(cell)) ? params[3] : 1000;
    int blinkCount = (params[0] >= 4 * sizeof(cell)) ? params[4] : 3;
    
    if (g_AnimManager) {
        int animID = g_AnimManager->blink(playerid, textdraw, true, duration, blinkCount);
        return animID;
    }
    
    return -1;
}

// AMX Native: TD_Stop
// native TD_Stop(playerid, PlayerText:textdraw);
static cell AMX_NATIVE_CALL n_TD_Stop(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    
    if (g_AnimManager) {
        // Find and stop animation for this textdraw
        // Implementation would search through active animations
        return 1;
    }
    
    return 0;
}

// AMX Native: TD_StopAll
// native TD_StopAll(playerid);
static cell AMX_NATIVE_CALL n_TD_StopAll(AMX* amx, cell* params) {
    int playerid = params[1];
    
    if (g_AnimManager) {
        int count = g_AnimManager->stopAllAnimations(playerid);
        return count;
    }
    
    return 0;
}

// AMX Native: TD_IsAnimating
// native TD_IsAnimating(playerid, PlayerText:textdraw);
static cell AMX_NATIVE_CALL n_TD_IsAnimating(AMX* amx, cell* params) {
    int playerid = params[1];
    int textdraw = params[2];
    
    if (g_AnimManager) {
        return g_AnimManager->isAnimating(textdraw) ? 1 : 0;
    }
    
    return 0;
}

// Native list
AMX_NATIVE_INFO PluginNatives[] = {
    {"TD_FadeIn", n_TD_FadeIn},
    {"TD_FadeOut", n_TD_FadeOut},
    {"TD_SlideFromRight", n_TD_SlideFromRight},
    {"TD_SlideFromLeft", n_TD_SlideFromLeft},
    {"TD_SlideFromTop", n_TD_SlideFromTop},
    {"TD_SlideFromBottom", n_TD_SlideFromBottom},
    {"TD_Pulse", n_TD_Pulse},
    {"TD_Blink", n_TD_Blink},
    {"TD_Stop", n_TD_Stop},
    {"TD_StopAll", n_TD_StopAll},
    {"TD_IsAnimating", n_TD_IsAnimating},
    {0, 0}
};

// Plugin callbacks
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
    
    logprintf("***********************************************");
    logprintf("*  TD Animation Plugin v1.0.0                *");
    logprintf("*  Smooth textdraw animations for SA-MP      *");
    logprintf("*  Author: Claude                            *");
    logprintf("***********************************************");
    
    // Initialize manager
    g_AnimManager = new TDAnimationManager();
    
    // Start animation thread
    g_Running = true;
    g_AnimThread = std::thread(AnimationUpdateLoop);
    
    logprintf("  Animation thread started (60 FPS)");
    logprintf("  Plugin loaded successfully!");
    
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    logprintf("  Stopping animation thread...");
    
    // Stop animation thread
    g_Running = false;
    if (g_AnimThread.joinable()) {
        g_AnimThread.join();
    }
    
    // Cleanup
    if (g_AnimManager) {
        delete g_AnimManager;
        g_AnimManager = nullptr;
    }
    
    logprintf("  TD Animation Plugin unloaded");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
    return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
    return AMX_ERR_NONE;
}
