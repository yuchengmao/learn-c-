#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

void test01(){
//共享内存标识符
    int shmid;

    printf("pid = %d\n", getpid());

    //创建共享内存，键值为 0x5005，共 1024 字节
    if((shmid = shmget((key_t)0x5005, 1024, 0640|IPC_CREAT)) == -1){
        printf("shmat(0x5005) failed\n");
        return;
    }
//用于指向共享内存的指针
    char *ptext = 0;

//将共享内存连接到当前进程的地址空间，由 ptext 指针指向它
    ptext = (char *)shmat(shmid, 0, 0);

//操作本程序的 ptext 指针（相当于操作共享内存）
    printf("写入前： %s\n", ptext);
    sprintf(ptext, "本程序的进程号是：%d", getpid());
    printf("写入后： %s\n", ptext);

//把共享内存从当前进程中分离
    shmdt(ptext);

//删除共享内存
#if 0
    if(shmctl(shmid, IPC_RMID, 0) == -1){
        printf("shmctl(0x5005) failed\n");
        return;
    }
#endif
}

int main(){
    test01();
#if 0
    //共享内存标识符
    int shmid;

    printf("pid = %d\n", getpid());

    //创建共享内存，键值为 0x5005，共 1024 字节
    if((shmid = shmget((key_t)0x5005, 1024, 0640|IPC_CREAT)) == -1){
        printf("shmat(0x5005) failed\n");
        return -1;
    }
//用于指向共享内存的指针
    char *ptext = 0;

//将共享内存连接到当前进程的地址空间，由 ptext 指针指向它
    ptext = (char *)shmat(shmid, 0, 0);

//操作本程序的 ptext 指针（相当于操作共享内存）
    printf("写入前： %s\n", ptext);
    sprintf(ptext, "本程序的进程号是：%d", getpid());
    printf("写入后： %s\n", ptext);

//把共享内存从当前进程中分离
    shmdt(ptext);

//删除共享内存
    if(shmctl(shmid, IPC_RMID, 0) == -1){
        printf("shmctl(0x5005) failed\n");
        return -1;
    }
#endif
}