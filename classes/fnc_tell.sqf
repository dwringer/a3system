/////////////////////////////// fnc_tell /////////////////////////// 2016-10-23
/*  Send a message to an object, collecting the result   */
///////////////////////////////////////////////////////////
private [                //                                    
         "_instance",    // Vehicle  [IN/0]                            //
         "_message",     // String   [IN/1]                           //// 
         "_parameters",  // Array    [IN/2[,3..]]                    ////// 
         "_classes",     // alists                                  ///  ///  
         "_methods",     // alist                                  ///    ///
         "_results"      // Array or element [OUT]                ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_instance = _this select 0;
_message = _this select 1;
_parameters = [_this, 2, 0] call fnc_subseq;
_classes = [[["_cname"],
             "[_cname, Classes] call fnc_alist_get"] call fnc_lambda,
            _instance getVariable ["class_names", []]] call fnc_map;
_methods = [[["_method_list", "_msg"],
             "[_msg, _method_list] call fnc_alist_get"] call fnc_lambda,
            _classes, [_message]] call fnc_mapwith;
_results = [[["_m", "_inst", "_params"],
             "([_inst] + _params) call _m"] call fnc_lambda,
            _methods, [_instance, _parameters]] call fnc_mapwith;
if ((count _results) == 1) then {
	_results = _results select 0;
};
_results;  // RETURN //////////////////////////////////////////////////////////