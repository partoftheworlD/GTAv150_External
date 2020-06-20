#pragma once

struct CSignatures {
	char* m_worldPtrSign    = "\x48\x8B\x05\x00\x00\x00\x00\x45\x00\x00\x00\x00\x48\x8B\x48\x08\x48\x85\xC9\x74\x07";
	char* m_worldPtrMask    = "xxx????x????xxxxxxxxx";
	char* m_globalArraySign = "\x4C\x8D\x4D\x08\x48\x8D\x15\x00\x00\x00\x00\x4C\x8B\xC0";
	char* m_globalArrayMask = "xxxxxxx????xxx";
	char* m_blipSign        = "\x48\x8D\x0D\x00\x00\x00\x00\xC6\x44\x24\x00\x00\xE8\x00\x00\x00\x00\xB0\x01";
	char* m_blipMask        = "xxx????xxx??x????xx";
};

struct Vector3 {
	float x;
	float y;
	float z;
};

class CPedModelInfo {
	public:
		char pad_0000[8]; //0x0000
}; //Size: 0x0008

class CCphInstGta {
	public:
		char    pad_0000[80]; //0x0000
		Vector3 m_vecCoords; //0x0050
}; //Size: 0x005C

class CNavigation {
	public:
		char    pad_0000[80]; //0x0000
		Vector3 m_vecCoords; //0x0050
}; //Size: 0x005C

class CCustomShaderEffectVehicle {
	public:
		char pad_0000[164]; //0x0000
		BYTE btPrimaryBlue; //0x00A4
		BYTE btPrimaryGreen; //0x00A5
		BYTE btPrimaryRed; //0x00A6
		BYTE btPrimaryAlpha; //0x00A7
		BYTE btSecondaryBlue; //0x00A8
		BYTE btSecondaryGreen; //0x00A9
		BYTE btSecondaryRed; //0x00AA
		BYTE btSecondaryAlpha; //0x00AB
}; //Size: 0x0190

class CVehicleType {
	public:
		char  pad_0000[2312]; //0x0000
		float m_fBoostCharge; //0x0908
		char  pad_090C[2424]; //0x090C
		int   iVehicleAmmo; //0x1284
		char  pad_1288[16]; //0x1288
		int   iVehicleSave; //0x1298
}; //Size: 0x1448

class CVehicle {
	public:
		char                        pad_0000[48]; //0x0000
		class CNavigation*          pCNavigation; //0x0030
		char                        pad_0038[16]; //0x0038
		class CVehicleColorOptions* pCVehicleColorOptions; //0x0048
		char                        pad_0050[68]; //0x0050
		Vector3                     vecPosition; //0x0094
		char                        pad_00A0[48]; //0x00A0
		class CNetObj*              pCNetObj; //0x00D0
		char                        pad_00D8[32]; //0x00D8
		class CVehicleType*         pCVehicleType; //0x00F8
		char                        pad_0100[137]; //0x0100
		bool                        God_Mode; //0x0189
		char                        pad_018A[278]; //0x018A
		float                       Vehicle_health_1; //0x02A0
		char                        pad_02A4[1424]; //0x02A4
		float                       N000011A6; //0x0834
		float                       Gas_engine_stats_0; //0x0838
		char                        pad_083C[60]; //0x083C
		float                       m_fBackwardMovements; //0x0878
		float                       m_fForwardMovements; //0x087C
		char                        pad_0880[36]; //0x0880
		float                       m_fAcceleration; //0x08A4
		float                       m_fMinSpeed; //0x08A8
		float                       m_fMaxSpeed; //0x08AC
		float                       m_fGasValue0; //0x08B0
		float                       m_fGasValue1; //0x08B4
		char                        pad_08B8[4]; //0x08B8
		float                       m_fGasValue2; //0x08BC
};

class CPlayerInfo {
	public:
		char         pad_0000[324]; //0x0000
		float        Swim_speed; //0x0144
		float        Run_speed; //0x0148
		char         pad_014C[168]; //0x014C
		unsigned int FRAMEFLAGS; //0x01F4
		char         pad_01F8[1632]; //0x01F8
		int          Wanted_Level; //0x0858
		char         pad_085C[1124]; //0x085C
		float        Current_Stamina; //0x0CC0
		float        Max_Stamina; //0x0CC4
		char         pad_0CC8[16]; //0x0CC8
		float        DamageMultiplier; //0x0CD8
}; //Size: 0x107C

class Ammo {
	public:
		char         pad_0000[24]; //0x0000
		unsigned int Current_Ammo; //0x0018
}; //Size: 0x0048

class pAmmo {
	public:
		class Ammo* pAmmo; //0x0000
}; //Size: 0x0048

class CAmmoInfo {
	public:
		char         pad_0000[8]; //0x0000
		class pAmmo* ppAmmo; //0x0008
		char         pad_0010[24]; //0x0010
		unsigned int Max_Ammo; //0x0028
}; //Size: 0x0148

