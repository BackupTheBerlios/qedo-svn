
include ../MakeComponentVars

all: hello_$(OS).zip

hello_$(OS).zip: HelloWorld_CalleeImpl_$(OS).zip HelloWorld_CallerImpl_$(OS).zip meta-inf/hello_$(OS).cad
	zip hello_$(OS).zip HelloWorld_CalleeImpl_$(OS).zip HelloWorld_CallerImpl_$(OS).zip meta-inf/hello_$(OS).cad

HelloWorld_CalleeImpl_$(OS).zip:
	cp ../HelloWorld_CalleeImpl/HelloWorld_CalleeImpl_$(OS).zip .

HelloWorld_CallerImpl_$(OS).zip:
	cp ../HelloWorld_CallerImpl/HelloWorld_CallerImpl_$(OS).zip .

