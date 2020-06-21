#pragma once
#include <cstdint>

struct CSignatures {
	char* m_worldPtrSign    = "\x48\x8B\x05\x00\x00\x00\x00\x45\x00\x00\x00\x00\x48\x8B\x48\x08\x48\x85\xC9\x74\x07";
	char* m_worldPtrMask    = "xxx????x????xxxxxxxxx";
	char* m_globalArraySign = "\x4C\x8D\x4D\x08\x48\x8D\x15\x00\x00\x00\x00\x4C\x8B\xC0";
	char* m_globalArrayMask = "xxxxxxx????xxx";
	char* m_blipSign        = "\x48\x8D\x0D\x00\x00\x00\x00\xC6\x44\x24\x00\x00\xE8\x00\x00\x00\x00\xB0\x01";
	char* m_blipMask        = "xxx????xxx??x????xx";
};

struct CVector3 {
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
		char     pad_0000[80]; //0x0000
		CVector3 m_vecCoords; //0x0050
}; //Size: 0x005C

class CNavigation {
	public:
		char     m_pad0000[80]; //0x0000
		CVector3 m_vecCoords; //0x0050
}; //Size: 0x005C

class CCustomShaderEffectVehicle {
	public:
		char   m_pad0000[164]; //0x0000
		int8_t m_btPrimaryBlue; //0x00A4
		int8_t m_btPrimaryGreen; //0x00A5
		int8_t m_btPrimaryRed; //0x00A6
		int8_t m_btPrimaryAlpha; //0x00A7
		int8_t m_btSecondaryBlue; //0x00A8
		int8_t m_btSecondaryGreen; //0x00A9
		int8_t m_btSecondaryRed; //0x00AA
		int8_t m_btSecondaryAlpha; //0x00AB
		char   m_pad00Ac[228]; //0x00AC
}; //Size: 0x0190

class CVehicleColorOptions {
	public:
		char                              m_pad0000[32]; //0x0000
		class CCustomShaderEffectVehicle* m_customShaders; //0x0020
		char                              m_pad0028[96]; //0x0028
}; //Size: 0x0088

class CNetObj {
	public:
		char m_pad0000[328]; //0x0000
}; //Size: 0x0148

class CVehicleType {
	public:
		char    m_pad0000[2312]; //0x0000
		float   m_fBoostCharge; //0x0908
		char    m_pad090C[2424]; //0x090C
		int32_t m_iVehicleAmmo; //0x1284
		char    pad_1288[16]; //0x1288
		int32_t m_iVehicleSave; //0x1298
		char    m_pad129C[428]; //0x129C
}; //Size: 0x1448

class CVehicle {
	public:
		char                        pad_0000[48]; //0x0000
		class CNavigation*          m_pCNavigation; //0x0030
		char                        pad_0038[16]; //0x0038
		class CVehicleColorOptions* m_pCVehicleColorOptions; //0x0048
		char                        pad_0050[68]; //0x0050
		CVector3                    m_vecPosition; //0x0094
		char                        pad_00A0[48]; //0x00A0
		class CNetObj*              m_pCNetObj; //0x00D0
		char                        pad_00D8[32]; //0x00D8
		class CVehicleType*         m_pCVehicleType; //0x00F8
		char                        pad_0100[137]; //0x0100
		bool                        m_godMode; //0x0189
		char                        pad_018A[278]; //0x018A
		float                       m_vehicleHealth1; //0x02A0
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
		char                        pad_08C0[72]; //0x08C0
		float                       m_fBoost; //0x0908
		char                        pad_090C[2424]; //0x090C
		int32_t                     m_iAmmo; //0x1284
		char                        pad_1288[16]; //0x1288
		int32_t                     m_iAmmo2; //0x1298
		char                        pad_129C[34]; //0x129C
}; //Size: 0x12BE

class CPlayerInfo {
	public:
		char     pad_0000[324]; //0x0000
		float    m_fSwimSpeed; //0x0144
		float    m_fRunSpeed; //0x0148
		char     pad_014C[168]; //0x014C
		uint32_t m_frameflags; //0x01F4
		char     pad_01F8[1632]; //0x01F8
		int32_t  m_iWantedLevel; //0x0858
		char     pad_085C[1124]; //0x085C
		float    m_fCurrentStamina; //0x0CC0
		float    m_fMaxStamina; //0x0CC4
		char     pad_0CC8[16]; //0x0CC8
		float    m_fDamageMultiplier; //0x0CD8
		char     pad_0CDC[928]; //0x0CDC
}; //Size: 0x107C

class CAmmo {
	public:
		char     pad_0000[24]; //0x0000
		uint32_t m_currentAmmo; //0x0018
		char     pad_001C[44]; //0x001C
}; //Size: 0x0048

class CPAmmo {
	public:
		class CAmmo* m_ammo; //0x0000
}; //Size: 0x0008

class CAmmoInfo {
	public:
		char          pad_0000[8]; //0x0000
		class CPAmmo* m_ppAmmo; //0x0008
		char          pad_0010[24]; //0x0010
		uint32_t      m_maxAmmo; //0x0028
		char          pad_002C[284]; //0x002C
}; //Size: 0x0148

