#define PP_MODES  [["none",  \
                    [1, 1, 0,[ 0, 0, 0, 0],[ 1, 1, 1, 1],[ 0, 0, 0, 0]]],  \
                   ["middle_east",  \
		    [0.9, 1, 0, [0.1, 0.1, 0.1, -0.1], [1, 1, 0.8, 0.528],  [1, 0.2, 0, 0]]],				\
		   ["real_is_brown_2",  \
		    [1,1,0,[0.1,0.2,0.3,-0.3],[1,1,1,0.5],[0.5,0.2,0,1]]],		     \
		   ["nightstalkers",  \
		    [1, 1.1, 0.0, [0.0, 0.0, 0.0, 0.0], [1.0,0.7, 0.6, 0.60], [0.200, 0.600, 0.100, 0.0]]],		   \
		   ["gray_tone",  \
		    [1.0, 1.0, 0.0,[1.0, 1.0, 1.0, 0.0],[1.0, 1.0, 0.9, 0.35],[0.3,0.3,0.3,-0.1]]],	       \
		   ["cold_tone",  \
		    [1.0, 1.0, 0.0,[0.2, 0.2, 1.0, 0.0],[0.4, 0.75, 1.0, 0.60],[0.5,0.3,1.0,-0.1]]]]


DEFCLASS("PostProcessing") ["_self", "_mode"] DO {
	/* Post processing module initialization to named mode (or "random") */
	[_self, "set", _mode] call fnc_tell;
	_self
} ENDCLASS;


DEFMETHOD("PostProcessing", "set") ["_self", "_mode", "_commit"] DO {
	/* Set specified mode, with optional commit time (seconds) */
	if (not isNil "_commit") then {
		[_self, "apply",
		 [_self, "settings", _mode] call fnc_tell,
		 _commit] call fnc_tell;
	} else {
		[_self, "apply",
		 [_self, "settings", _mode] call fnc_tell] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("PostProcessing", "settings") ["_self", "_mode"] DO {
	/* Retrieve numeric settings for a given mode name */
	if (_mode == "random") then {
		(PP_MODES select (floor random count PP_MODES)) select 1;
	} else {
		[_mode, PP_MODES] call fnc_alist_get;
	};
} ENDMETHOD;


DEFMETHOD("PostProcessing", "apply") ["_self", "_settings", "_commit"] DO {
	/* Apply settings with optional commit time (in seconds) */
	if (isNil "_commit") then {
		_commit = 0;
	};
	"colorCorrections" ppEffectEnable false;
	if (not (_settings isEqualTo [])) then {
		"colorCorrections" ppEffectEnable true;
		"colorCorrections" ppEffectAdjust _settings;
		"colorCorrections" ppEffectCommit _commit;
	};
} ENDMETHOD;


DEFMETHOD("PostProcessing", "list") ["_self"] DO {
	/* List available color correction mode names */
        [[["_x"], {_x select 0}] call fnc_lambda, PP_MODES] call fnc_map;
} ENDMETHOD;
