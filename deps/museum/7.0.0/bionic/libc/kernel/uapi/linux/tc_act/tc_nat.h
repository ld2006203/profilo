/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef __LINUX_TC_NAT_H
#define __LINUX_TC_NAT_H
#define _LINUX_TC_NAT_H
#define _LINUX_TC_NAT_H_
#define _UAPI_LINUX_TC_NAT_H
#define _UAPI_LINUX_TC_NAT_H_
#define _UAPI__LINUX_TC_NAT_H
#define _UAPI__LINUX_TC_NAT_H_
#define __LINUX_TC_NAT_H_
#include <museum/7.0.0/bionic/libc/linux/pkt_cls.h>
#include <museum/7.0.0/bionic/libc/linux/types.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define TCA_ACT_NAT 9
enum {
  TCA_NAT_UNSPEC,
  TCA_NAT_PARMS,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
  TCA_NAT_TM,
  __TCA_NAT_MAX
};
#define TCA_NAT_MAX (__TCA_NAT_MAX - 1)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define TCA_NAT_FLAG_EGRESS 1
struct tc_nat {
  tc_gen;
  __be32 old_addr;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
  __be32 new_addr;
  __be32 mask;
  __u32 flags;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#endif
