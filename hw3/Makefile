HW=hw3
all: $(HW)

#  Unix/Linux
%: %.c;gcc -Wall -O3 -o $@ $< -lglut -lGLU -lGL -lm

clean:
	rm -f $(HW)
