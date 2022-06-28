#include <stdio.h>

#define LOG(MSG) printf("[LOG] : FILENAME : %s FUNC : %s LINE : %d \n[MESSAGE : %s]\n",__FILE__,__FUNCTION__,__LINE__,MSG)
#define LOG_ERRNO(MSG,errornum) printf("[LOG] : FILENAME : %s FUNC : %s LINE : %d \n [MESSAGE : %s ERRORNO : %d]",__FILE__,__FUNCTION__,__LINE__,MSG,errornum)
#define DEBUG_ERR(MSG,errornum)\
{\
    printf("[DEBUG LOG] : FILENAME : %s FUNC : %s LINE : %d \n",__FILE__,__FUNCTION__,__LINE__);\
    perror(MSG);\
}\