class CWeaponInfo {
	public:
		char             pad_0000[83]; //0x0000
		uint32_t         m_ammoType; //0x0053
		uint32_t         m_weaponSlot; //0x0057
		char             pad_005B[5]; //0x005B
		class CAmmoInfo* pCAmmoInfo; //0x0060
		char             pad_0068[12]; //0x0068
		float            m_fSpread; //0x0074
		char             pad_0078[52]; //0x0078
		float            m_fBulletMinDamage; //0x00AC
		float            m_fBulletMaxDamage; //0x00B0
		char             pad_00B4[28]; //0x00B4
		float            m_fForce; //0x00D0
		float            m_fForcePed; //0x00D4
		float            m_fForceVehicle; //0x00D8
		float            m_fForceFlying; //0x00DC
		char             pad_00E0[52]; //0x00E0
		float            m_fMuzzleVelocity; //0x0114
		int32_t          m_iBulletsPerShot; //0x0118
		char             pad_011C[12]; //0x011C
		float            m_fVehicleReloadTime; //0x0128
		float            m_fAnimReloadRate; //0x012C
		char             pad_0130[12]; //0x0130
		float            m_fSpinUpTime; //0x013C
		float            m_fSpinTime; //0x0140
		char             pad_0144[300]; //0x0144
		float            m_fLockOnRange; //0x0270
		float            m_fWeaponRange; //0x0274
		char             pad_0278[68]; //0x0278
		float            m_fRecoil; //0x02BC
		char             pad_02C0[2496]; //0x02C0
		float            m_fMeleeDamageMultiplier; //0x0C80
		char             pad_0C84[4]; //0x0C84
}; //Size: 0x0C88

class CPedWeaponManager {
	public:
		char               pad_0000[32]; //0x0000
		class CWeaponInfo* m_weaponInfo; //0x0020
		char               pad_0028[5152]; //0x0028
}; //Size: 0x1448

class CMkAmmo {
	public:
		char    pad_0000[32]; //0x0000
		int64_t m_iAmmo; //0x0020
		char    pad_0028[32]; //0x0028
}; //Size: 0x0048

class CMkInventory {
	public:
		char           pad_0000[56]; //0x0000
		class CMkAmmo* m_pMkPistol; //0x0038
		class CMkAmmo* m_pMkAutoRifle; //0x0040
		class CMkAmmo* m_pMkHeavyRifle; //0x0048
		class CMkAmmo* m_pMkShotgun; //0x0050
		char           pad_0058[48]; //0x0058
}; //Size: 0x0088

class CPedInventory {
	public:
		char                     pad_0000[40]; //0x0000
		class CPedWeaponManager* m_pWeaponManager; //0x0028
		char                     pad_0030[24]; //0x0030
		class CMkInventory*      m_pMkInventory; //0x0048
		char                     pad_0050[56]; //0x0050
}; //Size: 0x0088

class CLocalPlayer {
	public:
		char                 pad_0000[32]; //0x0000
		class CPedModelInfo* m_pCPedModelInfo; //0x0020
		char                 pad_0028[8]; //0x0028
		class CCphInstGta*   m_pCphInstGta; //0x0030
		char                 pad_0038[88]; //0x0038
		CVector3             m_position; //0x0090
		char                 pad_009C[237]; //0x009C
		bool                 m_btGodMode; //0x0189
		char                 pad_018A[246]; //0x018A
		float                m_currentHealth; //0x0280
		char                 pad_0284[28]; //0x0284
		float                m_maxHealth; //0x02A0
		char                 pad_02A4[2692]; //0x02A4
		class CVehicle*      m_currentVehicle; //0x0D28
		char                 pad_0D30[904]; //0x0D30
		class CPlayerInfo*   m_pCPlayerInfo; //0x10B8
		class CPedInventory* m_pedInventory; //0x10C0
		char                 pad_10C8[804]; //0x10C8
		uint8_t              m_dwBeatSeat; //0x13EC
		char                 pad_13ED[195]; //0x13ED
		float                m_armor; //0x14B0
		char                 pad_14B4[242]; //0x14B4
}; //Size: 0x15A6

class CPedFactory {
	public:
		char                pad_0000[8]; //0x0000
		class CLocalPlayer* m_pCLocalPlayer; //0x0008
}; //Size: 0x0010

class CPCWorldMain {
	public:
		class CPedFactory* m_world; //0x0000
}; //Size: 0x0008

class CLastAttackersOnCar {
	public:
		char pad_0000[72]; //0x0000
}; //Size: 0x0048

class CHandlingData {
	public:
		char pad_0000[72]; //0x0000
}; //Size: 0x0048

class Vehicle {
	public:
		char                        pad_0000[48]; //0x0000
		class CNavigation*          m_pCNavigation; //0x0030
		char                        pad_0038[16]; //0x0038
		class CVehicleColorOptions* m_pCVehicleColorOptions; //0x0048
		char                        pad_0050[68]; //0x0050
		CVector3                    m_vecPosition; //0x0094
		char                        pad_00A0[237]; //0x00A0
		bool                        m_godMode; //0x018D
		char                        pad_018E[246]; //0x018E
		float                       m_vehicleHealth1; //0x0284
		char                        pad_0288[36]; //0x0288
		class CLastAttackersOnCar*  m_lastAttackersOnCar; //0x02AC
		char                        pad_02B4[1484]; //0x02B4
		float                       m_vehicleHealth; //0x0880
		char                        pad_0884[40]; //0x0884
		class CHandlingData*        m_vehicleHandling; //0x08AC
		char                        pad_08B4[3]; //0x08B4
		bool                        m_bulletproofTires; //0x08B7
		char                        pad_08B8[356]; //0x08B8
		int32_t                     m_alarmLength; //0x0A1C
		char                        pad_0A20[392]; //0x0A20
		float                       N000029ED; //0x0BA8
		char                        pad_0BAC[1692]; //0x0BAC
}; //Size: 0x1248

class CPCWeaponInfo {
	public:
		char             pad_0000[96]; //0x0000
		class CAmmoInfo* m_ammoInfo; //0x0060
		char             pad_0068[224]; //0x0068
}; //Size: 0x0148

class CBlip {
	public:
		char  pad_0000[32]; //0x0000
		float X; //0x0020
		float Y; //0x0024
}; //Size: 0x0540
