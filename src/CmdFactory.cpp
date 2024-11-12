#include "CmderFactory.hpp"

namespace adas
{
    CmderList CmderFactory::GetCmders(const std::string &commands) const noexcept
    {
        CmderList list;
        for (const auto cmd : ParseCommandString(commands))
        {
            const auto it = cmderMap.find(cmd);
            if (it != cmderMap.end())
            {
                list.push_back(it->second);
            }
        }
        return list;
    }

    std::string CmderFactory::ParseCommandString(std::string_view commands) const noexcept
    {
        std::string result(commands);
        ReplaceALL(result, "TR", "Z");
        return result;
    }
    void CmderFactory::ReplaceALL(std::string &inout, std::string_view what, std::string_view with) const noexcept
    {
        for (
            std::string::size_type pos{};
            inout.npos != (pos = inout.find(what.data(), pos, what.length()));
            pos += with.length())
        {
            inout.replace(pos, what.length(), with.data(), with.length());
        }
    }
}