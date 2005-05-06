
include ../MakeComponentVars

all: chat_$(OS).zip

chat_$(OS).zip: Chat_Reader_Compo.zip Chat_Channel_Compo.zip Chat_Writer_Compo.zip meta-inf/chat_$(OS).cad
	zip chat_$(OS).zip Chat_Reader_Compo.zip Chat_Channel_Compo.zip Chat_Writer_Compo.zip meta-inf/chat_$(OS).cad

Chat_Reader_Compo.zip :
	cp ../Chat_Reader_Compo/Chat_Reader_Compo.zip  .

Chat_Channel_Compo.zip :
	cp ../Chat_Channel_Compo/Chat_Channel_Compo.zip  .

Chat_Writer_Compo.zip :
	cp ../Chat_Writer_Compo/Chat_Writer_Compo.zip  .

