#ifndef __VECTOOLS_H__
#define __VECTOOLS_H__
fnc_sorted = compile preprocessfile "core\vectools\fnc_sorted.sqf";
fnc_subseq = compile preprocessfile "core\vectools\fnc_subseq.sqf";
fnc_range = compile preprocessfile "core\vectools\fnc_range.sqf";
fnc_zip = compile preprocessfile "core\vectools\fnc_zip.sqf";
fnc_enumerate = compile preprocessfile "core\vectools\fnc_enumerate.sqf";
fnc_homogenize = compile preprocessfile "core\vectools\fnc_homogenize.sqf";
fnc_dehomogenize = compile preprocessfile "core\vectools\fnc_dehomogenize.sqf";
fnc_neighbors = compile preprocessfile "core\vectools\fnc_neighbors.sqf";
fnc_closest = compile preprocessfile "core\vectools\fnc_closest.sqf";
fnc_collect_sequence = compile preProcessFile "core\vectools\fnc_collect_sequence.sqf";

fnc_vector_mean = {
	/* Find the mean vector of a list of vectors */
	_vectors = _this;
	private ["_alen", "_component", "_mean"];
	_mean = [];
	_alen = count _vectors;
	for "_i" from 0 to 2 do {
		_component = 0;
		for "_j" from 0 to (_alen - 1) do {
			_component = _component +
				(((_vectors select _j) select _i) / _alen);
		};
		_mean pushBack _component;
	};
	_mean
};

#endif
