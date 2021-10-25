#pragma once

#include <string>
#include "client/client-message.hh"

namespace client
{

    // XXX: maybe thinks about hierarchy of different messages
    //
    //          - REPL
    //         |
    // Message - RPC -> Append, Request, ....
    //         |
    //          - Client message
    //
    class ClientRequest : public ClientMsg
    {
    public:
        explicit ClientRequest(const std::string& command,
                unsigned int serial_number, unsigned int client_index);
        explicit ClientRequest(const json& json_obj);


        void apply(Server &server) final;

        std::string get_command() const;
        unsigned int get_serial_number() const;
        unsigned int get_client_index() const;

    private:
        json serialize_json() const final;

        const std::string command;
        const unsigned int serial_number;
        const unsigned int client_index;
    };

}