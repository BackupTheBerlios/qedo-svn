
include ../MakeComponentVars

all: chat_$(OS).zip

chat_$(OS).zip: Chat_Reader_Compo_$(OS).zip Chat_Channel_Compo_$(OS).zip Chat_Writer_Compo_$(OS).zip meta-inf/chat_$(OS).cad
	zip Chat_Reader_Compo_$(OS).zip Chat_Channel_Compo_$(OS).zip Chat_Writer_Compo_$(OS).zip meta-inf/chat_$(OS).cad

Chat_Reader_Compo_$(OS).zip :
	cp ../Chat_Reader_Compo/Chat_Reader_Compo_$(OS).zip  .

Chat_Channel_Compo_$(OS).zip :
	cp ../Chat_Reader_Compo/Chat_Channel_Compo_$(OS).zip  .

Chat_Writer_Compo_$(OS).zip :
	cp ../Chat_Reader_Compo/Chat_Writer_Compo_$(OS).zip  .

