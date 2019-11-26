
/**************
  DIALOG SETUP:
 **************/
[] spawn {
  // Initialize dialog contents:
  waitUntil {alive player};
  call compile preprocessfile "misc\asinc\initDialogs.sqf";
};

[] spawn {
  // Conversation drivers:
  fnc_talk = compile preprocessfile "misc\asinc\talk.sqf";
  fnc_text = compile preprocessfile "misc\asinc\text.sqf";
  
  // Dialog retrieval helper:
  fnc_getText = compile preprocessfile "misc\asinc\getText.sqf";
  
  // Interaction handler:
  fnc_diagAct = compile preprocessfile "misc\asinc\diagAct.sqf";
  
};

DialogOpen = false;
SelectionClick = false;