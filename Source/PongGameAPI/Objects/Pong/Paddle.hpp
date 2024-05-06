#pragma once

#include "PongGameAPI.hpp"

#define PADDLE_WIDTH  (16)
#define PADDLE_HEIGHT (64)

#define PADDLE_MOVESPEED (5)

namespace GameLogic
{

struct Paddle : RSDK::GameObject::Entity {

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
        RSDK::Hitbox hitbox;
    };

    // ==============================
    // INSTANCE VARS
    // ==============================
    uint16 playerID;
    int32 controllerID;
    bool32 isAI;
    RSDK::StateMachine<Paddle> stateInput;
    color paddleColor;
    RSDK::Vector2 originPos;
    bool32 up;
    bool32 down;
    int32 aiTimer;

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

    // Input States
    void Input_Player(void);
    void Input_AI(void);

    // ==============================
    // DECLARATION
    // ==============================

    RSDK_DECLARE(Paddle);
};
} // namespace GameLogic
