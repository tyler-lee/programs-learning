# AUTHOR: Tyler Lee
#		<lihuorong010@gmail.com>, UCAS
# DATE: 2013-12-10
#
# DESCR: for webServer project
#

# BEGIN
#--------------------------------------#
JAVAC=/usr/bin/javac
JAVACFLAGS = -d $(WEB_PROJECT)
Source=$(PWD)

JavaFiles = $(filter %.java,  $(Source))

#JavaFiles = HttpServer.java \
	  Response.java \
	  Request.java

CLS= $(JavaFiles:.java=.class)

all:  $(CLS)


.SUFFIXES : .class .java
.java.class :
	$(JAVAC) $(JAVACFLAGS) $<
	#$(JAVAC) $(JAVACFLAGS) $(JavaFiles)

clean:
	$(RM) $(WEB_PROJECT)/*.class

#--------------------------------------#
# END
