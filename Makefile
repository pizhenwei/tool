DTOH=dtoh
HTOD=htod

.PHONY : $(DTOH) $(HTOD)

all : $(DTOH) $(HTOD)

$(DTOH) :
	gcc $(DTOH).c -O2 -o $(DTOH)

$(HTOD) :
	gcc $(HTOD).c -O2 -o $(HTOD)

install :
	@sudo cp $(DTOH) /usr/bin
	@sudo cp $(HTOD) /usr/bin

clean :
	@rm -rf $(HTOD)
	@rm -rf $(DTOH)
