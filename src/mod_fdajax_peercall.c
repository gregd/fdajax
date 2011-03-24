#line 1 "mod_fdajax_peercall.rl"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mod_fdajax_defs.h"

#line 18 "mod_fdajax_peercall.rl"



#line 13 "mod_fdajax_peercall.c"
static const int fdamod_peercall_start = 1;
static const int fdamod_peercall_first_final = 48;
static const int fdamod_peercall_error = 0;

static const int fdamod_peercall_en_main = 1;

#line 21 "mod_fdajax_peercall.rl"

int mod_fdajax_cinit(int *pcs)
{
	int cs = 0;
	
#line 26 "mod_fdajax_peercall.c"
	{
	cs = fdamod_peercall_start;
	}
#line 26 "mod_fdajax_peercall.rl"
	*pcs = cs;
	return 1;
}

int mod_fdajax_cexec(int *pcs, char *start, size_t len)
{
	char *p, *pe;
	int cs = *pcs;

	assert(*(start + len) == 0);
	p = start;
	pe = start + len + 1;
	
#line 44 "mod_fdajax_peercall.c"
	{
	if ( p == pe )
		goto _out;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 34: goto st2;
		case 45: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st7;
	goto st0;
st0:
	goto _out0;
st2:
	if ( ++p == pe )
		goto _out2;
case 2:
	switch( (*p) ) {
		case 34: goto st3;
		case 92: goto st47;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st2;
st3:
	if ( ++p == pe )
		goto _out3;
case 3:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	goto st0;
st48:
	if ( ++p == pe )
		goto _out48;
case 48:
	goto st0;
st4:
	if ( ++p == pe )
		goto _out4;
case 4:
	switch( (*p) ) {
		case 32: goto st4;
		case 44: goto st5;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _out5;
case 5:
	switch( (*p) ) {
		case 32: goto st5;
		case 34: goto st2;
		case 45: goto st6;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st7;
	goto st0;
st6:
	if ( ++p == pe )
		goto _out6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _out7;
case 7:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st28;
	goto st0;
st8:
	if ( ++p == pe )
		goto _out8;
case 8:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _out9;
case 9:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _out10;
case 10:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _out11;
case 11:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _out12;
case 12:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _out13;
case 13:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _out14;
case 14:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _out15;
case 15:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _out16;
case 16:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st17;
	goto st0;
st17:
	if ( ++p == pe )
		goto _out17;
case 17:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st18;
	goto st0;
st18:
	if ( ++p == pe )
		goto _out18;
case 18:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _out19;
case 19:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _out20;
case 20:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st21;
	goto st0;
st21:
	if ( ++p == pe )
		goto _out21;
case 21:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _out22;
case 22:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _out23;
case 23:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _out24;
case 24:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st25;
	goto st0;
st25:
	if ( ++p == pe )
		goto _out25;
case 25:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st26;
	goto st0;
st26:
	if ( ++p == pe )
		goto _out26;
case 26:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st27;
	goto st0;
st27:
	if ( ++p == pe )
		goto _out27;
case 27:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st3;
	goto st0;
st28:
	if ( ++p == pe )
		goto _out28;
case 28:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st29;
	goto st0;
st29:
	if ( ++p == pe )
		goto _out29;
case 29:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st30;
	goto st0;
st30:
	if ( ++p == pe )
		goto _out30;
case 30:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st31;
	goto st0;
st31:
	if ( ++p == pe )
		goto _out31;
case 31:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st32;
	goto st0;
st32:
	if ( ++p == pe )
		goto _out32;
case 32:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st33;
	goto st0;
st33:
	if ( ++p == pe )
		goto _out33;
case 33:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st34;
	goto st0;
st34:
	if ( ++p == pe )
		goto _out34;
case 34:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st35;
	goto st0;
st35:
	if ( ++p == pe )
		goto _out35;
case 35:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st36;
	goto st0;
st36:
	if ( ++p == pe )
		goto _out36;
case 36:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _out37;
case 37:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st38;
	goto st0;
st38:
	if ( ++p == pe )
		goto _out38;
case 38:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _out39;
case 39:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st40;
	goto st0;
st40:
	if ( ++p == pe )
		goto _out40;
case 40:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st41;
	goto st0;
st41:
	if ( ++p == pe )
		goto _out41;
case 41:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st42;
	goto st0;
st42:
	if ( ++p == pe )
		goto _out42;
case 42:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st43;
	goto st0;
st43:
	if ( ++p == pe )
		goto _out43;
case 43:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st44;
	goto st0;
st44:
	if ( ++p == pe )
		goto _out44;
case 44:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st45;
	goto st0;
st45:
	if ( ++p == pe )
		goto _out45;
case 45:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st46;
	goto st0;
st46:
	if ( ++p == pe )
		goto _out46;
case 46:
	switch( (*p) ) {
		case 0: goto st48;
		case 32: goto st4;
		case 44: goto st5;
		case 46: goto st8;
	}
	goto st0;
st47:
	if ( ++p == pe )
		goto _out47;
case 47:
	switch( (*p) ) {
		case 34: goto st2;
		case 92: goto st2;
		case 102: goto st2;
		case 110: goto st2;
		case 114: goto st2;
		case 116: goto st2;
	}
	goto st0;
	}
	_out0: cs = 0; goto _out; 
	_out2: cs = 2; goto _out; 
	_out3: cs = 3; goto _out; 
	_out48: cs = 48; goto _out; 
	_out4: cs = 4; goto _out; 
	_out5: cs = 5; goto _out; 
	_out6: cs = 6; goto _out; 
	_out7: cs = 7; goto _out; 
	_out8: cs = 8; goto _out; 
	_out9: cs = 9; goto _out; 
	_out10: cs = 10; goto _out; 
	_out11: cs = 11; goto _out; 
	_out12: cs = 12; goto _out; 
	_out13: cs = 13; goto _out; 
	_out14: cs = 14; goto _out; 
	_out15: cs = 15; goto _out; 
	_out16: cs = 16; goto _out; 
	_out17: cs = 17; goto _out; 
	_out18: cs = 18; goto _out; 
	_out19: cs = 19; goto _out; 
	_out20: cs = 20; goto _out; 
	_out21: cs = 21; goto _out; 
	_out22: cs = 22; goto _out; 
	_out23: cs = 23; goto _out; 
	_out24: cs = 24; goto _out; 
	_out25: cs = 25; goto _out; 
	_out26: cs = 26; goto _out; 
	_out27: cs = 27; goto _out; 
	_out28: cs = 28; goto _out; 
	_out29: cs = 29; goto _out; 
	_out30: cs = 30; goto _out; 
	_out31: cs = 31; goto _out; 
	_out32: cs = 32; goto _out; 
	_out33: cs = 33; goto _out; 
	_out34: cs = 34; goto _out; 
	_out35: cs = 35; goto _out; 
	_out36: cs = 36; goto _out; 
	_out37: cs = 37; goto _out; 
	_out38: cs = 38; goto _out; 
	_out39: cs = 39; goto _out; 
	_out40: cs = 40; goto _out; 
	_out41: cs = 41; goto _out; 
	_out42: cs = 42; goto _out; 
	_out43: cs = 43; goto _out; 
	_out44: cs = 44; goto _out; 
	_out45: cs = 45; goto _out; 
	_out46: cs = 46; goto _out; 
	_out47: cs = 47; goto _out; 

	_out: {}
	}
#line 39 "mod_fdajax_peercall.rl"
	*pcs = cs;

	return 1;
}

int mod_fdajax_cfinish(int *pcs)
{
  int cs = *pcs;
  
#line 683 "mod_fdajax_peercall.c"
#line 48 "mod_fdajax_peercall.rl"
  *pcs = cs;

  if (cs == fdamod_peercall_error) {
	  return -1;
  } else if (cs >= fdamod_peercall_first_final) {
	  return 1;
  } 
  return 0;
}
