rootPath = ../
include ../include.mk

cflags += ${tokyoCabinetIncl}

all : ${binPath}/cactus_analyseAssembly ${binPath}/cactus_batch_mergeChunks ${binPath}/cactus_makeAlphaNumericHeaders.py ${binPath}/cactus_filterSmallFastaSequences.py
	cd lastzRepeatMasking && make all

${binPath}/cactus_filterSmallFastaSequences.py : cactus_filterSmallFastaSequences.py
		cp cactus_filterSmallFastaSequences.py ${binPath}/cactus_filterSmallFastaSequences.py
			chmod +x ${binPath}/cactus_filterSmallFastaSequences.py
				
${binPath}/cactus_makeAlphaNumericHeaders.py : cactus_makeAlphaNumericHeaders.py
		cp cactus_makeAlphaNumericHeaders.py ${binPath}/cactus_makeAlphaNumericHeaders.py
		chmod +x ${binPath}/cactus_makeAlphaNumericHeaders.py

${binPath}/cactus_analyseAssembly : cactus_analyseAssembly.c ${basicLibsDependencies} ${libPath}/cactusLib.a
	${cxx} ${cflags} -I${libPath} -o ${binPath}/cactus_analyseAssembly cactus_analyseAssembly.c ${libPath}/cactusLib.a ${basicLibs}

${binPath}/cactus_batch_mergeChunks : *.c ${libPath}/cactusLib.a ${basicLibsDependencies}
	${cxx} ${cflags} -I${libPath} -o ${binPath}/cactus_batch_mergeChunks cactus_batch_mergeChunks.c ${libPath}/cactusLib.a ${basicLibs}

clean : 
	rm -f *.o
	rm -f ${binPath}/cactus_analyseAssembly ${binPath}/cactus_batch_mergeChunks
	cd lastzRepeatMasking && make clean
