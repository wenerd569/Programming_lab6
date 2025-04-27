#pragma once

#include <cstddef>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <tuple>
#include <utility>

template<typename... Args>
class CommandCallRequest {
    std::string сommandName;
    std::tuple<Args...> arguments;
    long reqestId;

public:
    CommandCallRequest(std::string name, Args &&...args)
        : сommandName(std::move(name)), arguments(std::forward<Args>(args)...)
    {
    }

    static CommandCallRequest from_json (const nlohmann::json &j)
    {
        CommandCallRequest res = CommandCallRequest(j.at("сommandName").get<std::string>(),
                                                    j.at("arguments").get<std::tuple<Args...>>(),
                                                    j.at("reqestId").get<long>());
        return res;
    }

    static nlohmann::json to_json (const CommandCallRequest<Args...> &p)
    {
        nlohmann::json j {
            { "сommandName", p.сommandName },
            { "arguments", p.arguments },
            { "reqestId", p.reqestId },
        };
        return j;
    }

    long getRequestId () const
    {
        return reqestId;
    }

    void setRequestId (long requestId)
    {
        this->reqestId = requestId;
    }

    std::tuple<Args...> getArguments ()
    {
        return arguments;
    }

    std::string getName ()
    {
        return сommandName;
    }

private:
    CommandCallRequest(std::string name, std::tuple<Args...> arguments, long reqestId)
        : сommandName(std::move(name)), arguments { std::move(arguments) }, reqestId { reqestId }
    {
    }
};