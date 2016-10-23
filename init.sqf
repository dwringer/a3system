#include <desrc\ga.h>
#include <include\alist.hpp>
#include <include\lambda.hpp>
#include <include\randint.hpp>
#include <include\vectools.hpp>
#include <include\directed_graph.hpp>
#include <include\mkcivs.hpp>
#include <include\weapon_shop.hpp>
#include <include\asinc.hpp>

if (!isServer) exitWith {};


 

execVM "misc\randomWeather.sqf";
([[["sunrise", "sunset"] select floor random 2], []]
 select floor random 2) execVM "misc\randomTime.sqf";
