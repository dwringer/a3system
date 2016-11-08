///////////////////////////// fnc_logarithm //////////////////////// 2016-10-18
/*  Finds the logarithm in any given base: [[base=e], num] call...  */
//////////////////////////////////////////////////////////////////////
private [                 //
         "_argc",         // int
         "_base",         // int   [IN/1]                              //
         "_number",       // float [IN/2]                             //// 
         "_numerator",    // float                                   ////// 
         "_denominator",  // float                                  ///  ///  
         "_e",            // float                                 ///    ///
         "_result"        // float [OUT]                          ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
#include <include\constants.h>
_e = E;
_argc = count _this;
switch (_argc) do {
	case 1: {
		_base = _e;
		_number = _this select 0;
	};
	case 2: {
		_base = _this select 0;
		_number = _this select 1;
	};
};
/* Formula: (log b x) = (log a x) / (log a b) */
_numerator = log _number;
_denominator = log _base;
_result = _numerator / _denominator;
_result;  // RETURN ///////////////////////////////////////////////////////////
