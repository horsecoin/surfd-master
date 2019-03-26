#include <surf/witness/witness_operations.hpp>

#include <surf/protocol/operation_util_impl.hpp>

namespace surf { namespace witness {

void enable_content_editing_operation::validate()const
{
   chain::validate_account_name( account );
}

} } // surf::witness

DEFINE_OPERATION_TYPE( surf::witness::witness_plugin_operation )
