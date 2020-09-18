/*
 *	bypasses.cpp
 *	Syncopated
 *
 *	Created by Azurilex on 07/28/2020
 *	Copyright © 2020 Azurilex. All rights reserved.
 *	Copyright © 2020 Eternal. All rights reserved.
 *	Copyright © 2020 Brandon. All rights reserved.
 *	All bypasses used in the source to get around Roblox's checks
 */

#include "bypasses.hpp"
#include <string>
#include <random>

void writeshell(unsigned char* address, std::vector<BYTE> sc)
{
	auto* oldProtection = new DWORD;
	VirtualProtect(static_cast<LPVOID>(address), sc.size(), PAGE_EXECUTE_READWRITE, oldProtection);
	for (int n = 0; n < static_cast<int>(sc.size()); n++)
	{
		*(address + n) = sc[static_cast<unsigned>(n)];
	}
	VirtualProtect(static_cast<LPVOID>(address), sc.size(), *oldProtection, oldProtection);
	delete oldProtection;
}

DWORD eternal_unprotect(DWORD addr)
{
	BYTE* tAddr = reinterpret_cast<BYTE*>(addr);

	do
	{
		tAddr += 16;
	}
	while (!(tAddr[0] == push && tAddr[1] == mov_r16 && tAddr[2] == in));

	DWORD funcSz = tAddr - reinterpret_cast<BYTE*>(addr);

	PVOID nFunc = VirtualAlloc(nullptr, funcSz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (nFunc == nullptr)
		return addr;

	memcpy(nFunc, reinterpret_cast<void*>(addr), funcSz);

	BYTE* pos = static_cast<BYTE*>(nFunc);
	BOOL valid = false;
	do
	{
		if (pos[0] == jb && pos[2] == mov_eax && pos[7] == mov_r16)
		{
			*static_cast<BYTE*>(pos) = jmp;

			auto cByte = reinterpret_cast<DWORD>(nFunc);
			do
			{
				if (*reinterpret_cast<BYTE*>(cByte) == call)
				{
					DWORD oFuncPos = addr + (cByte - reinterpret_cast<DWORD>(nFunc));
					DWORD oFuncAddr = (oFuncPos + *reinterpret_cast<DWORD*>(oFuncPos + 1)) + 5;

					if (oFuncAddr % 16 == 0)
					{
						DWORD relativeAddr = oFuncAddr - cByte - 5;
						*reinterpret_cast<DWORD*>(cByte + 1) = relativeAddr;

						cByte += 4;
					}
				}

				cByte += 1;
			}
			while (cByte - reinterpret_cast<DWORD>(nFunc) < funcSz);

			valid = true;
		}
		pos += 1;
	}
	while (reinterpret_cast<DWORD>(pos) < reinterpret_cast<DWORD>(nFunc) + funcSz);

	if (!valid)
	{
		VirtualFree(nFunc, 0, MEM_RELEASE);
		return addr;
	}

	return reinterpret_cast<DWORD>(nFunc);
}

//im a fucking genius
void write_instruction(DWORD addr, opcodes o)
{
	DWORD old_prot;
	VirtualProtect(reinterpret_cast<void*>(addr), 0x05, PAGE_EXECUTE_READWRITE, &old_prot);
	*reinterpret_cast<unsigned char*>(addr) = o;
	VirtualProtect(reinterpret_cast<void*>(addr), 0x05, old_prot, &old_prot);
}

unsigned char hde32_table[] = {
	0xa3, 0xa8, 0xa3, 0xa8, 0xa3, 0xa8, 0xa3, 0xa8, 0xa3, 0xa8, 0xa3, 0xa8, 0xa3, 0xa8, 0xa3,
	0xa8, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xac, 0xaa, 0xb2, 0xaa, 0x9f, 0x9f,
	0x9f, 0x9f, 0xb5, 0xa3, 0xa3, 0xa4, 0xaa, 0xaa, 0xba, 0xaa, 0x96, 0xaa, 0xa8, 0xaa, 0xc3,
	0xc3, 0x96, 0x96, 0xb7, 0xae, 0xd6, 0xbd, 0xa3, 0xc5, 0xa3, 0xa3, 0x9f, 0xc3, 0x9c, 0xaa,
	0xaa, 0xac, 0xaa, 0xbf, 0x03, 0x7f, 0x11, 0x7f, 0x01, 0x7f, 0x01, 0x3f, 0x01, 0x01, 0x90,
	0x82, 0x7d, 0x97, 0x59, 0x59, 0x59, 0x59, 0x59, 0x7f, 0x59, 0x59, 0x60, 0x7d, 0x7f, 0x7f,
	0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x9a, 0x88, 0x7d,
	0x59, 0x50, 0x50, 0x50, 0x50, 0x59, 0x59, 0x59, 0x59, 0x61, 0x94, 0x61, 0x9e, 0x59, 0x59,
	0x85, 0x59, 0x92, 0xa3, 0x60, 0x60, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59, 0x59,
	0x59, 0x59, 0x9f, 0x01, 0x03, 0x01, 0x04, 0x03, 0xd5, 0x03, 0xcc, 0x01, 0xbc, 0x03, 0xf0,
	0x10, 0x10, 0x10, 0x10, 0x50, 0x50, 0x50, 0x50, 0x14, 0x20, 0x20, 0x20, 0x20, 0x01, 0x01,
	0x01, 0x01, 0xc4, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xc0, 0xc2, 0x10, 0x11,
	0x02, 0x03, 0x11, 0x03, 0x03, 0x04, 0x00, 0x00, 0x14, 0x00, 0x02, 0x00, 0x00, 0xc6, 0xc8,
	0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xca,
	0x01, 0x01, 0x01, 0x00, 0x06, 0x00, 0x04, 0x00, 0xc0, 0xc2, 0x01, 0x01, 0x03, 0x01, 0xff,
	0xff, 0x01, 0x00, 0x03, 0xc4, 0xc4, 0xc6, 0x03, 0x01, 0x01, 0x01, 0xff, 0x03, 0x03, 0x03,
	0xc8, 0x40, 0x00, 0x0a, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x33, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xbf, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x7f, 0x00, 0x00, 0xff, 0x4a, 0x4a, 0x4a, 0x4a, 0x4b, 0x52, 0x4a, 0x4a, 0x4a, 0x4a, 0x4f,
	0x4c, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x55, 0x45, 0x40, 0x4a, 0x4a, 0x4a,
	0x45, 0x59, 0x4d, 0x46, 0x4a, 0x5d, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x4a,
	0x4a, 0x4a, 0x4a, 0x4a, 0x4a, 0x61, 0x63, 0x67, 0x4e, 0x4a, 0x4a, 0x6b, 0x6d, 0x4a, 0x4a,
	0x45, 0x6d, 0x4a, 0x4a, 0x44, 0x45, 0x4a, 0x4a, 0x00, 0x00, 0x00, 0x02, 0x0d, 0x06, 0x06,
	0x06, 0x06, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x02, 0x06,
	0x00, 0x0a, 0x0a, 0x07, 0x07, 0x06, 0x02, 0x05, 0x05, 0x02, 0x02, 0x00, 0x00, 0x04, 0x04,
	0x04, 0x04, 0x00, 0x00, 0x00, 0x0e, 0x05, 0x06, 0x06, 0x06, 0x01, 0x06, 0x00, 0x00, 0x08,
	0x00, 0x10, 0x00, 0x18, 0x00, 0x20, 0x00, 0x28, 0x00, 0x30, 0x00, 0x80, 0x01, 0x82, 0x01,
	0x86, 0x00, 0xf6, 0xcf, 0xfe, 0x3f, 0xab, 0x00, 0xb0, 0x00, 0xb1, 0x00, 0xb3, 0x00, 0xba,
	0xf8, 0xbb, 0x00, 0xc0, 0x00, 0xc1, 0x00, 0xc7, 0xbf, 0x62, 0xff, 0x00, 0x8d, 0xff, 0x00,
	0xc4, 0xff, 0x00, 0xc5, 0xff, 0x00, 0xff, 0xff, 0xeb, 0x01, 0xff, 0x0e, 0x12, 0x08, 0x00,
	0x13, 0x09, 0x00, 0x16, 0x08, 0x00, 0x17, 0x09, 0x00, 0x2b, 0x09, 0x00, 0xae, 0xff, 0x07,
	0xb2, 0xff, 0x00, 0xb4, 0xff, 0x00, 0xb5, 0xff, 0x00, 0xc3, 0x01, 0x00, 0xc7, 0xff, 0xbf,
	0xe7, 0x08, 0x00, 0xf0, 0x02, 0x00
};

DWORD Bypass::retcheck_unprotect(DWORD addr)
{
	return static_cast<DWORD>(unprotect(reinterpret_cast<BYTE*>(addr)));
}

unsigned Bypass::hde32_disasm(const void* code, hde32s* hs)
{
	uint8_t x;
	uint8_t c = 0;
	auto* p = static_cast<uint8_t*>(const_cast<void*>(code));
	uint8_t pref = 0;
	uint8_t *ht = hde32_table, m_mod, m_reg, m_rm, disp_size = 0;

	memset(hs, 0, sizeof(hde32s));

	for (x = 16; x; x--)
		switch (c = *p++)
		{
		case 0xf3:
			hs->p_rep = c;
			pref |= PRE_F3;
			break;
		case 0xf2:
			hs->p_rep = c;
			pref |= PRE_F2;
			break;
		case 0xf0:
			hs->p_lock = c;
			pref |= PRE_LOCK;
			break;
		case 0x26:
		case 0x2e:
		case 0x36:
		case 0x3e:
		case 0x64:
		case 0x65:
			hs->p_seg = c;
			pref |= PRE_SEG;
			break;
		case 0x66:
			hs->p_66 = c;
			pref |= PRE_66;
			break;
		case 0x67:
			hs->p_67 = c;
			pref |= PRE_67;
			break;
		default:
			goto pref_done;
		}
pref_done:

	hs->flags = static_cast<uint32_t>(pref) << 23;

	if (!pref)
		pref |= PRE_NONE;

	if ((hs->opcode = c) == 0x0f)
	{
		hs->opcode2 = c = *p++;
		ht += DELTA_OPCODES;
	}
	else if (c >= 0xa0 && c <= 0xa3)
	{
		if (pref & PRE_67)
			pref |= PRE_66;
		else
			pref &= ~PRE_66;
	}

	uint8_t opcode = c;
	uint8_t cflags = ht[ht[opcode / 4] + (opcode % 4)];

	if (cflags == C_ERROR)
	{
		hs->flags |= F_ERROR | F_ERROR_OPCODE;
		cflags = 0;
		if ((opcode & -3) == 0x24)
			cflags++;
	}

	x = 0;
	if (cflags & C_GROUP)
	{
		uint16_t t = *reinterpret_cast<uint16_t*>(ht + (cflags & 0x7f));
		cflags = static_cast<uint8_t>(t);
		x = static_cast<uint8_t>(t >> 8);
	}

	if (hs->opcode2)
	{
		ht = hde32_table + DELTA_PREFIXES;
		if (ht[ht[opcode / 4] + (opcode % 4)] & pref)
			hs->flags |= F_ERROR | F_ERROR_OPCODE;
	}

	if (cflags & C_MODRM)
	{
		hs->flags |= F_MODRM;
		hs->modrm = c = *p++;
		hs->modrm_mod = m_mod = c >> 6;
		hs->modrm_rm = m_rm = c & 7;
		hs->modrm_reg = m_reg = (c & 0x3f) >> 3;

		if (x && ((x << m_reg) & 0x80))
			hs->flags |= F_ERROR | F_ERROR_OPCODE;

		if (!hs->opcode2 && opcode >= 0xd9 && opcode <= 0xdf)
		{
			uint8_t t = opcode - 0xd9;
			if (m_mod == 3)
			{
				ht = hde32_table + DELTA_FPU_MODRM + t * 8;
				t = ht[m_reg] << m_rm;
			}
			else
			{
				ht = hde32_table + DELTA_FPU_REG;
				t = ht[t] << m_reg;
			}
			if (t & 0x80)
				hs->flags |= F_ERROR | F_ERROR_OPCODE;
		}

		if (pref & PRE_LOCK)
		{
			if (m_mod == 3)
			{
				hs->flags |= F_ERROR | F_ERROrLOCK;
			}
			else
			{
				uint8_t *table_end, op = opcode;
				if (hs->opcode2)
				{
					ht = hde32_table + DELTA_OP2_LOCK_OK;
					table_end = ht + DELTA_OP_ONLY_MEM - DELTA_OP2_LOCK_OK;
				}
				else
				{
					ht = hde32_table + DELTA_OP_LOCK_OK;
					table_end = ht + DELTA_OP2_LOCK_OK - DELTA_OP_LOCK_OK;
					op &= -2;
				}
				for (; ht != table_end; ht++)
					if (*ht++ == op)
					{
						if (!((*ht << m_reg) & 0x80))
							goto no_lock_error;
						break;
					}
				hs->flags |= F_ERROR | F_ERROrLOCK;
			no_lock_error:
				;
			}
		}

		if (hs->opcode2)
		{
			switch (opcode)
			{
			case 0x20:
			case 0x22:
				m_mod = 3;
				if (m_reg > 4 || m_reg == 1)
					goto error_operand;
				goto no_error_operand;
			case 0x21:
			case 0x23:
				m_mod = 3;
				if (m_reg == 4 || m_reg == 5)
					goto error_operand;
				goto no_error_operand;
			}
		}
		else
		{
			switch (opcode)
			{
			case 0x8c:
				{
					if (m_reg > 5)
						goto error_operand;
					goto no_error_operand;
				}
			case 0x8e:
				{
					if (m_reg == 1 || m_reg > 5)
						goto error_operand;
					goto no_error_operand;
				}
			}
		}

		if (m_mod == 3)
		{
			uint8_t* table_end;
			if (hs->opcode2)
			{
				ht = hde32_table + DELTA_OP2_ONLY_MEM;
				table_end = ht + sizeof(hde32_table) - DELTA_OP2_ONLY_MEM;
			}
			else
			{
				ht = hde32_table + DELTA_OP_ONLY_MEM;
				table_end = ht + DELTA_OP2_ONLY_MEM - DELTA_OP_ONLY_MEM;
			}
			for (; ht != table_end; ht += 2)
				if (*ht++ == opcode)
				{
					if ((*ht++ & pref) && !((*ht << m_reg) & 0x80))
						goto error_operand;
					break;
				}
			goto no_error_operand;
		}
		if (hs->opcode2)
		{
			switch (opcode)
			{
			case 0x50:
			case 0xd7:
			case 0xf7:
				if (pref & (PRE_NONE | PRE_66))
					goto error_operand;
				break;
			case 0xd6:
				if (pref & (PRE_F2 | PRE_F3))
					goto error_operand;
				break;
			case 0xc5:
				goto error_operand;
			}
			goto no_error_operand;
		}
		goto no_error_operand;

	error_operand:
		hs->flags |= F_ERROR | F_ERROR_OPERAND;
	no_error_operand:

		c = *p++;
		if (m_reg <= 1)
		{
			if (opcode == 0xf6)
				cflags |= C_IMM8;
			else if (opcode == 0xf7)
				cflags |= C_IMM_P66;
		}

		switch (m_mod)
		{
		case 0:
			if (pref & PRE_67)
			{
				if (m_rm == 6)
					disp_size = 2;
			}
			else if (m_rm == 5)
				disp_size = 4;
			break;
		case 1:
			disp_size = 1;
			break;
		case 2:
			disp_size = 2;
			if (!(pref & PRE_67))
				disp_size <<= 1;
			break;
		}

		if (m_mod != 3 && m_rm == 4 && !(pref & PRE_67))
		{
			hs->flags |= F_SIB;
			p++;
			hs->sib = c;
			hs->sib_scale = c >> 6;
			hs->sib_index = (c & 0x3f) >> 3;
			if ((hs->sib_base = c & 7) == 5 && !(m_mod & 1))
				disp_size = 4;
		}

		p--;
		switch (disp_size)
		{
		case 1:
			hs->flags |= F_DISP8;
			hs->disp.disp8 = *p;
			break;
		case 2:
			hs->flags |= F_DISP16;
			hs->disp.disp16 = *reinterpret_cast<uint16_t*>(p);
			break;
		case 4:
			hs->flags |= F_DISP32;
			hs->disp.disp32 = *reinterpret_cast<uint32_t*>(p);
			break;
		}
		p += disp_size;
	}
	else if (pref & PRE_LOCK)
		hs->flags |= F_ERROR | F_ERROrLOCK;

	if (cflags & C_IMM_P66)
	{
		if (cflags & C_REL32)
		{
			if (pref & PRE_66)
			{
				hs->flags |= F_IMM16 | F_RELATIVE;
				hs->imm.imm16 = *reinterpret_cast<uint16_t*>(p);
				p += 2;
				goto disasm_done;
			}
			goto rel32_ok;
		}
		if (pref & PRE_66)
		{
			hs->flags |= F_IMM16;
			hs->imm.imm16 = *reinterpret_cast<uint16_t*>(p);
			p += 2;
		}
		else
		{
			hs->flags |= F_IMM32;
			hs->imm.imm32 = *reinterpret_cast<uint32_t*>(p);
			p += 4;
		}
	}

	if (cflags & C_IMM16)
	{
		if (hs->flags & F_IMM32)
		{
			hs->flags |= F_IMM16;
			hs->disp.disp16 = *reinterpret_cast<uint16_t*>(p);
		}
		else if (hs->flags & F_IMM16)
		{
			hs->flags |= F_2IMM16;
			hs->disp.disp16 = *reinterpret_cast<uint16_t*>(p);
		}
		else
		{
			hs->flags |= F_IMM16;
			hs->imm.imm16 = *reinterpret_cast<uint16_t*>(p);
		}
		p += 2;
	}
	if (cflags & C_IMM8)
	{
		hs->flags |= F_IMM8;
		hs->imm.imm8 = *p++;
	}

	if (cflags & C_REL32)
	{
	rel32_ok:
		hs->flags |= F_IMM32 | F_RELATIVE;
		hs->imm.imm32 = *reinterpret_cast<uint32_t*>(p);
		p += 4;
	}
	else if (cflags & C_REL8)
	{
		hs->flags |= F_IMM8 | F_RELATIVE;
		hs->imm.imm8 = *p++;
	}

disasm_done:

	if ((hs->len = static_cast<uint8_t>(p - static_cast<unsigned char const*>(code))) > 15)
	{
		hs->flags |= F_ERROR | F_ERROrLENGTH;
		hs->len = 15;
	}

	return static_cast<unsigned int>(hs->len);
}

DWORD Bypass::unprotect(BYTE* funcaddr)
{
	static int total_alloc;
	static std::map<DWORD, DWORD> cache;
	try
	{
		DWORD& cached_func = cache.at(reinterpret_cast<DWORD>(funcaddr));
		return static_cast<DWORD>(cached_func);
	}
	catch (std::out_of_range&)
	{
	} //cache miss, do nothing and continue

	DWORD func_size = get_func_end(funcaddr) - funcaddr;
	if (!func_size)
	{
		return reinterpret_cast<DWORD>(funcaddr);
	}

	if (total_alloc + static_cast<int>(func_size) > max_alloc)
		return reinterpret_cast<DWORD>(funcaddr); //failsafe, using too much memory (over 1MB)

	void* new_func = VirtualAlloc(nullptr, func_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (new_func == nullptr)
		return reinterpret_cast<DWORD>(funcaddr); //alloc failed

	total_alloc += func_size;
	memcpy(new_func, funcaddr, func_size);
	if (disable_retcheck(reinterpret_cast<DWORD>(new_func), func_size))
	{
		cache.emplace(reinterpret_cast<DWORD>(funcaddr), reinterpret_cast<DWORD>(new_func));
		fix_calls(reinterpret_cast<DWORD>(new_func), reinterpret_cast<DWORD>(funcaddr), func_size);
		return reinterpret_cast<DWORD>(new_func);
	}

	//no retcheck was found, abort
	VirtualFree(new_func, 0, MEM_RELEASE);
	//VirtualFree(new_func, func_size, MEM_DECOMMIT); //this is a memory leak, doesn't even need to be run
	return reinterpret_cast<DWORD>(funcaddr);
}

const int Bypass::max_alloc = 1024 * 1024;

bool Bypass::is_prolog(const BYTE* addr)
{
	return addr[0] == 0x55 && addr[1] == 0x8B && addr[2] == 0xEC;
}

BYTE* Bypass::get_func_end(BYTE* funcaddr)
{
	BYTE* addr = funcaddr + 0x10;
	while (true)
	{
		if (IsBadReadPtr(addr, 4))
		{
			return funcaddr;
		}
		if (is_prolog(addr))
		{
			break;
		}
		addr += 0x10;
	}
	return addr;
}

bool Bypass::disable_retcheck(DWORD new_func, DWORD func_len)
{
	bool has_retcheck = false;
	DWORD disasm_ptr = new_func;
	while (disasm_ptr - new_func < func_len)
	{
		hde32s disasm = {0};
		hde32_disasm(reinterpret_cast<void*>(disasm_ptr), &disasm);
		if (disasm.opcode == 0x3B) //CMP
		{
			DWORD ptr = disasm.disp.disp32;
			if (ptr > 0xFFFF) //filter CMP instructions, disp32 should be a pointer to the bound constant
			{
				memcpy(reinterpret_cast<void*>(disasm_ptr), "\xF9\x90\x90\x90\x90\x90", 6); //setc nop nop nop nop nop
				has_retcheck = true;
			}
		}
		disasm_ptr += disasm.len;
	}
	return has_retcheck;
}

BYTE Bypass::test_function(DWORD func)
{
	__try
	{
		BYTE x = *reinterpret_cast<BYTE*>(func);
		return x == 0 ? 1 : x;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}


void Bypass::fix_calls(DWORD new_func, DWORD orig_func, DWORD func_len)
{
	DWORD disasm_ptr = new_func;
	while (disasm_ptr - new_func < func_len)
	{
		hde32s disasm = {0};
		hde32_disasm(reinterpret_cast<void*>(disasm_ptr), &disasm);
		if (disasm.opcode == 0xE8) //CALL
		{
			DWORD rel_addr = disasm.imm.imm32;
			DWORD orig_call_instr = orig_func + (disasm_ptr - new_func);
			DWORD orig_called_func = orig_call_instr + rel_addr + 5;
			if (orig_called_func % 0x10 == 0 && test_function(orig_called_func)) //functions are aligned to 0x10 bytes
			{
				__try
				{
					DWORD new_called_func = unprotect(reinterpret_cast<BYTE*>(orig_called_func));
					DWORD new_rel_addr = new_called_func - disasm_ptr - 5;
					*reinterpret_cast<DWORD*>(disasm_ptr + 1) = new_rel_addr;
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
					//ignore it
				}
			}
		}
		disasm_ptr += disasm.len;
	}
}
