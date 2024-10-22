#include <gtest/gtest.h>
#include <memory>
// #include <tuple>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
    // 重载Pose的==，用的全局函数，用于比较两个姿态对象是否相同
    // bool operator==(const Pose &lhs, const Pose &rhs)
    // {
    //     return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
    // }

    // 下⾯是⼀个测试⽤例，测试静态⽅法Executor::NewExecutor
    // 测试⽤例1
    TEST(ExecutorTest, should_return_init_pose_when_with_command)
    {
        // given 给定初始条件
        // 测试条件是调用Executor的静态方法NewExecutor 返回⼀个指向Executor对象的智能指针executor，这样我们就不需要去delete了
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); // 给了初始姿势

        // when

        // then
        const Pose target{0, 0, 'E'}; // 构造⼀个姿态对象target，其内容为{0, 0, 'E'}
        // 已构造出来executor对象时的初始姿态是{0, 0, 'E'}，那么executor->Query()返回的Executor对象的姿态必须等于target
        // 所以这里用了断言：executor->Query()的姿态必须等于target，否则测试⽆法通过，说明Executor的实现有问题
        ASSERT_EQ(target, executor->Query()); // ASSERT_EQ内部已经重载了重载函数Pose的==
    }

    // 测试⽤例2
    TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
    {
        // given
        std::unique_ptr<Executor> executor(Executor::NewExecutor()); // 没有给初始姿势

        // when

        // then
        const Pose target{0, 0, 'N'};
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例3 测试测试Execute方法,在朝向为E,起点为(0,0)时去执行M指令是否正确
    TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
    {
        // given给定一个executor,调用executor的Execute方法去执行M指令
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); // 给了初始姿势，当前朝向是E，起点（0,0）
        // when调用executor的Execute方法去执行M指令
        executor->Execute("M");

        // then
        const Pose target({1, 0, 'E'});       // 如果执行M指令正确，新的姿势应该是target：{1，0，'E'}
        ASSERT_EQ(target, executor->Query()); // 当M指令执行完，executor->Query（)返回的汽车姿势应该等于target：{1，0，'E'}
    }

    // 测试用例4 测试测试Execute方法,在朝向为W,起点为(0,0)时去执行M指令是否正确
    TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

        executor->Execute("M");

        const Pose target({-1, 0, 'W'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例5 测试测试Execute方法,在朝向为N,起点为(0,0)时去执行M指令是否正确
    TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

        executor->Execute("M");

        const Pose target({0, 1, 'N'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例6 测试测试Execute方法,在朝向为S,起点为(0,0)时去执行M指令是否正确
    TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

        executor->Execute("M");

        const Pose target({0, -1, 'S'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例7 测试测试Execute方法,在朝向为E,起点为(0,0)时去执行L指令是否正确
    TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

        executor->Execute("L");

        const Pose target({0, 0, 'N'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例8 测试测试Execute方法,在朝向为N,起点为(0,0)时去执行L指令是否正确
    TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

        executor->Execute("L");

        const Pose target({0, 0, 'W'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例9 测试测试Execute方法,在朝向为W,起点为(0,0)时去执行L指令是否正确
    TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

        executor->Execute("L");

        const Pose target({0, 0, 'S'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例10 测试测试Execute方法,在朝向为S,起点为(0,0)时去执行L指令是否正确
    TEST(ExecutorTest, should_return_facing_E_given_command_is_L_and_facing_is_S)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

        executor->Execute("L");

        const Pose target({0, 0, 'E'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例11 测试测试Execute方法,在朝向为E,起点为(0,0)时去执行R指令是否正确
    TEST(ExecutorTest, should_return_facing_S_given_command_is_R_and_facing_is_E)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

        executor->Execute("R");

        const Pose target({0, 0, 'S'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例12 测试测试Execute方法,在朝向为S,起点为(0,0)时去执行R指令是否正确
    TEST(ExecutorTest, should_return_facing_W_given_command_is_R_and_facing_is_S)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

        executor->Execute("R");

        const Pose target({0, 0, 'W'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例13 测试测试Execute方法,在朝向为W,起点为(0,0)时去执行R指令是否正确
    TEST(ExecutorTest, should_return_facing_N_given_command_is_R_and_facing_is_W)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

        executor->Execute("R");

        const Pose target({0, 0, 'N'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试用例14 测试测试Execute方法,在朝向为N,起点为(0,0)时去执行R指令是否正确
    TEST(ExecutorTest, should_return_facing_E_given_command_is_R_and_facing_is_N)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

        executor->Execute("R");

        const Pose target({0, 0, 'E'});
        ASSERT_EQ(target, executor->Query());
    }
}
