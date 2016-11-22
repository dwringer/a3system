DEFCLASS("CivilianZone") ["_self",
                          "_civ_groups",
                          "_max_civs_per_group",
                          "_zone_radius",
                          "_spawn_radius",
                          "_despawn_radius"] DO {
        /* Instantiate the ambient civilian trigger zone */
	SUPER("ObjectRoot", _self);
	[_self, _civ_groups, _max_civs_per_group, _zone_radius, _spawn_radius,
	 _despawn_radius] execVM "mkcivs\civtriggers.sqf";
	_self
} ENDCLASS;
