/**
 * @file mcu_util_lib.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief マイコン用C言語ユーティリティライブラリ
 * @version 0.1
 * @date 2026-08-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "mcu_util_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

// ---------------------------------------------------
// デバッグ用コンパイルスイッチ
#define DEBUG_MCU_UTIL_LIB

// ---------------------------------------------------

#ifdef DEBUG_MCU_UTIL_LIB
#define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

int main(void)
{
    uint32_t test_reg = 0x12345678;
    uint8_t tmp_u8;
    uint16_t tmp_u16;
    uint32_t tmp_u32;

    DEBUG_PRINT("----------------------------------------------------");
    DEBUG_PRINT("MCU Util Library Debug Test");
    DEBUG_PRINT("----------------------------------------------------");
    //---------------------------------------------------
    // レジスタの8/16/32bit読み出し関数のテスト
    tmp_u8 = REG_READ_BYTE((uint32_t)&test_reg);
    DEBUG_PRINT("Reg 8bit Func Test: Addr=0x%08X, Value=0x%02X", (uint32_t)&test_reg, tmp_u8);

    tmp_u16 = REG_READ_HALFWORD((uint32_t)&test_reg);
    DEBUG_PRINT("Reg 16bit Func Test: Addr=0x%08X, Value=0x%04X", (uint32_t)&test_reg, tmp_u16);

    tmp_u32 = REG_READ_WORD((uint32_t)&test_reg);
    DEBUG_PRINT("Reg 32bit Func Test: Addr=0x%08X, Value=0x%08X", (uint32_t)&test_reg, tmp_u32);
    //---------------------------------------------------
    // レジスタの8/16/32bit書き込み関数のテスト
    REG_WRITE_BYTE((uint32_t)&test_reg, 0xAA);
    DEBUG_PRINT("Reg 8bit Write Func Test: Addr=0x%08X, Value=0x%02X", (uint32_t)&test_reg, test_reg);

    REG_WRITE_HALFWORD((uint32_t)&test_reg, 0xBBBB);
    DEBUG_PRINT("Reg 16bit Write Func Test: Addr=0x%08X, Value=0x%04X", (uint32_t)&test_reg, test_reg);

    REG_WRITE_WORD((uint32_t)&test_reg, 0xCCCCCCCC);
    DEBUG_PRINT("Reg 32bit Write Func Test: Addr=0x%08X, Value=0x%08X", (uint32_t)&test_reg, test_reg);
    //---------------------------------------------------
    // レジスタのビット操作マクロのテスト
    REG_BIT_SET(test_reg, 0);
    DEBUG_PRINT("Reg Bit Set Macro Test: Addr=0x%08X, Value=0x%08X", (uint32_t)&test_reg, test_reg);

    REG_BIT_CLR(test_reg, 1);
    DEBUG_PRINT("Reg Bit Clear Macro Test: Addr=0x%08X, Value=0x%08X", (uint32_t)&test_reg, test_reg);

    REG_BIT_TGL(test_reg, 2);
    DEBUG_PRINT("Reg Bit Toggle Macro Test: Addr=0x%08X, Value=0x%08X", (uint32_t)&test_reg, test_reg);

    if (REG_BIT_CHK(test_reg, 3))
    {
        DEBUG_PRINT("Reg Bit Check Macro Test: Addr=0x%08X, Bit 3 is SET", (uint32_t)&test_reg);
    }
    else
    {
        DEBUG_PRINT("Reg Bit Check Macro Test: Addr=0x%08X, Bit 3 is CLEAR", (uint32_t)&test_reg);
    }
    //---------------------------------------------------
    DEBUG_PRINT("----------------------------------------------------");

    return 0;
}
#endif

// ---------------------------------------------------