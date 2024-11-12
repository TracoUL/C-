#pragma once

#include "Executor.hpp"
#include "core\PoseHandler.hpp"
#include <string>

namespace adas
{
    /*
     * Executor的具体实现
     */
    class ExecutorImpl final : public Executor
    {
    public:
        // 构造函数
        explicit ExecutorImpl(const Pose &pose) noexcept;
        // 默认析构函数
        ~ExecutorImpl() noexcept = default;

        // 不能拷贝
        ExecutorImpl(const ExecutorImpl &) = delete;
        // 不能赋值
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

    public:
        // 查询当前汽车姿态，是父类抽象方法Query的具体实现
        Pose Query(void) const noexcept override;
        // override关键字用于明确地表示一个函数是基类的虚函数的重写（override）。它不会改变函数行为，但如果函数签名不匹配基类的虚函数，将导致编译错误。这有助于防止拼写错误或参数不匹配等问题。

        // 第二阶段新增的函数，执行字符串表示的指令
        void Execute(const std::string &commands) noexcept override;

        // 以上函数在cpp中实现
    private:
        PoseHandler poseHandler; // 状态管理类
    };
}
