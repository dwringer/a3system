///////////////////////////// dg_closest.sqf /////////////////////// 2016-10-19
/*  Given an obj, neighbors and radius r, get neighbors within r */
///////////////////////////////////////////////////////////////////
private [           //                                         
         "_object",   // vehicle   [IN]                                //
         "_targets",  // vehicle[]                                    //// 
         "_radius",   // float                                       ////// 
         "_closest",  // vehicle[] [OUT]                            ///  ///  
         "_tgt"       // vehicle                                   ///    ///
                    //                                            ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_object = _this select 0;
_targets = _this select 1;
_radius = _this select 2;
_closest = [];
for "_i" from 0 to ((count _targets) - 1) do {
	_tgt = _targets select _i;
	if ((_object distance _tgt) <= _radius) then {
		_closest = _closest + [_tgt];
	};
};
_closest;  // RETURN //////////////////////////////////////////////////////////
