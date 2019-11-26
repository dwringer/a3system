//////////////////////////////// fnc_map /////////////////////////// 2016-10-21
/*  Map a function across array(s) using provided extra vars  */
////////////////////////////////////////////////////////////////
private [                 //                                   
         "_fn",           // Function [IN/0]                           //
         "_arg_lists",    // Arrays   [IN/1[,2..]]                    //// 
         "_extra_vars",   // Array                                   ////// 
         "_array_count",  // int                                    ///  ///  
         "_params",       // Array                                 ///    ///
         "_acc"           // Array    [OUT]                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_fn = _this select 0;
_arg_lists = [];
_extra_vars = _this select ((count _this) - 1);
_array_count = (count _this) - 2;
for "_i" from 1 to _array_count do {
	_arg_lists pushBack (_this select _i);
};
_acc = [];
for "_i" from 0 to ((count (_arg_lists select 0)) - 1) do {
	_params = [];
	for "_j" from 0 to (_array_count - 1) do {
		_params pushBack ((_arg_lists select _j) select _i);
	};
	_acc pushBack ((_params + _extra_vars) call _fn);
};
_acc;  // RETURN //////////////////////////////////////////////////////////////