#!/usr/bin/env python


import sys
from Fnorb.orb import CORBA, BOA, uuid
from Fnorb.cos.naming import CosNaming
import thread
import DCI, DCI_skel
import Components
import util


######################
class PythonScripting:
  """the implementation class"""


  def doEval( self, code, ctx ):
    """evaluate code and return result"""
    context = self.makeContext( ctx )
    
    print "evaluating :\n <", code, ">\n"
    try:
      val = eval( code, globals(), context )
    except:
      util.debug( code )
      raise DCI.EvalError
    
    print "result was : ", str( val ), "\n\n"
    
    return val
    
    
  def doExec( self, code, ctx ):
    """execute code"""
    context = self.makeContext( ctx )

    print "executing :\n <", code, ">\n\n"
    try:
      exec code in globals(), context
    except:
      util.debug( code )
      raise DCI.ExecError

      
  def makeContext ( self, ctx ):
    """generate a dictionary containing the bindings for all objects from the
    NamingContext"""
    dict = {}
    how_many = 10
    try:
      namecontext = ctx._narrow( CosNaming.NamingContext )
      (binding_list, binding_iterator) = namecontext.list( how_many )

      # process returned bindinglist
      for binding in binding_list:
	name = binding.binding_name
	dict[name[0].id] = namecontext.resolve( name )

      # process iterator
      if binding_iterator:
	(cond, binding) = binding_iterator.next_one()
	while cond:
	  name = binding.binding_name
	  dict[name[0].id] = namecontext.resolve( name )
          (cond, binding) = binding_iterator.next_one()
    except :
      util.debug( "makeContext" )
      
    return dict


######################################################
class Script( PythonScripting, DCI_skel.Script_skel ):
  """class representing a Script object"""


  ##### interface operations #####


  def _get_language( self ):
    return self.language


  def _get_code( self ):
    return self.code


  def _set_code( self, code ):
    self.code = code

    
  def eval( self ):
    """evaluate code and return result"""
    return self.doEval( self.code, self.ctx )
    
    
  def _exec( self ):
    """execute code"""
    self.doExec( self.code, self.ctx )


  def  destroy( self ):
    """deactivates this Script"""
    self.boa.deactivate_obj( self )


  ##### other operations #####


  def __init__ ( self, boa, code, ctx, processor ):
    self.boa = boa
    self.code =code
    self.ctx = ctx
    self.processor = processor
    self.language = "Python"


########################################################################
class ScriptProcessor( PythonScripting, DCI_skel.ScriptProcessor_skel ):
  """this is a Python interpreter"""


  ##### interface operations #####


  def _get_language( self ):
    return self.language

    
  def create_script( self, code, ctx ):
    """create a Script"""
    try:
      obj = self.boa.create( uuid.uuid(), Script._FNORB_ID )
      impl = Script( self.boa, code, ctx, self )
      self.boa.obj_is_ready( obj, impl )
    except:
      util.debug()
      print "..... error while creating script"
    else:
      print "..... new script created"

    return obj


  def eval( self, code, ctx ):
    """evaluate code and return result"""
    return self.doEval( code, ctx )
    
    
  def _exec( self, code, ctx ):
    """execute code"""
    self.doExec( code, ctx )
      

  ##### other operations #####


  def __init__ ( self, orb, boa ):
    # params
    self.orb = orb
    self.boa = boa
    self.language = "Python"

    
######################################################################   
class ScriptProcessorRegistry( DCI_skel.ScriptProcessorRegistry_skel):
  """the registry for ScriptProcessors"""


  ##### interface operations #####


  def get_processor( self, language ):
    """provide a ScriptProcessor for a certain language"""
    try :
    	obj = self.registry[language]
    except :
    	raise( DCI.UnknownLanguage )

    return obj


  def register_processor( self, language, proc):
    """register a ScriptProcessor for a certain language"""
    self.registry[language] = proc
  

  def get_languages( self ):
    return self.registry
    
  
  ##### other operations #####

  
  def __init__ ( self, orb, boa ):
    self.orb = orb
    self.boa = boa
    self.registry = {}

    # register ScriptProcessor for Python
    try :
    	obj = self.boa.create( uuid.uuid(), ScriptProcessor._FNORB_ID )
    	impl = ScriptProcessor( self.orb, self.boa )
    	self.boa.obj_is_ready( obj, impl )
        self.registry["Python"] = obj
    except :
    	util.debug( "register ScriptProcessor for Python" )
	print "..... error with Python script processor"


#orig = thread.start_new_thread
#def snt(function,args,kw={}):
#	print "Starting",function
#	return orig(function,args,kw)
#thread.start_new_thread=snt


##################
def main ( argv ):
  # init ORB
  try:
    argv.append( "--ORBthreading-model=Threaded" )
    orb = CORBA.ORB_init( argv, CORBA.ORB_ID )
    boa = BOA.BOA_init( sys.argv, BOA.BOA_ID )
  except: 
    print "..... can`t initialize ORB"
    sys.exit( 1 )

  # resolve NameService
  try :
    nsior = open( "ns.ior", "r" ).read()
  except :
    print "..... ns.ior file for NameService missing"
    sys.exit( 1 )
    
  try :
    ns = orb.string_to_object( nsior )._narrow( CosNaming.NamingContext )
  except :
    print "..... no NameService IOR in ns.ior file or service not running"
    sys.exit( 1 ) 
  
  # create naming contexts
  nspath = [CosNaming.NameComponent( 'DCI', '' )]
  try:
    for component in nspath :
      ns.bind_new_context( [component] )
  except CosNaming.NamingContext.AlreadyBound:
    pass
    
  # create ScriptProcessorRegistry object
  obj = boa.create( 'ScriptProcessorRegistry', ScriptProcessorRegistry._FNORB_ID )
  impl = ScriptProcessorRegistry( orb, boa )
  boa.obj_is_ready( obj, impl )
  open( "script.ref", "w" ).write( orb.object_to_string( obj ) )
      
  # bind name in name service
  name = nspath + [CosNaming.NameComponent( 'ScriptProcessorRegistry', '' )]
  ns.rebind( name, obj )
  
  # mainloop
  print "..... ScriptProcessorRegistry running with ior:\n"
  print orb.object_to_string( obj )
  boa._fnorb_mainloop()


##############################
# Call main when run as script
if __name__ == '__main__':
  sys.exit( main( sys.argv ) )
