#include "Memory.h"

DWORD64 GLOBAL_STRUCT = 0;

DWORD64 CMemory::m_getHiddenStruct(const DWORD64 index) {
	DWORD64 newGlobalPageBase = 0;

	ReadProcessMemory(m_hProcess, reinterpret_cast<PBYTE*>(GLOBAL_STRUCT + ((index >> 18 & 0x3F) << 3)), &newGlobalPageBase, sizeof newGlobalPageBase, nullptr);
	if (newGlobalPageBase != 0) {
		return newGlobalPageBase + ((index & 0x3FFFF) << 3);
	}
	return 0;
}

void CMemory::m_updateSignatures() {
	auto basePtr  = 0;
	auto worldPtr = 0;

	const auto worldPtrAddr = m_findSignature<DWORD64>(m_hProcess, reinterpret_cast<DWORD64>(m_mi.lpBaseOfDll), static_cast<DWORD>(m_mi.SizeOfImage),
													   reinterpret_cast<BYTE*>(this->m_worldPtrSign), this->m_worldPtrMask) + 3;
	const auto arrayOfStructs = m_findSignature<DWORD64>(m_hProcess, reinterpret_cast<DWORD64>(m_mi.lpBaseOfDll), static_cast<DWORD>(m_mi.SizeOfImage),
														 reinterpret_cast<BYTE*>(this->m_globalArraySign), this->m_globalArrayMask) + 7;
	const auto blip = m_findSignature<DWORD64>(m_hProcess, reinterpret_cast<DWORD64>(m_mi.lpBaseOfDll), static_cast<DWORD>(m_mi.SizeOfImage),
											   reinterpret_cast<BYTE*>(this->m_blipSign), this->m_blipMask) + 3;
	if (worldPtrAddr) {
		ReadProcessMemory(m_hProcess, reinterpret_cast<PBYTE*>(worldPtrAddr), &worldPtr, sizeof(DWORD64), nullptr);
		printf("-> CWorldAddr 0x%llX Delta bytes 0x%X\n", worldPtrAddr - 3, worldPtr);
		auto buffer = worldPtrAddr + worldPtr + 4;
		printf("-> pCWorld 0x%llX \n", buffer);
		this->m_pWorld = buffer;
		buffer -= reinterpret_cast<DWORD64>(m_mi.lpBaseOfDll);
		printf("-> RVA CWorld	0x%llX\n", buffer);
		ReadProcessMemory(m_hProcess, reinterpret_cast<PBYTE*>(this->m_pWorld), &this->m_pWorld, sizeof this->m_pWorld, nullptr);
		ReadProcessMemory(m_hProcess, reinterpret_cast<PBYTE*>(this->m_pWorld + 0x8), &this->m_player, sizeof this->m_player, nullptr);
		printf("-> CPed 0x%llX\n", this->m_player);
	}
	if (arrayOfStructs) {
		ReadProcessMemory(m_hProcess, reinterpret_cast<PBYTE*>(arrayOfStructs), &basePtr, sizeof(DWORD64), nullptr);
		const auto buf = arrayOfStructs + basePtr + 4;
		printf("-> GArray 0x%llX\n", buf);
		GLOBAL_STRUCT = buf;
	}
	if (blip) {
		ReadProcessMemory(m_hProcess, reinterpret_cast<PBYTE*>(blip), &basePtr, sizeof(DWORD64), nullptr);
		const auto buf = blip + basePtr + 4;
		printf("-> CBlip 0x%llX \n", buf);
		m_cBlip = buf;
	}
	this->m_threads();
}

int CMemory::m_getListProcesses() {
	DWORD processList[1024];
	DWORD cbNeeded;

	if (!K32EnumProcesses(processList, sizeof processList, &cbNeeded)) {
		return 1;
	}
	for (unsigned int i = 0; i < cbNeeded / sizeof(DWORD); i++) {
		if (processList[i] != 0) {
			m_getProcessByName(processList[i], "GTA5.exe");
		}
	}
	return 0;
}

int CMemory::m_getProcessByName(const DWORD pId, char* processName) {
	this->m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_ALL_ACCESS, FALSE, pId);
	if (this->m_hProcess && K32EnumProcessModules(this->m_hProcess, &this->m_hMod, sizeof this->m_hMod, &m_needed)) {
		K32GetModuleBaseNameA(this->m_hProcess, this->m_hMod, m_processName, sizeof m_processName / sizeof(char));
	}
	if (this->m_hProcess && !strcmp(m_processName, processName) && K32EnumProcessModules(this->m_hProcess, this->m_modulesList, sizeof this->m_modulesList,
																						 &this->m_neededMods)) {
		for (unsigned int i = 0; i < this->m_neededMods / sizeof(HMODULE); ++i) {
			if (this->m_hProcess && K32GetModuleBaseNameA(this->m_hProcess, this->m_modulesList[i], this->m_moduleName,
														  sizeof this->m_moduleName / sizeof DWORD64) && !strcmp(this->m_moduleName, processName)) {
				K32GetModuleInformation(this->m_hProcess, this->m_modulesList[i], &this->m_mi, sizeof(MODULEINFO));
				printf("Module: %s BaseAddress:0x%p Size:0x%lX\n", this->m_moduleName, this->m_mi.lpBaseOfDll, this->m_mi.SizeOfImage);
				this->m_updateSignatures();
			}
		}
	}
	return 0;
}

