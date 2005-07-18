import os, sys
from xml.dom import minidom

# Also *_EXPORTS
uninteresting_defines = ['WIN32', '_DEBUG', 'NDEBUG', '_CONSOLE',
                         '_WINDOWS', '_USRDLL', '_LIB' , '__DEBUG__' ,
                         '__STDC__' ]

interesting_defines = ['ZLIB_DLL','KC_DEPRECATED','YYERROR_VERBOSE','YYDEBUG',
                       'TAO_ORB']

uninteresting_libs = [ 'odbc32.lib', 'odbccp32.lib' ]

trans_libs = { 'OBD.lib' : 'OB.lib' , 'JTCD.lib' : 'JTC.lib' }

add_libs_to_libs = { 'OB.lib' : [ 'socket' ] , 'JTC.lib' : [ 'posix4' ] }

global_defines = { 'Name': 'ProjectName' }
config_defines = { 'IntermediateDirectory': 'IntDir' , 'Name' : 'Name' }

class Configuration:
    def __init__(self, conf):
        self.optim = 1
        self.debug = 0
        self.preprocessor = []
        self.includes = []
        self.libs = []
        self.libdirs = []
        self.files = { 'idl' : {}, 'yacc' : {}, 'lex' : {}, 'Kimwitu' : {} }
        self.output = None
        self.type = None

        for i in config_defines.keys():
            if conf.getAttribute(i):
                setattr(self,i,conf.getAttribute(i))

        tools = [t for t in conf.childNodes if t.nodeName == 'Tool']
        compiler = [t for t in tools if t.getAttribute('Name') == 'VCCLCompilerTool']
        if compiler:
            compiler = compiler[0]
            if compiler.hasAttribute('Optimization'):
                self.optim = int(compiler.getAttribute('Optimization'))
            if compiler.hasAttribute('DebugInformationFormat'):
                self.debug = int(compiler.getAttribute('DebugInformationFormat'))
            preprocessor = compiler.getAttribute('PreprocessorDefinitions')
            if ';' in preprocessor:
                preprocessor = preprocessor.split(';')
            elif ',' in preprocessor:
                preprocessor = preprocessor.split(',')
            else:
                preprocessor = [preprocessor]
            for d in preprocessor:
                if d in uninteresting_defines or d.endswith("_EXPORTS"):
                    continue
                if d not in interesting_defines:
                    print >>sys.stderr, "UNKNOWN DEFINE", d
                self.preprocessor.append(d)

            includes = unesc(compiler.getAttribute('AdditionalIncludeDirectories'))
            if ';' in includes:
                includes = includes.split(';')
            elif ',' in includes:
                includes = includes.split(',')
            else:
                includes = [includes]
            for d in includes:
                self.includes.append(d)

        linker = [t for t in tools if t.getAttribute('Name') == 'VCLinkerTool']
        if linker:
            linker = linker[0]
            self.type = "Executable"
            self.output = unesc(linker.getAttribute('OutputFile'))
            if not self.output:
                self.output = "$(IntDir)/$(ProjectName)"
            if self.output.endswith('.exe'):
                self.output = self.output[:-4]
            libdirs = unesc(linker.getAttribute('AdditionalLibraryDirectories'))
            libdirs = libdirs.replace('"','')
            if ';' in libdirs:
                libdirs = libdirs.split(';')
            elif ',' in includes:
                libdirs = libdirs.split(',')
            else:
                libdirs = [libdirs]
            for d in libdirs:
                self.libdirs.append(d)
            for l in linker.getAttribute('AdditionalDependencies').split():
                if l.endswith('.lib'):
                    if l in trans_libs.keys():
                        l= trans_libs[l]
                    if  not l in uninteresting_libs:
                        self.libs.append(l[:-4])
                        if l in add_libs_to_libs.keys():
                            self.libs += add_libs_to_libs[l]
                else:
                    print >>sys.stderr, "UNKNOWN DEPENDENCY", l

        librarian = [t for t in tools if t.getAttribute('Name') == 'VCLibrarianTool']
        if librarian:
            librarian = librarian[0]
            self.type = "Library"
            self.output = librarian.getAttribute('OutputFile')
            for l in librarian.getAttribute('AdditionalDependencies').split():
                if l.endswith('.lib'):
                    self.libs.append(l[:-4])
                else:
                    print >>sys.stderr, "UNKNOWN DEPENDENCY", l
                                    
