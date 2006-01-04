// Copyright (C) 1998-2003 Humboldt-University at Berlin, Institute of Informatics
// All rights reserved.
//
// Kimwitu++ is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Kimwitu++ is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Kimwitu++; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

void
yyerror_1(const char *s, int state_no)
{
  int rule_pos, i;

  fprintf(stderr, "error at %s line %d: %s:\n", filename , yylinenumber, s);
  for (rule_pos = error_state[state_no]; error_rules[rule_pos][0] != 0; rule_pos++)
  {
    int rule = error_rules[rule_pos][0];
    int rhs = yyprhs[rule+1];
    int pos = error_rules[rule_pos][1];
    fprintf(stderr, "\t%s ->", yytname[yyr1[rule+1]]);
    for (i = 0; yyrhs[rhs+i] != -1; i++)
    {
      if (i == pos) fprintf(stderr, " .");
      fprintf(stderr, " %s", yytname[yyrhs[rhs+i]]);
    }
    if (i == pos) fprintf(stderr, " .");
    fprintf(stderr, "\n");
  }
  if (strlen(yytext) > 0)
  fprintf(stderr, "\ttoken last read was: '%s'\n", yytext);
  //exit(1);
}
// vim:sts=2:ts=4:cino=g0,t0,\:0
