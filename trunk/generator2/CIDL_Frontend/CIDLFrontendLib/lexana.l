%{
#include "symtab.h"
#include "yystype.h"
#ifndef YYSTYPE
#define YYSTYPE YYSTYPE
#endif
#include "cidl.h"
#include "lexana.h"
#include <string.h>

using namespace std;

static int state_before_coment = YYSTATE;
static int yylinenumber = 1;
static char filename[1024];
static char first_filename[1024]={0,};
char* input_basename = 0; /* base name of the input file */
idl_name_list g_included_files = 0;
static char *prefix_start;
static char *prefix_end;

static char *my_stream_key_words[] = {
"sink",
"source",
"streamtype",
0};

static char *my_cidl_key_words[] = {
"delegatesto",
"proxy",
"executor",
"segment",
"facet",
"session",
"service",
"process",
"entity",
"bindsto",
"scope",
"context",
"composition",
0};

static char *my_psdl_key_words[] = {
"storagehome",
"storage",
"storedOn",
"ref",
"key",
"primary",
"of",
"as",
"stores",
"storagetype",
"strong",
"state",
"primarykey",
0};

static char *my_key_words[] = {
"private",
"public",
"local",
"abstract",
"provides",
"implements",
"uses",
"readonly",
"ValueBase",
"fixed",
"raises",
"inout",
"out",
"in",
"void",
"oneway",
"exception",
"finder",
"factory",
"setraises",
"getraises",
"attribute",
"wstring",
"string",
"sequence",
"enum",
"default",
"case",
"switch",
"union",
"struct",
"Object",
"any",
"octet",
"boolean",
"wchar",
"char",
"long",
"unsigned",
"short",
"double",
"float",
"native",
"typedef",
"FALSE",
"TRUE",
"<<",
">>",
"const",
"truncatable",
"supports",
"valuetype",
"custom",
"::",
"interface",
"module",
"consumes",
"publishes",
"emits",
"multiple",
"component",
"home",
"manages",
"typeprefix",
"typeid",
"import",
"eventtype",
0};


static char my_buff[1024];

idl_name
MkIdentifier()
{
	idl_name name;
	nocasestring nc = mknocasestring(yytext);
	key_word k=KeyWord(nc);
	if(k->foo) {
		sprintf(my_buff,"found identifier which differs only in capitalization from keyword ('%s')"
		,yytext);
//		yyerror_1(my_buff);
//		exit(1);
	}
	name = Name(mkcasestring(yytext));
	name->filename=mkcasestring(filename);
	name->line=mkinteger(yylinenumber);
	name->nc = nc;
	if(!strcmp(filename,first_filename)) name->code=true;
	return name;
}

idl_name
MkEscapedIdentifier()
{
	idl_name name;
	nocasestring nc = mknocasestring(yytext+1);
	name = EscapedName(mkcasestring(yytext+1));
	name->filename=mkcasestring(filename);
	name->line=mkinteger(yylinenumber);
	name->nc = nc;
	if(!strcmp(filename,first_filename)) name->code=true;
	return name;
}

const_expression
MkIntegerLiteral()
{
	return IntegerLiteral(mkcasestring(yytext));
}

const_expression
MkCharacterLiteral()
{
	return CharacterLiteral(mkcasestring(yytext));
}

const_expression
MkStringLiteral()
{
	return StringLiteral(mkcasestring(yytext));
}

const_expression
MkFixedPtLiteral()
{
	return FixedPtLiteral(mkcasestring(yytext));
}

const_expression
MkFloatingPtLiteral()
{
	return FloatingPtLiteral(mkcasestring(yytext));
}

void
included_files(char* filename)
{
	char *slash=0,*dot=0;
	if(!g_included_files) g_included_files = Nilidl_name_list();
        slash = strrchr(filename,'/');
        if(!slash) slash = filename;
        dot = strchr(slash,'.');
        if(dot) *dot = '\0';
	if(strcmp(slash,input_basename)!=0) {
	  g_included_files = Considl_name_list(Name(mkcasestring(filename)),g_included_files);
	}
	if(dot) *dot = '.';
}

#include <string>
#include <map>
std::map < std::string, std::string > *user_sections;
std::string section;
%}

%option noyywrap
%option never-interactive

S                       [ \t]
D                       [0-9]
L1                      [a-zA-Z]
L2                      [a-zA-Z_]
HEX                     [a-fA-F0-9]
OCT                     [0-7]
EXP                     [Ee][+-]?{D}+
FS                      [lLfF]
IS                      [lLuU]
ENOL                    (\n|\n)


%s psdl
%s cidl
%s cidl_psdl
%s stream

%x userinput
%x sections
%x comment

%%

