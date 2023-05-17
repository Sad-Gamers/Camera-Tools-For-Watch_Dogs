#include "SadMemEdit.h"

/*
* This function allows us to modify memory freely by partially Disabling the game's DRM.
* PatchVMProtect was NOT written by me.
* All credits go to @yubie-re on GitHub.
* https://github.com/yubie-re
*/
void SadMemEdit::PatchVMProtect()
{
	DWORD oldProtect = 0;
	auto ntdll = GetModuleHandleA("ntdll.dll");
	BYTE callcode = ((BYTE*)GetProcAddress(ntdll, "NtQuerySection"))[4] - 1;
	BYTE restore[] = { 0x4C, 0x8B, 0xD1, 0xB8, callcode };
	auto nt_vp = (BYTE*)GetProcAddress(ntdll, "NtProtectVirtualMemory");
	VirtualProtect(nt_vp, sizeof(restore), PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(nt_vp, restore, sizeof(restore));
	VirtualProtect(nt_vp, sizeof(restore), oldProtect, &oldProtect);
}

/*
* This function allocates memory and returns the address of the allocated memory.
* We will be using the virtual page to write our custom code for trampoline hooks.
*/
DWORD64 SadMemEdit::AllocateMemory(int pageSize) {
	return DWORD64(VirtualAlloc(0, pageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
}

/*
* This function disables instructions by replacing them with NOP bytes.
* We will be using this to prevent the game from overwriting certain values.
*/
void SadMemEdit::DisableInstruction(DWORD64 targetAddress, int instructionLength) {
	DWORD oldProtect;
	VirtualProtect(LPVOID(targetAddress), 64, PAGE_EXECUTE_READWRITE, &oldProtect); //overwrite page protections
	memset(LPVOID(targetAddress), 0x90, instructionLength);  //disable instruction 
}

/*
* This function writes bytes at the specified address.
* We will mainly be using function to write most our x86 assembly in byte code, as well as restoring original byte code.
*/
void SadMemEdit::WriteBytes(std::vector<uint8_t> bytes, DWORD64 targetAddress) {
	DWORD oldProtect;
	VirtualProtect(LPVOID(targetAddress), 64, PAGE_EXECUTE_READWRITE, &oldProtect); //overwrite page protections
	memcpy(LPVOID(targetAddress), bytes.data(), bytes.size());
}

/*
* This function writes a far jump in to a specified address at a memory location x86 byte code.
* We will be using this to make trampoline hooks (jumping from instruction to custom function, and back).
*/
void SadMemEdit::WriteFarJump(DWORD64 jumpLocation, DWORD64 jumpTo, SIZE_T numberOfBytesToClear) {
	DWORD oldProtect;
	VirtualProtect(LPVOID(jumpLocation), 64, PAGE_EXECUTE_READWRITE, &oldProtect); //overwrite page protections

	/*
	* We "clear" a specific number of bytes where we may be writing a trampoline hook because the far jump
	* instruction may overwrite only a few bytes of an instruction that follows the jump which will lead
	* to crashes because missing a byte or two can make byte code mean something totally different.
	*/
	memset(LPVOID(jumpLocation), 0x90, numberOfBytesToClear); //set all bytes initially to NOP, this is how we "clear". 

	WriteBytes({ 0xFF, 0x25 }, jumpLocation);
	memset(LPVOID(jumpLocation + 0x2), 0x0, 4); //this line and the line that preccedes it are byte code for far jump
	__int64 jumpToHex = jumpTo; //converting our destination address to hexadecimal so we can write it in byte code
	//writes what address to far jump to making our final instruction jmp [jumpTo]
	memcpy(LPVOID(jumpLocation + 0x6), &jumpToHex, sizeof(jumpToHex));
}