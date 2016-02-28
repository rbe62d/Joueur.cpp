#include "register.hpp"

#include "exceptions.hpp"
#include "base_game.hpp"

namespace cpp_client
{

std::unordered_map<std::string,
                   std::unique_ptr<Base_game>,
                   Game_registry::Hasher,
                   Game_registry::Comper> Game_registry::name_map{};

Game_registry::Game_registry(const std::string& name,
                             std::unique_ptr<Base_game> game)
{
   name_map[name] = std::move(game);
}

Base_game& Game_registry::get_game(const std::string& name)
{
   if(name_map.count(name))
   {
      return *name_map[name];
   }
   else
   {
      throw Game_not_found("The requested game \"" + name + "\" was not found.");
   }
}

} //cpp_client
