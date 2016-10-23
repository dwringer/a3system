/////////////////////////////               ////////////////////////     -  -  
/*   */
//////////////////////////////////////////////////////////////////
private [                                                      
         "_instance",                                                  //
         "_class_name",                                               //// 
         "_init_args",                                               ////// 
         "_init_",                                                  ///  ///  
         "_return"                                                 ///    ///
                                                                  ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_instance = _this select 0;
_class_name = _this select 1;
_init_args = [_this, 2, 0] call fnc_subseq;
_instanceClasses = _instance getVariable ["class_names", []];
_instanceClasses = _instanceClasses + [_class_name];
_instance setVariable ["class_names", _instanceClasses];
_init_ = ["__init__",
          [_class_name, Classes] call fnc_alist_get] call fnc_alist_get;
if (not isNil "_init_") then {
	_return = _init_args call _init_;
} else {
	_return = nil;
};
_return;