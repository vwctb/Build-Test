import os, sys

bundle = open(sys.argv[1], 'a')
bundle.write(open('visTest_glue.js', 'r').read())
bundle.write('''

this['DLL'] = Module; // With or without a closure, the proper usage is Box2D.*

''')
bundle.close()

