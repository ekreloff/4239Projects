/* *******************************************************
 * Created By Ethan Kreloff April 4th, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * Uses CUDA GPU computing to parallelize a brute force 
 * search.
 * *******************************************************
 * hw10.cu
 * ******************************************************/


/*
 *  CUDA BruteSearch
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <cuda.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

/*
 *  Return elapsed wall time since last call (seconds)
 */
static double t0=0;
double Elapsed(void)
{
#ifdef _WIN32
   //  Windows version of wall time
   LARGE_INTEGER tv,freq;
   QueryPerformanceCounter((LARGE_INTEGER*)&tv);
   QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
   double t = tv.QuadPart/(double)freq.QuadPart;
#else
   //  Unix/Linux/OSX version of wall time
   struct timeval tv;
   gettimeofday(&tv,NULL);
   double t = tv.tv_sec+1e-6*tv.tv_usec;
#endif
   double s = t-t0;
   t0 = t;
   return s;
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Initialize array with random values
 */

void arrayInit(unsigned int x[], const long long int n)
{
    for(unsigned int i = 0; i < n; i++)
    {
        x[i] = i;
    }
}

void shuffle(unsigned int x[], const long long int n)
{
    if (n > 1) 
    {
        for (unsigned int i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          unsigned int t = x[j];
          x[j] = x[i];
          x[i] = t;
        }
    }
}

void RandomInit(unsigned int x[],const long long int n)
{
   arrayInit(x, n);
   shuffle(x, n);
}

/*
 *  Initialize fastest GPU device
 */
int InitGPU(int verbose)
{
   //  Get number of CUDA devices
   int num;
   if (cudaGetDeviceCount(&num)) Fatal("Cannot get number of CUDA devices\n");
   if (num<1) Fatal("No CUDA devices found\n");

   //  Get fastest device
   cudaDeviceProp prop;
   int   MaxDevice = -1;
   int   MaxGflops = -1;
   for (int dev=0;dev<num;dev++)
   {
      if (cudaGetDeviceProperties(&prop,dev)) Fatal("Error getting device %d properties\n",dev);
      int Gflops = prop.multiProcessorCount * prop.clockRate;
      if (verbose) printf("CUDA Device %d: %s Gflops %f Processors %d Threads/Block %d\n",dev,prop.name,1e-6*Gflops,prop.multiProcessorCount,prop.maxThreadsPerBlock);
      if(Gflops > MaxGflops)
      {
         MaxGflops = Gflops;
         MaxDevice = dev;
      }
   }

   //  Print and set device
   if (cudaGetDeviceProperties(&prop,MaxDevice)) Fatal("Error getting device %d properties\n",MaxDevice);
   printf("Fastest CUDA Device %d: %s\n",MaxDevice,prop.name);
   cudaSetDevice(MaxDevice);

   //  Return max thread count
   return prop.maxThreadsPerBlock;
}

/*
 * Host
 */
long long int BruteSearch(unsigned int x[], const long long int match, const long long int n)
{   
   int index = -1;

   for (unsigned int i=0; i<n; i++){
        if(x[i] == match) index = i;
   }
   
   return index;

}

/*
 *  Subset Device Function
 */

__global__ void findInSubset(int *index, const unsigned int x[], const unsigned int n, const unsigned int match)
{
   unsigned int j = blockIdx.x*blockDim.x+threadIdx.x;
   unsigned int i = blockIdx.y*blockDim.y+threadIdx.y;
   if(x[i*j] == match) *index = i*j;
}

/*
 *  Device Function
 */
 
 void ParallelBrute(int *index, const unsigned int x[], const unsigned int n, const unsigned int match)
{
   //  Calculate matrix dimensions
   int N = n*sizeof(unsigned int);

   // Allocate device memory
   unsigned int* list;
   int *position;
   if (cudaMalloc((void**)&list,N)) Fatal("Cannot allocate device memory list\n");
   if (cudaMalloc((void**)&position,sizeof(int))) Fatal("Cannot allocate device memory position\n");

   // Copy A and B from host to device
   if (cudaMemcpy(list,x,N,cudaMemcpyHostToDevice)) Fatal("Cannot copy list from host to device\n");
   if (cudaMemcpy(position,index,sizeof(int),cudaMemcpyHostToDevice)) Fatal("Cannot copy position from host to device\n");

   // Set size of block to Bw x Bw, and Bn x Bn blocks
   dim3 threads(10,10);
   dim3 grid((n/2)/threads.x,(n/2)/threads.y);

   // Execute the kernel
   findInSubset<<<grid,threads>>>(position,list,n,match);
   if (cudaGetLastError()) Fatal("findinsubset failed\n");

   // Copy C from device to host
   if (cudaMemcpy(index,position,sizeof(int),cudaMemcpyDeviceToHost)) Fatal("Cannot copy position from device to host\n");

   //  Free device memory
   cudaFree(list);
   cudaFree(position);

}


/*
 *  main
 */
int main(int argc, char* argv[])
{

   //  Process options
   int opt;
   int verbose=0;
   while ((opt=getopt(argc,argv,"v"))!=-1)
   {
      if (opt=='v')
         verbose++;
      else
         Fatal("Usage: [-v] <number to search for> <length of list>\n");
   }
   argc -= optind;
   argv += optind;

   
   //  Get number to search for and length of list
   if (argc!=2) Fatal("Usage: [-v] <number to search for> <length of list>\n");
   long long int find = atoi(argv[0]);
   if (find<0) Fatal("Number must not be negative.");
   long long int n = atoi(argv[1]);
   if (n<1) Fatal("Length of list must be positive.");
   printf("Looking for %lld in a list %lld items long.\n", find, n);
   

   //  Initialize GPU
   int Mw = InitGPU(verbose);
   if (Mw<n) Fatal("Thread count %lld exceeds threads per block of %d\n", n, Mw);
   
   // Allocate host memory
   unsigned int* array = (unsigned int*)malloc(n);
   if (!array) Fatal("Cannot allocate host memory\n");
   
   // Initialize List
   srand(time(NULL));
   RandomInit(array, n);
   
   Elapsed();
   long long int hostIndex = BruteSearch(array, find, n);
   double Th = Elapsed();
   
   //  Free host memory
   free(array);

   if(hostIndex < 0){
        printf("Host didn't find %lld in %6.3f s\n", find, Th);
   }else{
        printf("Host found %lld at position %lld in %6.22f s\n", find, hostIndex + 1, Th);
   }

   //  Done
   return 0;
}
