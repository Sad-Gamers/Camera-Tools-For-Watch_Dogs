#include "SadHook.h"
#include <vector>

class SadMemEdit {
public:
	static void PatchVMProtect();
	static void WriteFarJump(DWORD64 jumpLocation, DWORD64 jumpTo, SIZE_T numberOfBytesToClear);
	static void DisableInstruction(DWORD64 targetAddress, int instructionLength);
	static void WriteBytes(std::vector<uint8_t> bytes, DWORD64 targetAddress);
	static DWORD64 AllocateMemory(int pageSize);
};