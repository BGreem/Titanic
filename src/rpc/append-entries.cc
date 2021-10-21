#include "rpc/append-entries.hh"

#include "exception/follower_exception.hh"
#include "raft/server.hh"

namespace rpc
{
    AppendEntriesRPC::AppendEntriesRPC(const int term,
                                       const unsigned int leader_id,
                                       const unsigned int prev_log_index,
                                       const unsigned int prev_log_term,
                                       const std::vector<LogEntry> entries,
                                       const unsigned int leader_commit_index)
        : RemoteProcedureCall(term, RPC_TYPE::APPEND_ENTRIES_RPC)
        , leader_id(leader_id)
        , prev_log_index(prev_log_index)
        , prev_log_term(prev_log_term)
        , entries(entries)
        , leader_commit_index(leader_commit_index)
    {}

    // XXX logentry serialization
    AppendEntriesRPC::AppendEntriesRPC(const json &json_obj)
        : AppendEntriesRPC(json_obj["term"], json_obj["leader_id"],
                           json_obj["prev_log_index"],
                           json_obj["prev_log_term"], std::vector<LogEntry>(),
                           json_obj["leader_commit_index"])
    {}

    json AppendEntriesRPC::serialize_json() const
    {
        json serialization = json();

        serialization["leader_id"] = leader_id;
        serialization["prev_log_index"] = prev_log_index;
        serialization["prev_log_term"] = prev_log_term;
        serialization["entries"] = entries;
        serialization["leader_commit_index"] = leader_commit_index;

        return serialization;
    }

    const std::vector<LogEntry> &AppendEntriesRPC::get_entries() const
    {
        return entries;
    }

    unsigned int AppendEntriesRPC::get_leader_id() const
    {
        return leader_id;
    }

    unsigned int AppendEntriesRPC::get_prev_log_index() const
    {
        return prev_log_index;
    }

    unsigned int AppendEntriesRPC::get_prev_log_term() const
    {
        return prev_log_term;
    }

    unsigned int AppendEntriesRPC::get_leader_commit_index() const
    {
        return leader_commit_index;
    }

    void AppendEntriesRPC::apply(Server &server)
    {
        if (server.get_status() == ServerStatus::CANDIDATE)
        {
            if (this->get_term() >= server.get_term())
                server.convert_to_follower();
        }

        server.on_append_entries_rpc(*this);
    }
} // namespace rpc
