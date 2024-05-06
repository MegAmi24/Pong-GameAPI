// ---------------------------------------------------------------------
// RSDK Project: Pong GameAPI
// Object Description: Paddle Object
// Object Author: MegAmi
// ---------------------------------------------------------------------

#include "Paddle.hpp"

using namespace RSDK;

namespace GameLogic
{
RSDK_REGISTER_OBJECT(Paddle);

void Paddle::Update(void) {}
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
        this->active       = ACTIVE_ALWAYS;
        this->visible      = true;
        this->drawGroup    = 2;
        this->playerID     = this->Slot();
        this->controllerID = this->playerID + 1;
        if (this->playerID == 0) {
            this->isAI        = false;
            this->paddleColor = 0xFF0000;
        }
        else {
            this->isAI        = globals->gameMode == MODE_VSAI;
            this->paddleColor = 0x0000FF;
        }
        this->stateInput.Set(this->isAI ? &Paddle::Input_AI : &Paddle::Input_Player);
        this->hitbox.left   = -(PADDLE_WIDTH / 2);
        this->hitbox.top    = -(PADDLE_HEIGHT / 2);
        this->hitbox.right  = PADDLE_WIDTH / 2;
        this->hitbox.bottom = PADDLE_HEIGHT / 2;
        this->originPos     = this->position;
    }
}

void Paddle::StageLoad(void)
{
    // Copy Paddle objects to the beginning of the entity list
    int32 slotID = 0;
    foreach_all(Paddle, spawn)
    {
        Paddle *paddle = RSDK_GET_ENTITY(slotID, Paddle);
        spawn->Copy(paddle, true);
        slotID++;
    }
}

bool32 Paddle::CheckBallTouch(Paddle *paddle, void *ball, RSDK::Hitbox *ballHitbox) {}

void Paddle::Input_Player(void) {}
void Paddle::Input_AI(void) {}

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
