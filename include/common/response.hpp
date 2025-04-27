#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <utility>

/**
 * @brief Коды ответа
 */
enum ResponseCode {
    OK,
    NULL_RESULT,
    ELEMENT_NOT_FOUND,
    CANT_SAVE_DATA,
    INDEX_OUT_OF_RANGE,
    FAIL,
    SERVER_NOT_RESPONCE,
    INCORRECT_REQUESTION,
};

/**
 * @brief Класс ответа от сервера
 * Может содержать либо возвращаемые данные и код OK либо код ошибки
 * @tparam T
 */
template<typename T>
class Response {
private:
    ResponseCode statusCode;
    std::optional<T> data;
    long reqestId = 0;

public:
    /**
     * @brief Фабричный метод создания ответа без ошибки
     * Отвечат за инвариант класса
     * @param value
     * @return Response
     */
    static Response success (T value)
    {
        return Response<T>(std::move(value), OK);
    }

    /**
     * @brief Фабричный метод создания ответа c ошибкой
     * Отвечат за инвариант класса
     * @param errorCode
     * @return Response
     */
    static Response failure (ResponseCode errorCode)
    {
        return Response<T>(errorCode);
    }

    Response(Response &&other) noexcept = default;
    Response &operator=(Response &&other) noexcept;
    ~Response() = default;

    static nlohmann::json to_json (const Response<T> &p)
    {
        nlohmann::json j;
        if ( p.data.has_value() ) {
            j = { { "data", p.data.value() },
                  { "reqestId", p.reqestId },
                  { "statusCode", p.statusCode } };
        } else {
            j = { { "reqestId", p.reqestId }, { "statusCode", p.statusCode } };
        }
        return j;
    }

    static Response from_json (const nlohmann::json &j)
    {
        T data;
        if ( j.contains("data") ) {
            data = j.at("data").get<T>();
        } else {
            data = std::optional<T>();
        }
        Response<T> res { std::move(data), j.at("statusCode").get<ResponseCode>() };
        res.setRequestId(j.at("reqestId").get<long>());
        return res;
    }

    const std::optional<T> &getData () const &
    {
        return data;
    }

    ResponseCode getStatusCode () const
    {
        return statusCode;
    }

    long getRequestId () const
    {
        return reqestId;
    }

    void setRequestId (long requestId)
    {
        this->reqestId = requestId;
    }

private:
    Response(ResponseCode error) : statusCode { error } {};

    Response(T &&data, ResponseCode error) : data { data }, statusCode { error } {};
};

/**
 * @brief Класс ответа от сервера без данных
 * Нужно реализовывать отдельно поскольку он не хранит данные
 * @tparam
 */
template<>
class Response<void> {

private:
    ResponseCode statusCode;
    long reqestId;

public:
    static Response success ();
    static Response failure (ResponseCode errorCode);

    Response(Response &&other) noexcept = default;
    Response &operator=(Response &&other) noexcept = default;
    ~Response() = default;

    static nlohmann::json to_json (const Response<void> &p);
    static Response<void> from_json (const nlohmann::json &j);

    long getRequestId () const;

    void setRequestId (long requestId);

    ResponseCode getStatusCode () const;

private:
    Response(ResponseCode error);
};