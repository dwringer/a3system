// Core system (REQUIRED):
#include <include\core.h>

// Misc modules:
#include <misc\include\directed_graph.h>
#include <misc\include\weapon_shop.h>
#include <misc\include\asinc.h>

// ObjectRoot class (REQUIRED):
#include <classdef\ObjectRoot.hpp>

// Assorted classes:
#include <classdef\PostProcessing.hpp>
#include <classdef\Dictionary.hpp>
#include <classdef\UnitGroup.hpp>
#include <classdef\CrewUnitGroup.hpp>
#include <classdef\CargoVehicle.hpp>
#include <classdef\Waypoint.hpp>

// Optimizer module:
#include <include\optimizer.h>

// MKCIVS module:
#include <include\mkcivs.h>


//////////////////////////////////////////////////
// Allow waiting editor objects to instantiate: //
//////////////////////////////////////////////////
ClassesInitialized = true;                      //
//////////////////////////////////////////////////


// [NOT MP DESIGNED OR TESTED!]
//if (!isServer) exitWith {}; 

 
// Random weather - not fully functional:
//execVM "misc\randomWeather.sqf";


// Random time and date - sort of glitchy:
([[["sunrise", "sunset"] select floor random 2], []]
 select floor random 2) execVM "misc\randomTime.sqf";
