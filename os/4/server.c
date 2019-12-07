#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 75      /*定义一个消息关键字*/
struct  msgform          /*定义一个与客户端相同的消息关键字*/
{
    long  mtype;       /*消息类型*/
    char  mtext[256];    /*消息正文数组*/
}msg;                 /*也可以使用这种方式说明消息结构变量*/

void cleanup ( int signo );    /*说明一个外部函数*/
int  msggid;

int main(){
    int i,pid, *pint;
    for (i = 0; i < 23;  i++ )             /*对22个软中断的特殊处理*/
    signal(i, cleanup );               /*若收到22个软中断，转向执行cleanup*/
    msggid = msgget ( MSGKEY, 0777 | IPC_CREAT );
    // 创建一个与客户程序相同关键字的消息队列
    // 但它的标志是0777与IPC_CREAT 做“或”操作的结果
    printf("server:pid = %d\n", getpid());  /*输出服务端的进程ID*/
    for ( ; ; )                          /*用无限循环完成下列语句*/
    {
        msgrcv (msggid, &msg, 256, 1, 0 );     /*接收来自客户进程或类型为1的消息 */
        pint = (int*) msg.mtext;          /*将客户端的消息正文传递给pint*/
        pid = *pint;     /*将读出消息指针送pid，此时*pint中是客户进程的pid值*/
        printf("server:receive from pid %d\n", pid );
        msg.mtype = pid;    /*已接受客户进程的pid为消息类型*/
        *pint = getpid();     /*以本进程pid作为消息构成消息传递内容*/
        msgsnd(msggid, &msg, sizeof(int), 0);    /*发送消息*/
    }
}

void cleanup(int signo){
    msgctl(msggid, IPC_RMID, 0);    /*删除消息队列*/
    exit(0);
}

