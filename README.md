# a3system

To create an ambient civilian zone, place a Game Logic at the center and in
its initialization field, put the following:
```html  _nil = [this,
	         <#-of-groups>,
   		 <max-group-size>,
 		 <placement-radius>,
 		 <spawn-radius>,
		 <despawn-radius>] execVM "mkcivs\civtriggers.sqf";```

To set up an ambush from the ambient civilians, place one or more objects in
the area to represent weapon caches, giving each a unique name in the editor.
Then, set up a trigger and in its on-activation field put the following:
```html  _nil = [<civ-muster-distance-from-weapon-cache>,
	        [<weapon-cache-name-1>,
		 <weapon-cache-name-2>,
		 ...]] execVM "mkcivs\layAmbush.sqf";```

To set up an IED, create or select an object to specify its target and a trigger
to activate the bomb.  In the trigger on-activation field put one of these:
```html  _nil = [target] execVM "mkcivs\bomb.sqf";  // Standard, or
 	 _nil = [target] execVM "mkcivs\fragbomb.sqf";  // Fragmentation```
