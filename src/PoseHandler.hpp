#pragma once

#include "Executor.hpp"
#include "Direction.hpp"

namespace adas
{

    class PoseHandler final
    {
    public:
        PoseHandler(const Pose &pose) noexcept;
        PoseHandler(const PoseHandler &) = delete;            // 禁止拷贝构造
        PoseHandler &operator=(const PoseHandler &) = delete; // 禁止拷贝赋值

    public:
        void Forward(void) noexcept;   // 向前移动
        void Backward(void) noexcept;  // 向后移动

        void TurnLeft(void) noexcept;  // 向左转
        void TurnRight(void) noexcept; // 向右转

        void Fast(void) noexcept;      // 切换模式
        void Reverse(void) noexcept;

        bool IsFast(void) const noexcept; // 是否处于快速模式
        bool IsReverse(void) const noexcept;

        Pose Query(void) const noexcept;  // 查询当前位置

    private:
        Point point;
        const Direction *facing;
        bool fast{false}; // 是否处于快速状态
        bool reverse{false};
    };

}
