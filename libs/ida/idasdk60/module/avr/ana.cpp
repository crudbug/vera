/*
 *      Interactive disassembler (IDA).
 *      Copyright (c) 1990-99 by Ilfak Guilfanov.
 *      ALL RIGHTS RESERVED.
 *                              E-mail: ig@datarescue.com
 *
 *      Atmel AVR - 8-bit RISC processor
 *
 */

#include "avr.hpp"
#include <fixup.hpp>
#include "../../ldr/elf/elfr_avr.h"

//--------------------------------------------------------------------------
/*

0000 0000 0000 0000     nop
0000 0001 dddd rrrr     movw   Rd,Rr
0000 0010 dddd rrrr     muls   Rd,Rr
0000 0011 0ddd 0rrr     mulsu  Rd,Rr
0000 0011 0ddd 1rrr     fmul   Rd,Rr
0000 0011 1ddd 0rrr     fmuls  Rd,Rr
0000 0011 1ddd 1rrr     fmulsu Rd,Rr
0000 01rd dddd rrrr     cpc     rd, rr
0000 10rd dddd rrrr     sbc     rd, rr
0000 11rd dddd rrrr     add     rd, rr    lsl rd if rd==rr
0001 00rd dddd rrrr     cpse    rd, rr
0001 01rd dddd rrrr     cp      rd, rr
0001 10rd dddd rrrr     sub     rd, rr
0001 11rd dddd rrrr     adc     rd, rr    rol rd if rd==rr
0010 00rd dddd rrrr     and     rd, rr    tst rd if rd==rr
0010 01rd dddd rrrr     eor     rd, rr    clr rd if rd==rr
0010 10rd dddd rrrr     or      rd, rr
0010 11rd dddd rrrr     mov     rd, rr
0011 kkkk dddd kkkk     cpi     rd, k   (16<=d<=31)
0100 kkkk dddd kkkk     sbci    rd, k   (16<=d<=31)
0101 kkkk dddd kkkk     subi    rd, k   (16<=d<=31)
0110 kkkk dddd kkkk     ori/sbr rd, k   (16<=d<=31)
0111 kkkk dddd kkkk     andi    rd, k   (16<=d<=31) cbr rd, k if op2 is bitwise negated
1000 000d dddd 0000     ld      rd, Z
1000 000d dddd 1000     ld      rd, Y
1000 001r rrrr 0000     st Z, rr
1000 001r rrrr 1000     st Y, rr
1001 000d dddd 0000(1*k)lds     rd, k
1001 000d dddd 0001     ld      rd, Z+
1001 000d dddd 0010     ld      rd, -Z
1001 000d dddd 0100     lpm     Rd, Z
1001 000d dddd 0101     lpm     Rd, Z+
1001 000d dddd 0110     elpm    Rd, Z
1001 000d dddd 0111     elpm    Rd, Z+
1001 000d dddd 1001     ld      rd, Y+
1001 000d dddd 1010     ld      rd, -Y
1001 000d dddd 1100     ld      rd, X
1001 000d dddd 1101     ld      rd, X+
1001 000d dddd 1110     ld      rd, -X
1001 000d dddd 1111     pop     rd
1001 001d dddd 0000(1*k)sts     k, rd
1001 001d dddd 1111     push    rd
1001 001r rrrr 0001     st Z+, rr
1001 001r rrrr 0010     st -Z, rr
1001 001r rrrr 1001     st Y+, rr
1001 001r rrrr 1010     st -Y, rr
1001 001r rrrr 1100     st X, rr
1001 001r rrrr 1101     st X+, rr
1001 001r rrrr 1110     st -X, rr
1001 0100 0000 1000     sec
1001 0100 0001 1000     sez
1001 0100 0010 1000     sen
1001 0100 0011 1000     sev
1001 0100 0100 1000     ses
1001 0100 0101 1000     seh
1001 0100 0110 1000     set
1001 0100 0111 1000     sei
1001 0100 0sss 1000     bset    s
1001 0100 1000 1000     clc
1001 0100 1001 1000     clz
1001 0100 1010 1000     cln
1001 0100 1011 1000     clv
1001 0100 1100 1000     cls
1001 0100 1101 1000     clh
1001 0100 1110 1000     clt
1001 0100 1111 1000     cli
1001 0100 1sss 1000     bclr    s
1001 0100 xxxx 1001     ijmp
1001 0101 0xx0 1000     ret
1001 0101 0xx1 1000     reti
1001 0101 100x 1000     sleep
1001 0101 101x 1000     wdr
1001 0101 110x 1000     lpm
1001 0101 1101 1000     elpm
1001 0101 1110 1000     spm
1001 0101 1111 1000     espm
1001 0101 xxxx 1001     icall
1001 010d dddd 0000     com     rd
1001 010d dddd 0001     neg     rd
1001 010d dddd 0010     swap    rd
1001 010d dddd 0011     inc     rd
1001 010d dddd 0101     asr     rd
1001 010d dddd 0110     lsr     rd
1001 010d dddd 0111     ror     rd
1001 010d dddd 1010     dec     rd
1001 010k kkkk 110k(1*k)jmp     k
1001 010k kkkk 111k(1*k)call    k
1001 0110 kkdd kkkk     adiw    rd, k   (d=24,26,28,30)
1001 0111 kkdd kkkk     sbiw    rd, k   (d=24,26,28,30)
1001 1000 pppp pbbb     cbi     p, b
1001 1001 pppp pbbb     sbic    p, b
1001 1010 pppp pbbb     sbi     p, b
1001 1011 pppp pbbb     sbis    p, b
1001 11rd dddd rrrr     mul     rd, rr
1011 0ppd dddd pppp     in      rd, p
1011 1ppr rrrr pppp     out     p, rr
10q0 qq0d dddd 0qqq     ldd     rd, Z+q
10q0 qq0d dddd 1qqq     ldd     rd, Y+q
10q0 qq1r rrrr 0qqq     std Z+d, rr
10q0 qq1r rrrr 1qqq     std Y+d, rr
1100 kkkk kkkk kkkk     rjmp    k
1101 kkkk kkkk kkkk     rcall   k
1110 1111 dddd 1111     ser     rd      (16<=d<=31)
1110 kkkk dddd kkkk     ldi     rd, k
1111 00kk kkkk k000     brcs/brlo    k
1111 00kk kkkk k001     brne    k
1111 00kk kkkk k010     brmi    k
1111 00kk kkkk k011     brvs    k
1111 00kk kkkk k100     brlt    k
1111 00kk kkkk k101     brhs    k
1111 00kk kkkk k110     brts    k
1111 00kk kkkk k111     brie    k
1111 00kk kkkk ksss     brbs    s, k
1111 01kk kkkk k000     brcc/brsh    k
1111 01kk kkkk k001     breq    k
1111 01kk kkkk k010     brpl    k
1111 01kk kkkk k011     brvc    k
1111 01kk kkkk k100     brge    k
1111 01kk kkkk k101     brhc    k
1111 01kk kkkk k110     brtc    k
1111 01kk kkkk k111     brid    k
1111 01kk kkkk ksss     brbc    s, k
1111 100d dddd 0bbb     bld     rd, b
1111 101d dddd Xbbb     bst     rd, b
1111 110r rrrr xbbb     sbrc    rr, b
1111 111r rrrr xbbb     sbrs    rr, b
*/

