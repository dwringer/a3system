/*
  PostProcessing class
    :: PostProcessing -> ObjectRoot

  Methods:
   __init__      :: Initialize Post Processing to the specified color mode
   set           :: Set a specific color mode, with optional commit time
     mode
     [commit]
   settings      :: Retrieve settings for a given mode
     mode
   apply         :: Apply given settings, with optional commit time
     settings
     [commit]
   list          :: List available mode names

      This class manages in-game post-processing to apply color corrections
  based on several preset color profiles.  Currently available* are:
 
        o none
        o middle_east
        o real_is_brown_2
        o nightstalkers
        o gray_tone
        o cold_tone

    * These settings were taken from evromalarkey's helpful post at:
      https://forums.bistudio.com/topic/169842-ascz-custom-post-process-effects/
      and the extensive archive at:
      https://forums.bistudio.com/topic/74135-ppeffect-collection/
      Permission to redistribute the color values was neither asked nor 
      granted, so if you have a license issue or other claim of interest on
      these values just let me know and I can remove/replace them or provide
      additional information as desired.

  Example:
   PostProcessing = ["PostProcessing", "none"] call fnc_new;
   [PostProcessing, "set", "middle_east", 2] call fnc_tell;
   // Fades to the middle_east color profile over a period of 2 seconds.

*/

#define PP_MODES  [["none",                    [1, 1, 0, [ 0, 0, 0, 0], [ 1, 1, 1, 1], [ 0, 0, 0, 0]]], \
                   ["middle_east",		    [0.9, 1, 0, [0.1, 0.1, 0.1, -0.1], [1, 1, 0.8, 0.528],  [1, 0.2, 0, 0]]], \
		   ["real_is_brown_2",		    [1, 1, 0, [0.1, 0.2, 0.3, -0.3], [1, 1, 1, 0.5], [0.5, 0.2, 0, 1]]], \
		   ["nightstalkers",		    [1, 1.1, 0.0, [0.0, 0.0, 0.0, 0.0], [1.0, 0.7, 0.6, 0.60], [0.200, 0.600, 0.100, 0.0]]], \
		   ["gray_tone",		    [1.0, 1.0, 0.0, [1.0, 1.0, 1.0, 0.0], [1.0, 1.0, 0.9, 0.35], [0.3, 0.3, 0.3, -0.1]]], \
		   ["cold_tone",		    [1.0, 1.0, 0.0, [0.2, 0.2, 1.0, 0.0], [0.4, 0.75, 1.0, 0.60], [0.5, 0.3, 1.0, -0.1]]], \
		   ["stalker",		    [1, 0.75, 0, [0.8, 0.9, 1, -0.1], [1, 1, 1, 2], [-0.5, 0, -1, 5]]], \
		   ["high_contrast", 		    [1, 0.9, -0.002, [0.0, 0.0, 0.0, 0.0], [1.0, 0.6, 0.4, 0.6], [0.199, 0.587, 0.114, 0.0]]], \
                   ["night_blue",		    [1, 1, 0, [0.0, 0.0, 0.0, 0.0], [0.6, 0.6, 1.8, 0.7],  [0.199, 0.587, 0.114, 0.0]]], \
                   ["cold_blue",		    [1, 0.9, -0.002, [0.0, 0.0, 0.0, 0.0], [0.6, 0.6, 1.8, 0.7], [0.199, 0.587, 0.114, 0.0]]], \
                   ["ofp_gamma",		    [1, 1, 0, [0.0, 0.0, 0.0, 0.0], [0.6, 1.4, 0.6, 0.7],  [0.199, 0.587, 0.114, 0.0]]], \
                   ["golden_autumn",		    [1, 1, 0, [0.0, 0.0, 0.0, 0.0], [1.8, 1.8, 0.3, 0.7],  [0.199, 0.587, 0.114, 0.0]]], \
		   ["summer_chernarus", 		    [1, 1, 0, [0, 0, 0, 0], [2, 0, 0, 1.25], [2.5, -2.5, 0, 0]]], \
		   ["movie_day", 		    [1, 1.02, -0.005, [0.0, 0.0, 0.0, 0.0], [1, 0.8, 0.6, 0.65],  [0.199, 0.587, 0.114, 0.0]]], 	\
		   ["dog_vision",		    [1, 0.6, 0, [0, 0, 0, 0], [3, 3, 1, 0.75], [2.5, 2.5, -2.75, 0]]], \
		   ["africa_1", 		    [ 1, 1.3, 0.001, [-0.11, -0.65, -0.76, 0.015], [-5, -1.74, 0.09, 0.86], [-1.14, -0.73, 1.14, -0.09]]], \
		   ["africa_2", 		    [ 1.0, 1.3, 0.001, [-0.15, -0.5, -0.81, 0.002], [-5, -1.74, -0.09, 0.85], [-1.34, -0.83, 0.4, -0.09]]], \
 		   ["africa_3", 		    [ 1, 1, 0.001, [-2.08, -1.55, -1.9, 0.013], [1.69, 0.21, 0.79, 1.64], [-0.21, -1.08, 0.91, -0.09]]], \
		   ["tropical", 		    [ 1, 1, 0.01, [-0.11, -0.65, -0.76, 0.015], [-5, 2.74, 0.09, 0.95], [-1.14, -0.73, 1.14, -0.09]]], \
		   ["ofp_palette", 		    [1, 1, 0, [0, 0, 0, 0], [1, 1, 1.2, 0.85], [1, 1, -2.5, 0]]], 	\
		   ["brown", 		    [0.9, 1, 0, [-2.32, 0.17, 0.71, 0], [1.09, 0.91, 0.66, 0.27], [-1.24, 3.03, 0.37, -1.69]]], \
		   ["blue", 		    [0.9, 1, 0, [-2.32, 0.17, 0.71, 0], [1.09, 0.91, 1.1, 0.27], [-1.24, 3.03, 0.37, -1.69]]], \
		   ["green", 		    [1, 1, 0, [-2.32, 0.17, 0.71, 0], [1.53, 1.26, 0.75, 0.27], [-1.51, 3.56, 0.45, -1.69]]] \
]


DEFCLASS("PostProcessing") ["_self", "_mode"] DO {
	/* Post processing module initialization to named mode (or "random") */
	SUPER("ObjectRoot", _self);
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