template <typename function_type, typename vector_type>
function_type CMemory::m_readMemory(const HANDLE hProcess, function_type Address, std::vector<vector_type> offsets) {
	function_type tmp = Address;
	for (function_type i : offsets) {
		ReadProcessMemory(hProcess, reinterpret_cast<PBYTE*>(tmp + i), &tmp, sizeof(function_type), nullptr);
	}
	return tmp;
}

template <typename function_type, typename return_type>
return_type CMemory::m_readMemory(const HANDLE hProcess, function_type Address) {
	return_type tmp = 0;
	ReadProcessMemory(hProcess, reinterpret_cast<PBYTE*>(Address), &tmp, sizeof(return_type), nullptr);
	return tmp;
}

template <typename function_type, typename vector_type, typename return_type>
return_type CMemory::m_readMemory(const HANDLE hProcess, function_type Address, std::vector<vector_type> offsets) {
	function_type tmp = Address;
	for (function_type i : offsets) {
		ReadProcessMemory(hProcess, reinterpret_cast<PBYTE*>(tmp + i), &tmp, sizeof(return_type), nullptr);
	}
	return tmp;
}

template <typename function_type>
function_type CMemory::m_readMemory(HANDLE const hProcess, function_type Address) {
	function_type tmp = 0;
	ReadProcessMemory(hProcess, reinterpret_cast<PBYTE*>(Address), &tmp, sizeof(function_type), nullptr);
	return tmp;
}

template <typename function_type, typename buffer_type>
void CMemory::m_writeMemory(HANDLE const hProcess, function_type Address, buffer_type buffer) {
	WriteProcessMemory(hProcess, reinterpret_cast<PBYTE*>(Address), &buffer, sizeof(buffer_type), nullptr);
}

bool CMemory::m_dataCompare(BYTE* data, BYTE* sign, char* mask) {
	for (; *mask; mask++, sign++, data++) {
		if (*mask == 'x' && *data != *sign) {
			return false;
		}
	}
	return true;
}

