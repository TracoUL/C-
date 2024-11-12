#pragma once

#include "CmderOrchestrator.hpp"

namespace adas
{

    class NormalOrchestrator : public CmderOrchestrator
    {
    public:
        ActionGroup Move(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);
            actionGroup.PushAction(GetStepAction(poseHandler));
            return actionGroup;
        }

        ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);

            const auto action2 = poseHandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION;

            actionGroup.PushAction(action2);

            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(poseHandler);

            const auto action2 = poseHandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION;

            actionGroup.PushAction(action2);

            return actionGroup;
        }

        ActionGroup TurnRound(const PoseHandler &poseHandler) const noexcept override
        {
            if (poseHandler.IsReverse())
            {
                return ActionGroup();
            }
            else
            {
                if (poseHandler.IsFast())
                {
                    return ActionGroup({ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION, ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION});
                }
                else
                {
                    return ActionGroup({ActionType::TURNLEFT_ACTION, ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION});
                }
            }
        }

    protected:
        ActionType GetStepAction(const PoseHandler &poseHandler) const noexcept
        {
            return poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        }

        ActionGroup OnFast(const PoseHandler &poseHandler) const noexcept
        {
            if (poseHandler.IsFast())
            {
                return ActionGroup({GetStepAction(poseHandler)});
            }
            return ActionGroup();
        }
    };

} // namespace adas