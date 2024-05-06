#pragma once

#include "GameAPI/Game.hpp"

// Enums

enum GameModes {
    MODE_VSAI,
    MODE_2PLAYER,
};

// Global Variables

// forward declare
struct GlobalVariables;

extern GlobalVariables *globals;

struct GlobalVariables {
    struct Constructor {
        Constructor()
        {
#if RETRO_REV0U
            RegisterGlobals((void **)&globals, sizeof(GlobalVariables), &GlobalVariables::Init);
#else
            RegisterGlobals((void **)&globals, sizeof(GlobalVariables));
#endif
        }
    };

    static Constructor c;

#if RETRO_REV0U
    static void Init(void *g);
#endif

    // Global Variables
    int32 gameMode;
};

// Game Helpers

namespace RSDK
{

template <typename R> struct Action {

    R (Action::*action)();

    inline void Init() { action = nullptr; }

    template <typename T> inline bool Set(R (T::*action)())
    {
        // converts from T:: -> Action:: without the compiler interfering :]
        union {
            R (T::*in)();
            R (Action::*out)();
        };
        in = action;

        this->action = out;
        return true;
    }

    inline bool Set(R (*action)())
    {
        // converts from T:: -> Action:: without the compiler interfering :]
        union {
            R (*in)();
            R (Action::*out)();
        };
        in = action;

        this->action = out;
        return true;
    }

    template <typename T> inline R SetAndRun(R (T::*action)(), void *self = nullptr)
    {
        bool applied = Set(action);

        if (applied)
            return Run(self);

        return R();
    }

    template <typename T> inline R SetAndRun(R (*action)(), void *self = nullptr)
    {
        bool applied = Set(action);

        if (applied)
            return Run(self);

        return R();
    }

    inline R Run(void *self)
    {
        if (action) {
            return (((Action *)self)->*action)();
        }

        return R();
    }

    template <typename T> inline bool Matches(void *other)
    {
        // converts from Action:: -> void (*)() without the compiler interfering :]
        union {
            R *in;
            R (Action::*out)();
        };
        in = other;

        return action == out;
    }

    template <typename T> inline bool Matches(R (T::*other)()) { return action == (R(Action::*)())other; }

    inline bool Matches(Action *other)
    {
        if (other == nullptr)
            return action == nullptr;
        else
            return action == other->action;
    }

    inline void Copy(Action *other)
    {
        if (other == nullptr)
            this->action = nullptr;
        else
            this->action = other->action;
    }

    // Equals
    inline void operator=(const Action &rhs) { this->Copy((Action *)&rhs); }

    // Conditionals
    inline bool operator==(const Action &rhs) { return this->Matches((Action *)&rhs); }
    inline bool operator!=(const Action &rhs) { return !(*this == rhs); }
};

} // namespace RSDK
