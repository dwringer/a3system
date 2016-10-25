# alist
- fnc_alist_get/fnc_alist_set - Use array of value pairs as a dictionary.
Folder structure:
```html
        include\alist.hpp
		alist\*.*
```
Config init.sqf:
```html
#include <include\alist.hpp>
```

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
state variables and enable the dialog system on individual units.  Currently
this file expects a unit named "cman" somewhere in the editor, so expect an
error message if this is included without taking care of it.

# classes
This is a highly experimental but very powerful module to enable a simplistic
system of classes to support primitive custom object-oriented-programming
beyond the confines of the game's object system and separate functions.  Now
it is possible to assign game objects as instances of one or more class,
responding appropriately to methods defined on those classes.  In these
examples, class definitions are grouped in the classdef/ folder in a single
file per class listing the initialization and other methods for each instance.
Dependencies:
```html
        init.sqf
        mission.sqm
        include\alist.hpp
		include\classes.hpp
		include\lambda.hpp
		include\vectools.hpp  // Used for examples
		alist\*.*
		classes\*.*
		classdef\*.*  // Example classes
		lambda\*.*
		vectools\*.*  // Used for examples
```

Init.sqf configuration:
```html
        #include <include\alist.hpp>
        #include <include\lambda.hpp>
        #include <include\vectools.hpp>
        #include <include\classes.hpp>
        #include <classdef\Dictionary.hpp>
		#include <classdef\... >
		 ...
        ClassesInitialized = true;
```

To use the provided Dictionary class example, drop a game logic in the editor,
then in its initialization field put:
```html
    _nil = this spawn {
	    waitUntil {not isNil "ClassesInitialized"};
		[_this, "Dictionary"] call fnc_instance;
	};
```
Now, in fact, classes can be created without a preexisting object using
fnc_new.  Each new class will be created as a Game Logic in a dedicated group
called Group_ClassLogic.  This is done like so:
```html
    // General form:
    _newObject = ["ObjectClassname", <parameter-1>, <parameter-2>, ...]
                     call fnc_new;

    // Dictionary class example:
    MyDict = ["Dictionary"] call fnc_new;  // (no parameters for constructor)
```

Some example usage of the dictionary is as follows (assuming the Game Logic was
named "TestDictionary" in the editor):
```html
        // Add a key, value to the dictionary:
        [TestDictionary, "set", "test key", "some test data"] call fnc_tell;

        // Look up the stored value from a key:
        _v = [TestDictionary, "get", "test key"] call fnc_tell;

        // Get all keys stored in the dictionary:
        _keys = [TestDictionary, "keys"] call fnc_tell;

        // Get an alist of all key, value pairs stored using this interface:
        _kvps = [TestDictionary, "items"] call fnc_tell;
```

This module, like all of these modules, is still under development.

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

# lambda
This is a barebones implementation of a functional programming layer on top of
SQF.  In addition to fnc_lambda for creating anonymous functions, we have
fnc_map and fnc_mapwith, fnc_reduce, and fnc_filter for processing arrays.

There are only a few things to keep in mind - the functions created with
fnc_lambda will always take an array of parameters (never an atomic value).
Code for fnc_lambda cannot close over variables, so anything you want accessed
from within the lambda body must be added as an additional parameter to the
anonymous function and then handed off to anything that will be using the
function so it can be plugged-in at call time.  The typical pattern can be seen
in mkcivs\fnc_closest and vectools\fnc_sorted, and an extra-parameters argument
is available in fnc_mapwith, fnc_reduce, and fnc_filter.

Files needed:
```html
        init.sqf
        mission.sqm
        include\lambda.hpp
        lambda\*.*
```
Headers required in init.sqf:
```html
        #include <include\lambda.hpp>
```
Setting up an anonymous function of three variables to compute the volume of
a cube:
```html
        _fn = [["_l", "_w", "_h"], {_l * _w * _h}] call fnc_lambda;
        _vol = [2, 2, 2] call _fn;
        // _vol = 8
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
                [<weapon-cache-1>,
                 <weapon-cache-2>,
                 ...]] execVM "mkcivs\layAmbush.sqf";
```

To set up an IED, create or select an object to specify its target and a trigger
to activate the bomb.  In the trigger on-activation field put one of these:
```html
        _nil = [<target-name>] execVM "mkcivs\bomb.sqf";  // Standard, or

        _nil = [<target-name>] execVM "mkcivs\fragbomb.sqf";  // Fragmentation
```

I included a couple of functions with this module that make use of the features
in lambda/: fnc_neighbors and fnc_closest.  fnc_neighbors accepts a target 
object, array, and distance parameter, returning all objects from the array 
within the specified distance of the target.  fnc_closest works similarly but
accepts an (optional) integer _n_ instead of distance, returning the [n]
closest objects.

# randint
This module is purely experimental and does nothing but attempt to add another
flavor to the random number generation in the simulation.  No guarantees are
made as to the quality of these random numbers except that they are possibly
worse than the stock PRNG.  There is a crude attempt to apply von Neumann's
whitening algorithm to randomly selected bits generated with the stock
function. See directed_graph or vectools for setup overview.

# vectools
This is a module of various functions used to manipulate arrays.  Many of these
derive syntax from Python functions, and the usage with respect to lower and
upper bound specifiers is the same.  Particularly, the subsequence function
is inclusive of the lower bound only (contrast this with SQF control structures
in which a for-from-to-do-loop covers both lower and upper bounds).  Negative
values can also be used for indexing from the right instead of left just as in
Python.
- fnc_choose - Choose [n=1] values at random from an array.
- fnc_range - Generate a range of integers, with optional step size.
- fnc_shuffle - Return a shuffled copy of an array.
- fnc_sorted - Sort array with a given comparator function of at least two
                 variables.  If > 2, an array of extra variables to insert to
		 each comparison call must be provided.
- fnc_subseq - Return a subsequence of an array (supports negative indices).
- fnc_zip - Matrix transpose, or, transform n-lists-of-m to m-lists-of-n.
- fnc_homogenize - Take a list of coordinates and convert to homogeneous 
representation.
- fnc_dehomogenize - Take a list of homogeneous coordinates and divide each by
its last element, then remove the last element.
File setup:
```html
        init.sqf
        mission.sqm
        include\randint.hpp
        include\vectools.hpp
        randint\*.*
        vectools\*.*
```
Setup of init.sqf:
```html
        #include <include\randint.hpp>
        #include <include\vectools.hpp>
```

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