class CWeaponInfo {
	public:
		char             pad_0000[83]; //0x0000
		unsigned int     Ammo_type; //0x0053
		unsigned int     Weapon_Slot; //0x0057
		char             pad_005B[5]; //0x005B
		class CAmmoInfo* pCAmmoInfo; //0x0060
		char             pad_0068[12]; //0x0068
		float            Spread; //0x0074
		char             pad_0078[52]; //0x0078
		float            Bullet_MINDamage; //0x00AC
		float            Bullet_MAXDamage; //0x00B0
		char             pad_00B4[28]; //0x00B4
		float            Force; //0x00D0
		float            Force_Ped; //0x00D4
		float            Force_Vehicle; //0x00D8
		float            Force_Flying; //0x00DC
		char             pad_00E0[52]; //0x00E0
		float            Muzzle_Velocity; //0x0114
		int              Bullets_per_shot; //0x0118
		char             pad_011C[12]; //0x011C
		float            Vehicle_ReloadTime; //0x0128
		float            Anim_ReloadRate; //0x012C
		char             pad_0130[12]; //0x0130
		float            SpinUpTime; //0x013C
		float            SpinTime; //0x0140
		char             pad_0144[300]; //0x0144
		float            LockOnRange; //0x0270
		float            WeaponRange; //0x0274
		char             pad_0278[68]; //0x0278
		float            Recoil; //0x02BC
		char             pad_02C0[2496]; //0x02C0
		float            MeleeDamageMultiplier; //0x0C80
}; //Size: 0x0C88

class CPedWeaponManager {
	public:
		char               pad_0000[32]; //0x0000
		class CWeaponInfo* pWeaponInfo; //0x0020
}; //Size: 0x0448

class CLocalPlayer {
	public:
		char                     pad_0000[32]; //0x0000
		class CPedModelInfo*     pCPedModelInfo; //0x0020
		char                     pad_0028[8]; //0x0028
		class CCphInstGta*       pCphInstGta; //0x0030
		char                     pad_0038[88]; //0x0038
		Vector3                  Position; //0x0090
		char                     pad_009C[237]; //0x009C
		bool                     btGodMode; //0x0189
		char                     pad_018A[246]; //0x018A
		float                    Current_Health; //0x0280
		char                     pad_0284[28]; //0x0284
		float                    Max_Health; //0x02A0
		char                     pad_02A4[2692]; //0x02A4
		class CVehicle*          Current_Vehicle; //0x0D28
		char                     pad_0D30[904]; //0x0D30
		class CPlayerInfo*       pCPlayerInfo; //0x10B8
		class PedInventory*      CPedInventory; //0x10C0
		class CPedWeaponManager* pCPedWeaponManager; //0x10C8
		char                     pad_10D0[796]; //0x10D0
		BYTE                     dwBeatSeat; //0x13EC
		char                     pad_13ED[195]; //0x13ED
		float                    Armor; //0x14B0
}; //Size: 0x15A6

class CPedFactory {
	public:
		char                pad_0000[8]; //0x0000
		class CLocalPlayer* pCLocalPlayer; //0x0008
}; //Size: 0x0010

class pCWorldMain {
	public:
		class CPedFactory* CWorld; //0x0000
}; //Size: 0x0008

class Vehicle {
	public:
		char                          pad_0000[48]; //0x0000
		class CNavigation*            pCNavigation; //0x0030
		char                          pad_0038[16]; //0x0038
		class CVehicleColorOptions*   pCVehicleColorOptions; //0x0048
		char                          pad_0050[68]; //0x0050
		Vector3                       vecPosition; //0x0094
		char                          pad_00A0[237]; //0x00A0
		bool                          God_Mode; //0x018D
		char                          pad_018E[246]; //0x018E
		float                         Vehicle_health_1; //0x0284
		char                          pad_0288[36]; //0x0288
		class CLast_attackers_on_car* Last_attackers_on_car; //0x02AC
		char                          pad_02B4[1484]; //0x02B4
		float                         Vehicle_health; //0x0880
		char                          pad_0884[40]; //0x0884
		class CHandlingData*          CVehicleHandling; //0x08AC
		char                          pad_08B4[3]; //0x08B4
		bool                          BulletproofTires; //0x08B7
		char                          pad_08B8[356]; //0x08B8
		int                           Alarm_length; //0x0A1C
		char                          pad_0A20[392]; //0x0A20
		float                         N000029ED; //0x0BA8
}; //Size: 0x1248

class CVehicleColorOptions {
	public:
		char                              pad_0000[32]; //0x0000
		class CCustomShaderEffectVehicle* CustomColor; //0x0020
}; //Size: 0x0048

class CHandlingData {
	public:
		char  pad_0000[144]; //0x0000
		float TRACTION_CURVE_MIN; //0x0090
		char  pad_0094[40]; //0x0094
		float SUSPENSION_FORCE; //0x00BC
		char  pad_00C0[40]; //0x00C0
		float Deform_multiplier; //0x00E8
		float N00001F7F; //0x00EC
}; //Size: 0x0C48

class CBlip {
	public:
		char  pad_0000[32]; //0x0000
		float X; //0x0020
		float Y; //0x0024
}; //Size: 0x0540
