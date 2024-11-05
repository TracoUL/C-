#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <memory>
#include <new>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
    }

    // void ExecutorImpl::Move() noexcept
    // {
    //     if (pose.heading == 'E')
    //     {
    //         ++pose.x;
    //     }
    //     else if (pose.heading == 'W')
    //     {
    //         --pose.x;
    //     }
    //     else if (pose.heading == 'N')
    //     {
    //         ++pose.y;
    //     }
    //     else if (pose.heading == 'S')
    //     {
    //         --pose.y;
    //     }
    // }

    // void ExecutorImpl::TurnLeft() noexcept
    // {
    //     if (pose.heading == 'E')
    //         pose.heading = 'N';
    //     else if (pose.heading == 'W')
    //         pose.heading = 'S';
    //     else if (pose.heading == 'N')
    //         pose.heading = 'W';
    //     else if (pose.heading == 'S')
    //         pose.heading = 'E';
    // }

    // void ExecutorImpl::TurnRight() noexcept
    // {
    //     if (pose.heading == 'E')
    //         pose.heading = 'S';
    //     else if (pose.heading == 'W')
    //         pose.heading = 'N';
    //     else if (pose.heading == 'N')
    //         pose.heading = 'E';
    //     else if (pose.heading == 'S')
    //         pose.heading = 'W';
    // }

    // void ExecutorImpl::Fast(void) noexcept
    // {
    //     fast = !fast;
    // }

    // bool ExecutorImpl::IsFast(void) const noexcept
    // {
    //     return fast;
    // }

    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose);
    }; // 只在C++17下有效

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        for (const auto cmd : commands)
        {
            std::unique_ptr<ICommand> cmder;
            // 如果是M指令
            if (cmd == 'M')
            {
                cmder = std::make_unique<MoveCommand>();
            }
            else if (cmd == 'L')
            {
                cmder = std::make_unique<TurnLeftCommand>();
            }
            else if (cmd == 'R')
            {
                cmder = std::make_unique<TurnRightCommand>();
            }
            else if (cmd == 'F')
            {
                cmder = std::make_unique<FastCommand>();
            }

            if (cmder)
                cmder->DoOperate(poseHandler);
        }
    }

}