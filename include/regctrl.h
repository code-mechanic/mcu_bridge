
#ifndef REGCTRL_H
#define REGCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* clang-format off */
#define BIT_Mask(bitpos)                                       (1U << (bitpos))
#define BIT_MaskFill(bitpos)                          (BIT_Mask((bitpos)) - 1U)
#define BIT_Set(reg, bitpos)                     ((reg) |=  BIT_Mask((bitpos)))
#define BIT_Clear(reg, bitpos)                   ((reg) &= ~BIT_Mask((bitpos)))
#define BIT_Read(reg, bitpos)                        (((reg) >> (bitpos)) & 1U)
#define BIT_Toggle(reg, bitpos)                  ((reg) ^=  BIT_Mask((bitpos)))
#define BIT_Write(reg, bitpos, val)                                           \
                ((val) ? BIT_Set((reg), (bitpos)) : BIT_Clear((reg), (bitpos)))
     
#define BIT_IsSet(reg, bitpos)                      (BIT_Read((reg), (bitpos)))
#define BIT_IsClear(reg, bitpos)              (BIT_Read((reg), (bitpos)) == 0U)
#define BIT_IsAllSet(reg, mask)                    (((reg) & (mask)) == (mask))
#define BIT_IsAnySet(reg, mask)                        (((reg) & (mask)) != 0U)

#define REG_Clear(reg, val)                                   ((reg) &= ~(val))
#define REG_Write(reg, val)                                     ((reg) = (val))
#define REG_Read(reg)                                                   ((reg))
#define REG_Update(reg)                                        ((reg) |= (val))
#define REG_Merge(reg, val, mask)                                             \
                                 ((reg) = ((reg) & ~(mask)) | ((val) & (mask)))
#define REG_GroupRead(reg, bitpos, len)                                       \
                                    (((reg) >> (bitpos)) & BIT_MaskFill((len)))
#define REG_GroupWrite(reg, val, bitpos)            ((reg) = (val) << (bitpos))

#define REG_Shift(val, bitpos)                              ((val) << (bitpos))
#define REG_RightShift(val, bitpos)                         ((val) >> (bitpos))
#define REG_Modify(reg, setmask, clearmask)                                   \
             REG_Write((reg), (((REG_Read(reg)) & (~(clearmask))) | (setmask)))
/* clang-format on */
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* REGCTRL_H */