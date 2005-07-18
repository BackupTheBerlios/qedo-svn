
include ../MakeComponentVars

all: philo_with_monitoring_$(OS).zip

philo_with_monitoring_$(OS).zip: dinner_CutleryImpl.zip \
			dinner_ObserverImpl.zip \
			dinner_PhilosopherImpl.zip \
			container_service_MonImpl.zip \
			meta-inf/philo_with_monitoring_$(OS).cad
	zip philo_with_monitoring_$(OS).zip \
		dinner_CutleryImpl.zip dinner_ObserverImpl.zip \
		dinner_PhilosopherImpl.zip \
		container_service_MonImpl.zip \
		meta-inf/philo_with_monitoring_$(OS).cad \
		meta-inf/atze.cpf \
		meta-inf/charly.cpf \
		meta-inf/bob.cpf \
		meta-inf/observer.cpf \
		meta-inf/fork1.cpf \
		meta-inf/fork2.cpf

container_service_MonImpl.zip:
	cp ../container_service_MonImpl/container_service_MonImpl.zip .

dinner_CutleryImpl.zip :
	cp ../../../general/philosopher/dinner_CutleryImpl/dinner_CutleryImpl.zip  .

dinner_ObserverImpl.zip :
	cp ../../../general/philosopher/dinner_ObserverImpl/dinner_ObserverImpl.zip  .

dinner_PhilosopherImpl.zip :
	cp ../../../general/philosopher/dinner_PhilosopherImpl/dinner_PhilosopherImpl.zip  .


