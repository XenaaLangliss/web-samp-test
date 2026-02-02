/*
 * TD Animation Plugin - Implementation
 * 
 * Author: Claude
 * Version: 1.0.0
 */

#include "TDAnimation.h"
#include <cmath>
#include <algorithm>

TDAnimationManager::TDAnimationManager() : nextAnimID(0), nextTDID(0) {
}

TDAnimationManager::~TDAnimationManager() {
    textdraws.clear();
    animations.clear();
}

// Easing functions
float TDAnimationManager::applyEasing(float t, EasingType easing) {
    switch (easing) {
        case EasingType::LINEAR:
            return t;
            
        case EasingType::EASE_IN:
            return t * t;
            
        case EasingType::EASE_OUT:
            return t * (2.0f - t);
            
        case EasingType::EASE_INOUT:
            if (t < 0.5f)
                return 2.0f * t * t;
            return -1.0f + (4.0f - 2.0f * t) * t;
            
        case EasingType::BOUNCE: {
            if (t < (1.0f / 2.75f)) {
                return 7.5625f * t * t;
            } else if (t < (2.0f / 2.75f)) {
                t -= (1.5f / 2.75f);
                return 7.5625f * t * t + 0.75f;
            } else if (t < (2.5f / 2.75f)) {
                t -= (2.25f / 2.75f);
                return 7.5625f * t * t + 0.9375f;
            } else {
                t -= (2.625f / 2.75f);
                return 7.5625f * t * t + 0.984375f;
            }
        }
        
        case EasingType::ELASTIC: {
            if (t == 0.0f || t == 1.0f) return t;
            float p = 0.3f;
            return std::pow(2.0f, -10.0f * t) * std::sin((t - p / 4.0f) * (2.0f * 3.14159f) / p) + 1.0f;
        }
        
        case EasingType::BACK: {
            float s = 1.70158f;
            return t * t * ((s + 1.0f) * t - s);
        }
        
        case EasingType::CUBIC:
            return t * t * t;
            
        default:
            return t;
    }
}

int TDAnimationManager::getElapsedMS(std::chrono::steady_clock::time_point start) {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}

// Textdraw management
int TDAnimationManager::registerTextdraw(int playerID, int tdID, bool isPlayerTD, const TextdrawData& data) {
    int internalID = nextTDID++;
    TextdrawData td = data;
    td.playerID = playerID;
    td.textdrawID = tdID;
    td.isPlayerTextdraw = isPlayerTD;
    
    // Store original values
    td.originalPosX = data.posX;
    td.originalPosY = data.posY;
    td.originalColor = data.color;
    
    textdraws[internalID] = td;
    return internalID;
}

void TDAnimationManager::unregisterTextdraw(int tdID) {
    textdraws.erase(tdID);
}

TextdrawData* TDAnimationManager::getTextdraw(int tdID) {
    auto it = textdraws.find(tdID);
    if (it != textdraws.end()) {
        return &it->second;
    }
    return nullptr;
}

// Fade In
int TDAnimationManager::fadeIn(int playerID, int textdrawID, bool isPlayerTD, int duration, int baseColor, EasingType easing) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::FADE_IN;
    anim.easing = easing;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startAlpha = 0;
    anim.endAlpha = 255;
    anim.baseColor = baseColor;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Fade Out
int TDAnimationManager::fadeOut(int playerID, int textdrawID, bool isPlayerTD, int duration, int baseColor, EasingType easing) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::FADE_OUT;
    anim.easing = easing;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startAlpha = 255;
    anim.endAlpha = 0;
    anim.baseColor = baseColor;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Slide From Right
int TDAnimationManager::slideFromRight(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::SLIDE;
    anim.easing = easing;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startX = 700.0f; // Off-screen right
    anim.startY = toY;
    anim.endX = toX;
    anim.endY = toY;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Slide From Left
int TDAnimationManager::slideFromLeft(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::SLIDE;
    anim.easing = easing;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startX = -100.0f; // Off-screen left
    anim.startY = toY;
    anim.endX = toX;
    anim.endY = toY;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Slide From Top
int TDAnimationManager::slideFromTop(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::SLIDE;
    anim.easing = easing;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startX = toX;
    anim.startY = -100.0f; // Off-screen top
    anim.endX = toX;
    anim.endY = toY;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Slide From Bottom
int TDAnimationManager::slideFromBottom(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::SLIDE;
    anim.easing = easing;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startX = toX;
    anim.startY = 500.0f; // Off-screen bottom
    anim.endX = toX;
    anim.endY = toY;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Pulse
int TDAnimationManager::pulse(int playerID, int textdrawID, bool isPlayerTD, int duration, int pulseCount, int baseColor) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::PULSE;
    anim.easing = EasingType::LINEAR;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.startAlpha = 100;
    anim.endAlpha = 255;
    anim.baseColor = baseColor;
    anim.pulseCount = pulseCount;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Blink
int TDAnimationManager::blink(int playerID, int textdrawID, bool isPlayerTD, int duration, int blinkCount) {
    AnimationState anim;
    anim.id = nextAnimID++;
    anim.playerID = playerID;
    anim.textdrawID = textdrawID;
    anim.isPlayerTextdraw = isPlayerTD;
    anim.type = AnimationType::BLINK;
    anim.easing = EasingType::LINEAR;
    anim.startTime = std::chrono::steady_clock::now();
    anim.duration = duration;
    anim.pulseCount = blinkCount;
    anim.blinkState = true;
    anim.active = true;
    anim.completed = false;
    anim.hasCallback = false;
    
    animations[anim.id] = anim;
    return anim.id;
}

// Stop animation
bool TDAnimationManager::stopAnimation(int animID) {
    auto it = animations.find(animID);
    if (it != animations.end()) {
        animations.erase(it);
        return true;
    }
    return false;
}

// Stop all animations for player
int TDAnimationManager::stopAllAnimations(int playerID) {
    int count = 0;
    for (auto it = animations.begin(); it != animations.end();) {
        if (it->second.playerID == playerID) {
            it = animations.erase(it);
            count++;
        } else {
            ++it;
        }
    }
    return count;
}

// Check if animating
bool TDAnimationManager::isAnimating(int textdrawID) {
    for (const auto& pair : animations) {
        if (pair.second.textdrawID == textdrawID && pair.second.active) {
            return true;
        }
    }
    return false;
}

// Get progress
float TDAnimationManager::getProgress(int animID) {
    auto it = animations.find(animID);
    if (it != animations.end()) {
        int elapsed = getElapsedMS(it->second.startTime);
        if (it->second.duration <= 0) return 1.0f;
        return std::min(1.0f, (float)elapsed / (float)it->second.duration);
    }
    return 0.0f;
}

// Update (called every frame)
void TDAnimationManager::update() {
    // This will be called from the plugin's main update loop
    // Implementation will interact with SA-MP native functions
    // Which will be done in the main plugin file
}

// Cleanup player
void TDAnimationManager::cleanupPlayer(int playerID) {
    // Remove all textdraws for player
    for (auto it = textdraws.begin(); it != textdraws.end();) {
        if (it->second.playerID == playerID) {
            it = textdraws.erase(it);
        } else {
            ++it;
        }
    }
    
    // Stop all animations for player
    stopAllAnimations(playerID);
}
