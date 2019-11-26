///////////////////////////// fnc_neighbors //////////////////////// 2016-10-21
/*  Given an array, obj, & dist, find neighbors of obj in arr  */
/////////////////////////////////////////////////////////////////
private [                //
         "_candidates",  // Array   [IN/1]                             //
         "_obj",         // Vehicle [IN/0]                            //// 
         "_dist",        // float   [IN/2]                           ////// 
         "_neighbors"    // Array   [OUT]                           ///  ///  
                         //                                        ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_obj = _this select 0;
_candidates = _this select 1;
_dist = _this select 2;
_neighbors = [];
{
	if ((_obj distance _x) <= _dist) then {
		_neighbors pushBack _x;
	};
} forEach _candidates;
_neighbors = [_neighbors,
              [["_a", "_b", "_obj"],
               "((_a distance _obj) < (_b distance _obj))"] call fnc_lambdastr,
              [_obj]] call fnc_sorted;
_neighbors;  // RETURN ////////////////////////////////////////////////////////