/*******************************************************************************
*   vim:sw=2:ts=2:et
*   File    : util.k
*   Author  : Harald Böhme
*   e-mail  : boehme@informatik.hu-berlin.de
*   Remark  : 
*   $Date: 2003/05/15 14:21:53 $
*   $Revision: 1.3 $
*   
*******************************************************************************/

%{ KC_TYPES_HEADER

#if !defined(UNUSED) && defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif


%}

%{ KC_UNPARSE
#include "util.h"
%}

%{
static char id[] UNUSED = "$Id: util.k,v 1.3 2003/05/15 14:21:53 boehme Exp $";
%}

/****************** generic parent, printing *************************/

%{ KC_TYPES_HEADER
/* XXX: need auto-initializing pointer */
struct abstract_phylum_zero{
  abstract_phylum val;
  abstract_phylum_zero():val(0){}
};
%}

%member abstract_phylum abstract_phylum::parent_node/*=0*/;
/* some indication flags */
%member int abstract_phylum::flags/*=0*/;
%ctor abstract_phylum() {
  parent_node=0;
  flags=0;
}

void abstract_phylum::gen_parent()
{
  abstract_phylum child;
  for(int i=0;(child= subphylum(i));i++)
    if(child->parent_node != this){
      child->gen_parent();
      child->parent_node = this;
    }
}

abstract_phylum abstract_phylum::get_parent_node()
{
  return parent_node;
}

abstract_phylum get_parent_node(abstract_phylum c)
{
  return c->get_parent_node();
}

/* generic print for gdb */
void print(abstract_phylum node)
{
  if (!node) return;
  node->print();
}

/*
checks whether member is a member of the list
*/
bool
abstract_list::contains(c_abstract_phylum member)
{
  if(subphylum(0)==member) return true;
  abstract_list tail=static_cast<abstract_list>(subphylum(1));
  if(tail) return tail->contains(member);
  return false;
}

bool
NameInList (
  idl_name name,
  idl_name_list namelist)
{
    foreach (listname; idl_name_list namelist)
    {
        if (name->eq(listname))
            /* the casestring is in the list */
            return (true);
    }
    return (false);
} /* NameInList */


idl_name_list 
AddNameToSet(
  idl_name name,
  idl_name_list set)
{
    if (! NameInList (name, set))
        return (Considl_name_list (name, set));
    else
        return (set);
} /* AddNameToSet */


// Singleton Phylum Variables
%{ KC_TYPES_HEADER
// Node flags
extern node_flag                      the_HomeN;
extern node_flag                      the_ComponentN;
extern node_flag                      the_InterfaceN;
extern node_flag                      the_ModuleN;
extern node_flag                      the_CatalogN;
extern node_flag                      the_CatalogLabelN;
extern node_flag                      the_StorageTypeN;
extern node_flag                      the_StorageHomeN;
extern node_flag                      the_AbstractStorageTypeN;
extern node_flag                      the_AbstractStorageHomeN;
extern node_flag                      the_ValueTypeN;
extern node_flag                      the_EventTypeN;
extern node_flag                      the_ValueBoxN;
extern node_flag                      the_OpN;
extern node_flag                      the_TypeN;
extern node_flag                      the_ExceptionN;
extern node_flag                      the_ConstantN;
extern node_flag                      the_ProvidesN;
extern node_flag                      the_PsdlStateN;
extern node_flag                      the_KeyN;
extern node_flag                      the_ElementN;
extern node_flag                      the_NilN;
extern node_flag                      the_EmitsDclN;
extern node_flag                      the_PublishesDclN;
extern node_flag                      the_ConsumesDclN;
extern node_flag                      the_StreamTypeN;
extern node_flag                      the_SourceN;
extern node_flag                      the_SinkN;
extern node_flag                      the_SiSoN;

%}