def unesc(path):
    return path.replace("\\","/");

def getFiles(filter):
    result = []
    for f in filter.childNodes:
        if f.nodeName != 'File':continue
        result.append(unesc(f.getAttribute('RelativePath')))
        for t in f.getElementsByTagName('Tool'):
            assert not t.hasAttribute('ObjectFile')
    return result

def objName(cfile):
    for ext in ['.cpp','.c']:
        if cfile.endswith(ext):
            cfile = os.path.basename(cfile)
            return os.path.join("$(IntDir)",cfile.replace(ext, '.o'))

class VisualStudioProject:
    def __init__(self, filename):
        dom = minidom.parse(open(filename))
        confs = dom.getElementsByTagName("Configurations")[0]
        self.confs = [Configuration(c) for c in confs.childNodes if c.nodeName == 'Configuration']
        self.sources = []
        self.files = { 'idl' : {}, 'yacc' : {}, 'lex' : {}, 'Kimwitu' : {} }

        for i in global_defines.keys():
            if dom.documentElement.getAttribute(i):
                setattr(self,i,dom.documentElement.getAttribute(i))
        for f in dom.getElementsByTagName('Files')[0].childNodes:
            if f.nodeName != 'Filter': continue
            ftype = f.getAttribute('Name')
            if ftype == 'Source Files':
                self.sources = getFiles(f)
            elif ftype in self.files.keys():
                for filetype in self.files.keys():
                    if filetype != ftype: continue
                    for file in f.childNodes:
                        if file.nodeName != 'File':continue
                        name = unesc(file.getAttribute('RelativePath'))
                        for conf in file.getElementsByTagName('FileConfiguration'):
                            cname = conf.getAttribute('Name')
                            tool = [t for t in file.getElementsByTagName('Tool')
                                    if t.getAttribute('Name') == 'VCCustomBuildTool'][0]
                            cmd = unesc(t.getAttribute('CommandLine'))
                            res = [unesc(x) for x in t.getAttribute('Outputs').split(';')]
                            self.files[filetype][name] = (cname, cmd, res)
                            for c in self.confs:
                                if cname == c.Name:
                                    c.files[filetype][name] = (cname, cmd, res)
                        
                    
            elif ftype in ('Header Files', 'Resource Files'):
                pass
            else:
                print >>sys.stderr, "UNKNOWN FILTER",ftype

    def genmakefile(self):
        for c in self.confs:
            stmps = []
            c.Name = c.Name.split("|")[0]
            mkfile = file("mk." + c.Name,"w+")  

            if not os.path.exists(unesc(c.IntermediateDirectory)):
                os.mkdir(unesc(c.IntermediateDirectory))

            print >> mkfile, "# Configuration", c.Name
            for i in global_defines.keys():
                if hasattr(self,i):
                    print >> mkfile, global_defines[i] + "=" + getattr(self,i)
            for i in config_defines.keys():
                if hasattr(c,i):
                    print >> mkfile, config_defines[i] + "=" + unesc(getattr(c,i))
            cflags = []
            for f in c.preprocessor:
                cflags.append('-D'+f)
            for f in c.includes:
                cflags.append('-I'+f)

            if c.optim > 0:
                cflags.append('-O'+str(c.optim))
            if c.debug > 0:
                cflags.append('-g')

            if cflags:
                print >> mkfile, "CFLAGS=%s" % " ".join(cflags)
                print >> mkfile, "CXXFLAGS=%s" % " ".join(cflags)

            libs = ["-L" + l for l in c.libdirs]
            libs += ["-l" + l for l in c.libs]
            if libs:
                print >> mkfile, "LIBS=%s" % " ".join(libs)

            print >> mkfile, ""
            print >> mkfile, "$(IntDir)/%.o:%.cpp\n\t",
            print >> mkfile, "$(COMPILE.cc) $(OUTPUT_OPTION) $<\n"

            if c.type == "Executable":
                print >> mkfile, "LDLIBS+=$(LIBS)"
                print >> mkfile, ""
                print >> mkfile, "CC=$(CXX)"
                print >> mkfile, ""
                print >> mkfile, "all: idl lex yacc ",
                if c.files['Kimwitu']:
                    print >> mkfile, "Kimwitu ",
                print >> mkfile ,c.output, ""
                print >> mkfile, ""
                print >> mkfile, c.output,":",
                for s in self.sources:
                    print >> mkfile, objName(s),
                print >> mkfile, ""
                print >> mkfile, "\t" + "$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@"
                print >> mkfile, ""
            elif c.type == "Library":
                c.output = os.path.join(os.path.dirname(c.output),
                           "lib" + os.path.basename(c.output).replace(".lib",".a"))
                print >> mkfile, ""
                print >> mkfile, "all: idl yacc lex ",
                if c.files['Kimwitu']:
                    print >> mkfile, "Kimwitu ",
                print >> mkfile ,c.output, ""
                print >> mkfile, ""
                print >> mkfile, c.output,":",
                for s in self.sources:
                    print >> mkfile, objName(s),
                print >> mkfile, ""
                print >> mkfile, "\t" + "$(AR) $(ARFLAGS) $@ $^"
                print >> mkfile, ""
            else:
                print >>sys.stderr, "UNKNOWN PROJECT TYPE"

            for s in self.sources:
                print >> mkfile, "%s:\t%s" % (objName(s), s)

            print >> mkfile, 'idl: ',
            for source, (cname, cmd, outputs) in c.files['idl'].items():
                print >> mkfile, '%s' % (" ".join(outputs)),
            print >> mkfile, ""
            print >> mkfile, ""

            print >> mkfile, "# IDL files"
            for source, (cname, cmd, outputs) in c.files['idl'].items():
                print >> mkfile, '%s:%s\n\t%s' % (" ".join(outputs), source, cmd)
            print >> mkfile, ""

            print >> mkfile, 'lex: ',
            for source, (cname, cmd, outputs) in c.files['lex'].items():
                print >> mkfile, '%s' % (" ".join(outputs)),
            print >> mkfile, ""
            print >> mkfile, ""

            print >> mkfile, "# LEX files"
            for source, (cname, cmd, outputs) in c.files['lex'].items():
                print >> mkfile, '%s:%s\n\t%s' % (" ".join(outputs), source, cmd)
            print >> mkfile, ""

            print >> mkfile, 'yacc: ',
            for source, (cname, cmd, outputs) in c.files['yacc'].items():
                print >> mkfile, '%s' % (" ".join(outputs)),
            print >> mkfile, ""
            print >> mkfile, ""

            print >> mkfile, "# YACC files"
            for source, (cname, cmd, outputs) in c.files['yacc'].items():
                print >> mkfile, '%s:%s\n\t%s' % (" ".join(outputs), source, cmd)
            print >> mkfile, ""
            print >> mkfile, ""

            print >> mkfile, "# Kimwitu files"
            for source, (cname, cmd, outputs) in c.files['Kimwitu'].items():
                print >> mkfile, '%s:%s\n' % (" ".join(outputs), source.replace(".k",".stmp"))
                stmps.append(source.replace(".k",".stmp"))
                print >> mkfile, '%s:%s\n\t%s' % (source.replace(".k",".stmp"),source,cmd)
                print >> mkfile, '\n\ttouch %s\n' % (source.replace(".k",".stmp"))
            print >> mkfile, ""
            print >> mkfile, ""

            print >> mkfile, 'Kimwitu: ', " ".join(stmps)
            print >> mkfile, ""

        mkfile = file("Makefile","w+")
        print >> mkfile, '-include mk.$(MAKECMDGOALS)'
        print >> mkfile, '$(MAKECMDGOALS): all'



def walker(arg, dir, files):
    for f in files:
        if not f.endswith('.vcproj'):
            continue
        name = os.path.join(dir, f)
        print '########',name
        proj = VisualStudioProject(name)
        proj.genmakefile()

os.path.walk('.',walker,None)
