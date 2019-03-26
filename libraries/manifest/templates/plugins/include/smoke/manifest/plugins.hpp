
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace surf { namespace app {

class abstract_plugin;
class application;

} }

namespace surf { namespace plugin {

void initialize_plugin_factories();
std::shared_ptr< surf::app::abstract_plugin > create_plugin( const std::string& name, surf::app::application* app );
std::vector< std::string > get_available_plugins();

} }
