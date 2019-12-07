#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 75     /*定义一个消息关键字*/
struct  msgform        /*定义一个结构，它是一个消息的模式，只说明结构的形式*/
{
    long  mtype;      /*消息类型*/
    char  mtext[256];   /*消息正文数组*/
};

int main(void){
	struct msgform msg;          /*定义msg是前面说明的消息结构类型的变量*/

	int msggid, pid, *pint;
	msggid = msgget(MSGKEY, 0777);   /*用系统调用创建一个消息队列*/
	pid = getpid();                    /*获得当前进程的PID*/
	printf("client:pid = %d\n", pid);
	pint = (int*) msg.mtext;             /*将消息正文的头指针赋给指针变量pint*/
	*pint = pid;
	msg.mtype = 1;                      /*指定客户进程的消息类型为1*/
	msgsnd(msggid, &msg, sizeof(int), 0);    /*向msggid的消息队列发送消息msg*/
	msgrcv(msggid, &msg, 256, pid, 0);      /*接收pid类型的消息 */
	printf("client:receive from pid %d\n", *pint);

	return 0;
}

