#include "ExecutorImpl.hpp"
// #include "Command.hpp"

#include "CmderFactory.hpp"
#include "Singleton.hpp"

#include <algorithm>
// #include <memory>
// #include <new>
// #include <unordered_map>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
    }

    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose);
    }; // 只在C++17下有效

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        // 表驱动
        // std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap;
        // cmderMap.emplace('M', MoveCommand());
        // cmderMap.emplace('L', TurnLeftCommand());
        // cmderMap.emplace('R', TurnRightCommand());
        // cmderMap.emplace('F', FastCommand());

        // const std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap{
        //     {'M', MoveCommand()},
        //     {'L', TurnLeftCommand()},
        //     {'R', TurnRightCommand()},
        //     {'F', FastCommand()},
        //     {'B', ReverseCommand()}};

        // for (const auto cmd : commands)
        // {
        //     const auto it = cmderMap.find(cmd);
        //     if (it != cmderMap.end())
        //     {
        //         it->second(poseHandler);
        //     }
        // }

        const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);

        std::for_each(
            cmders.begin(),
            cmders.end(),
            [this](const Cmder &cmder) noexcept
            {
                cmder(poseHandler);
            });
    }

}