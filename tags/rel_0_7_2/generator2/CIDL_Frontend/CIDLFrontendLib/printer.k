/*****************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                    */
/*                                                                           */
/* Copyright (c) 2002 by the Qedo Team                                       */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/


%{ HEADER
#include "unpk.h"
#define MSG_BUFF 8192
%}

%{ KC_UNPARSE
#include "printer.h"
%}

%{
static char id[] UNUSED = "";
#include <string.h>
#include "unpk.h"
#include "printer.h"

static struct {
  char msg[MSG_BUFF];
  int  len;
  int lock;
} msg_buffer;

static int bell = 50;   /* line break bell */


#undef DEBUG_FUNCTIONS
%}

/* access to the message buffer */
void init_msg_buf() { 
  switch (msg_buffer.lock++) {
    case 0 : msg_buffer.len=0; msg_buffer.msg[0]='\0'; return;
    case 1 : return;
    default: printer1("Ignored (debug) message log\n",base_uview); return;
} }

char *get_msg_buf() 
{ 
  msg_buffer.msg[msg_buffer.len]=0; 
  return msg_buffer.msg;
}

int  get_msg_pos()  { return msg_buffer.len; }
void put_msg_buf(char c)  { msg_buffer.msg[msg_buffer.len++]=c; }
void free_msg_buf() { msg_buffer.lock--; }

int 
set_bell(int col)
{
  int prev = bell;
  bell = col;
  return prev;
}

/* the dummy printer, do nothing */
void printer(const char* s,uview v){}

/* print to standard error directly */
void printer1(const char* s,uview v)
{ fprintf(stderr,"%s",s); }

/* print to standard output directly */
void printer2(const char* s,uview v)
{ printf("%s",s); }

/* put the string into the message buffer and break long lines */
void printer4(const char* s,uview v)
{ 
  static int col;
  static bool overflow = false;
  char *msg;
  int len = strlen(s);
  if (!msg_buffer.len) col = 0;
  if (len+msg_buffer.len > (int)sizeof(msg_buffer.msg)-2) {
    if (overflow) return;
    fprintf(stderr, "internal warning: printer.k(4) message buffer overflow\n");
    overflow = true;
    return;
  } else {
    overflow = false;
  }
  if (col+len < bell) {
    strcpy(msg_buffer.msg+msg_buffer.len, s);
    msg_buffer.len += len;
    col += len;
    return;
  }
  msg = msg_buffer.msg+msg_buffer.len;
  while (*s) {
    if ((++col>bell) && (*s == ' ' || *s == '\n')) {
      col = 0; s++;
      *msg++ = '\n'; *msg++ = ' ';
      msg_buffer.len += 2;
    } else {
      *msg++ = *s++;
      msg_buffer.len++;
    }
  }
}

/* put the string into the message buffer */
void printer5(const char* s,uview v)
{ 
  static bool overflow = false;
  int len = strlen(s);
  if ((unsigned)len+msg_buffer.len >= sizeof(msg_buffer.msg)-2) {
    if (overflow) return;
    fprintf(stderr, "internal warning: printer.k(5) message buffer overflow\n");
    overflow = true;
    return;
  } else {
    overflow = false;
  }
  strcpy(msg_buffer.msg+msg_buffer.len, s);
  msg_buffer.len += len;
  return;
}

/* print to stderr and break long lines, reset on \n */
void printer7(const char* s,uview v)
{ 
  static int col;
  char msg[2];
  msg[1] = '\0';
  while (*s) {
    if ((++col>bell) && (*s == ' ' || *s == '\n')) {
      col = 0; 
      printer1("\n",v);
    } else {
      msg[0] = *s;
      printer1(msg,v);
      if (*s == '\n') col=0;
    }
    s++;
  }
  fflush(stderr);
}


