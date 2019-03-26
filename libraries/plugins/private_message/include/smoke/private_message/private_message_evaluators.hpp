#pragma once

#include <surf/chain/evaluator.hpp>

#include <surf/private_message/private_message_operations.hpp>
#include <surf/private_message/private_message_plugin.hpp>

namespace surf { namespace private_message {

DEFINE_PLUGIN_EVALUATOR( private_message_plugin, surf::private_message::private_message_plugin_operation, private_message )

} }
