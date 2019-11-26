DEFCLASS("Armory") ["_self"] DO {
	_self
} ENDCLASS;

DEFMETHOD("Armory", "change_vests") ["_self", "_units", "_vest"] DO {
	//[["_units"], {
	 {
		 private ["_vestContainer", "_items", "_magazines",
			  //"_weaponCargo", //"_magazineCargo",
			  "_accessories", "_weapons",
			  //"_weaponCountAlist", //"_magazineCountAlist",
			  "_fn_get_count_alist"];
		 if (isNil "_vest") then { _vest = "V_I_G_resistanceLeader_F"; };
		 _fn_get_count_alist = [["_classname", "_count"], {
					    [_classname, _count]
				       }] call fnc_lambda;
		 _vestContainer      = vestContainer _x;
		 _items              = getItemCargo       _vestContainer;
		 _magazines          = magazinesAmmoCargo _vestContainer;
		 //_magazineCargo      = getMagazineCargo   _vestContainer;
		 //_magazineCountAlist = ([_fn_get_count_alist] +
		 //_magazineCargo) call fnc_map;
		 _weapons            = weaponsItemsCargo  _vestContainer;
		 //_weaponCargo        = getWeaponCargo     _vestContainer;
		 //_weaponCountAlist   = ([_fn_get_count_alist] +
		 //_weaponCargo) call fnc_map;
		 removeVest _x;
		 _X addVest _vest;
		 _vestContainer = vestContainer _x;
		 [[["_item", "_count"], {  // ADD ITEMS:
			 _vestContainer addItemCargo [_item, _count];
		  }] call fnc_lambda,
		  _items select 0, _items select 1] call fnc_map;
		 [[["_pair"], {            // ADD MAGAZINES:
			 private ["_classname"];
			 _classname = _pair select 0;
			 _vestContainer addMagazineCargoGlobal
				        [_classname, 1]
			 //[_classname,
			 //_magazineCountAlist] call fnc_alist_get];
		  }] call fnc_lambda,
		  _magazines] call fnc_map;
		 [[["_weaponItems"], {     // ADD WEAPONS:
			 _vestContainer addWeaponWithAttachmentsCargoGlobal
				 [_weaponItems, 1];
			 //[(_weaponItems select 0) select 0,
			 //_weaponCountAlist] call fnc_alist_get];
		  }] call fnc_lambda,
		  _weapons] call fnc_map;
	 } forEach _units;
	 //}] call fnc_lambda
} ENDMETHOD;
