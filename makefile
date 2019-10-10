INPUT=X11ScreenCap.cxx
OUTPUT=X11ScreenCap
FLAGS=-o 
LINKS= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_imgcodecs -lopencv_videoio  -lX11 -lXtst
CC=g++ -Wall
c: $(INPUT)
		$(CC) $(INPUT) $(FLAGS) $(OUTPUT) $(LINKS)