inline uint32 code_address(signed int delta)
{
  ea_t newip = cmd.ip + 1 + delta;
  int size = romsize ? romsize : 0x10000;
  return newip % size;
}

//------------------------------------------------------------------------
inline ushort ua_next_full_byte(void)
{
  return (ushort)get_full_byte(cmd.ea + cmd.size++);
}

//--------------------------------------------------------------------------
inline void opreg(op_t &x, uint16 n)
{
  x.type = o_reg;
  x.dtyp = dt_byte;
  x.reg  = n;
}

//--------------------------------------------------------------------------
inline void opimm(op_t &x, int value)
{
  x.type   = o_imm;
  x.dtyp   = dt_byte;
  x.value  = value;
  x.specflag1 = uchar(helper.charval(cmd.ea, ELF_AVR_TAG) == ELF_AVR_LDI_NEG);
}

//--------------------------------------------------------------------------
inline void opnear(op_t &x, ea_t addr)
{
  x.type   = o_near;
  x.dtyp   = dt_code;
  x.addr   = addr;
}

//--------------------------------------------------------------------------
inline void opmem(op_t &x)
{
  x.type   = o_mem;
  x.dtyp   = dt_byte;
  x.offb   = (char)cmd.size;
  x.addr   = ua_next_full_byte();
}

