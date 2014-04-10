HW=hw9
all: $(HW)

#  Unix/Linux
%: %.c;gcc -Wall -O3 -o $@ $< -lglut -lGLU -lGL -lm

#  OSX
#%: %.c;gcc -Wall -O3 -o $@ $< -framework GLUT -framework OpenGL 


clean:
	rm -f $(HW)
