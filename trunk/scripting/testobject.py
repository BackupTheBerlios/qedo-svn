#!/usr/bin/env python


import sys
import Tkinter
from Tkconstants import *
from tkMessageBox import *
from Fnorb.orb import CORBA, BOA, TkReactor
import Components, Components_skel


class TestObject_impl( Components_skel.CCMObject_skel ):
  
  def connect_consumer( self, emitter_name, consumer ):
    print "..... connect_consumer called"
    self.text.insert(END,"\nconnect_consumer " + emitter_name + " \n",END)
    
  def disconnect_consumer( self, source_name ):
    print "..... disconnect_consumer called"
    self.text.insert(END,"\ndisconnect_consumer " + source_name + " \n",END)
    
  def get_component_def( self ):
    print "..... get_component_def called"
    self.text.insert(END,"\nget_component_def\n",END)

  def get_ccm_home( self ):
    print "..... get_ccm_home called"
    self.text.insert(END,"\nget_ccm_home\n",END)
    
  def remove( self ):
    print "..... remove called"
    self.text.insert(END,"\nremove\n",END)
  
  def quit ( self ):
    self.frame.quit()

  def clear(self):
    self.text.delete("1.0",END)

  def __init__ ( self, master, obj, orb ):
    # params
    self.orb = orb
    self.obj = obj
    
    self.ior = self.orb.object_to_string(self.obj)
    open("testobject.ref","w").write(self.ior)
    
    # GUI
    self.frame = Tkinter.Frame ( master)

    # quit button
    quitframe = Tkinter.Frame(self.frame, relief=FLAT, borderwidth=2)
    quitbutton = Tkinter.Button ( quitframe, fg="red", text="quit", command=self.quit )
    quitbutton.pack(side=RIGHT,anchor=CENTER,expand=1)
    clearbutton = Tkinter.Button ( quitframe, text="clear", command=self.clear )
    clearbutton.pack(side=RIGHT,expand=1)
    quitframe.pack(side=BOTTOM, anchor=S, expand=0, fill=X)
    
    frame2 = Tkinter.Frame(self.frame)
    self.text = Tkinter.Text(frame2,width=30, height=10)
    self.text.pack(side=LEFT,expand=1,fill=BOTH)
    self.vscroll = Tkinter.Scrollbar(frame2,orient=VERTICAL)
    self.vscroll.pack(side=LEFT,fill=Y,anchor=E)
    self.vscroll.config(command=self.text.yview)
    self.text.config(yscrollcommand=self.vscroll.set)
    frame2.pack(expand=1,fill=BOTH)

    self.frame.pack(expand=1,fill=BOTH)
    master.title('TestObject')


##################
def main ( argv ): 

  try:
    orb = CORBA.ORB_init(argv, CORBA.ORB_ID)
  except: 
    print "Can`t initialize ORB"
    sys.exit(1)

  boa = BOA.BOA_init(sys.argv,BOA.BOA_ID)
  
  obj = boa.create('TestObject',TestObject_impl._FNORB_ID)

  root = Tkinter.Tk()
  impl = TestObject_impl( root, obj, orb )

  boa.obj_is_ready(obj,impl)
  import thread
  thread.start_new_thread(boa._fnorb_mainloop,())
  root.mainloop()


##############################
# Call main when run as script
if __name__ == '__main__':
  sys.exit( main( sys.argv ) )
