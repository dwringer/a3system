////////////////////////////// dg_synced.sqf /////////////////////// 2016-10-19
/*   Find synchronized objects flagged with "dg_isNode"   */
////////////////////////////////////////////////////////////
private [             //                                       
         "_node",       // vehicle   [IN]                              //
         "_synced",     // vehicle[] [OUT]                            //// 
         "_non_nodes",  // vehicle[]                                 ////// 
         "_ni"          // vehicle                                  ///  ///  
                      //                                           ///    ///
                      //                                          ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_node = _this;
_synced = synchronizedObjects _node;
_non_nodes = [];
for "_i" from 0 to ((count _synced) - 1) do {
	_ni = _synced select _i;
	if (not (_ni getVariable "dg_isNode")) then {
		_non_nodes = _non_nodes + [_ni]
        };
	_synced = _synced - _non_nodes;
};
_synced;  // RETURN ///////////////////////////////////////////////////////////