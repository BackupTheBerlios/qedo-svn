
include ../MakeComponentVars

all: hello_$(OS).zip

hello_$(OS).zip: HelloWorld_CalleeImpl.zip HelloWorld_CallerImpl.zip meta-inf/hello_$(OS).cad
	zip hello_$(OS).zip HelloWorld_CalleeImpl.zip HelloWorld_CallerImpl.zip meta-inf/hello_$(OS).cad

HelloWorld_CalleeImpl.zip:
	cp ../HelloWorld_CalleeImpl/HelloWorld_CalleeImpl.zip .

HelloWorld_CallerImpl.zip:
	cp ../HelloWorld_CallerImpl/HelloWorld_CallerImpl.zip .

