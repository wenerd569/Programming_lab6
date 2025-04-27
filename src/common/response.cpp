#include "common/response.hpp"

Response<void> Response<void>::success()
{
    return Response<void>(OK);
}

ResponseCode Response<void>::getStatusCode() const
{
    return statusCode;
}

Response<void> Response<void>::failure(ResponseCode errorCode)
{
    return Response<void>(errorCode);
}

Response<void>::Response(ResponseCode statusCode) : statusCode { statusCode } { }

void Response<void>::to_json(nlohmann::json &j, const Response<void> &p)
{
    j = { { "reqestId", p.reqestId }, { "statusCode", p.statusCode } };
}

void Response<void>::from_json(const nlohmann::json &j, Response<void> &p)
{
    j.at("statusCode").get_to(p.statusCode);
    j.at("reqestId").get_to(p.reqestId);
}