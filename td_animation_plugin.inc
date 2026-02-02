/*
 * TD Animation Plugin - Pawn Include
 * 
 * Super simple API for smooth textdraw animations
 * 
 * Author: Claude
 * Version: 1.0.0
 */

#if defined _td_animation_plugin_included
    #endinput
#endif
#define _td_animation_plugin_included

// ========== EASING TYPES ==========
#define EASE_LINEAR     0
#define EASE_IN         1
#define EASE_OUT        2
#define EASE_INOUT      3
#define EASE_BOUNCE     4
#define EASE_ELASTIC    5
#define EASE_BACK       6
#define EASE_CUBIC      7

// ========== NATIVE FUNCTIONS ==========

/**
 * Fade In - Muncul dari transparent
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @param duration - Duration in milliseconds (default: 300)
 * @param baseColor - Base color of textdraw (default: white)
 * @param easing - Easing type (default: EASE_OUT)
 * @return Animation ID
 */
native TD_FadeIn(playerid, PlayerText:textdraw, duration = 300, baseColor = 0xFFFFFFFF, easing = EASE_OUT);

/**
 * Fade Out - Hilang ke transparent
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @param duration - Duration in milliseconds (default: 300)
 * @param baseColor - Base color of textdraw (default: white)
 * @param easing - Easing type (default: EASE_IN)
 * @return Animation ID
 */
native TD_FadeOut(playerid, PlayerText:textdraw, duration = 300, baseColor = 0xFFFFFFFF, easing = EASE_IN);

/**
 * Slide From Right - Masuk dari kanan layar
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @param Float:toX - Target X position
 * @param Float:toY - Target Y position
 * @param duration - Duration in milliseconds (default: 500)
 * @param easing - Easing type (default: EASE_OUT)
 * @return Animation ID
 */
native TD_SlideFromRight(playerid, PlayerText:textdraw, Float:toX, Float:toY, duration = 500, easing = EASE_OUT);

/**
 * Slide From Left - Masuk dari kiri layar
 */
native TD_SlideFromLeft(playerid, PlayerText:textdraw, Float:toX, Float:toY, duration = 500, easing = EASE_OUT);

/**
 * Slide From Top - Masuk dari atas layar
 */
native TD_SlideFromTop(playerid, PlayerText:textdraw, Float:toX, Float:toY, duration = 500, easing = EASE_OUT);

/**
 * Slide From Bottom - Masuk dari bawah layar
 */
native TD_SlideFromBottom(playerid, PlayerText:textdraw, Float:toX, Float:toY, duration = 500, easing = EASE_OUT);

/**
 * Pulse - Denyut/breathing effect
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @param duration - Total duration in milliseconds (default: 1000)
 * @param pulseCount - Number of pulses (default: 2)
 * @param baseColor - Base color (default: white)
 * @return Animation ID
 */
native TD_Pulse(playerid, PlayerText:textdraw, duration = 1000, pulseCount = 2, baseColor = 0xFFFFFFFF);

/**
 * Blink - Kedip-kedip (show/hide)
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @param duration - Total duration in milliseconds (default: 1000)
 * @param blinkCount - Number of blinks (default: 3)
 * @return Animation ID
 */
native TD_Blink(playerid, PlayerText:textdraw, duration = 1000, blinkCount = 3);

/**
 * Stop - Stop animation untuk textdraw tertentu
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @return 1 if stopped, 0 if not found
 */
native TD_Stop(playerid, PlayerText:textdraw);

/**
 * Stop All - Stop semua animasi untuk player
 * 
 * @param playerid - Player ID
 * @return Number of animations stopped
 */
native TD_StopAll(playerid);

/**
 * Is Animating - Check apakah textdraw sedang animating
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @return 1 if animating, 0 if not
 */
native TD_IsAnimating(playerid, PlayerText:textdraw);

// ========== HELPER FUNCTIONS ==========

/**
 * Cleanup - Call in OnPlayerDisconnect
 */
stock TD_OnPlayerDisconnect(playerid)
{
    TD_StopAll(playerid);
    return 1;
}

// ========== CALLBACK ==========

/**
 * Called when animation finishes
 * 
 * @param playerid - Player ID
 * @param textdraw - PlayerTextdraw ID
 * @param animID - Animation ID
 */
forward OnTDAnimationFinish(playerid, PlayerText:textdraw, animID);
