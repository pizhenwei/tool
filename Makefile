DTOH=dtoh
HTOD=htod
CTIME=ctime
GETTIMEOFDAY=gettimeofday
GETALLCHANGELOG=get-all-changelog.py
OBJDUMPFUNCTION=objdump-function.sh
SPARSEFILE=sparse-file
FILEMAP=filemap
PMU-COUNTERS=pmu-counters
GETTIMEOFDAY-BENCH=gettimeofday-bench
MEMORYFILL=memoryfill

.PHONY : $(DTOH) $(HTOD) $(CTIME) $(GETTIMEOFDAY) $(SPARSEFILE) $(FILEMAP) $(PMU-COUNTERS) $(GETTIMEOFDAY-BENCH) $(MEMORYFILL)

all : $(DTOH) $(HTOD) $(CTIME) $(GETTIMEOFDAY) $(SPARSEFILE) $(FILEMAP) $(PMU-COUNTERS) $(MEMORYFILL)

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

$(PMU-COUNTERS) :
	gcc $(PMU-COUNTERS).c -O2 -o $(PMU-COUNTERS)

$(GETTIMEOFDAY-BENCH) :
	gcc $(GETTIMEOFDAY-BENCH).c -O2 -o $(GETTIMEOFDAY-BENCH)

$(MEMORYFILL) :
	gcc $(MEMORYFILL).c -O2 -o $(MEMORYFILL)

install :
	@sudo cp $(DTOH) /usr/bin
	@sudo cp $(HTOD) /usr/bin
	@sudo cp $(CTIME) /usr/bin
	@sudo cp $(GETTIMEOFDAY) /usr/bin
	@sudo cp $(GETALLCHANGELOG) /usr/bin
	@sudo cp $(OBJDUMPFUNCTION) /usr/bin
	@sudo cp $(SPARSEFILE) /usr/bin
	@sudo cp $(FILEMAP) /usr/bin
	@sudo cp $(PMU-COUNTERS) /usr/bin
	@sudo cp $(GETTIMEOFDAY-BENCH) /usr/bin
	@sudo cp $(MEMORYFILL) /usr/bin

clean :
	@rm -rf $(DTOH)
	@rm -rf $(HTOD)
	@rm -rf $(CTIME)
	@rm -rf $(GETTIMEOFDAY)
	@rm -rf $(GETALLCHANGELOG)
	@rm -rf $(OBJDUMPFUNCTION)
	@rm -rf $(SPARSEFILE)
	@rm -rf $(FILEMAP)
	@rm -rf $(PMU-COUNTERS)
	@rm -rf $(GETTIMEOFDAY-BENCH)
	@rm -rf $(MEMORYFILL)
