#pragma once
#include "ExecutorImpl.hpp"
#include "PoseHandler.hpp"

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

        void operator()(PoseHandler &poseHandler) const noexcept
        {
            if (poseHandler.IsFast())
            {
                poseHandler.Move();
            }
            poseHandler.Move();
        }
    };

    class TurnLeftCommand final// : public ICommand
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

        void operator()(PoseHandler &poseHandler) const noexcept
        {
            if (poseHandler.IsFast())
            {
                poseHandler.Move();
            }
            poseHandler.TurnLeft();
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

        void operator()(PoseHandler &poseHandler) const noexcept
        {
            if (poseHandler.IsFast())
            {
                poseHandler.Move();
            }
            poseHandler.TurnRight();
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

        void operator()(PoseHandler &poseHandler) const noexcept
        {
            poseHandler.Fast();
        }
    };
}
