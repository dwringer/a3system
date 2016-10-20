# asinc
This system adds simple conversation windows and a rudimentary state machine
for managing dialog trees on NPC's.  The goal is extreme simplicity and
minimalism, and conversations can branch three ways at a time (as in many
console-style RPG's).  To use, ensure these files are in the mission path:
```html
        Description.ext
        init.sqf
        mission.sqm
        include\asinc.hpp
        include\asinc_defines.hpp
        include\asinc_dialogs.hpp
        asinc\*.*
```
Put the following at the top of Description.ext:
```html
        #include <include\asinc_defines.hpp>
        #include <include\asinc_dialogs.hpp>
```
And the following at the head of init.sqf:
```html
        #include <include\asinc.hpp>
```
Now edit asinc\initDialogs.sqf following the example to fill in dialog
state variables and enable the dialog system on individual units.

# desrc
This is not documented and highly experimental - use at your own risk.  With
the right triggers these functions can be used to evolve vantage positions
around a given area.

# directed_graph
These functions realize a directed graph in the editor made up of synchronized
Game Logic entities.  Each node needs only be initialized with the following:
```html
        this setVariable ["dg_isNode", true];
```
You may start the graph with a single node.  A directed edge is terminated by
two consecutive nodes spaced within a sufficiently small distance (currently
within a couple of meters).  Ending a path is done with three consecutive
nodes grouped similarly.  The function fnc_dg_next takes a node and makes two
steps from it, going to the next "full" node (every other node can be viewed
as merely a transition, or edge state).  When multiple paths are available,
then fnc_randint is called to pick one.

NOTE: This module requires the randint module.  Your path should be as follows:
```html
        init.sqf
        mission.sqm
        include\randint.hpp
        include\directed_graph.hpp
        randint\*.*
        directed_graph\*.*
```
The following two lines should be in init.sqf:
```html
        #include <include\randint.hpp>
        #include <include\directed_graph.hpp>
```

# misc
Here are a few scripts that are not part of any comprehensive module.
- randomTime.sqf - sets the simulation to sunrise, sunset, or any random time.
- randomWeather.sqf - sets an assortment of random weather parameters.
- rube_fn_sun.sqf - function used in randomTime to determine sunrise/set.
- shove.sqf - experimental function to allow the pushing-away of an object.

# mkcivs
To add the ambient civilian subsystem, ensure the following files are in your
mission path:
```html
        init.sqf
        mission.sqm
        include\mkcivs.hpp
        mkcivs\*.*
```

Then, place the following at the top of your misson's init.sqf file:
```html
        #include <include\mkcivs.hpp>
```

To create an ambient civilian zone, place a Game Logic at the center and in
its initialization field, put the following:
```html
        _nil = [this,
                <#-of-groups>,
                <max-group-size>,
                <placement-radius>,
                <spawn-radius>,
                <despawn-radius>] execVM "mkcivs\civtriggers.sqf";
```

To set up an ambush from the ambient civilians, place one or more objects in
the area to represent weapon caches, giving each a unique name in the editor.
Then, set up a trigger and in its on-activation field put the following:
```html
        _nil = [<civ-muster-distance-from-weapon-cache>,
                [<weapon-cache-name-1>,
                 <weapon-cache-name-2>,
                 ...]] execVM "mkcivs\layAmbush.sqf";
```

To set up an IED, create or select an object to specify its target and a trigger
to activate the bomb.  In the trigger on-activation field put one of these:
```html
        _nil = [<target-name>] execVM "mkcivs\bomb.sqf";  // Standard, or

        _nil = [<target-name>] execVM "mkcivs\fragbomb.sqf";  // Fragmentation
```

# randint
This module is purely experimental and does nothing but attempt to add another
flavor to the random number generation in the simulation.  No guarantees are
made as to the quality of these random numbers except that they are quite
probably worse than the stock PRNG.  There is a crude attempt to apply von
Neumann's whitening algorithm to randomly selected bits generated with the
stock function. See directed_graph for setup information.

# weapon_shop
This is a simple dialog module to allow the purchasing of weapons and their
associated magazines within the simulation.  To show the dialog, execute the
following:
```html
        _nil = execVM "weapon_shop\openshop.sqf";
```
To use, the following files are required:
```html
        Description.ext
        init.sqf
        include\weapon_shop_defines.hpp
        include\weapon_shop_dialogs.hpp
        include\weapon_shop.hpp
        weapon_shop\*.*
```
In Description.ext:
```html
        #include <include\weapon_shop_defines.hpp>
        #include <include\weapon_shop_dialogs.hpp>
```
And in init.sqf:
```html
        #include <include\weapon_shop.hpp>
```
