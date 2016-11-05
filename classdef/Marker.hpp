/*
  Marker Class
    :: Marker -> ObjectRoot

  Globals:
    MarkerIndex :: Integer to track count of instantiated markers (for naming)

  Methods:
    __init__ position shape type size :: Create the Marker instance (hidden)
    show                              :: Create and display the game marker
    hide                              :: Remove the game marker from the map
    redraw                            :: If marker is visible, recompose it
    set_alpha alpha                   :: Set configured alpha [and redraw]
    set_brush brush                   :: Set configured brush type [and redraw]
    set_color color                   :: Set configured color [and redraw]
    set_direction direction           :: Set configured direction [and redraw]
    set_position position             :: Set configured position [and redraw]
    set_shape shape                   :: Set configured shape [and redraw]
    set_size size                     :: Set configured size [and redraw]
    set_text text                     :: Set configured text [and redraw]
    set_type type                     :: Set configured type [and redraw]

      This class is an object wrapper for map marker objects (made with the
  createMarker command).  These can be shown/hidden at will, and reconfigured
  on the fly with immediate results if the marker is currently shown.  Each 
  marker is given a unique name by using the value of global variable 
  MarkerIndex and then incrementing it by one.  See the official documentation
  for information on what parameters are supported.  In the initializer, type
  may be passed as nil if drawing an area (i.e. "RECTANGLE", "ELLIPSE") marker.

  Example:
   mkr = ["Marker", position player, "ELLIPSE", nil, [25, 25]] call fnc_new;
   [mkr, "show"] call fnc_tell;
   // This puts a circle of 25m-diameter directly on the player's position in
   //  the map.   
  
   [mkr, "set_color", "ColorGreen"] call fnc_tell;
   // The marker is now green.

*/

MarkerIndex = 0;


DEFCLASS("Marker") ["_self", "_position", "_shape", "_type", "_size"] DO {
	/* Initialize marker parameters with the minimum required info */
	SUPER("ObjectRoot", _self);
	[_self, "_setf", "name",
	 format ["MarkerInstance%1", MarkerIndex]] call fnc_tell;
	MarkerIndex = MarkerIndex + 1;
	[_self, "_setf", "position", _position] call fnc_tell;
	[_self, "_setf", "shape", _shape] call fnc_tell;
	if (not isNil "_type") then {
		[_self, "_setf", "type", _type] call fnc_tell;
	};
	if (not isNil "_size") then {
		[_self, "_setf", "size", _size] call fnc_tell;
	};
        _self
} ENDCLASS;


DEFMETHOD("Marker", "set_alpha") ["_self", "_alpha"] DO {
	/* Configure alpha (opacity) */
	[_self, "_setf", "alpha", _alpha] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_brush") ["_self", "_brush"] DO {
	/* Configure brush (area fill type) */
	[_self, "_setf", "brush", _brush] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_color") ["_self", "_color"] DO {
	/* Configure color (array or Cfg value) */
	[_self, "_setf", "color", _color] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_direction") ["_self", "_direction"] DO {
	/* Set marker orientation (in degrees) */
	[_self, "_setf", "direction", _direction] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_position") ["_self", "_position"] DO {
	/* Set marker position */
	[_self, "_setf", "position", _position] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_shape") ["_self", "_shape"] DO {
	/* Set marker shape (i.e. "RECTANGLE", "ELLIPSE", "ICON") */
	[_self, "_setf", "shape", _shape] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_size") ["_self", "_size"] DO {
	/* Set size [X x Y] */
	[_self, "_setf", "size", _size] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_text") ["_self", "_text"] DO {
	/* Configure marker text */
	[_self, "_setf", "text", _text] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "set_type") ["_self", "_type"] DO {
	/* Configure marker type (i.e. which icon) */
	[_self, "_setf", "type", _type] call fnc_tell;
	[_self, "redraw"] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "redraw") ["_self"] DO {
	/* If shown, hide and then recreate the marker */
	private ["_marker"];
	_marker = [_self, "_getf", "marker"] call fnc_tell;
	if (not isNil "_marker") then {
		[_self, "hide"] call fnc_tell;
		[_self, "show"] call fnc_tell;
	};
} ENDMETHOD;


DEFMETHOD("Marker", "show") ["_self"] DO {
	/* Create the marker using the loaded configuration */
	private ["_marker", "_name", "_position", "_shape", "_type", "_size",
                 "_brush", "_color", "_direction", "_text", "_alpha"];
	_name = [_self, "_getf", "name"] call fnc_tell;
	_position = [_self, "_getf", "position"] call fnc_tell;
	_marker = createMarker [_name, _position];
	_shape = [_self, "_getf", "shape"] call fnc_tell;
	_type = [_self, "_getf", "type"] call fnc_tell;
	_size = [_self, "_getf", "size"] call fnc_tell;
	_brush = [_self, "_getf", "brush"] call fnc_tell;
	_color = [_self, "_getf", "color"] call fnc_tell;
	_direction = [_self, "_getf", "direction"] call fnc_tell;
	_text = [_self, "_getf", "text"] call fnc_tell;
	_alpha = [_self, "_getf", "alpha"] call fnc_tell;
	_marker setMarkerShape _shape;
	if (not isNil "_type") then {
		_marker setMarkerType _type;
	};
	if (not isNil "_size") then {
		_marker setMarkerSize _size;
	};
	if (not isNil "_brush") then {
		_marker setMarkerBrush _brush;
	};
	if (not isNil "_color") then {
		_marker setMarkerColor _color;
	};
	if (not isNil "_direction") then {
		_marker setMarkerDir _direction;
	};
	if (not isNil "_text") then {
		_marker setMarkerText _text;
	};
	if (not isNil "_alpha") then {
		_marker setMarkerAlpha _alpha;
	};
	[_self, "_setf", "marker", _marker] call fnc_tell;
} ENDMETHOD;


DEFMETHOD("Marker", "hide") ["_self"] DO {
	/* Remove marker from the map */
	deleteMarker ([_self, "_getf", "name"] call fnc_tell);
	[_self, "_setf", "marker", nil] call fnc_tell;
} ENDMETHOD;
