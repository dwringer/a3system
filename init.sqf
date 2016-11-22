// Old experimental optimizer functions - DEPRECATED:
//#include <desrc\ga.h> 

//////////////////////////////////////
// Base support modules - REQUIRED: //
//////////////////////////////////////
#include <include\alist.h>          //
#include <include\lambda.h>         //
#include <include\randint.h>        //
#include <include\vectools.h>       //
//////////////////////////////////////

// Editor-based Directed Graph module:
#include <include\directed_graph.h>

// Simple weapon shop dialog module:
#include <include\weapon_shop.h>

// Primitive RPG-style conversation module:
#include <include\asinc.h>


///////////////////////////////////////////////////////
// Class system module - REQUIRED FOR HPP #INCLUDES: //
///////////////////////////////////////////////////////
#include <include\classes.h>                         //
///////////////////////////////////////////////////////

// ObjectRoot class:
#include <classdef\ObjectRoot.hpp>

// Simple Dictionary class:
#include <classdef\Dictionary.hpp>

// Unit Group class and Crew class for loading vehicles:
#include <classdef\UnitGroup.hpp>
#include <classdef\CrewUnitGroup.hpp>

// CargoVehicle:
#include <classdef\CargoVehicle.hpp>


/////////////////////////// Optimization library: /////////////////////////////
#include <opti\distance_fns.h>
#include <opti\road_fns.h>
#include <opti\objective_fns.h>
#include <opti\application_fns.h>
#include <opti\Marker.hpp>
#include <opti\Particle.hpp>
#include <opti\Optimizer.hpp>
///////////////////////////////////////////////////////////////////////////////


///////////////////// MKCIVS module and support classes: //////////////////////
#include <include\mkcivs.h>
#include <mkcivs\ambush_fns.h>
#include <mkcivs\WeaponCache.hpp>
#include <mkcivs\Victim.hpp>
#include <mkcivs\CivilianZone.hpp>
///////////////////////////////////////////////////////////////////////////////


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
