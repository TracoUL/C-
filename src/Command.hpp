#pragma once
#include "ExecutorImpl.hpp"

namespace adas
{
    class ICommand
    {
    public:
        // 请在这里给出析构函数和纯虚函数DoOperate的声明
        virtual void DoOperate(ExecutorImpl &executor) const noexcept = 0;
        virtual ~ICommand() = default;
    };

    class MoveCommand final : public ICommand // 定义一个嵌套类MoveCommand，完成Move动作（M指令）
    {
    public:
        // 执行Move动作，需要委托ExecutorImp&执行器来完成动作
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.Move();
        }
    };

    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnLeft();
        }
    };

    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnRight();
        }
    };

    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl &executor) const noexcept override
        {
            executor.Fast();
        }
    };
}
