/**
 * @file mcu_util_lib.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief マイコン用C言語ユーティリティライブラリ
 * @version 0.1
 * @date 2026-08-13
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#ifndef MCU_UTIL_LIB_H
#define MCU_UTIL_LIB_H
// ---------------------------------------------------
// [Include]
#include <stdint.h>
#include <stdbool.h>

// ---------------------------------------------------
#if defined(__GNUC__) && (__SIZEOF_POINTER__ == 8)
typedef uint64_t    reg_addr_t;
#else
typedef uint32_t    reg_addr_t;
#endif

typedef enum {
    BIT_ORDER_8_BIT,
    BIT_ORDER_16_BIT,
    BIT_ORDER_32_BIT,
} BIT_ORDER;
// ---------------------------------------------------
// レジスタの8/16/32bitでR/W

static inline uint8_t REG_READ_BYTE(reg_addr_t addr)
{
    return *(volatile uint8_t *)(addr);
}

static inline uint16_t REG_READ_WORD(reg_addr_t addr)
{
    return *(volatile uint16_t *)(addr);
}

static inline uint32_t REG_READ_DWORD(reg_addr_t addr)
{
    return *(volatile uint32_t *)(addr);
}

static inline void REG_WRITE_BYTE(reg_addr_t addr, uint8_t val)
{
    *(volatile uint8_t *)(addr) = val;
}

static inline void REG_WRITE_WORD(reg_addr_t addr, uint16_t val)
{
    *(volatile uint16_t *)(addr) = val;
}

static inline void REG_WRITE_DWORD(reg_addr_t addr, uint32_t val)
{
    *(volatile uint32_t *)(addr) = val;
}

// ---------------------------------------------------
// レジスタの8/16/32bitでビット操作マクロ

#define REG_BIT_SET(reg, bit)                 ((reg) |=  (1UL << (bit))) // レジスタのビットをセット
#define REG_BIT_CLR(reg, bit)                 ((reg) &= ~(1UL << (bit))) // レジスタのビットをクリア
#define REG_BIT_TGL(reg, bit)                 ((reg) ^=  (1UL << (bit))) // レジスタのビットをトグル
#define REG_BIT_CHK(reg, bit)                 ((reg) &   (1UL << (bit))) // レジスタのビットチェック

// ---------------------------------------------------

// インラインアセンブラ: NOP
static inline void _ASM_NOP(void)
{
    asm __volatile__("nop");
}

// ---------------------------------------------------
// [API]
void* mcu_util_reg_read(BIT_ORDER bit_order, reg_addr_t addr);
void mcu_util_reg_write(BIT_ORDER bit_order, reg_addr_t addr, void *p_val);

// ---------------------------------------------------

#endif // MCU_UTIL_LIB_H