
include ../MakeComponentVars

all: chat_with_EF_$(OS).zip

chat_with_EF_$(OS).zip: Chat_Reader_Compo.zip Chat_Channel_Compo.zip Chat_Writer_Compo.zip EventFrequency_EFQoSProviderComposition.zip meta-inf/chat_with_EF_$(OS).cad
	zip chat_with_EF_$(OS).zip Chat_Reader_Compo.zip Chat_Channel_Compo.zip Chat_Writer_Compo.zip EventFrequency_EFQoSProviderComposition.zip meta-inf/chat_with_EF_$(OS).cad

Chat_Reader_Compo.zip :
	cp ../../../../events/ChatChannel/Chat_Reader_Compo/Chat_Reader_Compo.zip  .

Chat_Channel_Compo.zip :
	cp ../../../../events/ChatChannel/Chat_Channel_Compo/Chat_Channel_Compo.zip  .

Chat_Writer_Compo.zip :
	cp ../../../../events/ChatChannel/Chat_Writer_Compo/Chat_Writer_Compo.zip  .

EventFrequency_EFQoSProviderComposition.zip :
	cp ../EventFrequency_EFQoSProviderComposition/EventFrequency_EFQoSProviderComposition.zip .
