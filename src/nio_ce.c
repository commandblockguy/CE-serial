/**
 * @file nio_ce.c
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @author  Adrien Bertrand aka Adriweb (CE port and mods)
 * @version 4.0
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * Nspire I/O (CE port) implementation file
 */

#include "nio_ce.h"





/**
 * @file charmap.h
 * @author  Manfred Becker <mani.becker@web.de>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * This file contains all characters.
 */

static const char MBCharSet8x6_definition[256][6] = {
/*000*/ {0x00,0x49,0x7A,0x40,0x00,0x00},
/*001*/ {0x04,0x1E,0x1F,0x1E,0x04,0x00},
/*002*/ {0x1C,0x1C,0x3E,0x1C,0x08,0x00},
/*003*/ {0x10,0x3C,0x7C,0x3C,0x10,0x00},
/*004*/ {0x08,0x1C,0x3E,0x1C,0x1C,0x00},
/*005*/ {0x30,0x48,0x45,0x40,0x20,0x00},
/*006*/ {0x20,0x55,0x56,0x54,0x78,0x00},
/*007*/ {0x7E,0x71,0x49,0x47,0x3F,0x00},
/*008*/ {0x78,0x64,0x54,0x4C,0x3C,0x00},
/*009*/ {0x38,0x45,0x46,0x44,0x38,0x00},
/*010*/ {0x38,0x42,0x44,0x40,0x38,0x00},
/*011*/ {0x7A,0x09,0x12,0x24,0x7A,0x00},
/*012*/ {0x4C,0x52,0x32,0x12,0x12,0x00},
/*013*/ {0x38,0x56,0x55,0x56,0x18,0x00},
/*014*/ {0x7C,0x54,0x56,0x55,0x44,0x00},
/*015*/ {0x38,0x54,0x56,0x55,0x18,0x00},
/*016*/ {0x38,0x55,0x56,0x54,0x18,0x00},
/*017*/ {0x7E,0x09,0x7F,0x49,0x49,0x00},
/*018*/ {0x24,0x54,0x7C,0x54,0x58,0x00},
/*019*/ {0x78,0x14,0x15,0x14,0x78,0x00},
/*020*/ {0x20,0x54,0x55,0x54,0x78,0x00},
/*021*/ {0x78,0x15,0x14,0x15,0x78,0x00},
/*022*/ {0x20,0x55,0x54,0x55,0x78,0x00},
/*023*/ {0x3C,0x43,0x42,0x43,0x3C,0x00},
/*024*/ {0x38,0x45,0x44,0x45,0x38,0x00},
/*025*/ {0x3C,0x41,0x40,0x41,0x3C,0x00},
/*026*/ {0x38,0x42,0x40,0x42,0x38,0x00},
/*027*/ {0x03,0x3B,0x44,0x44,0x44,0x00},
/*028*/ {0x03,0x03,0x7C,0x14,0x14,0x00},
/*029*/ {0x7E,0x01,0x25,0x26,0x18,0x00},
/*030*/ {0x48,0x7E,0x49,0x41,0x42,0x00},
/*031*/ {0x15,0x16,0x7C,0x16,0x15,0x00},
/*032*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*033*/ {0x00,0x00,0x5F,0x00,0x00,0x00},
/*034*/ {0x00,0x07,0x00,0x07,0x00,0x00},
/*035*/ {0x14,0x7F,0x14,0x7F,0x14,0x00},
/*036*/ {0x24,0x2A,0x7F,0x2A,0x12,0x00},
/*037*/ {0x27,0x15,0x6B,0x54,0x72,0x00},
/*038*/ {0x36,0x49,0x56,0x20,0x50,0x00},
/*039*/ {0x00,0x00,0x0B,0x07,0x00,0x00},
/*040*/ {0x00,0x1C,0x22,0x41,0x00,0x00},
/*041*/ {0x00,0x41,0x22,0x1C,0x00,0x00},
/*042*/ {0x2A,0x1C,0x7F,0x1C,0x2A,0x00},
/*043*/ {0x08,0x08,0x3E,0x08,0x08,0x00},
/*044*/ {0x00,0x58,0x38,0x00,0x00,0x00},
/*045*/ {0x08,0x08,0x08,0x08,0x08,0x00},
/*046*/ {0x00,0x60,0x60,0x00,0x00,0x00},
/*047*/ {0x20,0x10,0x08,0x04,0x02,0x00},
/*048*/ {0x3E,0x51,0x49,0x45,0x3E,0x00},
/*049*/ {0x00,0x42,0x7F,0x40,0x00,0x00},
/*050*/ {0x72,0x49,0x49,0x49,0x46,0x00},
/*051*/ {0x22,0x41,0x49,0x49,0x36,0x00},
/*052*/ {0x18,0x14,0x12,0x7F,0x10,0x00},
/*053*/ {0x27,0x45,0x45,0x45,0x39,0x00},
/*054*/ {0x3C,0x4A,0x49,0x49,0x30,0x00},
/*055*/ {0x01,0x71,0x09,0x05,0x03,0x00},
/*056*/ {0x36,0x49,0x49,0x49,0x36,0x00},
/*057*/ {0x06,0x49,0x49,0x29,0x1E,0x00},
/*058*/ {0x00,0x36,0x36,0x00,0x00,0x00},
/*059*/ {0x00,0x5B,0x3B,0x00,0x00,0x00},
/*060*/ {0x08,0x14,0x22,0x41,0x00,0x00},
/*061*/ {0x14,0x14,0x14,0x14,0x14,0x00},
/*062*/ {0x00,0x41,0x22,0x14,0x08,0x00},
/*063*/ {0x02,0x01,0x51,0x09,0x06,0x00},
/*064*/ {0x32,0x49,0x79,0x41,0x3E,0x00},
/*065*/ {0x7C,0x12,0x11,0x12,0x7C,0x00},
/*066*/ {0x41,0x7F,0x49,0x49,0x36,0x00},
/*067*/ {0x3E,0x41,0x41,0x41,0x22,0x00},
/*068*/ {0x41,0x7F,0x41,0x41,0x3E,0x00},
/*069*/ {0x7F,0x49,0x49,0x41,0x41,0x00},
/*070*/ {0x7F,0x09,0x09,0x01,0x01,0x00},
/*071*/ {0x3E,0x41,0x49,0x49,0x3A,0x00},
/*072*/ {0x7F,0x08,0x08,0x08,0x7F,0x00},
/*073*/ {0x00,0x41,0x7F,0x41,0x00,0x00},
/*074*/ {0x20,0x40,0x41,0x3F,0x01,0x00},
/*075*/ {0x7F,0x08,0x14,0x22,0x41,0x00},
/*076*/ {0x7F,0x40,0x40,0x40,0x40,0x00},
/*077*/ {0x7F,0x02,0x0C,0x02,0x7F,0x00},
/*078*/ {0x7F,0x02,0x04,0x08,0x7F,0x00},
/*079*/ {0x3E,0x41,0x41,0x41,0x3E,0x00},
/*080*/ {0x7F,0x09,0x09,0x09,0x06,0x00},
/*081*/ {0x3E,0x41,0x51,0x21,0x5E,0x00},
/*082*/ {0x7F,0x09,0x19,0x29,0x46,0x00},
/*083*/ {0x26,0x49,0x49,0x49,0x32,0x00},
/*084*/ {0x01,0x01,0x7F,0x01,0x01,0x00},
/*085*/ {0x3F,0x40,0x40,0x40,0x3F,0x00},
/*086*/ {0x07,0x18,0x60,0x18,0x07,0x00},
/*087*/ {0x7F,0x20,0x18,0x20,0x7F,0x00},
/*088*/ {0x63,0x14,0x08,0x14,0x63,0x00},
/*089*/ {0x03,0x04,0x78,0x04,0x03,0x00},
/*090*/ {0x61,0x51,0x49,0x45,0x43,0x00},
/*091*/ {0x00,0x7F,0x41,0x41,0x00,0x00},
/*092*/ {0x02,0x04,0x08,0x10,0x20,0x00},
/*093*/ {0x00,0x41,0x41,0x7F,0x00,0x00},
/*094*/ {0x04,0x02,0x01,0x02,0x04,0x00},
/*095*/ {0x40,0x40,0x40,0x40,0x40,0x40},
/*096*/ {0x00,0x00,0x07,0x0B,0x00,0x00},
/*097*/ {0x20,0x54,0x54,0x54,0x38,0x00},
/*098*/ {0x7F,0x28,0x44,0x44,0x38,0x00},
/*099*/ {0x00,0x38,0x44,0x44,0x44,0x00},
/*100*/ {0x38,0x44,0x44,0x28,0x7F,0x00},
/*101*/ {0x38,0x54,0x54,0x54,0x18,0x00},
/*102*/ {0x08,0x7E,0x09,0x01,0x02,0x00},
/*103*/ {0x08,0x54,0x54,0x54,0x3C,0x00},
/*104*/ {0x7F,0x08,0x04,0x04,0x78,0x00},
/*105*/ {0x00,0x44,0x7D,0x40,0x00,0x00},
/*106*/ {0x20,0x40,0x44,0x3D,0x00,0x00},
/*107*/ {0x00,0x7F,0x10,0x28,0x44,0x00},
/*108*/ {0x00,0x41,0x7F,0x40,0x00,0x00},
/*109*/ {0x7C,0x04,0x78,0x04,0x78,0x00},
/*110*/ {0x7C,0x08,0x04,0x04,0x78,0x00},
/*111*/ {0x38,0x44,0x44,0x44,0x38,0x00},
/*112*/ {0x7C,0x14,0x14,0x14,0x08,0x00},
/*113*/ {0x08,0x14,0x14,0x14,0x7C,0x00},
/*114*/ {0x7C,0x08,0x04,0x04,0x08,0x00},
/*115*/ {0x48,0x54,0x54,0x54,0x24,0x00},
/*116*/ {0x00,0x04,0x3F,0x44,0x44,0x00},
/*117*/ {0x3C,0x40,0x40,0x20,0x7C,0x00},
/*118*/ {0x1C,0x20,0x40,0x20,0x1C,0x00},
/*119*/ {0x3C,0x40,0x30,0x40,0x3C,0x00},
/*120*/ {0x44,0x28,0x10,0x28,0x44,0x00},
/*121*/ {0x0C,0x50,0x50,0x50,0x3C,0x00},
/*122*/ {0x44,0x64,0x54,0x4C,0x44,0x00},
/*123*/ {0x00,0x08,0x36,0x41,0x00,0x00},
/*124*/ {0x00,0x00,0x77,0x00,0x00,0x00},
/*125*/ {0x00,0x41,0x36,0x08,0x00,0x00},
/*126*/ {0x08,0x04,0x08,0x10,0x08,0x00},
/*127*/ {0xAA,0x55,0xAA,0x55,0xAA,0x55},
/*128*/ {0x14,0x3E,0x55,0x41,0x22,0x00},
/*129*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*130*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*131*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*132*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*133*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*134*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*135*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*136*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*137*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*138*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*139*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*140*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*141*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*142*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*143*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*144*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*145*/ {0x00,0x00,0x02,0x01,0x00,0x00},
/*146*/ {0x00,0x00,0x02,0x01,0x00,0x00},
/*147*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*148*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*149*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*150*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*151*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*152*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*153*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*154*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*155*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*156*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*157*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*158*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*159*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*160*/ {0x00,0x00,0x00,0x00,0x00,0x00},
/*161*/ {0x00,0x00,0x7D,0x00,0x00,0x00},
/*162*/ {0x18,0x24,0x66,0x24,0x00,0x00},
/*163*/ {0x48,0x7E,0x49,0x41,0x42,0x00},
/*164*/ {0x5A,0x24,0x24,0x24,0x5A,0x00},
/*165*/ {0x15,0x16,0x7C,0x16,0x15,0x00},
/*166*/ {0x00,0x00,0x77,0x00,0x00,0x00},
/*167*/ {0x4A,0x55,0x55,0x29,0x00,0x00},
/*168*/ {0x00,0x01,0x00,0x01,0x00,0x00},
/*169*/ {0x3E,0x49,0x55,0x55,0x3E,0x00},
/*170*/ {0x00,0x24,0x29,0x2A,0x24,0x00},
/*171*/ {0x08,0x14,0x2A,0x14,0x22,0x00},
/*172*/ {0x08,0x08,0x08,0x08,0x38,0x00},
/*173*/ {0x00,0x00,0x08,0x08,0x00,0x00},
/*174*/ {0x3E,0x41,0x5F,0x4B,0x55,0x3E},
/*175*/ {0x02,0x02,0x02,0x02,0x02,0x02},
/*176*/ {0x00,0x02,0x05,0x02,0x00,0x00},
/*177*/ {0x00,0x24,0x2E,0x24,0x00,0x00},
/*178*/ {0x00,0x19,0x15,0x12,0x00,0x00},
/*179*/ {0x00,0x11,0x15,0x0A,0x00,0x00},
/*180*/ {0x00,0x00,0x02,0x01,0x00,0x00},
/*181*/ {0x7C,0x10,0x20,0x20,0x1C,0x00},
/*182*/ {0x02,0x05,0x7F,0x05,0x7F,0x00},
/*183*/ {0x00,0x00,0x08,0x00,0x00,0x00},
/*184*/ {0x00,0x20,0x20,0x30,0x00,0x00},
/*185*/ {0x00,0x02,0x1F,0x00,0x00,0x00},
/*186*/ {0x00,0x17,0x15,0x17,0x00,0x00},
/*187*/ {0x22,0x14,0x2A,0x14,0x08,0x00},
/*188*/ {0x20,0x17,0x28,0x34,0x7A,0x00},
/*189*/ {0x20,0x17,0x08,0x6C,0x52,0x00},
/*190*/ {0x35,0x1A,0x28,0x34,0x7A,0x00},
/*191*/ {0x20,0x50,0x4D,0x40,0x20,0x00},
/*192*/ {0x78,0x15,0x16,0x14,0x78,0x00},
/*193*/ {0x78,0x14,0x16,0x15,0x78,0x00},
/*194*/ {0x78,0x16,0x15,0x16,0x78,0x00},
/*195*/ {0x78,0x16,0x15,0x16,0x79,0x00},
/*196*/ {0x78,0x15,0x14,0x15,0x78,0x00},
/*197*/ {0x78,0x16,0x15,0x16,0x78,0x00},
/*198*/ {0x7E,0x09,0x7F,0x49,0x49,0x00},
/*199*/ {0x1E,0x21,0x61,0x21,0x12,0x00},
/*200*/ {0x7C,0x55,0x56,0x54,0x44,0x00},
/*201*/ {0x7C,0x54,0x56,0x55,0x44,0x00},
/*202*/ {0x7C,0x56,0x55,0x56,0x44,0x00},
/*203*/ {0x7C,0x55,0x54,0x55,0x44,0x00},
/*204*/ {0x00,0x45,0x7E,0x44,0x00,0x00},
/*205*/ {0x00,0x44,0x7E,0x45,0x00,0x00},
/*206*/ {0x00,0x46,0x7D,0x46,0x00,0x00},
/*207*/ {0x00,0x45,0x7C,0x45,0x00,0x00},
/*208*/ {0x49,0x7F,0x49,0x41,0x3E,0x00},
/*209*/ {0x7E,0x09,0x12,0x22,0x7D,0x00},
/*210*/ {0x38,0x45,0x46,0x44,0x38,0x00},
/*211*/ {0x38,0x44,0x46,0x45,0x38,0x00},
/*212*/ {0x38,0x46,0x45,0x46,0x38,0x00},
/*213*/ {0x3A,0x45,0x46,0x45,0x38,0x00},
/*214*/ {0x3C,0x43,0x42,0x43,0x3C,0x00},
/*215*/ {0x00,0x14,0x08,0x14,0x00,0x00},
/*216*/ {0x7E,0x71,0x49,0x47,0x3F,0x00},
/*217*/ {0x3C,0x41,0x42,0x40,0x3C,0x00},
/*218*/ {0x3C,0x40,0x42,0x41,0x3C,0x00},
/*219*/ {0x38,0x42,0x41,0x42,0x38,0x00},
/*220*/ {0x3C,0x41,0x40,0x41,0x3C,0x00},
/*221*/ {0x04,0x08,0x72,0x09,0x04,0x00},
/*222*/ {0x7E,0x24,0x24,0x24,0x18,0x00},
/*223*/ {0x7E,0x01,0x25,0x26,0x18,0x00},
/*224*/ {0x20,0x55,0x56,0x54,0x78,0x00},
/*225*/ {0x20,0x54,0x56,0x55,0x78,0x00},
/*226*/ {0x20,0x56,0x55,0x56,0x78,0x00},
/*227*/ {0x22,0x55,0x56,0x55,0x78,0x00},
/*228*/ {0x20,0x55,0x54,0x55,0x78,0x00},
/*229*/ {0x20,0x56,0x55,0x56,0x78,0x00},
/*230*/ {0x24,0x54,0x7C,0x54,0x58,0x00},
/*231*/ {0x4C,0x52,0x32,0x12,0x12,0x00},
/*232*/ {0x38,0x55,0x56,0x54,0x18,0x00},
/*233*/ {0x38,0x54,0x56,0x55,0x18,0x00},
/*234*/ {0x38,0x56,0x55,0x56,0x18,0x00},
/*235*/ {0x38,0x55,0x54,0x55,0x18,0x00},
/*236*/ {0x00,0x49,0x7A,0x40,0x00,0x00},
/*237*/ {0x00,0x48,0x7A,0x41,0x00,0x00},
/*238*/ {0x00,0x4A,0x79,0x42,0x00,0x00},
/*239*/ {0x00,0x4A,0x78,0x42,0x00,0x00},
/*240*/ {0x30,0x4D,0x4A,0x4D,0x30,0x00},
/*241*/ {0x7A,0x11,0x0A,0x09,0x70,0x00},
/*242*/ {0x38,0x45,0x46,0x44,0x38,0x00},
/*243*/ {0x38,0x44,0x46,0x45,0x38,0x00},
/*244*/ {0x38,0x46,0x45,0x46,0x38,0x00},
/*245*/ {0x3A,0x45,0x46,0x45,0x38,0x00},
/*246*/ {0x38,0x45,0x44,0x45,0x38,0x00},
/*247*/ {0x08,0x08,0x2A,0x08,0x08,0x00},
/*248*/ {0x78,0x64,0x54,0x4C,0x3C,0x00},
/*249*/ {0x38,0x42,0x44,0x40,0x38,0x00},
/*250*/ {0x38,0x40,0x44,0x42,0x38,0x00},
/*251*/ {0x38,0x42,0x41,0x42,0x38,0x00},
/*252*/ {0x38,0x42,0x40,0x42,0x38,0x00},
/*253*/ {0x0C,0x50,0x52,0x51,0x3C,0x00},
/*254*/ {0x7F,0x24,0x24,0x24,0x18,0x00},
/*255*/ {0x0C,0x51,0x50,0x51,0x3C,0x00}
};





