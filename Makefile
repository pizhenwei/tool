DTOH=dtoh
HTOD=htod
CTIME=ctime
GETTIMEOFDAY=gettimeofday
GETALLCHANGELOG=get-all-changelog.py
OBJDUMPFUNCTION=objdump-function.sh
SPARSEFILE=sparse-file
FILEMAP=filemap

.PHONY : $(DTOH) $(HTOD) $(CTIME) $(GETTIMEOFDAY) $(SPARSEFILE) $(FILEMAP)

all : $(DTOH) $(HTOD) $(CTIME) $(GETTIMEOFDAY) $(SPARSEFILE) $(FILEMAP)

$(DTOH) :
	gcc $(DTOH).c -O2 -o $(DTOH)

$(HTOD) :
	gcc $(HTOD).c -O2 -o $(HTOD)

$(CTIME) :
	gcc $(CTIME).c -O2 -o $(CTIME)

$(GETTIMEOFDAY) :
	gcc $(GETTIMEOFDAY).c -O2 -o $(GETTIMEOFDAY)

$(SPARSEFILE) :
	gcc $(SPARSEFILE).c -O2 -o $(SPARSEFILE)

$(FILEMAP) :
	gcc $(FILEMAP).c -O2 -o $(FILEMAP)

install :
	@sudo cp $(DTOH) /usr/bin
	@sudo cp $(HTOD) /usr/bin
	@sudo cp $(CTIME) /usr/bin
	@sudo cp $(GETTIMEOFDAY) /usr/bin
	@sudo cp $(GETALLCHANGELOG) /usr/bin
	@sudo cp $(OBJDUMPFUNCTION) /usr/bin
	@sudo cp $(SPARSEFILE) /usr/bin
	@sudo cp $(FILEMAP) /usr/bin

clean :
	@rm -rf $(DTOH)
	@rm -rf $(HTOD)
	@rm -rf $(CTIME)
	@rm -rf $(GETTIMEOFDAY)
	@rm -rf $(GETALLCHANGELOG)
	@rm -rf $(OBJDUMPFUNCTION)
	@rm -rf $(SPARSEFILE)
	@rm -rf $(FILEMAP)