<sections>.|"\n" {}
<sections>"// BEGIN USER INSERT SECTION "[a-zA-Z_:~]*"\n" {
               BEGIN(userinput);
               section = string(yytext+29,yyleng-30);
               (*user_sections)[section]=string("");
            }
<sections>"// BEGIN USER INSERT SECTION "[a-zA-Z_:~]*
"\n" {
               BEGIN(userinput);
               section = string(yytext+29,yyleng-31);
               (*user_sections)[section]=string("");
            }
<userinput>.|"\n" { (*user_sections)[section]+=yytext[0]; }
<userinput>"// END USER INSERT SECTION "[a-zA-Z_:~]*.*"\n" {
               BEGIN(sections);
               /*fprintf(stderr,"found end section %s\n",section.c_str());
               fprintf(stderr,"contents is '%s'\n",(*user_sections)[section].c_str()); 
               */
               section = "";
            }
"//"[^\n]*		{}
"/*"			{ state_before_coment = YYSTATE; BEGIN(comment); }
<comment>"*/"		{ BEGIN(state_before_coment); }
<comment>[^\n]		{}
<comment>\n		{ yylinenumber++; }

"#"{S}*"include"{S}*[<\"][a-zA-Z\/\._]+[>\"]{S}*\n  {
                    yylval.yt_definition = PreDirect(mkcasestring(yytext)); 
                    yylinenumber++;
                    return PREDIRECT;
                  } 
{S}*"#"{S}*"ifndef"[^\n]*   {}
{S}*"#"{S}*"define"[^\n]*   {}
{S}*"#"{S}*"endif"[^\n]*    {}
{S}*"#"{S}*"pragma"{S}*"prefix"{S}*\"[^\n\"]*\"[^\n]*   {
              prefix_start = strchr(yytext,'"');
              if(prefix_start) {
                prefix_start+=1;
                prefix_end = strchr(prefix_start,'"');
                if(prefix_end) {
                  *prefix_end = '\0';
                  push_prefix(string(prefix_start));
                }
              }
            }
{S}*"#"{S}*"pragma"[^\n]*   {}
"#"{S}*{D}+{S}*\n { fprintf(stderr,">>%s<<\n",yytext); yylinenumber++;}
"#"{S}*{D}+{S}+\n { fprintf(stderr,">>%s<<\n",yytext); yylinenumber++;}
"#"{S}*"line"{S}+{D}+{S}*\n { fprintf(stderr,">>%s<<\n",yytext); yylinenumber++;}
"#"{S}*"line"{S}+{D}+{S}+"\""[^\"]*"\"".*\n {  /* for VC++ as cpp */
              if(sscanf(yytext,"#line %d \"%s\"",&yylinenumber,filename)!=2)
                fprintf(stderr,"Ooops in scanning %s",yytext);
              else if(!input_basename) {
                char *slash=0,*dot=0;
                /* XXX hack remove the trailing " */
                filename[strlen(filename)-1]=0;
                strcpy(first_filename,filename);
                slash = strrchr(first_filename,'/');
                if(!slash) slash = first_filename;
                else slash++;
                dot = strchr(slash,'.');
                if(dot) *dot = '\0';
                input_basename = strdup(slash);
                if(dot) *dot = '.';
              }
	            else {
		            /* XXX hack remove the trailing " */
		            filename[strlen(filename)-1]=0;
                included_files(filename); /* add to list of all included files */
              }
              }


"#"{S}+{D}+{S}+"\""[^\"]*"\"".*\n { 
              if(sscanf(yytext,"# %d \"%s\"",&yylinenumber,filename)!=2)
                fprintf(stderr,"Ooops in scanning %s",yytext);
              else if(!input_basename) {
                char *slash=0,*dot=0;
                /* XXX hack remove the trailing " */
                filename[strlen(filename)-1]=0;
                strcpy(first_filename,filename);
                slash = strrchr(first_filename,'/');
                if(!slash) slash = first_filename;
                else slash++;
                dot = strchr(slash,'.');
                if(dot) *dot = '\0';
                input_basename = strdup(slash);
                if(dot) *dot = '.';
              }
	            else {
		            /* XXX hack remove the trailing " */
		            filename[strlen(filename)-1]=0;
                included_files(filename); /* add to list of all included files */
              }
              }

"private"	{ return TOK_private; }
"public"	{ return TOK_public; }
"local"	{ return TOK_local; }
"abstract"	{ return TOK_abstract; }
"readonly"	{ return TOK_readonly; }
"inout"	{ return TOK_inout; }
"out"	{ return TOK_out; }
"in"	{ return TOK_in; }
"ValueBase"	{ return TOK_ValueBase; }
"Object"	{ return TOK_Object; }
"fixed"	{ return TOK_fixed; }
"void"	{ return TOK_void; }
"string"	{ return TOK_string; }
"wstring"	{ return TOK_wstring; }
"any"	{ return TOK_any; }
"octet"	{ return TOK_octet; }
"boolean"	{ return TOK_boolean; }
"wchar"	{ return TOK_wchar; }
"char"	{ return TOK_char; }
"long"	{ return TOK_long; }
"unsigned"	{ return TOK_unsigned; }
"short"	{ return TOK_short; }
"double"	{ return TOK_double; }
"float"	{ return TOK_float; }
"native"	{ return TOK_native; }
"case"	{ return TOK_case; }
"switch"	{ return TOK_switch; }
"default"	{ return TOK_default; }
"union"	{ return TOK_union; }
"sequence"	{ return TOK_sequence; }
"enum"	{ return TOK_enum; }
"struct"	{ return TOK_struct; }
"typedef"	{ return TOK_typedef; }
"raises"	{ return TOK_raises; }
"oneway"	{ return TOK_oneway; }
"exception"	{ return TOK_exception; }
"finder"	{ return TOK_finder; }
"factory"	{ return TOK_factory; }
"setraises"	{ return TOK_setRaises; }
"getraises"	{ return TOK_getRaises; }
"attribute"	{ return TOK_attribute; }
"FALSE"	{ return TOK_FALSE; }
"TRUE"	{ return TOK_TRUE; }
"<<"	{ return TOK__lt__lt_; }
">>"	{ return TOK__gt__gt_; }
"const"	{ return TOK_const; }
"truncatable"	{ return TOK_truncatable; }
"supports"	{ return TOK_supports; }
"valuetype"	{ return TOK_valuetype; }
"custom"	{ return TOK_custom; }
"::"	{ return TOK__colon__colon_; }
"interface"	{ return TOK_interface; }
"module"	{ return TOK_module; }
"consumes"	{ return TOK_consumes; }
"publishes"	{ return TOK_publishes; }
"emits"	{ return TOK_emits; }
"multiple"	{ return TOK_multiple; }
"uses"	{ return TOK_uses; }
"provides"	{ return TOK_provides; }
"component"	{ return TOK_component; }
"typeprefix"	{ return TOK_typePrefix; }
"typeid"	{ return TOK_typeId; }
"import"	{ return TOK_import; }
"eventtype"	{ return TOK_eventtype; }
"home"	{ return TOK_home; }
"manages"	{ return TOK_manages; }
"primarykey"	{ return TOK_primaryKey; }
<stream,cidl_psdl,cidl>"delegatesto"	{ return TOK_delegatesTo; }
<stream,cidl_psdl,cidl>"proxy"	{ return TOK_proxy; }
<stream,cidl_psdl,cidl>"executor"	{ return TOK_executor; }
<stream,cidl_psdl,cidl>"facet"	{ return TOK_facet; }
<stream,cidl_psdl,cidl>"segment"	{ return TOK_segment; }
<stream,cidl_psdl,cidl>"bindsto"	{ return TOK_bindsTo; }
<stream,cidl_psdl,cidl>"session"	{ return TOK_session; }
<stream,cidl_psdl,cidl>"service"	{ return TOK_service; }
<stream,cidl_psdl,cidl>"process"	{ return TOK_process; }
<stream,cidl_psdl,cidl>"entity"	{ return TOK_entity; }
<stream,cidl_psdl,cidl>"extension" { return TOK_extension; }
<stream,cidl_psdl,cidl>"scope"	{ return TOK_scope; }
<stream,cidl_psdl,cidl>"composition"	{ return TOK_composition; }
<stream,cidl_psdl,cidl>"context"	{ return TOK_context; }
<stream,cidl_psdl,psdl,cidl>"implements"	{ return TOK_implements; }
<stream,cidl_psdl,psdl>"storagehome"	{ return TOK_storagehome; }
<stream,cidl_psdl,psdl>"storage"	{ return TOK_storage; }
<stream,cidl_psdl,psdl>"storedOn"	{ return TOK_storedOn; }
<stream,cidl_psdl,psdl>"ref"	{ return TOK_ref; }
<stream,cidl_psdl,psdl>"key"	{ return TOK_key; }
<stream,cidl_psdl,psdl>"primary"	{ return TOK_primary; }
<stream,cidl_psdl,psdl>"of"	{ return TOK_of; }
<stream,cidl_psdl,psdl>"as"	{ return TOK_as; }
<stream,cidl_psdl,psdl>"stores"	{ return TOK_stores; }
<stream,cidl_psdl,psdl>"storagetype"	{ return TOK_storagetype; }
<stream,cidl_psdl,psdl>"strong"	{ return TOK_strong; }
<stream,cidl_psdl,psdl>"state"	{ return TOK_state; }
"sink" { return TOK_sink; }
"source" { return TOK_source; }
"streamtype" { return TOK_streamtype; }

{L1}({L2}|{D})*  {yylval.yt_idl_name = MkIdentifier(); return TOK_identifier; }
_{L1}({L2}|{D})*  {yylval.yt_idl_name = MkEscapedIdentifier(); return TOK_identifier; }
0[xX]{HEX}+{IS}?  { yylval.yt_const_expression = MkIntegerLiteral(); return integer_literal; }
0{OCT}+{IS}?  { yylval.yt_const_expression = MkIntegerLiteral(); return integer_literal; }
{D}+{IS}?  { yylval.yt_const_expression = MkIntegerLiteral(); return integer_literal; }
"'"\\({OCT}{1,3})"'" { yylval.yt_const_expression = MkCharacterLiteral(); return character_literal; }
"'"\\x({HEX}{1,2})"'" { yylval.yt_const_expression = MkCharacterLiteral(); return character_literal; }
"'"\\u({HEX}{1,4})"'" { yylval.yt_const_expression = MkCharacterLiteral(); return character_literal; }
"'"\\."'" { yylval.yt_const_expression = MkCharacterLiteral(); return character_literal; }
"'"."'" { yylval.yt_const_expression = MkCharacterLiteral(); return character_literal; }
L"'"\\({OCT}{1,3})"'" { return wide_character_literal; }
L"'"\\x({HEX}{1,2})"'" { return wide_character_literal; }
L"'"\\u({HEX}{1,4})"'" { return wide_character_literal; }
L"'"\\."'" { return wide_character_literal; }
L"'"."'" { return wide_character_literal; }

{D}+{EXP}{FS}?		{ yylval.yt_const_expression = MkFloatingPtLiteral(); return floating_pt_literal; }
{D}*"."{D}+{EXP}?{FS}?  { yylval.yt_const_expression = MkFloatingPtLiteral(); return floating_pt_literal; }
{D}+"."{D}*{EXP}?{FS}?	{ yylval.yt_const_expression = MkFloatingPtLiteral(); return floating_pt_literal; }

{D}+[dD] { yylval.yt_const_expression = MkFixedPtLiteral(); return fixed_pt_literal; }
{D}*"."{D}+[dD]   { yylval.yt_const_expression = MkFixedPtLiteral(); return fixed_pt_literal; }
{D}+"."{D}*[dD]  { yylval.yt_const_expression = MkFixedPtLiteral(); return fixed_pt_literal; }

\"[^\n"]*\"     { yylval.yt_const_expression = MkStringLiteral(); return string_literal; }
L\"[^\n"]*\"     { return wide_character_literal; }
\n              { yylinenumber++; }
[\t \r]+          { /* ignored */ }
.               { return yytext[0]; }
%%

