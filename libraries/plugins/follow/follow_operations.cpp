#include <surf/follow/follow_operations.hpp>

#include <surf/protocol/operation_util_impl.hpp>

namespace surf { namespace follow {

void follow_operation::validate()const
{
   FC_ASSERT( follower != following, "You cannot follow yourself" );
}

void reblog_operation::validate()const
{
   FC_ASSERT( account != author, "You cannot reblog your own content" );
}

} } //surf::follow

DEFINE_OPERATION_TYPE( surf::follow::follow_plugin_operation )