template <typename type>
type CMemory::m_findSignature(const HANDLE hProcess, type base, const DWORD size, BYTE* sign, char* mask) {
	MEMORY_BASIC_INFORMATION mbi    = {};
	DWORD64                  offset = 0;

	while (offset < size) {
		VirtualQueryEx(hProcess, reinterpret_cast<LPCVOID>(base + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE) {
			auto* const buffer = new BYTE[mbi.RegionSize];
			ReadProcessMemory(hProcess, mbi.BaseAddress, buffer, mbi.RegionSize, nullptr);
			for (size_t i = 0; i < mbi.RegionSize; i++) {
				if (m_dataCompare(buffer + i, sign, mask)) {
					delete[] buffer;
					return reinterpret_cast<DWORD64>(mbi.BaseAddress) + i;
				}
			}
		}
		offset += mbi.RegionSize;
	}
	return 0;
}

void CMemory::m_tunables() {
	std::vector<DWORD> ammo_ptr    = {0x20, 0x60, 0x8, 0x0};
	auto               value       = 1234123123;
	auto               localPlayer = reinterpret_cast<CLocalPlayer*>(this->m_player);
	auto               pInventory  = this->m_readMemory<DWORD64, CPedInventory*>(m_hProcess, reinterpret_cast<DWORD64>(&localPlayer->m_pedInventory));
	while (TRUE) {

		// Ammo Box (regular)
		auto Weapons = this->m_readMemory<DWORD64, CPedWeaponManager*>(m_hProcess, reinterpret_cast<DWORD64>(&pInventory->m_pWeaponManager));
		auto pAmmo   = reinterpret_cast<CAmmo*>(this->m_readMemory<DWORD64, DWORD>(m_hProcess, reinterpret_cast<DWORD64>(&Weapons), ammo_ptr));
		this->m_writeMemory<DWORD64, int>(m_hProcess, reinterpret_cast<DWORD64>(&pAmmo->m_currentAmmo), m_iAmmo);

		// MK2
		auto MKWeapons = this->m_readMemory<DWORD64, CMkInventory*>(m_hProcess, reinterpret_cast<DWORD64>(&pInventory->m_pMkInventory));
		for (auto i = 0; i < 20; i++) {
			auto mkAmmo = this->m_readMemory<DWORD64>(m_hProcess, reinterpret_cast<DWORD64>(MKWeapons) + i * 8);
			if (mkAmmo != -1) {
				this->m_writeMemory<DWORD64, int>(m_hProcess, reinterpret_cast<DWORD64>(&reinterpret_cast<CMkAmmo*>(mkAmmo)->m_iAmmo), m_iAmmo);
			}

		}
		// Anti-afk
		this->m_writeMemory(m_hProcess, this->m_getHiddenStruct(0x40001 + 0x57), &value);
		// I/E cooldown
		this->m_writeMemory<DWORD64, int>(m_hProcess, this->m_getHiddenStruct(0x2649C2), m_ieCooldown);
		// Mechanic cooldown Global_25615B.f_10D6.f_13E.f_8
		this->m_writeMemory<DWORD64, int>(m_hProcess, this->m_getHiddenStruct(0x25615B + 0x10D6 + 0x13E + 0x8), m_ieCooldown);
		// Vip mission cooldown
		this->m_writeMemory<DWORD64, int>(m_hProcess, this->m_getHiddenStruct(0x40001 + 0x3AA4), m_ieCooldown);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void CMemory::m_unlocker() {
	std::vector<DWORD> offsets = {
			0x1FB2, 0x1FB3, 0x1FB4, 0x1FB5, 0x1FB6, 0x1FB7, 0x1FB8, 0x1FB9, 0x1FBA, 0x1FBB, 0x1FBC, 0x1FBD, 0x1FBE, 0x1FC0, 0x1FC7, 0x1FC8, 0x1FC9, 0x2210,
			0x2316, 0x2317, 0x2318, 0x3035, 0x3036, 0x3037, 0x3038, 0x5967, 0x5968, 0x5969, 0x596A, 0x596B, 0x596C, 0x596D, 0x596E, 0x596F, 0x5981, 0x5982,
			0x5983, 0x5984, 0x5C83, 0x6150, 0x6193, 0x6194, 0x6195, 0x6197, 0x6198, 0x6199, 0x619A, 0x699D, 0x699E, 0x699F, 0x6B42, 0x6B45, 0x6B46, 0x6B47,
			0x6B48, 0x6B49, 0x6B4A, 0x6B4B, 0x6B4C, 0x6B4D, 0x6B4E, 0x6B4F, 0x6B50, 0x6B51, 0x6B52, 0x6B53, 0x6B54, 0x6B55, 0x6B56, 0x6B57, 0x6B58, 0x6C65,
			0x6C68, 0x6C69, 0x6C6A, 0x6C6B, 0x6C6E, 0x6C6F, 0x6C70, 0x6C71, 0x6C76, 0x6C8F, 0x6C92, 0x6C97, 0x6C99, 0x6CB0, 0x6CB1, 0x6CB2, 0x6CB3, 0x6CB4
			};
	for (auto i : offsets) {
		this->m_writeMemory<DWORD64, bool>(m_hProcess, this->m_getHiddenStruct(static_cast<DWORD64>(0x40001) + i), true);
	}
}

void CMemory::m_opressorAmmo() {
	const auto ammo  = 20;
	const auto boost = 3.f;
	while (TRUE) {
		auto* const pPlayer  = reinterpret_cast<CLocalPlayer*>(this->m_player);
		auto* const pVehicle = this->m_readMemory<DWORD64, CVehicle*>(m_hProcess, reinterpret_cast<DWORD64>(&pPlayer->m_currentVehicle));
		auto* const pVehSpec = this->m_readMemory<DWORD64, CVehicleType*>(m_hProcess, reinterpret_cast<DWORD64>(&pVehicle->m_pCVehicleType));

		if (pVehicle) {
			this->m_writeMemory<DWORD64, int>(m_hProcess, reinterpret_cast<DWORD64>(&pVehSpec->m_iVehicleAmmo), ammo);
			this->m_writeMemory<DWORD64, int>(m_hProcess, reinterpret_cast<DWORD64>(&pVehSpec->m_iVehicleSave), ammo);
			this->m_writeMemory<DWORD64, float>(m_hProcess, reinterpret_cast<DWORD64>(&pVehSpec->m_fBoostCharge), boost);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void CMemory::m_money() {
	const auto activator = this->m_getHiddenStruct(0x2643C8 + 0x1A);
	const auto setMoney  = this->m_getHiddenStruct(0x2643C8 + 0x1C);
	while (TRUE) {
		if (m_inputs[EMONEY] & 0x1) {
			for (auto i = 0; i <= 1; i++) {
				this->m_writeMemory<DWORD64, int>(m_hProcess, setMoney, m_moneyValue);
				this->m_writeMemory<DWORD64, bool>(m_hProcess, activator, TRUE);

				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				this->m_writeMemory<DWORD64, bool>(m_hProcess, activator, FALSE);
				this->m_writeMemory<DWORD64, int>(m_hProcess, setMoney, m_resetMoney);
			}
			std::this_thread::sleep_for(std::chrono::minutes(3));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void CMemory::m_orbitalMoney() {
	const auto activator = this->m_getHiddenStruct(0x171A3D);
	while (TRUE) {
		if (m_inputs[EORBIT] & 0x1) {
			for (auto i = 1; i <= 2; i++) {
				this->m_writeMemory<DWORD64, int>(this->m_hProcess, activator, i);
				std::this_thread::sleep_for(std::chrono::seconds(5));
			}
			std::this_thread::sleep_for(std::chrono::seconds(15));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void CMemory::m_teleportPlayer() {
	CVector3 blip{};
	while (TRUE) {
		const auto teleportPlayerState = GetKeyState(VK_F3) & 0x8000;
		if (teleportPlayerState) {
			auto* const pPlayer       = reinterpret_cast<CLocalPlayer*>(this->m_player);
			auto* const pPlayerCoords = this->m_readMemory<DWORD64, CCphInstGta*>(m_hProcess, reinterpret_cast<DWORD64>(&pPlayer->m_pCphInstGta));
			auto* const Blip          = reinterpret_cast<CBlip*>(this->m_cBlip);
			blip.x                    = this->m_readMemory<DWORD64, float>(m_hProcess, reinterpret_cast<DWORD64>(&Blip->X));
			blip.y                    = this->m_readMemory<DWORD64, float>(m_hProcess, reinterpret_cast<DWORD64>(&Blip->Y));
			blip.z                    = -5000.f;

			if (blip.x != 64000.000 && blip.y != 64000.000) {
				this->m_writeMemory<DWORD64, CVector3>(m_hProcess, reinterpret_cast<DWORD64>(&pPlayerCoords->m_vecCoords), blip);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void CMemory::m_teleportVehicle() {
	CVector3 blip{};
	while (TRUE) {
		const auto teleportVehState = GetKeyState(VK_PAUSE) & 0x8000;
		if (teleportVehState) {
			auto* const pPlayer     = reinterpret_cast<CLocalPlayer*>(this->m_player);
			auto* const pVehicle    = this->m_readMemory<DWORD64, CVehicle*>(m_hProcess, reinterpret_cast<DWORD64>(&pPlayer->m_currentVehicle));
			auto* const pNavigation = this->m_readMemory<DWORD64, CNavigation*>(m_hProcess, reinterpret_cast<DWORD64>(&pVehicle->m_pCNavigation));
			auto* const Blip        = reinterpret_cast<CBlip*>(this->m_cBlip);

			blip.x = this->m_readMemory<DWORD64, float>(m_hProcess, reinterpret_cast<DWORD64>(&Blip->X));
			blip.y = this->m_readMemory<DWORD64, float>(m_hProcess, reinterpret_cast<DWORD64>(&Blip->Y));
			blip.z = -5000.f;

			if (blip.x != 64000.000 && blip.y != 64000.000) {
				this->m_writeMemory<DWORD64, CVector3>(m_hProcess, reinterpret_cast<DWORD64>(&pNavigation->m_vecCoords), blip);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void CMemory::m_inputHandler() {
	while (TRUE) {
		const auto moneyKeyState   = GetKeyState(VK_F6) & 0x1;
		const auto orbitalKeyState = GetKeyState(VK_F7) & 0x1;

		if (moneyKeyState) {
			m_inputs[EMONEY] = moneyKeyState | 0x80;
		}
		else {
			m_inputs[EMONEY] = 0x80;
		}
		if (orbitalKeyState) {
			m_inputs[EORBIT] = orbitalKeyState | 0x80;
		}
		else {
			m_inputs[EORBIT] = 0x80;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void CMemory::m_threads() {
	std::thread orbitalMoneyThread(&CMemory::m_orbitalMoney, this);
	std::thread opressorAmmoThread(&CMemory::m_opressorAmmo, this);
	std::thread teleportPlayerThread(&CMemory::m_teleportPlayer, this);
	std::thread teleportVehicleThread(&CMemory::m_teleportVehicle, this);
	std::thread keyHandlerThread(&CMemory::m_inputHandler, this);
	std::thread tunablesThread(&CMemory::m_tunables, this);
	std::thread moneyThread(&CMemory::m_money, this);

	keyHandlerThread.join();
	orbitalMoneyThread.detach();
	teleportPlayerThread.detach();
	teleportVehicleThread.detach();
	tunablesThread.detach();
	opressorAmmoThread.detach();
	moneyThread.detach();
}