void
init_lexer(bool with_cidl,bool with_psdl,bool with_stream)
{
  int i=0;
  while(my_key_words[i]) {
    key_word k = KeyWord(mknocasestring(my_key_words[i++]));
    k->foo=1;
  }
  if(with_cidl) {
    i=0;
    while(my_cidl_key_words[i]) {
      key_word k = KeyWord(mknocasestring(my_cidl_key_words[i++]));
      k->foo=1;
    }
    BEGIN(cidl);
  }
  if(with_psdl) {
    i=0;
    while(my_psdl_key_words[i]) {
      key_word k = KeyWord(mknocasestring(my_psdl_key_words[i++]));
      k->foo=1;
    }
    if(with_cidl) BEGIN(cidl_psdl);
    else BEGIN(psdl);
  }
  /* This will enable all known key words */
  if(with_stream) {
    i=0;
    while(my_stream_key_words[i]) {
      key_word k = KeyWord(mknocasestring(my_stream_key_words[i++]));
      k->foo=1;
    }
    BEGIN(stream);
  }
}

#include "errmsg.cpp"

void 
yyerror_1 (char *s, int state_no)
{
  const char* s1 = "";
  if (state_no >= 0
      && state_no <= sizeof(error_message)/sizeof(error_message[0])
      && error_message[state_no]
      && error_message[state_no][0])
    s1 = error_message[state_no];
  fprintf(stderr, "syntax error in %s at line %d: %s:\n%s\n", filename , yylinenumber, s, s1);
  exit(1);
}

void
scann_file(FILE* file)
{
  int old_state=YYSTATE;
  int i;
  FILE* old_yyin=yyin;
  assert(file);
  yyrestart(file); 

  section = "";
  user_sections = new map<string,string>;
  BEGIN(sections);
  if((i=yylex())) {
    fprintf( stderr, "error(%d) while scanning for user input sections\n",i);
  }
  BEGIN(old_state);
}

