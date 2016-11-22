#define TEXT(STATE,WORDS)  \
        setVariable [format ["dialogText%1", STATE], WORDS]
#define RESP(STATE,NUM,WORDS)  \
        setvariable [format ["dialogResp%1%2", STATE, NUM], WORDS]
#define ACT(STATE,NUM,DEST)  \
        setvariable [format ["dialogAct%1%2", STATE, NUM], [DEST, ""]]
#define INIT(MAN, NAME, STATE)  \
        _nil = MAN execVM "misc\asinc\dialogEnable.sqf";  \
        MAN setVariable ["dialogState", STATE];  \
        MAN setVariable ["dialogStart", STATE];  \
        MAN setVariable ["dialogName", NAME]
#define INIT_AS(AS, MAN)  \
        _nil = [MAN, AS] execVM "misc\asinc\dialogEnable.sqf"
#define STEADY_STATE(MAN, STATE)  \
        MAN ACT(STATE, 1, STATE);  \
        MAN ACT(STATE, 2, STATE);  \
        MAN ACT(STATE, 3, STATE)

/*
INIT(cman, "Crewman", "AA");
#define CMAN_AA "Hey man, how's it going?"
cman TEXT("AA", CMAN_AA);
STEADY_STATE(cman, "AA");

INIT_AS(cman, cman_1);
*/

/*
AirportGuard setVariable ["dialogState", "AA"];
AirportGuard setVariable ["dialogStart", "AA"];
AirportGuard setVariable ["dialogName", "Guard"];
_ra = ["You got questions; talk to the Sergeant.","Get out of my face, pussy.","Get lost.","Fuck off, douchebag.","Hey man, you got any smokes?"];
AirportGuard setVariable ["dialogTextAA", _ra];
AirportGuard ACT("AA",1,"AA");
AirportGuard ACT("AA",2,"AA");
AirportGuard ACT("AA",3,"AA");

g1 setVariable ["dialogName", "Guard"];
g1 TEXT("Z","Watch yourself while you're here.  Don't even think of trying anything.");

AirportGuard_1 setVariable ["dialogState", "AA"];
AirportGuard_1 setVariable ["dialogStart", "AA"];
AirportGuard_1 setVariable ["dialogName", "Guard"];
_ra = ["Hey man!", "God, it's hot out here.", """Join the Guard,"" they said. ""Be all you can be,"" they said.","You got questions; talk to the Sergeant.","Hey man, you got any smokes?"];
AirportGuard_1 setVariable ["dialogTextAA", _ra];
AirportGuard_1 ACT("AA",1,"AA");
AirportGuard_1 ACT("AA",2,"AA");
AirportGuard_1 ACT("AA",3,"AA");


sarge setVariable ["dialogState", "AA"];
sarge setVariable ["dialogStart", "AA"];
sarge setVariable ["dialogName", "Sgt. Hartman"];
sarge setVariable ["dialogTextAA", ["Get out of my face, dirtbag!", "Is there a problem, maggot?", "Get your filthy pedestrian boots off of my taxiway!"]];
_rsp = "What's going on here? Why is this place under guard?";
sarge RESP("AA",1,_rsp);
sarge ACT("AA",1,"AB");
_rsp = "Your people should go back where you came from, pig!";
sarge RESP("AA",2,_rsp);
sarge ACT("AA",2,"AC");
sarge ACT("AA",3,"AA");


_rsp = "Well, some dickheads down the road thought it would send a nice message if they shot up a truck full of medical supplies as it was leaving this airfield.  Turns out there were some American journalists on board, so when Washington found out the only logical choice was an armed incursion.  <1,2,3: Continue...>";
sarge TEXT("AB",_rsp);
sarge ACT("AB",1,"AB_1");
sarge ACT("AB",2,"AB_1");
sarge ACT("AB",3,"AB_1");

sarge TEXT("AB_1","< . . . >");
_rsp = "Well, your people should go back where you came from, pig!";
sarge RESP("AB_1",1,_rsp);
sarge ACT("AB_1",1,"AC");
_rsp = "I see. Well, don't let me get in your way.";
sarge RESP("AB_1",2,_rsp);
sarge ACT("AB_1",2,"AD");

_rsp = "Are you sure you really want to be talking to me like that here, boy?";
sarge TEXT("AC",_rsp);
_rsp = "Ah, go fuck yourself, Gomer Pyle.";
sarge RESP("AC",1,_rsp);
sarge setVariable["dialogActAC1", ["AF", 
  "player addrating -10000;
   closeDialog 0;"
]];
_rsp = "Sorry. Well, don't let me get in your way.";
sarge RESP("AC",2,_rsp);
sarge ACT("AC",2,"AD");
sarge ACT("AC",3,"AC");

_rsp = "Don't worry about that, I won't.";
sarge TEXT("AD", _rsp);
sarge ACT("AD",1,"AD");
sarge ACT("AD",2,"AD");
sarge ACT("AD",3,"AD");
*/