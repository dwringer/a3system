#ifndef __MKCIVS_PROPS_H__
#define __MKCIVS_PROPS_H__
#define HE_BOMB_A "M_Zephyr"

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

#define CIVILIANS ["C_man_polo_1_F",  \
		   "C_man_polo_2_F",  \
		   "C_man_polo_3_F",  \
		   "C_man_polo_4_F",  \
		   "C_man_polo_5_F",  \
		   "C_man_polo_6_F"]
#endif
