#!/usr/bin/env python


import sys
from Fnorb.orb import CORBA, BOA, uuid
from Fnorb.cos.naming import CosNaming
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
      
    self.check_id = self.scheduler.start_check( self, self.frequency )
    
  
  def stop( self ):
    """stop automatic check"""
    if self.check_id:
      self.scheduler.stop_check( self.check_id )
      self.chek_id = None


  def destroy( self ):
    """deactivate this Rule"""
    self.boa.deactivate_obj( self )


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

    return obj


  def destroy( self ):
    """deactivate this processor"""
    self.boa.deactivate_obj(self)


  ##### other operations #####


  def __init__( self, orb, boa ):
    self.orb = orb
    self.boa = boa
    self.scheduler = CheckThread()
 

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
  obj = boa.create( 'RuleProcessor', RuleProcessor._FNORB_ID )
  impl = RuleProcessor( orb, boa )
  boa.obj_is_ready( obj, impl )
  open( "rule.ref", "w" ).write( orb.object_to_string( obj ) )

  # bind name in name service
  name = nspath + [CosNaming.NameComponent('RuleProcessor', '')]
  ns.rebind( name, obj )

  # mainloop
  print "..... RuleProcessor running with ior:\n"
  print orb.object_to_string( obj )
  boa._fnorb_mainloop()
  

##############################
# Call main when run as script
if __name__ == '__main__':
  sys.exit( main( sys.argv ) )
