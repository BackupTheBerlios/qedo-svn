#!/usr/bin/env python

import sys
from Fnorb.orb import CORBA, BOA, TkReactor
from Fnorb.cos.naming.NamingContext import NamingContext
from Fnorb.cos.naming import CosNaming
import Tkinter
from Tkconstants import *
import util
import DCI


#################
class TestClient:

  def __init__( self, orb, boa, root ):
    self.orb = orb
    self.boa = boa
    
    self.condition = "1"
    self.action = "TEST.hello()"
    self.frequency = 0
    self.rule = None
    self.id = None
    
    #
    # get reference to testobject
    #
    ior = open( "testobject.ref", "r" ).read()
    try:
      self.test = orb.string_to_object( ior )._narrow( DCI.TestObject )
    except:
      util.debug()
    
    #
    # create NamingContext and insert TEST
    #
    nc = self.boa.create( 'nc', NamingContext._FNORB_ID )
    context = NamingContext()
    self.boa.obj_is_ready( nc, context )
    context.bind( [CosNaming.NameComponent( 'TEST', '' )], self.test )
    self.namespace = nc
    
    #
    # get reference to ScriptProcessor
    #
    try:
      ior = open( "script.ref", "r" ).read()
      self.spr = orb.string_to_object( ior )._narrow( DCI.ScriptProcessorRegistry )
      self.sp = self.spr.get_processor( "Python" )
    except:
      print "..... start script processor first"
      sys.exit( 1 )

    #
    # get reference to RuleProcessor
    #
    try:
      ior = open( "rule.ref", "r" ).read()
      self.rp = orb.string_to_object( ior )._narrow( DCI.RuleProcessor )
    except:
      print "..... start rule processor first"
      sys.exit( 1 )
    
    #
    # create Test-GUI
    #

    # root widget
    self.tk = root
    self.tk.title('TestClient')
    
    # menue
    menubar = Tkinter.Menu(self.tk)
    self.tk.config(menu=menubar)
    controlmenu = Tkinter.Menu(menubar)
    menubar.add_cascade(label="Control", menu=controlmenu)
    controlmenu.add_command(label="Quit", command=self.quit)
    helpmenu = Tkinter.Menu(menubar)
    menubar.add_cascade(label="Help", menu=helpmenu)
    
    # quit button and clear button
    quitframe = Tkinter.Frame(self.tk, relief=FLAT, borderwidth=2)
    quitbutton = Tkinter.Button ( quitframe, fg="red", text="quit", command=self.quit )
    quitbutton.pack(side=RIGHT, expand=1)
    clearbutton = Tkinter.Button ( quitframe, text="clear", command=self.clear )
    clearbutton.pack(side=RIGHT,expand=1)
    quitframe.pack(side=BOTTOM, anchor=S, expand=0, fill=X)
    
    # condition
    cframe = Tkinter.Frame(self.tk, relief=RIDGE, borderwidth=2)
    cframeleft = Tkinter.Frame(cframe)
    self.ctext = Tkinter.Text(cframeleft, width=40, height=5)
    self.ctext.insert(END, self.condition)
    self.ctext.pack(side=LEFT, expand=1, fill=BOTH)
    cframeright = Tkinter.Frame(cframe)
    clabel = Tkinter.Label(cframeright, anchor=NW, text="condition")
    cbutton = Tkinter.Button(cframeright, text="eval", command=self.eval )
    clabel.pack(side=LEFT, expand=0)
    cbutton.pack(side=LEFT)
    cframeright.pack(side=RIGHT)
    cframeleft.pack(side=LEFT, expand=1, fill=BOTH)
    cframe.pack(expand=1, fill=BOTH)

    # action
    aframe = Tkinter.Frame(self.tk, relief=RIDGE, borderwidth=2)
    aframeleft = Tkinter.Frame(aframe)
    self.atext = Tkinter.Text(aframeleft, width=40, height=5)
    self.atext.insert(END, self.action)
    self.atext.pack(side=LEFT,expand=1,fill=BOTH)
    aframeright = Tkinter.Frame(aframe)
    alabel = Tkinter.Label(aframeright, anchor=NW, text="action")
    abutton = Tkinter.Button(aframeright, text="exec", command=self._exec )
    alabel.pack(side=LEFT, expand=0)
    abutton.pack(side=LEFT, anchor=E)
    aframeright.pack(side=RIGHT)
    aframeleft.pack(side=LEFT, expand=1, fill=BOTH)
    aframe.pack(expand=1, fill=BOTH)
    
    # rule
    rframe = Tkinter.Frame(self.tk, relief=RIDGE, borderwidth=2)
    rframeleft = Tkinter.Frame(rframe)
    self.rtext = Tkinter.Text(rframeleft, width=10, height=1)
    self.rtext.insert( END, self.frequency )
    self.rtext.pack( side=LEFT, expand=1, fill=BOTH )
    rframeright = Tkinter.Frame(rframe)
    rlabel = Tkinter.Label(rframeright, text="rule frequency")
    cr_button = Tkinter.Button(rframeright, text="create", command=self.create_rule)
    ex_button = Tkinter.Button(rframeright, text="eval", command=self.eval_rule)
    start_button = Tkinter.Button(rframeright,text="start", command=self.start)
    stop_button = Tkinter.Button(rframeright,text="stop", command=self.stop)
    de_button = Tkinter.Button(rframeright, text="destroy", command=self.destroy_rule)
    rlabel.pack(side=LEFT, expand=0)
    cr_button.pack(side=LEFT, anchor=E)
    ex_button.pack(side=LEFT, anchor=E)
    start_button.pack(side=LEFT, anchor=E)
    stop_button.pack(side=LEFT, anchor=E)
    de_button.pack(side=LEFT, anchor=E)
    rframeright.pack(side=RIGHT)
    rframeleft.pack(side=LEFT, expand=1, fill=BOTH)
    rframe.pack(expand=0, fill=BOTH)

    # status report
    statframe = Tkinter.Frame(self.tk, relief=RIDGE, borderwidth=2)
    statlabel = Tkinter.Label(statframe, fg="blue", text="status report")
    self.stattext = Tkinter.Text(statframe, width=40, height=10)
    statscroll = Tkinter.Scrollbar(statframe,orient=VERTICAL)
    statscroll.config(command=self.stattext.yview)
    self.stattext.config(yscrollcommand=statscroll.set)
    statlabel.pack(side=RIGHT)
    statscroll.pack(side=RIGHT,fill=Y,anchor=E)
    self.stattext.pack(side=LEFT, expand=1, fill=BOTH)
    statframe.pack(expand=1, fill=BOTH)
    

  #evaluate condition
  def eval( self ):
    condition = self.ctext.get("1.0",END)
    try:
      result = self.sp.eval( condition, self.namespace )
    except:
      self.stattext.insert( END, "exception occured during evaluation\n" )
      return
    
    if result:
      message = "evaluated true\n"
    else:
      message = "evaluated false\n"
    self.stattext.insert(END, message)
  
  
  #execute action
  def _exec( self ):
    action = self.atext.get("1.0",END)
    try:
      self.sp._exec( action, self.namespace )
    except:
      self.stattext.insert( END, "exception occured during execution\n" )
  
  
  #create rule
  def create_rule( self ):
    condition = self.ctext.get("1.0",END)
    action = self.atext.get("1.0",END)
    frequency = self.rtext.get("1.0",END)
    cond = self.sp.create_script( condition, self.namespace )
    act = self.sp.create_script( action, self.namespace )
    self.rule = self.rp.create_rule( cond, act, int(frequency) )
    if(self.rule):
      self.stattext.insert(END, "rule created\n")
    else:
      self.stattext.insert(END, "no rule created\n")

  #eval rule
  def eval_rule( self ):
    if not self.rule:
      self.stattext.insert( END, "you have to create a rule first\n" );
      return
    self.rule.eval()
    self.stattext.insert(END, "rule evaluated\n")
  
  #start evaluation
  def start( self ):
    if not self.rule:
      self.stattext.insert( END, "you have to create a rule first\n" );
      return
    try:
      self.rule.start()
    except:
      util.debug( "start error" );
    self.stattext.insert(END, "automatic check started\n")

  # stop evaluation
  def stop(self):
    if not self.rule:
      self.stattext.insert( END, "there is no rule that has to be stopped\n" );
      return
    try:
      self.rule.stop()
    except:
      util.debug( "stop error" );
    self.stattext.insert(END, "automatic check stopped\n")

  #destroy rule
  def destroy_rule( self ):
    if not self.rule:
      self.stattext.insert( END, "you have to create a rule first\n" );
      return
    self.rule.destroy()
    self.rule = None
    self.stattext.insert(END, "rule destroyed\n")
  
  def quit ( self ):
    self.tk.quit()
    self.tk.destroy()

  def clear(self):
    self.stattext.delete("1.0",END)


def main ( argv ):

  # get orb
  try:
    argv.append("--ORBthreading-model=Threaded")
    orb = CORBA.ORB_init(argv, CORBA.ORB_ID)
  except:
    print "Can`t initialize ORB"
    sys.exit(1)
  
  # get boa
  boa = BOA.BOA_init(sys.argv,BOA.BOA_ID)
  
  root = Tkinter.Tk()
  client = TestClient( orb, boa, root )

  # mainloop
  import thread
  thread.start_new_thread( boa._fnorb_mainloop, () )
  root.mainloop()


# main
sys.exit( main( sys. argv ) )
