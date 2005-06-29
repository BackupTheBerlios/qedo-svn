
include ../MakeComponentVars

all: simple_stream_$(OS).zip

simple_stream_$(OS).zip: SimpleStream_SinkCompo.zip SimpleStream_SourceCompo.zip meta-inf/simple_stream_$(OS).cad
	zip simple_stream_$(OS).zip SimpleStream_SinkCompo.zip SimpleStream_SourceCompo.zip meta-inf/simple_stream_$(OS).cad

SimpleStream_SinkCompo.zip:
	cp ../SimpleStream_SinkCompo/SimpleStream_SinkCompo.zip .

SimpleStream_SourceCompo.zip:
	cp ../SimpleStream_SourceCompo/SimpleStream_SourceCompo.zip .

