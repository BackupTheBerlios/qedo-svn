import sys, os

def debug( ctx ):
  import traceback
  try :
    out = open( 'errorlog_' + str( os.getpid() ), 'a' )
    out.write( "==========\nposition :\n" )
    out.write( ctx )
    out.write( "\nexception :\n" )
    out.write( str( sys.exc_type ) )
    out.write( "\ntraceback :\n" )
    traceback.print_tb( sys.exc_traceback, None, out )
    out.write( "==========\n\n" )
  except :
    pass
