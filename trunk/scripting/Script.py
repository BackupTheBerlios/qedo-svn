#!/usr/bin/env python


import sys
import Tkinter
from Tkconstants import *
from tkMessageBox import *
from Fnorb.orb import CORBA, BOA, uuid
from Fnorb.cos.naming import CosNaming
import thread
import DCI, DCI_skel
import Components
import util


######################
class PythonScripting:
  """the implementation class"""


  def doEval( self, code, ctx, text ):
    """evaluate code and return result"""
    context = self.makeContext( ctx )
    
    message = "evaluating : <" + code + ">\n"
    print message
    text.insert( END, message, END )
    
    try:
      val = eval( code, globals(), context )
    except:
      util.debug( code )
      raise DCI.EvalError
    
    print "result was : ", str( val ), "\n\n"
    
    return val
    
    
  def doExec( self, code, ctx, text ):
    """execute code"""
    context = self.makeContext( ctx )

    message = "executing : <" + code + ">\n"
    print message
    text.insert( END, message, END )
    
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
    return self.doEval( self.code, self.ctx, self.processor.text )
    
    
  def _exec( self ):
    """execute code"""
    self.doExec( self.code, self.ctx, self.processor.text )


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
    return self.doEval( code, ctx, self.text )
    
    
  def _exec( self, code, ctx ):
    """execute code"""
    self.doExec( code, ctx, self.text )
      

  ##### other operations #####


  def quit ( self ):
    self.frame.quit()


  def __init__ ( self, orb, boa ):
    # params
    self.orb = orb
    self.boa = boa
    self.language = "Python"

    #
    # GUI
    #
    root = Tkinter.Toplevel()
    self.frame = Tkinter.Frame ( root )

    # quit button
    quitframe = Tkinter.Frame( self.frame, relief=FLAT, borderwidth=2 )
    quitbutton = Tkinter.Button ( quitframe, fg="red", text="quit", command=self.quit )
    quitbutton.pack(side=RIGHT,anchor=CENTER,expand=1)
    quitframe.pack(side=BOTTOM, anchor=S, expand=0, fill=X)
    
    # text
    frame2 = Tkinter.Frame(self.frame)
    self.text = Tkinter.Text(frame2,width=50, height=10)
    self.text.pack(side=LEFT,expand=1,fill=BOTH)
    self.vscroll = Tkinter.Scrollbar(frame2,orient=VERTICAL)
    self.vscroll.pack(side=LEFT,fill=Y,anchor=E)
    self.vscroll.config(command=self.text.yview)
    self.text.config(yscrollcommand=self.vscroll.set)
    frame2.pack(expand=1,fill=BOTH)

    # title
    self.frame.pack(expand=1,fill=BOTH)
    root.title('Python ScriptProcessor')

  
######################################################################   
class ScriptProcessorRegistry( DCI_skel.ScriptProcessorRegistry_skel):
  """the registry for ScriptProcessors"""


  ##### interface operations #####


  def get_processor( self, language ):
    """provide a ScriptProcessor for a certain language"""
    try :
    	obj = self.registry[language]
    except :
	self.text.insert(END,"no processor for " + language + " \n",END)
    	raise( DCI.UnknownLanguage )

    self.text.insert(END,"get_processor for " + language + " \n",END)
    return obj


  def register_processor( self, language, proc):
    """register a ScriptProcessor for a certain language"""
    self.registry[language] = proc
    self.text.insert(END,"registered processor for " + language + " \n",END)
  

  def get_languages( self ):
    self.text.insert(END,"get_languages\n",END)
    return self.registry
    
  
  ##### other operations #####

  
  def quit ( self ):
    # get NameService
    try:
      nsior = open( "ns.ior", "r" ).read()
      ns = self.orb.string_to_object( nsior )._narrow( CosNaming.NamingContext )
    except :
      print "..... no NameService IOR in ns.ior or service not running"
  
    # unbind name in name service
    nspath = [CosNaming.NameComponent('DCI', '')]
    name = nspath + [CosNaming.NameComponent('ScriptProcessorRegistry', '')]
    try:
      ns.unbind( name )
    except:
      print "..... can not unbind in name service"
  
    # deactivate object
    try:
      self.boa.deactivate_obj( self )
    except:
      pass
      
    self.frame.quit()

    
  def __init__ ( self, root, orb, boa ):
    self.orb = orb
    self.boa = boa
    self.registry = {}

    #
    # GUI
    #
    self.frame = Tkinter.Frame ( root )
    root.protocol( "WM_DELETE_WINDOW", self.quit )

    # quit button
    quitframe = Tkinter.Frame( self.frame, relief=FLAT, borderwidth=2 )
    quitbutton = Tkinter.Button ( quitframe, fg="red", text="quit", command=self.quit )
    quitbutton.pack(side=RIGHT,anchor=CENTER,expand=1)
    quitframe.pack(side=BOTTOM, anchor=S, expand=0, fill=X)
    
    # text
    frame2 = Tkinter.Frame(self.frame)
    self.text = Tkinter.Text(frame2,width=50, height=10)
    self.text.pack(side=LEFT,expand=1,fill=BOTH)
    self.vscroll = Tkinter.Scrollbar(frame2,orient=VERTICAL)
    self.vscroll.pack(side=LEFT,fill=Y,anchor=E)
    self.vscroll.config(command=self.text.yview)
    self.text.config(yscrollcommand=self.vscroll.set)
    frame2.pack(expand=1,fill=BOTH)

    # title
    self.frame.pack(expand=1,fill=BOTH)
    root.title('ScriptProcessorRegistry')


#orig = thread.start_new_thread
#def snt(function,args,kw={}):
#	print "Starting",function
#	return orig(function,args,kw)
#thread.start_new_thread=snt


##################
def main ( argv ):
  
  # init ORB and BOA
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
  root = Tkinter.Tk()
  obj = boa.create( 'ScriptProcessorRegistry', ScriptProcessorRegistry._FNORB_ID )
  impl = ScriptProcessorRegistry( root, orb, boa )
  boa.obj_is_ready( obj, impl )
  open( "script.ref", "w" ).write( orb.object_to_string( obj ) )
      
  # bind name in name service
  name = nspath + [CosNaming.NameComponent( 'ScriptProcessorRegistry', '' )]
  ns.rebind( name, obj )

  # register ScriptProcessor for Python
  obj2 = boa.create( uuid.uuid(), ScriptProcessor._FNORB_ID )
  impl2 = ScriptProcessor( orb, boa )
  boa.obj_is_ready( obj2, impl2 )
  impl.register_processor( "Python", obj2 )
  
  # mainloop
  print "..... ScriptProcessorRegistry running with ior:\n"
  print orb.object_to_string( obj )
  #boa._fnorb_mainloop()
  thread.start_new_thread(boa._fnorb_mainloop,())
  root.mainloop()


##############################
# Call main when run as script
if __name__ == '__main__':
  sys.exit( main( sys.argv ) )
