#include <desrc\ga.h>  // Currently unused.
#include <include\randint.hpp>
#include <include\directed_graph.hpp>
#include <include\mkcivs.hpp>
#include <include\weapon_shop.hpp>

if (!isServer) exitWith {};


 

execVM "misc\randomWeather.sqf";
([[["sunrise", "sunset"] select floor random 2], []]
 select floor random 2) execVM "misc\randomTime.sqf";
