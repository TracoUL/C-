#pragma once

#include "NormalOrchestrator.hpp"

namespace adas
{

    class SportsCarOrchestrator : public NormalOrchestrator
    {
    public:
        ActionGroup Move(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;

            if (poseHandler.IsReverse())
            {
                if (poseHandler.IsFast())
                {
                    return ActionGroup({ActionType::BACKWARD_1_STEP_ACTION, ActionType::BACKWARD_1_STEP_ACTION, ActionType::BACKWARD_1_STEP_ACTION, ActionType::BACKWARD_1_STEP_ACTION});
                }
                else
                {
                    return ActionGroup({ActionType::BACKWARD_1_STEP_ACTION, ActionType::BACKWARD_1_STEP_ACTION});
                }
            }
            else
            {
                if (poseHandler.IsFast())
                {
                    return ActionGroup({ActionType::FORWARD_1_STEP_ACTION, ActionType::FORWARD_1_STEP_ACTION, ActionType::FORWARD_1_STEP_ACTION, ActionType::FORWARD_1_STEP_ACTION});
                }
                else
                {
                    return ActionGroup({ActionType::FORWARD_1_STEP_ACTION, ActionType::FORWARD_1_STEP_ACTION});
                }
            }

            return actionGroup;
        }

        ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);

            if (poseHandler.IsReverse())
            {
                actionGroup += ActionGroup({ActionType::TURNRIGHT_ACTION, ActionType::BACKWARD_1_STEP_ACTION});
            }
            else
            {
                actionGroup += ActionGroup({ActionType::TURNLEFT_ACTION, ActionType::FORWARD_1_STEP_ACTION});
            }

            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);

            if (poseHandler.IsReverse())
            {
                actionGroup += ActionGroup({ActionType::TURNLEFT_ACTION, ActionType::BACKWARD_1_STEP_ACTION});
            }
            else
            {
                actionGroup += ActionGroup({ActionType::TURNRIGHT_ACTION, ActionType::FORWARD_1_STEP_ACTION});
            }

            return actionGroup;
        }

        // 其他成员函数和属性
    };

} // namespace adas