%{
// Node flags
node_flag the_HomeN = HomeN();
node_flag the_ComponentN = ComponentN();
node_flag the_InterfaceN = InterfaceN();
node_flag the_ModuleN = ModuleN();
node_flag the_CatalogN = CatalogN();
node_flag the_CatalogLabelN = CatalogLabelN();
node_flag the_StorageTypeN = StorageTypeN();
node_flag the_StorageHomeN = StorageHomeN();
node_flag the_AbstractStorageTypeN = AbstractStorageTypeN();
node_flag the_AbstractStorageHomeN = AbstractStorageHomeN();
node_flag the_ValueTypeN = ValueTypeN();
node_flag the_EventTypeN = EventTypeN();
node_flag the_ValueBoxN = ValueBoxN();
node_flag the_OpN = OpN();
node_flag the_TypeN = TypeN();
node_flag the_ExceptionN = ExceptionN();
node_flag the_ConstantN = ConstantN();
node_flag the_ProvidesN = ProvidesN();
node_flag the_PsdlStateN = PsdlStateN();
node_flag the_KeyN = KeyN();
node_flag the_ElementN = ElementN();
node_flag the_NilN = NilN();
node_flag the_EmitsDclN = EmitsDclN();
node_flag the_PublishesDclN = PublishesDclN();
node_flag the_ConsumesDclN = ConsumesDclN();
node_flag the_StreamTypeN = StreamTypeN();
node_flag the_SinkN = SinkN();
node_flag the_SourceN = SourceN();
node_flag the_SiSoN = SiSoN();

%}

//
// =========================== functions ================================
//

const char*
get_repid_ident(idl_identifier ident)
{
  with(ident->symtab_entry) {
    TableItem(*,name_v,*) : {
      return get_repid(name_v);
    }
    TableItemDcl(*,*) : {
      with(ident->symtab_entry->symtab_entry) {
        TableItem(*,name_v,*) : {
          return get_repid(name_v);
        }
      }
    }
  }  
}

const char*
get_repid_ident_suffix(idl_identifier ident, char* suffix)
{
  with(ident->symtab_entry) {
    TableItem(*,name_v,*) : {
      return get_repid_suffix(name_v, suffix);
    }
    TableItemDcl(*,*) : {
      with(ident->symtab_entry->symtab_entry) {
        TableItem(*,name_v,*) : {
          return get_repid_suffix(name_v, suffix);
        }
      }
    }
  }  
}

const char*
get_repid(idl_name name_v)
{
  static char buff[1024] ;
  strcpy(buff,"IDL:");
  if(name_v->symtab_entry->scope)
    scope_of(name_v->symtab_entry->scope,buff);
  with(name_v) {
    Name(cs),
    EscapedName(cs) : {
      strcat(buff,cs->name);
      strcat(buff,":1.0");
    }
  }
  return buff;
}

const char*
get_repid(definition def_v,idl_name name_v)
{
  static char buff[1024] ;
  strcpy(buff,"IDL:");
  if(def_v && def_v->prefix.c_str()[0]) {
    strcat(buff,def_v->prefix.c_str());
    strcat(buff,"/");
  }
  if(name_v->symtab_entry->scope)
    scope_of(name_v->symtab_entry->scope,buff);
  with(name_v) {
    Name(cs),
    EscapedName(cs) : {
      strcat(buff,cs->name);
      strcat(buff,":1.0");
    }
  }
  return buff;
}

const char*
get_repid_suffix(idl_name name_v, char* suffix)
{
  static char buff[1024] ;
  strcpy(buff,"IDL:");
  if(name_v->symtab_entry->scope)
    scope_of(name_v->symtab_entry->scope,buff);
  with(name_v) {
    Name(cs),
    EscapedName(cs) : {
      strcat(buff,cs->name);
      strcat(buff, suffix);
      strcat(buff,":1.0");
    }
  }
  return buff;
}

static void
scope_of(table_item $item_v, char* buff)
{
  TableItem(*,EscapedName(cs),*),
  TableItem(*,Name(cs),*) : {
    if(item_v->scope) {
      scope_of(item_v->scope,buff);
    }
    if(strcmp(cs->name,"")) {
      strcat(buff,cs->name);
      strcat(buff,"/");
    }
  }
}

void
openNameSpace(table_item item)
{
  if (item->scope)
  {
    openNameSpace(item->scope);
    with (item->scope)
    {
      TableItem(*,EscapedName(cs),*),
      TableItem(*,Name(cs),*) :
      {
        if (strcmp(cs->name,""))
        {
          Print("namespace ");
          Print(cs->name);
          Print(" {\n");
        }
      }
    }
  }
}

void
closeNameSpace(table_item item)
{
  if (item->scope)
  {
    with (item->scope)
    {
      TableItem(*,EscapedName(cs),*),
      TableItem(*,Name(cs),*) :
      {
        if (strcmp(cs->name,""))
        {
          Print("}\n\n");
        }
      }
    }
    closeNameSpace(item->scope);
  }
}
