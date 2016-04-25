DTOH=dtoh
HTOD=htod
CTIME=ctime
GETTIMEOFDAY=gettimeofday

.PHONY : $(DTOH) $(HTOD) $(CTIME) $(GETTIMEOFDAY)

all : $(DTOH) $(HTOD) $(CTIME) $(GETTIMEOFDAY)

$(DTOH) :
	gcc $(DTOH).c -O2 -o $(DTOH)

$(HTOD) :
	gcc $(HTOD).c -O2 -o $(HTOD)

$(CTIME) :
	gcc $(CTIME).c -O2 -o $(CTIME)

$(GETTIMEOFDAY) :
	gcc $(GETTIMEOFDAY).c -O2 -o $(GETTIMEOFDAY)

install :
	@sudo cp $(DTOH) /usr/bin
	@sudo cp $(HTOD) /usr/bin
	@sudo cp $(CTIME) /usr/bin
	@sudo cp $(GETTIMEOFDAY) /usr/bin

clean :
	@rm -rf $(DTOH)
	@rm -rf $(HTOD)
	@rm -rf $(CTIME)
	@rm -rf $(GETTIMEOFDAY)
