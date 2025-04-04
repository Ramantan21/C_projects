#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>


int getrlimit(int resource,struct rlimit *reslimp); //επιστρεφει 0,αν ΟΚ,ενω σε σφαλμα επιστρεφει <> 0

int setrlimit(int resource,const struct rlimit *reslimp); // επιτρεφει 0 αν ΟΚ,ενω σε σφαλμα επιστρεφει <>0

int main(){
    struct rlimit myrlimit;
    //RLIMIT_AS: MAXIMUM size of process's AS in bytes
    getrlimit(RLIMIT_AS,&myrlimit);
    printf("Maximum adress space = %lu and current = %lu\n",myrlimit.rlim_max,myrlimit.rlim_cur);

    //Rlimit_CORE: maximum size of core file

    getrlimit(RLIMIT_CORE,&myrlimit);
    printf("Maximum core file size = %lu and current = %lu\n",myrlimit.rlim_max,myrlimit.rlim_cur);

    //RLIMIT_DATA: maximum size of data segment that the process may create

    getrlimit(RLIMIT_DATA,&myrlimit);
    printf("Maximum data+heap size = %lu and current = %lu\n",myrlimit.rlim_max,myrlimit.rlim_cur);

    //RLIMIT_FSIZE maximum size of files that process may create

    getrlimit(RLIMIT_FSIZE,&myrlimit);
    printf("Maximum file size = %lu and cxurrent = %lu",myrlimit.rlim_max,myrlimit.rlim_cur);

    //RLIMIT_STACK: maximum size of the process stack,in bytes.

    getrlimit(RLIMIT_STACK,&myrlimit);
    printf("Maximum stack size = %lu and current = %lu",myrlimit.rlim_max,myrlimit.rlim_cur);



    return 1;


}