//--------------------------------------------------------------------------
// 0001 10rd dddd rrrr     sub     rd, rr  6
static void tworegs(int code)
{
  opreg(cmd.Op1, (code >> 4) & 31);
  opreg(cmd.Op2, (code & 15) | ((code >> 5) & 16));
}

//--------------------------------------------------------------------------
// 1000 000d dddd 1000     ld      rd, Y
inline void opregd(op_t &x, int code)
{
  opreg(x, (code >> 4) & 31);
}

//--------------------------------------------------------------------------
inline void opphr(op_t &x, phrase_t phrase)
{
  x.type   = o_phrase;
  x.phrase = phrase;
  x.dtyp   = dt_byte;
}

//--------------------------------------------------------------------------
inline void opport(op_t &x, int portnum)
{
  x.type   = o_port;
  x.addr   = portnum;
  x.dtyp   = dt_byte;
}

//--------------------------------------------------------------------------
inline void opdisp(op_t &x, phrase_t phrase, int delta)
{
  if ( delta)
  {
    x.type   = o_displ;
    x.phrase = phrase;
    x.addr   = delta;
    x.dtyp   = dt_byte;
  }
  else
  {
    opphr(x, phrase);
  }
}

//--------------------------------------------------------------------------
int ana(void)
{
//  if ( cmd.ip & 1 ) return 0;           // alignment error
  int code = ua_next_full_byte();
  switch ( code >> 12 )
  {
    case 0:
    case 1:
    case 2:
// 0000 0000 0000 0000     nop             0
// 0000 0001 dddd rrrr     movw    Rd, Rr  0
// 0000 0010 dddd rrrr     muls    Rd, Rr  0
// 0000 0011 0ddd 0rrr     mulsu   Rd, Rr  0
// 0000 0011 0ddd 1rrr     fmul    Rd, Rr  0
// 0000 0011 1ddd 0rrr     fmuls   Rd, Rr  0
// 0000 0011 1ddd 1rrr     fmulsu  Rd, Rr  0
// 0000 01rd dddd rrrr     cpc     rd, rr  1
// 0000 10rd dddd rrrr     sbc     rd, rr  2
// 0000 11rd dddd rrrr     add     rd, rr  3  lsl rd if rd==rr
// 0001 00rd dddd rrrr     cpse    rd, rr  4
// 0001 01rd dddd rrrr     cp      rd, rr  5
// 0001 10rd dddd rrrr     sub     rd, rr  6
// 0001 11rd dddd rrrr     adc     rd, rr  7  rol rd if rd==rr
// 0010 00rd dddd rrrr     and     rd, rr  8  tst rd if rd==rr
// 0010 01rd dddd rrrr     eor     rd, rr  9  clr rd if rd==rr
// 0010 10rd dddd rrrr     or      rd, rr  A
// 0010 11rd dddd rrrr     mov     rd, rr  B
      {
        static uchar itypes[] =
        {
          AVR_nop,      // 0
          AVR_cpc,      // 1
          AVR_sbc,      // 2
          AVR_add,      // 3
          AVR_cpse,     // 4
          AVR_cp,       // 5
          AVR_sub,      // 6
          AVR_adc,      // 7
          AVR_and,      // 8
          AVR_eor,      // 9
          AVR_or,       // A
          AVR_mov       // B
        };
        int idx = (code >> 10) & 15;
        cmd.itype = itypes[idx];
        tworegs(code);
        switch ( idx )
        {
          case 0:
            switch ( (code>>8) & 3 )
            {
              case 0:           // nop
                if ( code != 0 ) return 0;
                cmd.Op1.type = cmd.Op2.type = o_void;
                break;
              case 1:           // movw
                cmd.itype = AVR_movw;
                opreg(cmd.Op1, ((code >> 3) & 30));
                opreg(cmd.Op2, ((code << 1) & 30));
                break;
              case 2:           // muls
                cmd.itype = AVR_muls;
                opreg(cmd.Op1, 16 + (((code >> 4) & 15)));
                opreg(cmd.Op2, 16 + (((code >> 0) & 15)));
                break;
// 0000 0011 0ddd 0rrr     mulsu   Rd, Rr  0
// 0000 0011 0ddd 1rrr     fmul    Rd, Rr  0
// 0000 0011 1ddd 0rrr     fmuls   Rd, Rr  0
// 0000 0011 1ddd 1rrr     fmulsu  Rd, Rr  0
              case 3:           // mulsu, fmul, fmuls, fmulsu
                {
                  int idx = ((code >> 6) & 2) | ((code>>3) & 1);
                  static const uchar itypes[] =
                    { AVR_mulsu, AVR_fmul, AVR_fmuls, AVR_fmulsu };
                  cmd.itype = itypes[idx];
                }
                opreg(cmd.Op1, 16 + (((code >> 4) & 7)));
                opreg(cmd.Op2, 16 + (((code >> 0) & 7)));
                break;
            }
            break;
          case 3: // lsl
            if ( cmd.Op1.reg == cmd.Op2.reg ) cmd.itype = AVR_lsl, cmd.Op2.type = o_void;
            break;
          case 7: // rol
            if ( cmd.Op1.reg == cmd.Op2.reg ) cmd.itype = AVR_rol, cmd.Op2.type = o_void;
            break;
          case 8: // tst
            if ( cmd.Op1.reg == cmd.Op2.reg ) cmd.itype = AVR_tst, cmd.Op2.type = o_void;
            break;
          case 9: // clr
            if ( cmd.Op1.reg == cmd.Op2.reg ) cmd.itype = AVR_clr, cmd.Op2.type = o_void;
            break;
        }
      }
      break;

    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
// 0011 kkkk dddd kkkk     cpi     rd, k   (16<=d<=31)
// 0100 kkkk dddd kkkk     sbci    rd, k   (16<=d<=31)
// 0101 kkkk dddd kkkk     subi    rd, k   (16<=d<=31)
// 0110 kkkk dddd kkkk     ori/sbr rd, k   (16<=d<=31)
// 0111 kkkk dddd kkkk     andi    rd, k   (16<=d<=31) cbr rd, k if op2 is bitwise negated
      {
        static uchar itypes[] =
        {
          AVR_cpi,
          AVR_sbci,
          AVR_subi,
          AVR_ori,
          AVR_andi,
        };
        cmd.itype = itypes[(code >> 12) - 3];
        opreg(cmd.Op1, ((code >> 4) & 15) + 16);
        opimm(cmd.Op2, (code & 0x0F) | ((code >> 4) & 0xF0));
      }
      break;

    case 8:
    case 10:
// 10q0 qq0d dddd 0qqq     ldd     rd, Z+q
// 10q0 qq0d dddd 1qqq     ldd     rd, Y+q
// 10q0 qq1r rrrr 0qqq     std     Z+d, rr
// 10q0 qq1r rrrr 1qqq     std     Y+d, rr
// 1000 000d dddd 0000     ld      rd, Z
// 1000 000d dddd 1000     ld      rd, Y
// 1000 001r rrrr 0000     st      Z, rr
// 1000 001r rrrr 1000     st      Y, rr
      {
        int delta =   ((code & 0x2000) >> 8)
                    | ((code & 0x0C00) >> 7)
                    |  (code & 0x0007);
        if ( code & 0x200 )
        {
          cmd.itype = delta ? AVR_std : AVR_st;
          opdisp(cmd.Op1, (code & 8) ? PH_Y : PH_Z, delta);
          opregd(cmd.Op2, code);
        }
        else
        {
          cmd.itype = delta ? AVR_ldd : AVR_ld;
          opregd(cmd.Op1, code);
          opdisp(cmd.Op2, (code & 8) ? PH_Y : PH_Z, delta);
        }
      }
      break;

    case 9:
      switch ( (code >> 8) & 15 )
      {
        case 0:
        case 1:
        case 2:
        case 3:
// 1001 000d dddd 0000(8*k)lds     rd, k         0
// 1001 000d dddd 0001     ld      rd, Z+        1
// 1001 000d dddd 0010     ld      rd, -Z        2
// 1001 000d dddd 0100     lpm     Rd, Z         4
// 1001 000d dddd 0101     lpm     Rd, Z+        5
// 1001 000d dddd 0110     elpm    Rd, Z         6
// 1001 000d dddd 0111     elpm    Rd, Z+        7
// 1001 000d dddd 1001     ld      rd, Y+        9
// 1001 000d dddd 1010     ld      rd, -Y        A
// 1001 000d dddd 1100     ld      rd, X         C
// 1001 000d dddd 1101     ld      rd, X+        D
// 1001 000d dddd 1110     ld      rd, -X        E
// 1001 000d dddd 1111     pop     rd            F
// 1001 001d dddd 0000(8*k)sts     k, rd         0
// 1001 001r rrrr 0001     st Z+, rr             1
// 1001 001r rrrr 0010     st -Z, rr             2
// 1001 001r rrrr 1001     st Y+, rr             9
// 1001 001r rrrr 1010     st -Y, rr             A
// 1001 001r rrrr 1100     st X, rr              C
// 1001 001r rrrr 1101     st X+, rr             D
// 1001 001r rrrr 1110     st -X, rr             E
// 1001 001d dddd 1111     push    rd            F
          {
            static uchar itypes[] =
            {
              AVR_lds, AVR_ld,  AVR_ld,   0,
              AVR_lpm, AVR_lpm, AVR_elpm, AVR_elpm,
              0,       AVR_ld,  AVR_ld,   0,
              AVR_ld,  AVR_ld,  AVR_ld,   AVR_pop
            };
            cmd.itype = itypes[code & 15];
            opregd(cmd.Op1, code);
            switch ( code & 15 )
            {
              case 0x0:
                opmem(cmd.Op2);
                switch ( helper.charval(cmd.ea+1, ELF_AVR_TAG) )
                {
                  case ELF_AVR_EEP_OFF:
                    cmd.Op2.addr += ELF_AVR_EEPROMBASE-ELF_AVR_RAMBASE;
                  case ELF_AVR_RAM_OFF:
                    cmd.Op2.addr += ELF_AVR_RAMBASE;
                  default:
                    break;
                }
                break;
              case 0x1: opphr(cmd.Op2, PH_ZPLUS);  break;
              case 0x2: opphr(cmd.Op2, PH_MINUSZ); break;
              case 0x4: opphr(cmd.Op2, PH_Z);      break;
              case 0x5: opphr(cmd.Op2, PH_ZPLUS);  break;
              case 0x6: opphr(cmd.Op2, PH_Z);      break;
              case 0x7: opphr(cmd.Op2, PH_ZPLUS);  break;
              case 0x9: opphr(cmd.Op2, PH_YPLUS);  break;
              case 0xA: opphr(cmd.Op2, PH_MINUSY); break;
              case 0xC: opphr(cmd.Op2, PH_X);      break;
              case 0xD: opphr(cmd.Op2, PH_XPLUS);  break;
              case 0xE: opphr(cmd.Op2, PH_MINUSX); break;
              case 0xF:                            break;
              default:  return 0;
            }
            if ( code & 0x200 )
            {
              switch ( cmd.itype )
              {
                case AVR_pop:
                  cmd.itype = AVR_push;
                  break;
                case AVR_lds:
                  cmd.itype = AVR_sts;
                  goto SWAP_OPERANDS;
                case AVR_ld:
                  cmd.itype = AVR_st;
SWAP_OPERANDS:
                  {
                    op_t tmp = cmd.Op1;
                    cmd.Op1 = cmd.Op2;
                    cmd.Op2 = tmp;
                  }
                  break;
                case AVR_lpm:
                case AVR_elpm:
                  return 0;
              }
            }
          }
          break;

        case 4:
        case 5:
          switch ( code & 15 )
          {
            case 9:
// 1001 0100 xxxx 1001     ijmp
// 1001 0101 xxxx 1001     icall
              cmd.itype = (code & 0x100) ? AVR_icall : AVR_ijmp;
              break;
            case 8:
// 1001 0101 0xx0 1000     ret
// 1001 0101 0xx1 1000     reti
// 1001 0101 100x 1000     sleep
// 1001 0101 101x 1000     wdr
// 1001 0101 1100 1000     lpm
// 1001 0101 1101 1000     elpm
// 1001 0101 1110 1000     spm
// 1001 0101 1111 1000     espm
              if ( (code & 0x0F00) == 0x0500 )
              {
                     if ( (code & 0x0090) == 0x0000 ) cmd.itype = AVR_ret;
                else if ( (code & 0x0090) == 0x0010 ) cmd.itype = AVR_reti;
                else if ( (code & 0x00E0) == 0x0080 ) cmd.itype = AVR_sleep;
                else if ( (code & 0x00E0) == 0x00A0 ) cmd.itype = AVR_wdr;
                else if ( (code & 0x00F0) == 0x00C0 ) cmd.itype = AVR_lpm;
                else if ( (code & 0x00F0) == 0x00D0 ) cmd.itype = AVR_elpm;
                else if ( (code & 0x00F0) == 0x00E0 ) cmd.itype = AVR_spm;
                else if ( (code & 0x00F0) == 0x00F0 ) cmd.itype = AVR_espm;
                break;
              }
// 1001 0100 0000 1000     sec                  0
// 1001 0100 0001 1000     sez                  1
// 1001 0100 0010 1000     sen                  2
// 1001 0100 0011 1000     sev                  3
// 1001 0100 0100 1000     ses                  4
// 1001 0100 0101 1000     seh                  5
// 1001 0100 0110 1000     set                  6
// 1001 0100 0111 1000     sei                  7
// 1001 0100 0sss 1000     bset    s
// 1001 0100 1000 1000     clc                  8
// 1001 0100 1001 1000     clz                  9
// 1001 0100 1010 1000     cln                  a
// 1001 0100 1011 1000     clv                  b
// 1001 0100 1100 1000     cls                  c
// 1001 0100 1101 1000     clh                  d
// 1001 0100 1110 1000     clt                  e
// 1001 0100 1111 1000     cli                  f
// 1001 0100 1sss 1000     bclr    s
              {
                static uchar itypes[] =
                {
                  AVR_sec, AVR_sez, AVR_sen, AVR_sev,
                  AVR_ses, AVR_seh, AVR_set, AVR_sei,
                  AVR_clc, AVR_clz, AVR_cln, AVR_clv,
                  AVR_cls, AVR_clh, AVR_clt, AVR_cli,
                };
                cmd.itype = itypes[(code >> 4) & 15];
              }
              break;  // case 8

            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
            case 10:
// 1001 010d dddd 0000     com     rd   0
// 1001 010d dddd 0001     neg     rd   1
// 1001 010d dddd 0010     swap    rd   2
// 1001 010d dddd 0011     inc     rd   3
// 1001 010d dddd 0101     asr     rd   5
// 1001 010d dddd 0110     lsr     rd   6
// 1001 010d dddd 0111     ror     rd   7
// 1001 010d dddd 1010     dec     rd   10
              {
                static uchar itypes[] =
                {
                  AVR_com, AVR_neg, AVR_swap, AVR_inc,
                  0,       AVR_asr, AVR_lsr,  AVR_ror,
                  0,       0,       AVR_dec,
                };
                cmd.itype = itypes[code & 15];
                opregd(cmd.Op1, code);
              }
              break;  // case 8

            case 12:
            case 13:
            case 14:
            case 15:
// 1001 010k kkkk 110k(1*k)jmp     k
// 1001 010k kkkk 111k(1*k)call    k
              cmd.itype = (code & 2) ? AVR_call : AVR_jmp;
              opnear(cmd.Op1, (ea_t((code & 1) | ((code >> 3) & 0x3E)) << 16)
                                                           | ua_next_full_byte());
              if ( helper.charval(cmd.ea+1, ELF_AVR_TAG) == ELF_AVR_ABS_OFF )
                cmd.Op1.addr += ELF_AVR_ABSBASE;
              break;
          }
          break;

        case 6:
        case 7:
// 1001 0110 kkdd kkkk     adiw    rd, k   (d=24,26,28,30)
// 1001 0111 kkdd kkkk     sbiw    rd, k   (d=24,26,28,30)
          cmd.itype = (code & 0x100) ? AVR_sbiw : AVR_adiw;
          opreg(cmd.Op1, R24 + ((code >> 3) & 6));
          opimm(cmd.Op2, ((code >> 2) & 0x30) | (code & 0x0F));
          break;

        case 8:
        case 9:
        case 10:
        case 11:
// 1001 1000 pppp pbbb     cbi     p, b
// 1001 1001 pppp pbbb     sbic    p, b
// 1001 1010 pppp pbbb     sbi     p, b
// 1001 1011 pppp pbbb     sbis    p, b
          {
            static uchar itypes[] = { AVR_cbi, AVR_sbic, AVR_sbi, AVR_sbis };
            cmd.itype = itypes[(code >> 8) & 3];
            opport(cmd.Op1, (code >> 3) & 0x1F);
            opimm (cmd.Op2, code & 7);
          }
          break;

        case 12:
        case 13:
        case 14:
        case 15:
// 1001 11rd dddd rrrr     mul     rd, rr
          cmd.itype = AVR_mul;
          tworegs(code);
          break;
      }
      break;

    case 11:
// 1011 0ppd dddd pppp     in      rd, p
// 1011 1ppr rrrr pppp     out     p, rr
      if ( code & 0x800 )
      {
        cmd.itype = AVR_out;
        opport(cmd.Op1, ((code & 0x0600) >> 5) | (code & 15));
        opregd(cmd.Op2, code);
      }
      else
      {
        cmd.itype = AVR_in;
        opregd(cmd.Op1, code);
        opport(cmd.Op2, ((code & 0x0600) >> 5) | (code & 15));
      }
      break;

    case 12:
    case 13:
// 1100 kkkk kkkk kkkk     rjmp    k
// 1101 kkkk kkkk kkkk     rcall   k
      {
        cmd.itype = (code & 0x1000) ? AVR_rcall : AVR_rjmp;
        signed int delta = (code & 0xFFF);
        if ( delta & 0x800 ) delta |= ~0xFFF;
        opnear(cmd.Op1, code_address(delta));
      }
      break;

    case 14:
// 1110 1111 dddd 1111     ser     rd      (16<=d<=31)
// 1110 kkkk dddd kkkk     ldi     rd, k
      {
        cmd.itype = AVR_ldi;
        opreg(cmd.Op1, ((code >> 4) & 15) + 16);
        int x = ((code >> 4) & 0xF0) | (code & 0x0F);
        if ( x == 0xFF && !get_fixup(cmd.ea, NULL) )
        {
          cmd.itype = AVR_ser;
          break;
        }
        opimm(cmd.Op2, x);
      }
      break;

    case 15:
      switch ( (code >> 9) & 7)
      {
        case 0:
        case 1:
        case 2:
        case 3:
// 1111 00kk kkkk k000     brcs/brlo    k
// 1111 00kk kkkk k001     breq    k
// 1111 00kk kkkk k010     brmi    k
// 1111 00kk kkkk k011     brvs    k
// 1111 00kk kkkk k100     brlt    k
// 1111 00kk kkkk k101     brhs    k
// 1111 00kk kkkk k110     brts    k
// 1111 00kk kkkk k111     brie    k
// 1111 00kk kkkk ksss     brbs    s, k
// 1111 01kk kkkk k000     brcc/brsh    k
// 1111 01kk kkkk k001     brne    k
// 1111 01kk kkkk k010     brpl    k
// 1111 01kk kkkk k011     brvc    k
// 1111 01kk kkkk k100     brge    k
// 1111 01kk kkkk k101     brhc    k
// 1111 01kk kkkk k110     brtc    k
// 1111 01kk kkkk k111     brid    k
// 1111 01kk kkkk ksss     brbc    s, k
          {
            static uchar itypes[] =
            {
              AVR_brcs, AVR_breq, AVR_brmi, AVR_brvs,
              AVR_brlt, AVR_brhs, AVR_brts, AVR_brie,
              AVR_brcc, AVR_brne, AVR_brpl, AVR_brvc,
              AVR_brge, AVR_brhc, AVR_brtc, AVR_brid,
            };
            cmd.itype = itypes[((code >> 7) & 8) | (code & 7)];
            signed int delta = (code >> 3) & 0x7F;
            if ( delta & 0x40 ) delta |= ~0x7F;
            opnear(cmd.Op1, code_address(delta));
          }
          break;
        case 4:
// 1111 100d dddd 0bbb     bld     rd, b
          if ( code & 8 ) return 0;
          cmd.itype = AVR_bld;
          goto REGBIT;
        case 5:
// 1111 101d dddd Xbbb     bst     rd, b
          cmd.itype = AVR_bst;
          goto REGBIT;
        case 6:
// 1111 110r rrrr xbbb     sbrc    rr, b
          cmd.itype = AVR_sbrc;
          goto REGBIT;
        case 7:
          cmd.itype = AVR_sbrs;
// 1111 111r rrrr xbbb     sbrs    rr, b
REGBIT:
          opregd(cmd.Op1, code);
          opimm(cmd.Op2, code & 7);
          break;
      }
      break;
  }
  if ( cmd.itype == AVR_null ) return 0;
  return cmd.size;
}