bool any_key_pressed(void)
{
    return kb_AnyKey();
}

void wait_key_pressed(void)
{
    while (!any_key_pressed());
}

bool nio_scrbuf_init()
{
    gfx_Begin();
    return true;
}

void nio_scrbuf_clear()
{
    gfx_ZeroScreen();
}

void nio_scrbuf_free()
{
    gfx_End();
}

uint8_t getPaletteColorIndex(unsigned int color)
{
    if(color < 16)
    {
        // To match the nspireio colo enum
        const uint8_t palette[16] = {
                gfx_black,
                gfx_red,
                gfx_green,
                gfx_yellow,
                gfx_blue,
                gfx_purple, // magenta
                gfx_blue,   // cyan
                gfx_white,  // grey
                gfx_black,  // light black
                gfx_red,    // light red
                gfx_green,  // light green
                gfx_yellow, // light yellow
                gfx_blue,   // light blue
                gfx_purple, // light magenta
                gfx_blue,   // light cyan
                gfx_white
        };
        return palette[color];
    }
    else if(color < 232)
    {
        // todo: fix me
        const int rbtable[6] = {0,6,12,18,24,31};
        const int gtable[6] = {0,12,25,37,50,63};
        unsigned int d = color-16;
        return (uint8_t) ((rbtable[d / 36] << 11) + (gtable[(d / 6) % 6] << 5) + rbtable[d % 6]);
    }
    else if(color < 256)
    {
        // todo: fix me
        unsigned int d = color-232;
        return (uint8_t) (((d + 1) << 11) + ((d * 2 + 2) << 5) + (d + 1));
    }
    return 0;
}

