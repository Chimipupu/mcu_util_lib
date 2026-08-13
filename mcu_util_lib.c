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

// ---------------------------------------------------
// デバッグ用コンパイルスイッチ
#define DEBUG_MCU_UTIL_LIB

// ---------------------------------------------------
// [API]

uint32_t mcu_util_reg_read(BIT_ORDER bit_order, reg_addr_t addr)
{
    uint32_t ret_val = 0;

    switch (bit_order)
    {
        case BIT_ORDER_8_BIT:
            ret_val = REG_READ_BYTE(addr);
            break;

        case BIT_ORDER_16_BIT:
            ret_val = REG_READ_WORD(addr);
            break;

        case BIT_ORDER_32_BIT:
        default:
            ret_val = REG_READ_DWORD(addr);
            break;
    }

    return ret_val;
}

void mcu_util_reg_write(BIT_ORDER bit_order, reg_addr_t addr, uint32_t val)
{
    switch (bit_order)
    {
        case BIT_ORDER_8_BIT:
            REG_WRITE_BYTE(addr, (uint8_t)val);
            break;

        case BIT_ORDER_16_BIT:
            REG_WRITE_WORD(addr, (uint16_t)val);
            break;

        case BIT_ORDER_32_BIT:
        default:
            REG_WRITE_DWORD(addr, val);
            break;
    }
}

// ---------------------------------------------------
// [DEBUG]

#ifdef DEBUG_MCU_UTIL_LIB
#define DEBUG_PRINT(fmt, ...)    printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)

#if defined(__GNUC__) && (__SIZEOF_POINTER__ == 8)
int main(void)
#else
int test_util(void)
#endif
{
    uint32_t test_reg;
    uint32_t *p_test_reg;
    uint8_t tmp_u8;
    uint16_t tmp_u16;
    uint32_t tmp_u32;
    bool is_chk;

    p_test_reg = &test_reg;

    DEBUG_PRINT("====================================================");
    DEBUG_PRINT(" MCU Util Library Debug Test");
    DEBUG_PRINT("====================================================");

    // ---------------------------------------------------
    // [1] レジスタの8/16/32bit読み出し関数のテスト
    DEBUG_PRINT("[1] READ TEST");
    test_reg = 0x12345678;

    tmp_u8 = (uint8_t)mcu_util_reg_read(BIT_ORDER_8_BIT, (reg_addr_t)p_test_reg);
    DEBUG_PRINT(" -> 8bit Read Test : 0x%02X", tmp_u8);

    tmp_u16 = (uint16_t)mcu_util_reg_read(BIT_ORDER_16_BIT, (reg_addr_t)p_test_reg);
    DEBUG_PRINT(" -> 16bit Read Test: 0x%04X", tmp_u16);

    tmp_u32 = mcu_util_reg_read(BIT_ORDER_32_BIT, (reg_addr_t)p_test_reg);
    DEBUG_PRINT(" -> 32bit Read Test: 0x%08X", tmp_u32);
    DEBUG_PRINT("----------------------------------------------------");
    //---------------------------------------------------
    // [2] レジスタの8/16/32bit書き込み関数のテスト
    DEBUG_PRINT("[2] WRITE TEST");

    test_reg = 0x00000000;
    mcu_util_reg_write(BIT_ORDER_8_BIT, (reg_addr_t)p_test_reg, 0xAA);
    DEBUG_PRINT(" -> 8bit Write (0xAA)       : 0x%08X", test_reg);

    test_reg = 0x00000000;
    mcu_util_reg_write(BIT_ORDER_16_BIT, (reg_addr_t)p_test_reg, 0xBBBB);
    DEBUG_PRINT(" -> 16bit Write (0xBBBB)    : 0x%08X", test_reg);

    test_reg = 0x00000000;
    mcu_util_reg_write(BIT_ORDER_32_BIT, (reg_addr_t)p_test_reg, 0xCCCCCCCC);
    DEBUG_PRINT(" -> 32bit Write (0xCCCCCCCC): 0x%08X", test_reg);

    DEBUG_PRINT("----------------------------------------------------");
    //---------------------------------------------------
    // [3] レジスタのビット操作マクロのテスト
    DEBUG_PRINT("[3] BIT MACRO TEST");

    test_reg = 0x00000000;
    REG_BIT_SET(test_reg, 0);
    DEBUG_PRINT(" -> Bit 0 SET              : 0x%08X", test_reg);

    test_reg = 0xFFFFFFFF;
    REG_BIT_CLR(test_reg, 1);
    DEBUG_PRINT(" -> Bit 1 CLR              : 0x%08X", test_reg);

    test_reg = 0x00000000;
    REG_BIT_TGL(test_reg, 2);
    DEBUG_PRINT(" -> Bit 2 TGL (0->1)       : 0x%08X", test_reg);
    REG_BIT_TGL(test_reg, 2);
    DEBUG_PRINT(" -> Bit 2 TGL (1->0)       : 0x%08X", test_reg);

    test_reg = 0x00000008; // Bit 3が立っている状態
    is_chk = (REG_BIT_CHK(test_reg, 3) != 0);
    DEBUG_PRINT(" -> Bit 3 CHK (Expected 1) : %d", is_chk);

    is_chk = (REG_BIT_CHK(test_reg, 4) != 0);
    DEBUG_PRINT(" -> Bit 4 CHK (Expected 0) : %d", is_chk);
    DEBUG_PRINT("====================================================");

    return 0;
}
#endif

// ---------------------------------------------------