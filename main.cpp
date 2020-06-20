#include  "Memory.h"

int main() {
	auto m = std::make_unique<CMemory>();
	m->m_getListProcesses();
	CloseHandle(m->m_hProcess);
	return 0;
}
