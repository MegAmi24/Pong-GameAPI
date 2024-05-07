// ---------------------------------------------------------------------
// RSDK Project: Pong GameAPI
// Object Description: PongGame Object
// Object Author: MegAmi
// ---------------------------------------------------------------------

#include "PongGame.hpp"
#include "Ball.hpp"

using namespace RSDK;

namespace GameLogic
{
RSDK_REGISTER_OBJECT(PongGame);

void PongGame::Update(void)
{
    if (sceneInfo->state == ENGINESTATE_FROZEN) {
        for (int8 i = Input::CONT_P1; i <= Input::CONT_P2; i++) {
            ControllerState *controller = &controllerInfo[i];
            Paddle *player1             = RSDK_GET_ENTITY(SLOT_PLAYER1, Paddle);
            Paddle *player2             = RSDK_GET_ENTITY(SLOT_PLAYER2, Paddle);

            if (player1->score >= PONGGAME_WINSCORE || player2->score >= PONGGAME_WINSCORE) {
                if (controller->keyStart.press || (API::GetConfirmButtonFlip() ? controller->keyB.press : controller->keyA.press)) {
                    player1->score = 0;
                    player2->score = 0;
                    ResetField(nullptr);
                    Stage::SetEngineState(ENGINESTATE_REGULAR);
                }
                else if (API::GetConfirmButtonFlip() ? controller->keyA.press : controller->keyB.press)
                    API::ExitGame();
            }
            else if (controller->keyStart.press)
                Stage::SetEngineState(ENGINESTATE_REGULAR);
        }
    }
}

void PongGame::LateUpdate(void) {}
void PongGame::StaticUpdate(void) {}

void PongGame::Draw(void)
{
    if (sceneInfo->state == ENGINESTATE_FROZEN) {
        RSDK::Vector2 position;
        position.x = TO_FIXED(screenInfo->center.x);
        position.y = TO_FIXED(screenInfo->center.y);
        this->animator.DrawSprite(&position, true);
    }
}

void PongGame::Create(void *data)
{
    if (!sceneInfo->inEditor) {
        this->active        = ACTIVE_ALWAYS;
        this->visible       = true;
        this->drawGroup     = 2;
        this->animator.SetAnimation(sVars->aniFrames, 1, true, 0);
    }
}

void PongGame::StageLoad(void)
{
    // Copy PongGame to slot 4
    foreach_all(PongGame, spawn)
    {
        PongGame *pongGame = RSDK_GET_ENTITY(SLOT_PONGGAME, PongGame);
        spawn->Copy(pongGame, true);
    }

    sVars->aniFrames.Load("Pong/HUD.bin", SCOPE_STAGE);
    sVars->roundStarted = false;
}

void PongGame::HandleGoal(Paddle *winner)
{
    winner->score++;
    if (winner->score >= PONGGAME_WINSCORE) {
        RSDK_GET_ENTITY(SLOT_PONGGAME, PongGame)->animator.frameID = winner->Slot() + 1;
        Stage::SetEngineState(ENGINESTATE_FROZEN);
    }
    else
        ResetField(winner);
}

void PongGame::ResetField(Paddle *winner)
{
    sVars->roundStarted = false;

    foreach_all(Paddle, paddle) {
        paddle->position = paddle->originPos;
        paddle->up       = false;
        paddle->down     = false;
        if (paddle->isAI)
            paddle->aiTimer = 0;
    }

    Ball *ball       = RSDK_GET_ENTITY(SLOT_BALL, Ball);
    ball->position.x = TO_FIXED(screenInfo->center.x);
    ball->position.y = TO_FIXED(screenInfo->center.y);

    bool32 flipVel = false;
    if (winner)
        flipVel = winner->playerID == SLOT_PLAYER1;
    else
        flipVel = Math::Rand(0, 1);
    ball->velocity.x = TO_FIXED(BALL_MOVESPEED * (flipVel ? -1 : 1));
    ball->velocity.y = TO_FIXED(BALL_MOVESPEED * (Math::Rand(0, 1) ? -1 : 1));
}

#if GAME_INCLUDE_EDITOR
void PongGame::EditorDraw(void) {}

void PongGame::EditorLoad(void) {}
#endif

#if RETRO_REV0U
void PongGame::StaticLoad(Static *sVars) { RSDK_INIT_STATIC_VARS(PongGame); }
#endif

void PongGame::Serialize(void) {}

} // namespace GameLogic
