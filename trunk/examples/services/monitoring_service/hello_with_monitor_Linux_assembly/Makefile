
include ../MakeComponentVars

all: hello_with_monitoring_$(OS).zip

hello_with_monitoring_$(OS).zip: HelloWorld_CalleeImpl.zip HelloWorld_CallerImpl.zip container_service_MonImpl.zip meta-inf/hello_with_monitoring_$(OS).cad
	zip hello_with_monitoring_$(OS).zip HelloWorld_CalleeImpl.zip HelloWorld_CallerImpl.zip container_service_MonImpl.zip meta-inf/hello_with_monitoring_$(OS).cad

container_service_MonImpl.zip:
	cp ../container_service_MonImpl/container_service_MonImpl.zip .

HelloWorld_CalleeImpl.zip:
	cp ../../../general/hello_world/HelloWorld_CalleeImpl/HelloWorld_CalleeImpl.zip .

HelloWorld_CallerImpl.zip:
	cp ../../../general/hello_world/HelloWorld_CallerImpl/HelloWorld_CallerImpl.zip .

