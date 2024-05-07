// ---------------------------------------------------------------------
// RSDK Project: Pong GameAPI
// Object Description: Paddle Object
// Object Author: MegAmi
// ---------------------------------------------------------------------

#include "Paddle.hpp"
#include "Ball.hpp"
#include "PongGame.hpp"

using namespace RSDK;

namespace GameLogic
{
RSDK_REGISTER_OBJECT(Paddle);

void Paddle::Update(void)
{
    this->stateInput.Run(this);

    if (this->up) {
        this->position.y -= TO_FIXED(PADDLE_MOVESPEED);
        if (FROM_FIXED(this->position.y) + sVars->hitbox.top < 0)
            this->position.y = TO_FIXED(sVars->hitbox.bottom);
    }
    else if (this->down) {
        this->position.y += TO_FIXED(PADDLE_MOVESPEED);
        if (FROM_FIXED(this->position.y) + sVars->hitbox.bottom > screenInfo->size.y)
            this->position.y = TO_FIXED(screenInfo->size.y + sVars->hitbox.top);
    }
}

void Paddle::LateUpdate(void) {}
void Paddle::StaticUpdate(void) {}

void Paddle::Draw(void)
{
    Graphics::DrawRect(FROM_FIXED(this->position.x) - PADDLE_WIDTH / 2, FROM_FIXED(this->position.y) - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT,
                       this->paddleColor, 0xFF, INK_NONE, true);
}

void Paddle::Create(void *data)
{
    if (!sceneInfo->inEditor) {
        this->active       = ACTIVE_NORMAL;
        this->visible      = true;
        this->drawGroup    = 2;
        this->playerID     = this->Slot();
        this->controllerID = this->playerID + 1;
        if (this->playerID == SLOT_PLAYER1) {
            this->isAI        = false;
            this->paddleColor = 0xFF0000;
            this->position.x  = TO_FIXED(72);
        }
        else {
            this->isAI        = globals->gameMode == MODE_VSAI;
            this->paddleColor = 0x0000FF;
            this->position.x  = TO_FIXED(screenInfo->size.x - 72);
        }
        this->position.y = TO_FIXED(screenInfo->center.y);
        this->stateInput.Set(this->isAI ? &Paddle::Input_AI : &Paddle::Input_Player);
        this->originPos = this->position;
        if (this->isAI)
            this->aiTimer = 0;
    }
}

void Paddle::StageLoad(void)
{
    // Copy Paddle objects to the beginning of the entity list
    int32 slotID = SLOT_PLAYER1;
    foreach_all(Paddle, paddle)
    {
        if (slotID < SLOT_PLAYER2 + 1) {
            paddle->Copy(RSDK_GET_ENTITY(slotID, Paddle), true);
            slotID++;
        }
        else
            paddle->Destroy(); // There should only be 2 paddles
    }

    sVars->hitbox.left   = -(PADDLE_WIDTH / 2);
    sVars->hitbox.top    = -(PADDLE_HEIGHT / 2);
    sVars->hitbox.right  = PADDLE_WIDTH / 2;
    sVars->hitbox.bottom = PADDLE_HEIGHT / 2;
}

void Paddle::Input_Player(void)
{
    if (this->controllerID <= Input::CONT_P2) {
        ControllerState *controller = &controllerInfo[this->controllerID];
        AnalogState *stick          = &analogStickInfoL[this->controllerID];

        if (!PongGame::sVars->roundStarted)
            PongGame::sVars->roundStarted |= controller->keyUp.press | controller->keyDown.press | stick->keyUp.press | stick->keyDown.press;
        else {
            this->up   = controller->keyUp.down;
            this->down = controller->keyDown.down;

            this->up |= stick->keyUp.down;
            this->down |= stick->keyDown.down;

            this->up |= stick->vDelta > 0.3;
            this->down |= stick->vDelta < -0.3;

            if (this->up && this->down) {
                this->up   = false;
                this->down = false;
            }
        }

        if (controller->keyStart.press) {
            RSDK_GET_ENTITY(SLOT_PONGGAME, PongGame)->animator.frameID = 0;
            Stage::SetEngineState(ENGINESTATE_FROZEN);
            controller->keyStart.press = false;
        }
    }
}

void Paddle::Input_AI(void)
{
    if (!PongGame::sVars->roundStarted)
        return;

    if (--this->aiTimer <= 0) {
        if (this->up || this->down) {
            this->up   = false;
            this->down = false;
        }
        else {
            Ball *ball = RSDK_GET_ENTITY(SLOT_BALL, Ball);
            bool32 checkPos = this->position.y < ball->position.y;
            if (this->position.y == ball->position.y)
                checkPos = ball->velocity.y > 0;
            if (checkPos)
                this->down = true;
            else
                this->up = true;
        }
        this->aiTimer = Math::Rand(10, 45);
    }
}

#if GAME_INCLUDE_EDITOR
void Paddle::EditorDraw(void)
{
    Graphics::DrawRect(this->position.x - TO_FIXED(PADDLE_WIDTH / 2), this->position.y - TO_FIXED(PADDLE_HEIGHT / 2), PADDLE_WIDTH, PADDLE_HEIGHT,
                       0xFFFFFF, 0xFF, INK_NONE, false);
}

void Paddle::EditorLoad(void) {}
#endif

#if RETRO_REV0U
void Paddle::StaticLoad(Static *sVars) { RSDK_INIT_STATIC_VARS(Paddle); }
#endif

void Paddle::Serialize(void) {}

} // namespace GameLogic
