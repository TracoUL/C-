#pragma once
#include "ExecutorImpl.hpp"
#include "core\PoseHandler.hpp"
#include "CmderOrchestrator.hpp"

#include <functional>

namespace adas
{
    class MoveCommand final //: public ICommand // 定义一个嵌套类MoveCommand，完成Move动作（M指令）
    {
    public:
        ActionGroup operator()(const PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.Move(poseHandler);
        }
    };

    class TurnLeftCommand final // : public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnLeft(poseHandler);
        }
    };

    class TurnRightCommand final //: public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            return orchestrator.TurnRight(poseHandler);
        }
    };

    class FastCommand final //: public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_FAST_ACTION);

            return actionGroup;
        }
    };

    class ReverseCommand final
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
        {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);

            return actionGroup;
        }
    };

    class TurnRoundCommand final
    {
    public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
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
    };
}
