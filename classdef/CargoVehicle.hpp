/*
  CargoVehicle class
    :: CargoVehicle -> ObjectRoot

  Methods:
    __init__                 :: Initialize the vehicle w/list of action methods
      special
    load_from_unit           :: Store unit's loadout in object
      unit
    restore_unit_loadout     :: Restore unit loadout from object
      unit
    load_group_equipment     :: Store loadout from all group members
      group
    restore_group_equipment  :: Restore loadout to all group members
      group    
    add_special_action       :: Add an action method to the vehicle
      method
    equip_civilian_attire    :: Switch a unit into civilian clothes
      unit
    equip_scuba_gear         :: Switch a unit into SCUBA gear
      unit
    outfit_group_civilian    :: Put whole group in civilian clothes
      group
    outfit_group_scuba       :: Put whole group in SCUBA gear
      group

      This class outfits a vehicle with special actions to allow the player to
  switch all group members into civilian clothes or scuba gear (then back into
  their regular loadouts).

  Example (in vehicle init):
      _nil = this spawn {
          waitUntil {not isNil "ClassesInitialized"};
          [_this, "CargoVehicle", ["outfit_group_scuba"]] spawn fnc_instance;
      };
   
*/

#define ACTIONS [["outfit_group_civilian", "Switch to civilian attire"],  \
                 ["outfit_group_scuba", "Switch to SCUBA gear"],  \
                 ["restore_group_equipment", "Switch back into equipment"]]


DEFCLASS("CargoVehicle") ["_self", "_special"] DO {
	/* Initialize the vehicle w/list of action methods */
	private ["_spec_method"];
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "units", []] call fnc_tell;
	[_self, "_setf", "loadouts", []] call fnc_tell;
	if (isNil "_special") then {
		_special = [];
	};
	[_self, "_setf", "special", _special] call fnc_tell;
	{
		[_self, "add_special_action", _x] call fnc_tell;
	} forEach _special;
	_self
} ENDCLASSV;


DEFMETHOD("CargoVehicle", "load_from_unit") ["_self", "_unit"] DO {
	/* Store unit's loadout in object */
	private ["_gear"];
	_gear = getUnitLoadout _unit;
	[_self, "_push_attr", "units", _unit] call fnc_tell;
	[_self, "_push_attr", "loadouts", _gear] call fnc_tell;
	removeAllWeapons _unit;
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "restore_unit_loadout") ["_self", "_unit"] DO {
	/* Restore unit loadout from object */
	private ["_units", "_loadouts", "_loadout"];
	_units = _self getVariable "units";
	_loadouts = _self getVariable "loadouts";
	for "_i" from 0 to ((count _units) - 1) do {
		scopeName "FindLoadout";
		if (_unit == (_units select _i)) then {
			_loadout = _loadouts select _i;
			_unit setUnitLoadout _loadout;
			_units = _units - [_unit];
			_loadouts = _loadouts - [_loadout];
			breakOut "FindLoadout";
		};
	};
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "load_group_equipment") ["_self", "_group"] DO {
	/* Store loadout from all group members */
	{
		[_self, "load_from_unit", _x] call fnc_tell;
	} forEach units _group;
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "restore_group_equipment") ["_self", "_group"] DO {
	/* Restore loadout to all group members */
	{
		[_self, "restore_unit_loadout", _x] call fnc_tell;
	} forEach units _group;
	{
		[_self, "add_special_action", _x] call fnc_tell;
	} forEach _special;
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "add_special_action") ["_self", "_method"] DO {
	/* Add an action method to the vehicle */
	private ["_text", "_action"];
	_text = [_method, ACTIONS] call fnc_alist_get;
	_action = _self addAction [
		_text,
		[["_target", "_caller", "_id", "_args"], {
			[_target, _args, group _caller] call fnc_tell
		}] call fnc_lambda,
		_method];
	[_self, "_setf", _method, _action] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "equip_civilian_attire") ["_self", "_unit"] DO {
	/* Switch a unit into civilian clothes */
	// .. outfit _unit with civilian attire ..
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "equip_scuba_gear") ["_self", "_unit"] DO {
	/* Switch a unit into SCUBA gear */
	// .. outfit _unit with scuba gear ..
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "outfit_group") ["_self", "_group", "_method"] DO {
	/* Change whole group equipment using _method */
	private ["_action"];
	[_self, "load_group_equipment", _group] call fnc_tell;
	{
		[_self, _method, _x] call fnc_tell;
	} forEach units _group;
	{
		_action = _self getvariable _x;
		_self removeAction _action;
	} forEach (_self getVariable "special");
	[_self, "add_special_action", "restore_group_equipment"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "outfit_group_civilian") ["_self", "_group"] DO {
	/* Put whole group in civilian clothes */
	[_self, "outfit_group", _group, "equip_civilian_attire"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("CargoVehicle", "outfit_group_scuba") ["_self", "_group"] DO {
	/* Put whole group in SCUBA gear */
	[_self, "outfit_group", _group, "equip_scuba_gear"] call fnc_tell;
} ENDMETHOD;
