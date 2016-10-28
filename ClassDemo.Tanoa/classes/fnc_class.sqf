/////////////////////////////// fnc_class ////////////////////////// 2016-10-23
/*  Create a new class with optional init method  */
////////////////////////////////////////////////////
private [                //                                    
         "_class_name",  // String   [IN/A0/B0]                        //
         "_init_",       // Function [IN/A1]                          //// 
         "_methods"      // alist                                    ////// 
                         //                                         ///  ///  
                         //                                        ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_class_name = _this select 0;

if ((count _this) == 2) then {
	_init_ = _this select 1;
} else {
	_init_ = nil;
};
_methods = [];
if (not isNil "_init_") then {
	_methods = ["__init__",
	            _init_,
	            _methods] call fnc_alist_set;
};
Classes = [_class_name, _methods, Classes] call fnc_alist_set;
///////////////////////////////////////////////////////////////////////////////