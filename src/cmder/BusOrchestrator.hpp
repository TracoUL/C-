#pragma once

#include "NormalOrchestrator.hpp"

namespace adas
{

    class BusOrchestrator : public NormalOrchestrator
    {
    public:
        ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);

            if (poseHandler.IsReverse())
            {
                actionGroup += ActionGroup({ActionType::BACKWARD_1_STEP_ACTION, ActionType::TURNRIGHT_ACTION});
            }
            else
            {
                actionGroup += ActionGroup({ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION});
            }

            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);

            if (poseHandler.IsReverse())
            {
                actionGroup += ActionGroup({ActionType::BACKWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION});
            }
            else
            {
                actionGroup += ActionGroup({ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNRIGHT_ACTION});
            }

            return actionGroup;
        }

        // 其他成员函数和属性
    };

} // namespace adas