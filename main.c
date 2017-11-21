/*Piotr Milewski
  Systems pd10
  HW13 -- Check your pipes for leaks
  2017-11-20*/

#include "main.h"

int main(){

  int READ = 0;
  int WRITE = 1;

  int parentToChild[2];
  int childToParent[2];
  pipe(parentToChild);
  pipe(childToParent);

  srand(time(NULL)); //seed the RNG
  int transfer;

  if (fork()){ //if parent
    close(childToParent[WRITE]);
    close(parentToChild[READ]);
    
    transfer = rand() % 256;

    printf("Parent sending %d to child\n", transfer);
    write(parentToChild[WRITE], &transfer, sizeof(transfer));

    read(childToParent[READ], &transfer, sizeof(transfer));
    printf("Parent received %d from child\n", transfer);
  }
  else{ //if child
    close(parentToChild[WRITE]);
    close(childToParent[READ]);

    read(parentToChild[READ], &transfer, sizeof(transfer));
    printf("Child received %d from parent\n", transfer);
    printf("Child be performing quick maths\n");

    transfer %= 10; //take ones place of transfer

    printf("Child sending %d to parent\n", transfer);
    write(childToParent[WRITE], &transfer, sizeof(transfer));
  }

  return 0;
}
