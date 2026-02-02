/*
 * TD Animation Plugin
 * Smooth textdraw animations for SA-MP
 * 
 * Author: Claude
 * Version: 1.0.0
 * License: MIT
 */

#ifndef TDANIMATION_H
#define TDANIMATION_H

#include <map>
#include <vector>
#include <string>
#include <chrono>

// Animation types
enum class AnimationType {
    FADE_IN,
    FADE_OUT,
    SLIDE,
    SCALE,
    ROTATE,
    PULSE,
    BLINK,
    BOUNCE
};

// Easing types
enum class EasingType {
    LINEAR,
    EASE_IN,
    EASE_OUT,
    EASE_INOUT,
    BOUNCE,
    ELASTIC,
    BACK,
    CUBIC
};

// Textdraw data structure
struct TextdrawData {
    int playerID;
    int textdrawID;
    bool isPlayerTextdraw;
    
    // Position
    float posX;
    float posY;
    
    // Size
    float sizeX;
    float sizeY;
    
    // Color & styling
    int color;
    int boxColor;
    int backgroundColor;
    int font;
    int outline;
    int shadow;
    int alignment;
    int proportional;
    int selectable;
    bool useBox;
    
    // Text
    std::string text;
    
    // Letter size
    float letterSizeX;
    float letterSizeY;
    
    // Original values (for reset)
    float originalPosX;
    float originalPosY;
    int originalColor;
};

// Animation state
struct AnimationState {
    int id;
    int playerID;
    int textdrawID;
    bool isPlayerTextdraw;
    
    AnimationType type;
    EasingType easing;
    
    // Timing
    std::chrono::steady_clock::time_point startTime;
    int duration; // milliseconds
    
    // Position animation
    float startX, startY;
    float endX, endY;
    
    // Color animation
    int startAlpha, endAlpha;
    int baseColor;
    
    // Scale animation
    float startScaleX, startScaleY;
    float endScaleX, endScaleY;
    
    // Pulse/Blink
    int pulseCount;
    bool blinkState;
    
    // Callback
    std::string callback;
    bool hasCallback;
    
    // State
    bool active;
    bool completed;
};

class TDAnimationManager {
private:
    std::map<int, TextdrawData> textdraws;
    std::map<int, AnimationState> animations;
    int nextAnimID;
    int nextTDID;
    
    // Helper functions
    float applyEasing(float t, EasingType easing);
    void updateTextdraw(int tdID, const TextdrawData& data);
    int getElapsedMS(std::chrono::steady_clock::time_point start);
    
public:
    TDAnimationManager();
    ~TDAnimationManager();
    
    // Textdraw management
    int registerTextdraw(int playerID, int tdID, bool isPlayerTD, const TextdrawData& data);
    void unregisterTextdraw(int tdID);
    TextdrawData* getTextdraw(int tdID);
    
    // Animation functions
    int startAnimation(int playerID, int textdrawID, bool isPlayerTD, AnimationType type, 
                      int duration, EasingType easing);
    int fadeIn(int playerID, int textdrawID, bool isPlayerTD, int duration, int baseColor, EasingType easing);
    int fadeOut(int playerID, int textdrawID, bool isPlayerTD, int duration, int baseColor, EasingType easing);
    int slideFromRight(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing);
    int slideFromLeft(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing);
    int slideFromTop(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing);
    int slideFromBottom(int playerID, int textdrawID, bool isPlayerTD, float toX, float toY, int duration, EasingType easing);
    int pulse(int playerID, int textdrawID, bool isPlayerTD, int duration, int pulseCount, int baseColor);
    int blink(int playerID, int textdrawID, bool isPlayerTD, int duration, int blinkCount);
    
    // Control functions
    bool stopAnimation(int animID);
    int stopAllAnimations(int playerID);
    bool isAnimating(int textdrawID);
    float getProgress(int animID);
    
    // Update (called every frame)
    void update();
    
    // Cleanup
    void cleanupPlayer(int playerID);
};

#endif // TDANIMATION_H
