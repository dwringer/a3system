#include <desrc\ga.h>
#include <include\alist.h>
#include <include\lambda.h>
#include <include\randint.h>
#include <include\vectools.h>
#include <include\directed_graph.h>
#include <include\weapon_shop.h>
#include <include\asinc.h>

#include <include\classes.h>
#include <classdef\ObjectRoot.hpp>
#include <classdef\Dictionary.hpp>
#include <classdef\UnitGroup.hpp>
#include <classdef\CrewUnitGroup.hpp>

#include <include\mkcivs.h>
#include <mkcivs\classdef\WeaponCache.hpp>
#include <mkcivs\classdef\Victim.hpp>
#include <mkcivs\classdef\CivilianZone.hpp>

#include <pso\distance_fns.h>
#include <pso\objective_fns.h>
#include <pso\Marker.hpp>
#include <pso\Particle.hpp>
#include <pso\Optimizer.hpp>

ClassesInitialized = true;

if (!isServer) exitWith {};


 
/*
execVM "misc\randomWeather.sqf";
([[["sunrise", "sunset"] select floor random 2], []]
 select floor random 2) execVM "misc\randomTime.sqf";
*/