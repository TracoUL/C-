#include "ExecutorImpl.hpp"
// #include "Command.hpp"

#include "cmder\CmderFactory.hpp"
#include "cmder\BusOrchestrator.hpp"
#include "cmder\NormalOrchestrator.hpp"
#include "cmder\SportsCarOrchestrator.hpp"
#include "core\Singleton.hpp"

#include <algorithm>
// #include <memory>
// #include <new>
// #include <unordered_map>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept : poseHandler(pose), orchestrator(orchestrator) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
    }

    Executor *Executor::NewExecutor(const Pose &pose, const ExecutorType executorType) noexcept
    {
        CmderOrchestrator *orchestrator = nullptr;
        switch (executorType)
        {
        case ExecutorType::NORMAL:
        {
            orchestrator = new (std::nothrow) NormalOrchestrator();
            break;
        }
        case ExecutorType::SPORTS_CAR:
        {
            orchestrator = new (std::nothrow) SportsCarOrchestrator();
            break;
        }
        case ExecutorType::BUS:
        {
            orchestrator = new (std::nothrow) BusOrchestrator();
            break;
        }
        }

        return new (std::nothrow) ExecutorImpl(pose, orchestrator);
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
                cmder(poseHandler, *orchestrator).DoOperate(poseHandler);
            });
    }

}