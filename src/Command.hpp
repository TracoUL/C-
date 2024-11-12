#pragma once
#include "ExecutorImpl.hpp"
#include "PoseHandler.hpp"
#include "ActionGroup.hpp"

#include <functional>

namespace adas
{
    // class ICommand
    // {
    // public:
    //     // 请在这里给出析构函数和纯虚函数DoOperate的声明
    //     virtual void DoOperate(PoseHandler &poseHandler) const noexcept = 0;
    //     virtual ~ICommand() = default;
    // };

    class MoveCommand final //: public ICommand // 定义一个嵌套类MoveCommand，完成Move动作（M指令）
    {
    public:
        // v1
        // 执行Move动作，需要委托ExecutorImp&执行器来完成动作
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.Move();
        // }

        // const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.Move();
        // };

        // v2
        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         if (poseHandler.IsReverse())
        //         {
        //             poseHandler.Backward();
        //         }
        //         else
        //             poseHandler.Forward();
        //     }

        //     if (poseHandler.IsReverse())
        //     {
        //         poseHandler.Backward();
        //     }
        //     else
        //         poseHandler.Forward();
        // };

        // v3
        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            ActionGroup actionGroup;

            const auto action = poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;

            if (poseHandler.IsFast())
            {
                actionGroup.PushAction(action);
            }

            actionGroup.PushAction(action);

            return actionGroup;
        }
    };

    class TurnLeftCommand final // : public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnLeft();
        // }

        // const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnLeft();
        // };

        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         if (poseHandler.IsReverse())
        //         {
        //             poseHandler.Backward();
        //         }
        //         else
        //             poseHandler.Forward();
        //     }

        //     if (poseHandler.IsReverse())
        //     {
        //         poseHandler.TurnRight();
        //     }
        //     else
        //         poseHandler.TurnLeft();
        // }

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            ActionGroup actionGroup;

            const auto action = poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;

            if (poseHandler.IsFast())
            {
                actionGroup.PushAction(action);
            }

            const auto action2 = poseHandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION;

            actionGroup.PushAction(action2);

            return actionGroup;
        }
    };

    class TurnRightCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnRight();
        // }

        // const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnRight();
        // };

        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         if (poseHandler.IsReverse())
        //         {
        //             poseHandler.Backward();
        //         }
        //         else
        //             poseHandler.Forward();
        //     }

        //     if (poseHandler.IsReverse())
        //     {
        //         poseHandler.TurnLeft();
        //     }
        //     else
        //         poseHandler.TurnRight();
        // }

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            ActionGroup actionGroup;

            const auto action = poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;

            if (poseHandler.IsFast())
            {
                actionGroup.PushAction(action);
            }

            const auto action2 = poseHandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION;

            actionGroup.PushAction(action2);

            return actionGroup;
        }
    };

    class FastCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     poseHandler.Fast();
        // }

        // const std::function<void(PoseHandler &poseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     poseHandler.Fast();
        // };

        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     poseHandler.Fast();
        // }

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_FAST_ACTION);

            return actionGroup;
        }
    };

    class ReverseCommand final
    {
    public:
        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     poseHandler.Reverse();
        // }

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);

            return actionGroup;
        }
    };
}
