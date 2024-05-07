#pragma once

#include "PongGameAPI.hpp"
#include "Paddle.hpp"

#define PONGGAME_WINSCORE (5)

namespace GameLogic
{

struct PongGame : RSDK::GameObject::Entity {

    // ==============================
    // ENUMS
    // ==============================

    // ==============================
    // STRUCTS
    // ==============================

    // ==============================
    // STATIC VARS
    // ==============================

    struct Static : RSDK::GameObject::Static {
        bool32 roundStarted;
        RSDK::SpriteAnimation aniFrames;
    };

    // ==============================
    // INSTANCE VARS
    // ==============================
    RSDK::Animator animator;

    // ==============================
    // EVENTS
    // ==============================

    void Create(void *data);
    void Draw();
    void Update();
    void LateUpdate();

    static void StaticUpdate();
    static void StageLoad();
#if RETRO_REV0U
    static void StaticLoad(Static *sVars);
#endif
    static void Serialize();

#if GAME_INCLUDE_EDITOR
    static void EditorLoad();
    void EditorDraw();
#endif

    // ==============================
    // FUNCTIONS
    // ==============================

    static void HandleGoal(Paddle *winner);
    static void ResetField(Paddle *winner);

    // ==============================
    // DECLARATION
    // ==============================

    RSDK_DECLARE(PongGame);
};
} // namespace GameLogic
