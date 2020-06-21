#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "Important_Stuff.h"
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

class CMemory : CSignatures {
	private:
		/**
		 * \brief CWorld pointer
		 */
		MODULEINFO m_mi                    = {};
		HMODULE    m_hMod                  = {};
		HMODULE    m_modulesList[1024]     = {};
		char       m_processName[MAX_PATH] = "<System Process>";
		char       m_moduleName[MAX_PATH]  = {};
		DWORD      m_needed                = {};
		DWORD      m_neededMods            = 0;
		BYTE       m_inputs[8]             = {
				0x80, 0x80, 0x80, 0x80,
				0x80, 0x80, 0x80, 0x80
				};

		int m_moneyValue = 300000;
		int m_resetMoney = -1;
		int m_ieCooldown = 0;
		int m_iAmmo      = 9999;

		/**
		 * \brief Inputs array
		 */
	public:
		HANDLE  m_hProcess{};
		DWORD64 m_pWorld{};
		DWORD64 m_player{};
		DWORD64 m_cBlip{};

		int m_getListProcesses();

		int m_getProcessByName(DWORD pId, char* processName);

		/**
		 * \brief Update important variables with signatures
		 */
		void m_updateSignatures();

		/**
		 * \brief Getting hidden structures by using an index
		 * \param index Index specified in game scripts as Global_XXXX
		 * \return Returns the address relative to the specified index
		 */
		inline DWORD64 m_getHiddenStruct(DWORD64 index);

		static bool m_dataCompare(BYTE* data, BYTE* sign, char* mask);

		/**
		 * \brief Signature search
		 * \param hProcess Process Handle
		 * \param base Module start address
		 * \param size Size of module
		 * \param sign Signature
		 * \param mask Signature mask
		 * \return Address to which the signature points
		 */
		template <typename type>
		static type m_findSignature(HANDLE hProcess, type base, DWORD size, BYTE* sign, char* mask);

		/**
		 * \brief Memory reading
		 */
		template <typename function_type, typename vector_type>
		function_type m_readMemory(HANDLE                   hProcess, function_type Address,
								   std::vector<vector_type> offsets);

		/**
		 * \brief Memory reading
		 */
		template <typename function_type, typename vector_type, typename return_type>
		return_type m_readMemory(HANDLE                   hProcess, function_type Address,
								 std::vector<vector_type> offsets);

		/**
		 * \brief Memory reading
		 */
		template <typename function_type>
		function_type m_readMemory(HANDLE hProcess, function_type Address);

		/**
		 * \brief Memory reading
		 */
		template <typename function_type, typename return_type>
		return_type m_readMemory(HANDLE hProcess, function_type Address);

		/**
		 * \brief Memory writing
		 */
		template <typename function_type, typename buffer_type>
		static void m_writeMemory(HANDLE hProcess, function_type Address, buffer_type buffer);

		void m_inputHandler();

		void m_teleportPlayer();

		void m_teleportVehicle();

		/**
		 * \brief CASH $$$ hehe
		 */
		void m_money();

		void m_orbitalMoney();

		void m_threads();

		/**
		 * \brief Function that resets timers, such as import/export, mechanic call
		 */
		void m_tunables();

		/**
		 * \brief Unlocks many things from past events
		 */
		inline void m_unlocker();

		/**
		 * \brief Ammo for Opressor MK2 and recharge boost
		 */
		void m_opressorAmmo();
};

enum inputs {
	EMONEY,
	EORBIT,
	ETELEPORT,
	EVEHTELEPORT
};

enum orbital_type {
	basic = 1,
	autoaim
};