void nio_set_global_color(unsigned int color)
{
    gfx_SetColor(getPaletteColorIndex(color));
}

void nio_vram_pixel_set(unsigned int x, unsigned int y)
{
    gfx_SetPixel(x, (uint8_t)y);
}

void nio_vram_fill(unsigned x, unsigned y, unsigned w, unsigned h)
{
    gfx_FillRectangle_NoClip(x, (uint8_t) y, w, (uint8_t) h);
}

void nio_vram_scroll(unsigned x, unsigned y, unsigned w, unsigned h, unsigned scroll) {
    if (!scroll) return;
    gfx_ShiftUp((uint8_t) scroll);

// TODO: support non-full scroll
/*
    unsigned int r = h - scroll;

    uint16_t *p1 = (uint16_t*)gfx_vram+x+SCREEN_WIDTH*y;
    uint16_t *p2 = p1 + SCREEN_WIDTH*scroll;
    size_t n = sizeof(uint16_t)*w;
    for (unsigned int i = 0; i < r; ++i, p1 += SCREEN_WIDTH, p2 += SCREEN_WIDTH)
        memmove(p1, p2, n);
 */

    nio_vram_fill(x, y + h - scroll, w, scroll);
}

void nio_vram_draw(void)
{
    // we could do gfx_Blit...
}

