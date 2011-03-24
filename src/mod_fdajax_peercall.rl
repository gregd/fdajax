#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mod_fdajax_defs.h"

%%{
  machine fdamod_peercall;

  num = (( '-' )? digit {1,20} ( '.' digit {1,20} )? ) ;

  allowed = any -- (cntrl | 127 | "\"" | "\\");
  str_char = allowed | ( "\\" ("\"" | "\\" | "n" | "t" | "f" | "r" ));
  str = "\"" str_char * "\"";

  arg = num | str ;
  main := arg (' '* ',' ' '* arg )* 0 ;
}%%

%% write data;

int mod_fdajax_cinit(int *pcs)
{
	int cs = 0;
	%% write init;
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
	%% write exec;
	*pcs = cs;

	return 1;
}

int mod_fdajax_cfinish(int *pcs)
{
  int cs = *pcs;
  %% write eof;
  *pcs = cs;

  if (cs == fdamod_peercall_error) {
	  return -1;
  } else if (cs >= fdamod_peercall_first_final) {
	  return 1;
  } 
  return 0;
}
