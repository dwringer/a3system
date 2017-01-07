/////////////////////////////// fnc_new //////////////////////////// 2016-10-23
/*   Create and init a new gamelogic of given class  */
///////////////////////////////////////////////////////
private [                //                                    
         "_class_name",  // String   [IN/1]                           
         "_init_args",   // Array    [[IN/2[,3..]]                     //
         "_init_",       // Function                                  ////
         "_center",      // Center                                   //////
         "_group",       // Group                                   ///  ///  
         "_curClasses",  // String                                 ///    ///
         "_return"       // Any      [OUT]                        ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_class_name = _this select 0;
_init_args = [_this, 1, 0] call fnc_subseq;
if (isNil "Group_ClassLogic") then {
	_group = createGroup sideLogic;
	if (isNil "_group") then {
		_center = createCenter sideLogic;
		_group = createGroup sideLogic;
	};
	Group_ClassLogic = _group;
};
_instance = Group_ClassLogic createUnit ["LOGIC", [0.0, 0.0, 0.0], [], 0, ""];
_curClasses = _instance getVariable ["class_names", []];
_curClasses pushBack _class_name;
_instance setVariable ["class_names", _curClasses];
_init_ = ["__init__",
          [_class_name, Classes] call fnc_alist_get] call fnc_alist_get;
if (not isNil "_init_") then {
	_return = ([_instance] + _init_args) call _init_;
};
if (not isNil "_return") then {
	_return;
};  // RETURN /////////////////////////////////////////////////////////////////