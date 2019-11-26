#include <include\core.h>
#include <classdef\ObjectRoot.hpp>
#include <classdef\PostProcessing.hpp>
#include <include\optimizer.h>
#include <include\mkcivs.h>
#include <misc\unload_helicopters.h>

#include <classdef\Waypoint.hpp>
#include <classdef\TargetImpression.hpp>
#include <classdef\LocationFinder.hpp>
#include <classdef\Armory.hpp>
#include <classdef\UnitGroup.hpp>
#include <classdef\CrewUnitGroup.hpp>
#include <classdef\Insurgency.hpp>
#include <classdef\Headquarters.hpp>

#include <classdef\LogicalGroup.hpp>

private ["_randomizerThread"];

ClassesInitialized = true;

// Burn some randoms as fast as possible while initializing for 20s
_randomizerThread = [] spawn {
	private ["_rand"];
	while { time < 20 } do {
		_rand = ([[1, 2, 3, 4], 3] call fnc_choose) select ([3] call fnc_randint);
	};
};

PostProcessing = ["PostProcessing",
  ["golden_autumn",
   "movie_day",
   "middle_east",
   "real_is_brown_2",
   "tropical",
   "ofp_palette",
   "none"] select ([7] call fnc_randint)
] call fnc_new;

//([["sunrise", "sunset", "", ""]] call fnc_choose) execVM "misc\randomTime.sqf";
([["sunrise", "sunset", "", ""]] call fnc_choose) execVM "misc\randomTime.sqf";
[] execVM "misc\randomWeather.sqf";
_nil = [] spawn { sleep 0.02; forceWeatherChange };

CivZones = [
  civzone_Athanos_1,
  civzone_Athanos_2,
  civzone_Athanos_3,
  civzone_AthanosChapel,
  civzone_Neri_1,
  civzone_Neri_2,
  civzone_Panochori_1,
  civzone_Panochori_2,
  civzone_Panochori_3,
  civzone_Panochori_4,
  civzone_Panochori_5,
  civzone_PanochoriBayFarm_1
];
