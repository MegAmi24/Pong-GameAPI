// ---------------------------------------------------------------------
// RSDK Project: Pong GameAPI
// Object Description: Ball Object
// Object Author: MegAmi
// ---------------------------------------------------------------------

#include "Ball.hpp"
#include "Paddle.hpp"
#include "PongGame.hpp"

using namespace RSDK;

namespace GameLogic
{
RSDK_REGISTER_OBJECT(Ball);

void Ball::Update(void)
{
    if (PongGame::sVars->roundStarted) {
        this->position.x += this->velocity.x;
        this->position.y += this->velocity.y;
    }

    // Handle Paddle collision
    foreach_active(Paddle, paddle)
    {
        switch (this->CheckCollisionBox(&sVars->hitbox, paddle, &Paddle::sVars->hitbox, false))
        {
            default:
            case C_NONE: break;

            case C_LEFT: {
                if (this->velocity.x < 0)
                    this->velocity.x *= -1;
                break;
            }

            case C_RIGHT: {
                if (this->velocity.x > 0)
                    this->velocity.x *= -1;
                break;
            }

            case C_TOP: {
                if (this->velocity.y < 0)
                    this->velocity.y *= -1;
                break;
            }

            case C_BOTTOM: {
                if (this->velocity.y > 0)
                    this->velocity.y *= -1;
                break;
            }
        }
    }

    // Handle Top/Bottom bounds collision
    if (FROM_FIXED(this->position.y) + sVars->hitbox.top < 0) {
        this->position.y = TO_FIXED(sVars->hitbox.bottom);
        this->velocity.y *= -1;
    }
    else if (FROM_FIXED(this->position.y) + sVars->hitbox.bottom > screenInfo->size.y) {
        this->position.y = TO_FIXED(screenInfo->size.y + sVars->hitbox.top);
        this->velocity.y *= -1;
    }

    // Handle goals
    if (FROM_FIXED(this->position.x) + BALL_RADIUS * 2 < 0)
        PongGame::HandleGoal(RSDK_GET_ENTITY(SLOT_PLAYER2, Paddle));
    else if (FROM_FIXED(this->position.x) - BALL_RADIUS * 2 > screenInfo->size.x)
        PongGame::HandleGoal(RSDK_GET_ENTITY(SLOT_PLAYER1, Paddle));
}

void Ball::LateUpdate(void) {}
void Ball::StaticUpdate(void) {}

void Ball::Draw(void) { Graphics::DrawCircle(this->position.x, this->position.y, BALL_RADIUS, 0x00FF00, 0xFF, INK_NONE, false); }

void Ball::Create(void *data)
{
    if (!sceneInfo->inEditor) {
        this->active        = ACTIVE_NORMAL;
        this->visible       = true;
        this->drawGroup     = 2;
        this->position.x    = TO_FIXED(screenInfo->center.x);
        this->position.y    = TO_FIXED(screenInfo->center.y);
        this->velocity.x    = TO_FIXED(BALL_MOVESPEED * (Math::Rand(0, 1) ? -1 : 1));
        this->velocity.y    = TO_FIXED(BALL_MOVESPEED * (Math::Rand(0, 1) ? -1 : 1));
    }
}

void Ball::StageLoad(void)
{
    // Copy Ball to slot 2
    foreach_all(Ball, spawn)
    {
        Ball *ball = RSDK_GET_ENTITY(SLOT_BALL, Ball);
        spawn->Copy(ball, true);
    }

    sVars->hitbox.left   = -(BALL_RADIUS / 2);
    sVars->hitbox.top    = -(BALL_RADIUS / 2);
    sVars->hitbox.right  = BALL_RADIUS / 2;
    sVars->hitbox.bottom = BALL_RADIUS / 2;
}

#if GAME_INCLUDE_EDITOR
void Ball::EditorDraw(void) { Draw(); }

void Ball::EditorLoad(void) {}
#endif

#if RETRO_REV0U
void Ball::StaticLoad(Static *sVars) { RSDK_INIT_STATIC_VARS(Ball); }
#endif

void Ball::Serialize(void) {}

} // namespace GameLogic
