# Makefile for webServer project

#-include ./src/webserver/Makefile
JAVAC=/usr/bin/javac
JAVACFLAGS = -d $(WEB_PROJECT)
SRC=$(WEB_PROJECT)/src/webserver
BIN=$(WEB_PROJECT)/webserver

all:
	$(JAVAC) $(JAVACFLAGS) $(SRC)/*.java

clean:
	$(RM) $(BIN)/*.class
