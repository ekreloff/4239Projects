HW=hw10
all: $(HW)

%: %.cu;nvcc -o $@ $< 

clean:
	rm -f $(HW)
