/*
 * 	Rockwell C39 processor module for IDA Pro.
 *	Copyright (c) 2000-2006 Konstantin Norvatoff, <konnor@bk.ru>
 *	Freeware.
 */

#ifndef __INSTRS_HPP
#define __INSTRS_HPP

// ᯨ᮪ ������権
extern instruc_t Instructions[];

//
enum nameNum ENUM_SIZE(uint16)
{
C39_null = 0,           // Unknown Operation
C39_adc,
C39_add,
C39_anc,
C39_and,
C39_ane,
C39_arr,
C39_asl,
C39_asr,
C39_bar,
C39_bas,
C39_bbr,
C39_bbs,
C39_bcc,
C39_bcs,
C39_beq,
C39_bit,
C39_bmi,
C39_bne,
C39_bpl,
C39_bra,
C39_brk,
C39_bvc,
C39_bvs,
C39_clc,
C39_cld,
C39_cli,
C39_clv,
C39_clw,
C39_cmp,
C39_cpx,
C39_cpy,
C39_dcp,
C39_dec,
C39_dex,
C39_dey,
C39_eor,
C39_exc,
C39_inc,
C39_ini,
C39_inx,
C39_iny,
C39_isb,
C39_jmp,
C39_jpi,
C39_jsb,
C39_jsr,
C39_lab,
C39_lae,
C39_lai,
C39_lan,
C39_lax,
C39_lda,
C39_ldx,
C39_ldy,
C39_lii,
C39_lsr,
C39_lxa,
C39_mpa,
C39_mpy,
C39_neg,
C39_nop,
C39_nxt,
C39_ora,
C39_pha,
C39_phi,
C39_php,
C39_phw,
C39_phx,
C39_phy,
C39_pia,
C39_pla,
C39_pli,
C39_plp,
C39_plw,
C39_plx,
C39_ply,
C39_psh,
C39_pul,
C39_rba,
C39_rla,
C39_rmb,
C39_rnd,
C39_rol,
C39_ror,
C39_rra,
C39_rti,
C39_rts,
C39_sax,
C39_sba,
C39_sbc,
C39_sbx,
C39_sec,
C39_sed,
C39_sei,
C39_sha,
C39_shs,
C39_shx,
C39_shy,
C39_slo,
C39_smb,
C39_sre,
C39_sta,
C39_sti,
C39_stx,
C39_sty,
C39_tax,
C39_tay,
C39_taw,
C39_tip,
C39_tsx,
C39_twa,
C39_txa,
C39_txs,
C39_tya,
C39_last
};

#endif
