/***************************************************************************
*
*   *** Copyright (c) Humboldt University of Berlin, Germany,
*   *** Department of Computer Science.
*   *** All rights reserved.
*
*	File	: lexana.h
*	Author	: Harald Böhme
*	e-mail	: boehme@informatik.hu-berlin.de
*	Project : CIDL-Compiler 
*	Date    : Thu Jan  6 14:07:11 MET 2000
*	Remark  : 
***************************************************************************/
#ifndef _LEXANA_H
#define _LEXANA_H

#include <stdio.h>
#include "k.h"
#include <map>
#include <string>
using namespace std;

/* scanning for user inputs */
void scann_file(FILE *);
extern map<string,string> *user_sections;

/* procedures exported by lexana.cpp */
void yyerror_1 (char *, int =-1);

/* procedures exported by lex */
int yylex (void);

/* procedures exported by yacc */
int yyparse (void);

/* set by lex */ /* defined by lex automatically */
extern FILE *yyin;
extern int  yynerrs;
extern char *yytext;
extern int  yyleng;

extern char  *input_basename;
extern idl_name_list g_included_files; /* contains all included files */
void init_lexer(bool with_cidl=false,bool with_psdl=false, bool with_stream=false);

extern cidl_specification Spec;
extern const string& current_prefix();
#endif
