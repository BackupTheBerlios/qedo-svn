#!/usr/bin/env python


import sys
import Tkinter
from Tkconstants import *
from tkMessageBox import *
from Fnorb.orb import CORBA, BOA, uuid
from Fnorb.cos.naming import CosNaming
import thread
import threading
import sched
import time
import util
import DCI, DCI_skel
from Script import Script


######################################
class CheckThread( threading.Thread ):
  """thread for automatic check of rules"""

  def __init__( self ):
    threading.Thread.__init__( self )
    
    self.sched = sched.scheduler( time.time, time.sleep )
    self.lock = threading.Lock()
    self.events = {}
    self.removed = []

    # start thread for automatic checks
    self.setDaemon( True )
    self.start()


  def run(self):
    self.sched.enter( 1, 2, self.heartbeat, () )
    print "..... thread for automatic check started"
    self.sched.run()


  def heartbeat( self ):
    self.lock.acquire()
    self.sched.enter( 1, 2, self.heartbeat, () )
    self.lock.release()


  def start_check( self, rule, frequency ):
    """start checking of a rule"""
    id = uuid.uuid()
    self.lock.acquire()
    self.events[id] = self.sched.enter( 0, 1, self.control, ( id, rule, frequency ) )
    self.lock.release()
    print "..... start check for rule ", id
    return id


  def stop_check( self, id ):
    """stop ckecking of a rule"""
    self.lock.acquire()
    
    # get scheduled event
    event = None
    try:
      event = self.events[id]
      del self.events[id]
      self.sched.cancel( event )
    except:
      pass
    
    self.lock.release()
    print "..... stop check for rule ", id
    return

    
  def control( self, id, rule, frequency ):
    """check rule and insert event for next check"""
    print "..... checking"
    self.lock.acquire()
    
    try:
      rule.eval()
    except DCI.StopRule:
      #do not reinsert!
      pass
    except:
      pass
    else:
      self.events[id] = self.sched.enter( frequency, 1, self.control, ( id, rule, frequency ) )
    
    self.lock.release()


################################
class Rule( DCI_skel.Rule_skel):
  """a Rule"""


  ##### interface operations #####


  def _get_active( self ):
    if self.check_id:
      return true
    else:
      return false


  def eval( self ):
    """evaluate the rule ones"""
    # eval condition 
    if self.cond:
      if self.cond.eval():
        self.act._exec()
	return 1
    # if no condition exec action
    else:
      self.act._exec()
      return 1

    return 0
      

  def start( self ):
    """start automatic check"""
    if self.check_id:
      self.scheduler.stop_check( self.check_id )
      self.chek_id = None
      
    if self.frequency == 0:
      self.eval()
    else:
      self.check_id = self.scheduler.start_check( self, self.frequency )
    
  
  def stop( self ):
    """stop automatic check"""
    if self.check_id:
      self.scheduler.stop_check( self.check_id )
      self.chek_id = None


  def destroy( self ):
    """deactivate this Rule"""
    try:
      #self.boa.deactivate_obj( self ) fixme
      pass
    except:
      pass


  ##### other operations #####


  def __init__( self, boa, cond, act, frequency, scheduler ):
    self.boa = boa
    self.cond = cond
    self.act = act
    self.frequency = frequency
    self.scheduler = scheduler
    self.check_id = None  


#####################################################################
class RuleProcessor( DCI_skel.RuleProcessor_skel ):
  """the RuleProcessor"""


  ##### interface operations #####


  def create_rule( self, cond, act, frequency ):
    """create a Rule"""
    obj = self.boa.create( uuid.uuid(), Rule._FNORB_ID )
    impl = Rule( self.boa, cond, act, frequency, self.scheduler )
    self.boa.obj_is_ready( obj, impl )
    print "..... new rule created"
    self.text.insert(END,"new rule created\n",END)

    return obj


  def destroy( self ):
    """deactivate this processor"""
    self.quit()

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
    name = nspath + [CosNaming.NameComponent('RuleProcessor', '')]
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


  def __init__( self, root, orb, boa ):
    self.orb = orb
    self.boa = boa
    self.scheduler = CheckThread()
 
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
    root.title('RuleProcessor')

    
  #to suppress message complaining about no Thread object
  #def _set_daemon(self):
  #  return 0


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

  # get NameService
  try:
    nsior = open( "ns.ior", "r" ).read()
  except:
    print "..... ns.ior file for NameService missing"
    sys.exit( 1 )
    
  try :
    ns = orb.string_to_object( nsior )._narrow( CosNaming.NamingContext )
  except :
    print "..... no NameService IOR in ns.ior or service not running"
    sys.exit( 1 ) 
  
  # create naming contexts
  nspath = [CosNaming.NameComponent('DCI', '')]
  try:
    for component in nspath :
      ns.bind_new_context([component])
  except CosNaming.NamingContext.AlreadyBound:
    pass

  # create object for RuleProcessor
  root = Tkinter.Tk()
  obj = boa.create( 'RuleProcessor', RuleProcessor._FNORB_ID )
  impl = RuleProcessor( root, orb, boa )
  boa.obj_is_ready( obj, impl )
  open( "rule.ref", "w" ).write( orb.object_to_string( obj ) )

  # bind name in name service
  name = nspath + [CosNaming.NameComponent('RuleProcessor', '')]
  ns.rebind( name, obj )

  # mainloop
  print "..... RuleProcessor running with ior:\n"
  print orb.object_to_string( obj )
  #boa._fnorb_mainloop()
  thread.start_new_thread(boa._fnorb_mainloop,())
  root.mainloop()
  

##############################
# Call main when run as script
if __name__ == '__main__':
  sys.exit( main( sys.argv ) )
