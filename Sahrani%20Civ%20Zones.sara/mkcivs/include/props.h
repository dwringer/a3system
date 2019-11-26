#ifndef __MKCIVS_PROPS_H__
#define __MKCIVS_PROPS_H__
#define HE_BOMB_A "R_PG32V_F"

#define AP_BOMB_A "Sh_120mm_APFSDS"

#define SMOKE_BOMB_A "F_40mm_White"

#define AP_BULLET_A "B_127x108_APDS"

#define WEAPON_A """arifle_MXM_F"""
#define AMMO_A """20Rnd_762x45_mag"""
#define WEAPON_B """arifle_Katiba_F"""
#define AMMO_B """30Rnd_65x39_caseless_green"""

#define ASSAULT_RIFLES  ["arifle_Katiba_F",  \
			 "arifle_MXM_F",  \
			 "arifle_AKM_F",  \
			 "arifle_AKS_F"]

#define MACHINE_GUNS ["LMG_Zafir_F"]

#define SMALL_ARMS  (ASSAULT_RIFLES + MACHINE_GUNS)

#define CUP_SMALL_ARMS (ASSAULT_RIFLES + MACHINE_GUNS + ["CUP_launch_RPG18"])

#define CIVILIANS ["C_man_polo_1_F",  \
		   "C_man_polo_2_F",  \
		   "C_man_polo_3_F",  \
		   "C_man_polo_4_F",  \
		   "C_man_polo_5_F",  \
		   "C_man_polo_6_F",  \
		   "C_man_p_beggar_F",  \
		   "C_man_w_worker_F",  \
		   "C_man_hunter_1_F",  \
		   "C_man_sport_1_F",  \
		   "C_man_sport_2_F",  \
		   "C_man_sport_3_F",  \
		   "C_Man_casual_1_F",  \
		   "C_Man_casual_2_F",  \
		   "C_Man_casual_3_F",  \
		   "C_Man_casual_4_F",  \
		   "C_Man_casual_5_F",  \
		   "C_Man_casual_6_F"]

#define CUP_CIVILIANS ["CUP_C_C_Citizen_01",  \
		       "CUP_C_C_Citizen_02",  \
		       "CUP_C_C_Citizen_03",  \
		       "CUP_C_C_Citizen_04",  \
		       "CUP_C_C_Villager_01",  \
		       "CUP_C_C_Villager_02",  \
		       "CUP_C_C_Villager_03",  \
		       "CUP_C_C_Villager_04",  \
		       "CUP_C_C_Woodlander_01",  \
		       "CUP_C_C_Woodlander_02",  \
		       "CUP_C_C_Woodlander_03",  \
		       "CUP_C_C_Woodlander_04",  \
		       "CUP_C_C_Worker_01",  \
		       "CUP_C_C_Worker_02",  \
		       "CUP_C_C_Worker_03",  \
		       "CUP_C_C_Worker_04",  \
		       "CUP_C_C_Worker_05",  \
		       "CUP_C_C_Profiteer_01", \
		       "CUP_C_C_Profiteer_02", \
		       "CUP_C_C_Profiteer_03", \
		       "CUP_C_C_Profiteer_04", \
		       "CUP_C_C_Priest_01", \
		       "CUP_C_C_Doctor_01", \
		       "CUP_C_C_Schoolteacher_01", \
		       "CUP_C_C_Assistant_01", \
		       "CUP_C_C_Rocker_01", \
		       "CUP_C_C_Rocker_02", \
		       "CUP_C_C_Rocker_03", \
		       "CUP_C_C_Rocker_04", \
       		       "CUP_C_C_Mechanic_01", \
       		       "CUP_C_C_Mechanic_02", \
       		       "CUP_C_C_Mechanic_03"]

#endif