unsigned int nio_cursor_clock(void) {
    return (unsigned int) rtc_Time();
}

unsigned nio_time_get() {
    return (unsigned int) rtc_Time();
}

unsigned char nio_ascii_get(uint8_t* adaptive_cursor_state)
{
    static bool second = false, alpha = false;
    sk_key_t key = os_GetCSC();

    if (key == sk_2nd) {
        second = (bool)!second;
    }
    if (key == sk_Alpha) {
        alpha = (bool)!alpha;
    }

    if (alpha && second) {
        *adaptive_cursor_state = 2; // uppercase alpha cursor
    } else if (alpha) {
        *adaptive_cursor_state = 3; // lowercase alpha cursor
    } else if (second) {
        *adaptive_cursor_state = 1; // arrow cursor
    } else {
        *adaptive_cursor_state = 0; // block cursor
    }

    switch (key)
    {
        case sk_Mode  : return 0;
        case sk_Clear : return NIO_KEY_ESC;

        case sk_DecPnt: return (unsigned char) (alpha ?                 ':'  : '.');
        case sk_Chs   : return (unsigned char) (alpha ?                 '?'  : '-');
        case sk_0     : return (unsigned char) (alpha ?                 ' '  : '0');
        case sk_1     : return (unsigned char) (alpha ? (second ? 'Y' : 'y') : '1');
        case sk_2     : return (unsigned char) (alpha ? (second ? 'Z' : 'z') : '2');
        case sk_3     : return (unsigned char) (alpha ?                 '@'  : '3');
        case sk_4     : return (unsigned char) (alpha ? (second ? 'T' : 't') : '4');
        case sk_5     : return (unsigned char) (alpha ? (second ? 'U' : 'u') : '5');
        case sk_6     : return (unsigned char) (alpha ? (second ? 'V' : 'v') : '6');
        case sk_7     : return (unsigned char) (alpha ? (second ? 'O' : 'o') : '7');
        case sk_8     : return (unsigned char) (alpha ? (second ? 'P' : 'p') : '8');
        case sk_9     : return (unsigned char) (alpha ? (second ? 'Q' : 'q') : '9');

        case sk_Math  : return (unsigned char) (alpha ? (second ? 'A' : 'a') :  0 );
        case sk_Apps  : return (unsigned char) (alpha ? (second ? 'B' : 'b') :  0 );
        case sk_Prgm  : return (unsigned char) (alpha ? (second ? 'C' : 'c') :  0 );
        case sk_Recip : return (unsigned char) (alpha ? (second ? 'D' : 'd') : '\'');
        case sk_Sin   : return (unsigned char) (alpha ? (second ? 'E' : 'e') :  0 );
        case sk_Cos   : return (unsigned char) (alpha ? (second ? 'F' : 'f') :  0 );
        case sk_Tan   : return (unsigned char) (alpha ? (second ? 'G' : 'g') :  0 );
        case sk_Square: return (unsigned char) (alpha ? (second ? 'I' : 'i') : ';');
        case sk_Comma : return (unsigned char) (alpha ? (second ? 'J' : 'j') : ',');
        case sk_LParen: return (unsigned char) (alpha ? (second ? 'K' : 'k') : (second ? '{' : '('));
        case sk_RParen: return (unsigned char) (alpha ? (second ? 'L' : 'l') : (second ? '}' : ')'));
        case sk_Log   : return (unsigned char) (alpha ? (second ? 'N' : 'n') : '%');
        case sk_Ln    : return (unsigned char) (alpha ? (second ? 'S' : 's') : '<');
        case sk_Store : return (unsigned char) (alpha ? (second ? 'X' : 'x') : '>');

        case sk_Add   : return (unsigned char) (alpha ?                 '"'  : '+');
        case sk_Sub   : return (unsigned char) (alpha ? (second ? 'W' : 'w') : (second ? ']' : '-'));
        case sk_Mul   : return (unsigned char) (alpha ? (second ? 'R' : 'r') : (second ? '[' : '*'));
        case sk_Div   : return (unsigned char) (alpha ? (second ? 'M' : 'm') : '/');
        case sk_Power : return (unsigned char) (alpha ? (second ? 'H' : 'h') : '^');

        case sk_Vars  : return '#';
        case sk_Yequ  : return '=';
        case sk_Del   : return '\b';
        case sk_Enter : return '\n';
        case sk_Up    : return NIO_KEY_UP;
        case sk_Down  : return NIO_KEY_DOWN;

        case sk_GraphVar: return 'X'; // why not

        default: return 0; // no key pressed
    }
}

