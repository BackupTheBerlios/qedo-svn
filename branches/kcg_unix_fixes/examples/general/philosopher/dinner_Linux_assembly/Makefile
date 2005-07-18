
include ../MakeComponentVars

all: dinner_$(OS).zip

dinner_$(OS).zip: dinner_CutleryImpl.zip dinner_ObserverImpl.zip dinner_PhilosopherImpl.zip meta-inf/dinner_$(OS).cad
	zip dinner_$(OS).zip dinner_CutleryImpl.zip \
	dinner_ObserverImpl.zip dinner_PhilosopherImpl.zip \
	meta-inf/dinner_$(OS).cad \
	meta-inf/atze.cpf \
	meta-inf/charly.cpf \
	meta-inf/bob.cpf

dinner_CutleryImpl.zip :
	cp ../dinner_CutleryImpl/dinner_CutleryImpl.zip  .

dinner_ObserverImpl.zip :
	cp ../dinner_ObserverImpl/dinner_ObserverImpl.zip  .

dinner_PhilosopherImpl.zip :
	cp ../dinner_PhilosopherImpl/dinner_PhilosopherImpl.zip  .

