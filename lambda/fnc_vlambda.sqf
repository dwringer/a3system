////////////////////////////// fnc_vlambda ///////////////////////// 2016-10-21
/*  Create and compile an anonymous function with variable args  */
///////////////////////////////////////////////////////////////////
private [                //
         "_parameters",  // Array  [IN/0]                              //
         "_code",        // String [IN/1]                             //// 
         "_context",     // String                                   ////// 
         "_func",        // Code   [OUT]                            ///  ///  
         "_guard"        // String                                 ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_parameters = _this select 0;
_code = (_this select 1) call fnc_decompile;
_context = "";
_guard = "private [""_LAMBDA_nextParameter""";
for "_i" from 0 to ((count _parameters) - 1) do {
	_guard = format ["%1, ""%2""", _guard, _parameters select _i];
};
_guard = format ["%1];", _guard];
for "_i" from 0 to ((count _parameters) - 1) do {
	_context = format ["%1
                            _LAMBDA_nextParameter = _this select %3;
                            if (not isNil ""_LAMBDA_nextParameter"") then {
                                    %2 = _this select %3; ",
	                   _context, _parameters select _i, _i];
};
for "_i" from 0 to ((count _parameters) - 1) do {
	_context = format ["%1};", _context];
};
_func = compile format ["%1 %2 %3;", _guard, _context, _code];
_func;  // RETURN /////////////////////////////////////////////////////////////

/* EX:
    _sum = [3] call ([["_x", "_y", "_z"], { 
           if (isNil "_z") then {_x}
           else {_x + _y + _z}
    }] call fnc_vlambda);
*/