char* nio_get_back_buffer()
{
    return (char*) (gfx_vram + LCD_WIDTH*LCD_HEIGHT); // back buffer since 8bpp
}



/***********************************************************************************************************/



static nio_console* nio_default = NULL;
static unsigned int csl_count = 0;

unsigned char adaptive_cursor[5][6] =
        {
                {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, // block cursor
                {0xF7,0xF3,0x01,0x01,0xF3,0xF7}, // arrow cursor
                {0x83,0xED,0xEE,0xED,0x83,0xFF}, // 'A' cursor
                {0xDF,0xAB,0xAB,0xAB,0xC7,0xFF}, // 'a' cursor
                {0xDB,0x81,0xDB,0xDB,0x81,0xDB}  // '#' cursor
        };

void nio_vram_pixel_putc(int x, int y, char ch, int bgColor, int textColor)
{
    // Put a char in VRAM
    int i, j, pixelOn;
    for(i = 0; i < NIO_CHAR_WIDTH; i++)
    {
        for(j = NIO_CHAR_HEIGHT; j > 0; j--)
        {
            pixelOn = MBCharSet8x6_definition[(unsigned char)ch][i] << j ;
            pixelOn = pixelOn & 0x80 ;
            nio_set_global_color(pixelOn ? textColor : bgColor);
            nio_vram_pixel_set(x+i,y+NIO_CHAR_HEIGHT-j);
        }
    }
}

void nio_vram_pixel_puts(int x, int y, const char* str, int bgColor, int textColor)
{
    // Put a string in VRAM
    int l = strlen(str);
    int i;
    int stop=0;
    int xtemp = x;
    for (i = 0; i < l && !stop; i++)
    {
        nio_vram_pixel_putc(xtemp, y, str[i], bgColor, textColor);
        xtemp += NIO_CHAR_WIDTH;
        if (xtemp >= SCREEN_WIDTH-NIO_CHAR_WIDTH)
        {
            stop=1;
        }
    }
}

void nio_vram_grid_puts(int offset_x, int offset_y, int x, int y, const char *str, unsigned char bgColor, unsigned char textColor)
{
    nio_vram_pixel_puts(offset_x+x*NIO_CHAR_WIDTH,offset_y+y*NIO_CHAR_HEIGHT,str,bgColor,textColor);
}
void nio_vram_grid_putc(int offset_x, int offset_y, int x, int y, char ch, unsigned char bgColor, unsigned char textColor)
{
    nio_vram_pixel_putc(offset_x+x*NIO_CHAR_WIDTH,offset_y+y*NIO_CHAR_HEIGHT,ch,bgColor,textColor);
}

void nio_set_default(nio_console* c)
{
    nio_default = c;
}

void nio_set_idle_callback(nio_console* csl, int (*callback)(void*), void* data)
{
    nio_console_private *c = *csl;
    c->idle_callback = callback;
    c->idle_callback_data = data;
}

bool nio_init(nio_console* csl, int size_x, int size_y, int offset_x, int offset_y, unsigned char background_color, unsigned char foreground_color, const bool drawing_enabled)
{
    uint8_t p;
    nio_console_private *c = *csl = malloc(sizeof(nio_console_private));
    if (!c) goto err;
    memset(c, 0, sizeof(nio_console_private));
    ++csl_count;

    c->max_x = size_x;
    c->max_y = size_y;

    c->offset_x = offset_x;
    c->offset_y = offset_y;

    c->drawing_enabled = drawing_enabled;
    c->default_background_color = background_color;
    c->default_foreground_color = foreground_color;

    c->data = malloc(c->max_x*c->max_y);
    if (!c->data) goto err;
    c->color = malloc(c->max_x*c->max_y*2);
    if (!c->color) goto err;

    c->input_buf = malloc(sizeof(queue));
    if (!c->input_buf) goto err;
    queue_init(c->input_buf);

    c->cursor_enabled = true;
    c->cursor_blink_enabled = true;
    c->cursor_blink_duration = 1;
    c->cursor_type = 4; // Defaults to "adaptive" cursor
    c->cursor_line_width = 1;

    for (p = 0; p <= 5; p++)
        c->cursor_custom_data[p] = 0xFF;

    c->history_line = -1;

    if (!nio_scrbuf_init()) goto err;
    nio_clear(csl);

    return true;

    err:
    nio_free(csl);
    return false;
}

int nio_fflush(nio_console* csl)
{
    nio_console_private *c = *csl;
    int row, col;
    for(row = 0; row < c->max_y; row++)
        for(col = 0; col < c->max_x; col++)
            nio_vram_csl_drawchar(csl,col,row);

    nio_vram_draw();
    return 0;
}

void nio_clear(nio_console* csl)
{
    int i;
    nio_console_private *c = *csl;
    unsigned short color = (c->default_background_color << 8) | c->default_foreground_color;
    memset(c->data,0,c->max_x*c->max_y);
    for(i = 0; i < c->max_x*c->max_y; i++)
    {
        c->color[i] = color;
    }
    c->cursor_x = 0;
    c->cursor_y = 0;
    if(c->drawing_enabled)
    {
        nio_set_global_color(c->default_background_color);
        nio_vram_fill(c->offset_x, c->offset_y, c->max_x*NIO_CHAR_WIDTH, c->max_y*NIO_CHAR_HEIGHT);
        nio_vram_draw();
    }
}

void nio_scroll(nio_console* csl)
{
    nio_console_private *c = *csl;
    memmove(c->data,c->data+c->max_x,c->max_x*(c->max_y-1));
    memmove(c->color,c->color+c->max_x,c->max_x*(c->max_y-1)*2);
    memset(c->data+(c->max_x*(c->max_y-1)),0,c->max_x);
    memset(c->color+(c->max_x*(c->max_y-1)*2),0,c->max_x*2);
    if (c->drawing_enabled) {
        nio_set_global_color(c->default_background_color);
        nio_vram_scroll(c->offset_x, c->offset_y, c->max_x*NIO_CHAR_WIDTH, c->max_y*NIO_CHAR_HEIGHT, NIO_CHAR_HEIGHT);
    }

    if(c->cursor_y > 0)
        c->cursor_y--;
    c->cursor_x = 0;
}

void nio_vram_csl_drawchar(nio_console* csl, int pos_x, int pos_y)
{
    nio_console_private *c = *csl;
    char ch = c->data[pos_y*c->max_x+pos_x];
    unsigned short color = c->color[pos_y*c->max_x+pos_x];

    unsigned char background_color = color >> 8;
    unsigned char foreground_color = color;

    nio_vram_grid_putc(c->offset_x, c->offset_y, pos_x, pos_y, ch == 0 ? ' ' : ch, background_color, foreground_color);
}

void nio_csl_savechar(nio_console* csl, char ch, int pos_x, int pos_y)
{
    nio_console_private *c = *csl;
    unsigned short color = (c->default_background_color << 8) | c->default_foreground_color;

    c->data[pos_y*c->max_x+pos_x] = ch;
    c->color[pos_y*c->max_x+pos_x] = color;
}

nio_console* nio_get_default(void)
{
    return nio_default;
}

static uint8_t adaptive_cursor_state = 0;
int nio_getch(nio_console* csl)
{
    nio_console_private *c = *csl;
    unsigned char tmp = 0;
    while(tmp == 0)
    {
        while(!any_key_pressed())
        {
            nio_cursor_blinking_draw(csl);
            if(c->idle_callback)
            {
                if(c->idle_callback(c->idle_callback_data) != 0)
                    return 0;
            }
        }

        nio_cursor_erase(csl);

        tmp = nio_ascii_get(&adaptive_cursor_state);

        if (c->cursor_type == 4)
            nio_cursor_custom(csl, &adaptive_cursor[adaptive_cursor_state][0]);
    }

    return tmp;
}

int nio__getch(void)
{
    return nio_getch(nio_default);
}

int nio_getche(nio_console* c)
{
    int tmp = nio_getch(c);
    nio_fputc(tmp,c);
    return tmp;
}

int nio__getche(void)
{
    return nio_getche(nio_default);
}

int nio_vram_fputc(int character, nio_console* csl)
{
    nio_console_private *c = *csl;
    // Newline. Increment Y cursor, set X cursor to zero. Scroll if necessary.
    if(character == '\n')
    {
        c->cursor_x = 0;
        c->cursor_y++;
        // Scrolling necessary?
        if(c->cursor_y >= c->max_y)
        {
            nio_scroll(csl);
        }
    }
        // Carriage return. Set X cursor to zero.
    else if(character == '\r')
    {
        c->cursor_x = 0;
    }
        // Backspace. Decrement X cursor.
    else if(character == '\b')
    {
        if(c->cursor_x > 0)
            c->cursor_x--;
    }
    else if(character == '\t')
    {
        // tabs are 8 character long
        c->cursor_x += 8 - c->cursor_x % 8;
    }
        // Must be a normal character...
    else
    {
        // Store char.
        nio_csl_savechar(csl,character,c->cursor_x,c->cursor_y);

        // Draw it when bool draw is true
        if(c->drawing_enabled) {
            nio_vram_csl_drawchar(csl,c->cursor_x,c->cursor_y);
        }

        // Increment X cursor. It will be checked for validity next time.
        c->cursor_x++;
    }

    // Check if cursor is valid
    if(c->cursor_x >= c->max_x)
    {
        c->cursor_x = 0;
        c->cursor_y++;
    }
    if(c->cursor_y >= c->max_y)
    {
        nio_scroll(csl);
    }
    return character;
}

int nio_fputc(int character, nio_console* csl)
{
    nio_console_private *c = *csl;
    nio_vram_fputc(character, csl);
    ++c->pending;
    if (c->drawing_enabled && (character == '\n' || c->pending >= 512))
    {
        nio_vram_draw();
        c->pending = 0;
    }
    return character;
}

int nio_write(nio_console *c, char *ptr, int len)
{
    int i;
    for (i = len; i > 0; ++ptr, --i)
        nio_vram_fputc(*ptr, c);
    nio_vram_draw();
    return len;
}

int nio_putchar(int character)
{
    return nio_fputc(character,nio_default);
}

int nio_fputs(const char* str, nio_console* c)
{
    while (str && *str)
        nio_fputc(*str++, c);
    return 1;
}

int nio_puts(const char* str)
{
    nio_fputs(str, nio_default);
    nio_fputc('\n', nio_default);
    return 1;
}

int nio_fprintf(nio_console* c, const char *format, ...)
{
    va_list arglist;
    int len = 0;
    char* buf = nio_get_back_buffer();
    va_start(arglist,format);
    if((len = vsprintf(buf,format,arglist)) < 0)
        abort();
    buf[len] = 0;
    nio_fputs(buf,c);
    va_end(arglist);
    return strlen(buf);
}

int nio_printf(const char *format, ...)
{
    va_list arglist;
    int len = 0;
    char* buf = nio_get_back_buffer();
    va_start(arglist,format);
    if((len = vsprintf(buf,format,arglist)) < 0)
        abort();
    buf[len] = 0;
    nio_fputs(buf, nio_default);
    va_end(arglist);
    return strlen(buf);
}

void nio_perror(const char* str)
{
    if (str && *str)
        nio_printf("%s: ", str);
    nio_puts(strerror(errno));
}

void nio_color(nio_console* csl, unsigned char background_color, unsigned char foreground_color)
{
    nio_console_private *c = *csl;
    c->default_background_color = background_color;
    c->default_foreground_color = foreground_color;
}

void nio_drawing_enabled(nio_console* csl, const bool enable_drawing)
{
    nio_console_private *c = *csl;
    c->drawing_enabled = enable_drawing;
}

int nio_fgetc(nio_console* c)
{
    char tmp[2];
    nio_fgets(tmp,2,c);
    return tmp[0];
}

int nio_getchar(void)
{
    return nio_fgetc(nio_default);
}

int nio_read(nio_console *csl, char* str, int num)
{
    nio_console_private *c = *csl;
    int str_pos = 0;
    int i = 0;
    uint8_t cursor;
    static unsigned char char_repeat = 0, tmp = 0;

    if (num < 1)
        return 0;

    for(; str_pos < num - 1 && !queue_empty(c->input_buf); str_pos++)
        str[str_pos] = queue_get(c->input_buf);

    if(str_pos > 0)
    {
        return str_pos;
    }

    while(1)
    {
        nio_cursor_draw(csl);
        c->cursor_blink_status = true;
        nio_cursor_blinking_reset(csl);

        do {
            nio_cursor_blinking_draw(csl);
            char_repeat = tmp;
            tmp = nio_ascii_get(&cursor);
            if (c->cursor_type == 4)
                nio_cursor_custom(csl, &adaptive_cursor[cursor][0]);
        } while(tmp == char_repeat || tmp == 0);
        char_repeat = tmp;
        nio_cursor_erase(csl);

        if(tmp == NIO_KEY_ESC)
        {
            if (c->cursor_x > 0 || i == 0)
                nio_fputc('\n', csl);
            return 0;
        }
        if(tmp == '\n')
        {
            queue_put(c->input_buf, '\n');
            if (c->cursor_x > 0 || i == 0)
                nio_fputc('\n', csl);
            break;
        }
        else if(tmp == '\b')
        {
            if (i > 0)
            {
                if(c->cursor_x == 0 && c->cursor_y > 0)
                {
                    c->cursor_y--;
                    c->cursor_x = c->max_x - 1;
                    nio_fputc(' ', csl);
                    c->cursor_y--;
                    c->cursor_x = c->max_x - 1;
                }
                else
                    nio_fputs("\b \b", csl);
                queue_get_top(c->input_buf);
                i--;
            }
        }
        else if(tmp == NIO_KEY_UP || tmp == NIO_KEY_DOWN)
        {
            if(tmp == NIO_KEY_UP && (++c->history_line == HISTORY_LINES || c->history[c->history_line] == NULL))
                --c->history_line;
            else if(tmp == NIO_KEY_DOWN && (--c->history_line <= -1 || c->history[c->history_line] == NULL))
                ++c->history_line;
            else if(c->history[c->history_line] != NULL)
            {
                while (i--)
                {
                    if (c->cursor_x == 0 && c->cursor_y > 0)
                    {
                        c->cursor_y--;
                        c->cursor_x = c->max_x - 1;
                        nio_fputc(' ', csl);
                        c->cursor_y--;
                        c->cursor_x = c->max_x - 1;
                    } else {
                        nio_fputs("\b \b", csl);
                    }
                    queue_get_top(c->input_buf);
                }
                ++i;

                {
                    const char* line = c->history[c->history_line];
                    while (*line && *line != '\n')
                    {
                        queue_put(c->input_buf, *line);
                        nio_fputc(*line++, csl);
                        ++i;
                    }
                }
            }
        }
        else if(tmp == '\t')
        {
            const unsigned int tab_width = 4;
            unsigned int j;
            for(j = 0; j < tab_width; ++j)
            {
                queue_put(c->input_buf, ' ');
                nio_fputc(' ', csl);
            }
            i += tab_width;
        }
        else
        {
            queue_put(c->input_buf, tmp);
            nio_fputc(tmp, csl);
            i++;
        }
    }

    for(; str_pos < num && !queue_empty(c->input_buf); str_pos++)
        str[str_pos] = queue_get(c->input_buf);

    if (str[0] != '\n' && (!c->history[0] || strncmp(str, c->history[0], str_pos) || c->history[0][str_pos])) {
        char *s;
        if ((s = strndup(str, str_pos)))
        {
            unsigned int j;
            free(c->history[HISTORY_LINES - 1]);
            for(j = HISTORY_LINES - 1; j > 0; --j)
                c->history[j] = c->history[j - 1];
            c->history[0] = s;
        }
    }

    c->history_line = -1;

    return str_pos;
}

char *nio_fgets(char* str, int num, nio_console* csl)
{
    int n = 0;

    if (num < 1)
        return NULL;
    else if (num > 1)
    {
        n = nio_read(csl, str, num - 1);
        if (!n)
            return NULL;
    }

    str[n] = '\0';
    return str;
}

char* nio_gets(char* str)
{
    return nio_getsn(str,50);
}

char* nio_getsn(char* str, int num)
{
    int n = 0;

    if (num < 1)
        return NULL;
    else if (num > 1)
    {
        n = nio_read(nio_default, str, num - 1);
        if (!n)
            return NULL;
    }
    if (n > 0 && str[n - 1] == '\n')
        --n;

    str[n] = '\0';
    return str;
}

void nio_free(nio_console* csl)
{
    if (*csl) {
        unsigned int i;
        nio_console_private *c = *csl;
        //if (c->drawing_enabled)
        //  nio_fflush(csl);
        free(c->data);
        free(c->color);
        free(c->input_buf);
        for(i = 0; i < HISTORY_LINES; ++i)
            free(c->history[i]);

        free(c);
        *csl = NULL;
        --csl_count;
        if (!csl_count)
            nio_scrbuf_free();
    }
}



/***********************************************************************************************************/



void nio_cursor_draw(nio_console* csl)
{
    nio_console_private *c = *csl;
    unsigned short color = c->color[c->cursor_y*c->max_x+c->cursor_x];

    unsigned char foreground_color = color;

    // The starting position of where to draw the cursor
    const unsigned short cursor_x_start = c->offset_x + c->cursor_x*NIO_CHAR_WIDTH;
    const unsigned short cursor_y_start = c->offset_y + (c->cursor_y*NIO_CHAR_HEIGHT) + NIO_CHAR_HEIGHT;

    if((c->drawing_enabled) && (c->cursor_enabled))
    {
        int i, j;
        if (!((c->cursor_type >= 0) && (c->cursor_type <= 4))) {
            // Set the cursor type to a valid one
            c->cursor_type = 0;
        }

        if (c->cursor_type == 0) {
            // Draw a box for the cursor
            nio_set_global_color(foreground_color);
            for(i = 0; i < NIO_CHAR_WIDTH; i++)
            {
                for(j = NIO_CHAR_HEIGHT; j > 0; j--)
                {
                    nio_vram_pixel_set(cursor_x_start+i,cursor_y_start-j);
                }
            }
        } else if (c->cursor_type == 1) {
            // Draw a horizontal underline (underscore) for the cursor

            // Sanity check for cursor_line_width
            if (!((c->cursor_line_width > 0) && (c->cursor_line_width <= NIO_CHAR_HEIGHT))) {
                // Set the cursor width to 1 (regular cursor width)
                c->cursor_line_width = 1;
            }

            // Draw it!
            nio_set_global_color(foreground_color);
            for(i = 0; i < NIO_CHAR_WIDTH; i++)
            {
                //for(j = NIO_CHAR_HEIGHT; j > (NIO_CHAR_HEIGHT - c->cursor_line_width); j--)
                for(j = 0; j < c->cursor_line_width; j++)
                {
                    nio_vram_pixel_set(cursor_x_start+i,cursor_y_start-j-1);
                }
            }
        } else if (c->cursor_type == 2) {
            // Draw a vertical bar for the cursor

            // Sanity check for cursor_line_width
            if (!((c->cursor_line_width > 0) && (c->cursor_line_width <= NIO_CHAR_WIDTH))) {
                // Set the cursor width to 1 (regular cursor width)
                c->cursor_line_width = 1;
            }

            // Draw it!
            nio_set_global_color(foreground_color);
            for(i = 0; i < c->cursor_line_width; i++)
            {
                for(j = NIO_CHAR_HEIGHT; j > 0; j--)
                {
                    nio_vram_pixel_set(cursor_x_start+i,cursor_y_start-j);
                }
            }
        } else if (c->cursor_type == 3 || c->cursor_type == 4) {
            // Draw a custom cursor
            // This uses pretty much the same code as the regular character drawing
            unsigned char background_color = color >> 8;
            int pixelOn;
            // Draw it!
            for (i = 0; i < NIO_CHAR_WIDTH; i++)
            {
                for (j = NIO_CHAR_HEIGHT; j > 0; j--)
                {
                    pixelOn = c->cursor_custom_data[i] << j;
                    pixelOn = pixelOn & 0x80;
                    nio_set_global_color(pixelOn ? foreground_color : background_color);
                    nio_vram_pixel_set(cursor_x_start + i, cursor_y_start - j);
                }
            }
        }
    }
    nio_vram_draw();
}

void nio_cursor_erase(nio_console* csl)
{
    nio_console_private *c = *csl;
    unsigned short color = c->color[c->cursor_y*c->max_x+c->cursor_x];

    char background_color = color >> 8;

    // The starting position of where to draw the cursor
    const unsigned short cursor_x_start = c->offset_x + c->cursor_x*NIO_CHAR_WIDTH;
    const unsigned short cursor_y_start = c->offset_y + (c->cursor_y*NIO_CHAR_HEIGHT) + NIO_CHAR_HEIGHT;

    // Draw a box for the cursor
    if((c->drawing_enabled) && (c->cursor_enabled)) {
        int i, j;
        nio_set_global_color(background_color);
        for(i = 0; i < NIO_CHAR_WIDTH; i++)
        {
            for(j = NIO_CHAR_HEIGHT; j > 0; j--)
            {
                nio_vram_pixel_set(cursor_x_start+i,cursor_y_start-j);
            }
        }
        nio_vram_csl_drawchar(csl,c->cursor_x,c->cursor_y);
    }
    nio_vram_draw();
}

void nio_cursor_blinking_draw(nio_console* csl)
{
    nio_console_private *c = *csl;
    if (!c->cursor_blink_enabled) return;
    if (c->cursor_blink_timestamp == 0) c->cursor_blink_timestamp = nio_cursor_clock();
    if (c->cursor_blink_duration == 0) c->cursor_blink_duration = 1;

    if ((nio_cursor_clock() - c->cursor_blink_timestamp) >= c->cursor_blink_duration) {
        if (c->cursor_blink_status)
            nio_cursor_draw(csl);
        else
            nio_cursor_erase(csl);
        c->cursor_blink_status = !c->cursor_blink_status;
        c->cursor_blink_timestamp = nio_cursor_clock();
    }
}

void nio_cursor_blinking_reset(nio_console* csl)
{
    nio_console_private *c = *csl;
    if (!c->cursor_blink_enabled) return;
    c->cursor_blink_timestamp = nio_cursor_clock();
}

void nio_cursor_enable(nio_console* csl, bool enable_cursor)
{
    nio_console_private *c = *csl;
    c->cursor_enabled = enable_cursor;
    if (!enable_cursor)
        nio_cursor_erase(csl);
    else
        nio_cursor_draw(csl);
}

void nio_cursor_blinking_enable(nio_console* csl, bool enable_cursor_blink)
{
    nio_console_private *c = *csl;
    c->cursor_blink_enabled = enable_cursor_blink;
    if (!enable_cursor_blink) nio_cursor_draw(csl);
}

void nio_cursor_blinking_duration(nio_console* csl, int duration)
{
    nio_console_private *c = *csl;
    c->cursor_blink_duration = (unsigned) duration;
}

void nio_cursor_type(nio_console* csl, int cursor_type)
{
    nio_console_private *c = *csl;
    if (!((c->cursor_type >= 0) && (c->cursor_type <= 4))) {
        // Set the cursor type to a valid one
        cursor_type = 0;
    }
    c->cursor_type = cursor_type;
}

void nio_cursor_width(nio_console* csl, int cursor_width)
{
    nio_console_private *c = *csl;
    c->cursor_line_width = cursor_width;
}

void nio_cursor_custom(nio_console* csl, const unsigned char cursor_data[6])
{
    nio_console_private *c = *csl;
    int i;
    for(i = 0; i <= 5; i++) {
        c->cursor_custom_data[i] = cursor_data[i];
    }
    //memcpy(c->cursor_custom_data, cursor_data, sizeof(cursor_data));
}



/***********************************************************************************************************/



void queue_init(queue* q)
{
    q->start = 0;
    q->end = QUEUE_SIZE - 1;
    q->count = 0;
}

void queue_put(queue* q, char val)
{
    if(q->count >= QUEUE_SIZE)
        return;
    else
    {
        q->end = (q->end + 1) % QUEUE_SIZE;
        q->data[q->end] = val;
        q->count++;
    }
}

char queue_get_top(queue* q)
{
    char val;

    if(q->count <= 0)
        return -1;
    else
    {
        val = q->data[q->end--];
        q->count--;
    }

    return val;
}

char queue_get(queue* q)
{
    char val;

    if(q->count <= 0)
        return -1;
    else
    {
        val = q->data[q->start];
        q->start = (q->start + 1) % QUEUE_SIZE;
        q->count--;
    }

    return val;
}

bool queue_empty(queue* q)
{
    return (q->count <= 0);
}
