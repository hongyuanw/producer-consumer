/*
 ============================================================================
 Name        : main.c
 Author      : why
 Version     :
 Copyright   : by why
 Description : Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//共享缓冲区
#define BUFFER_SIZE 100
typedef struct {
	int id;
} item;
item buffer[BUFFER_SIZE];
int in = 0; //下一个待生产位置
int out = 0; //下一个待消费位置
int counter = 0; //会被两个线程同时操作的计数器
int pro_number = 1; //产品编号

void * produce(void *);
void * consume(void *);

int main(int argc, char **argv) {
	//创建生产者、消费者线程
	pthread_t producer, consumer;
	int ret1, ret2;

	printf("creating 2 threads----\n");
	ret1 = pthread_create(&producer, NULL, produce, NULL );
	ret2 = pthread_create(&consumer, NULL, consume, NULL );

	if (ret1 != 0 || ret2 != 0) {
		printf("create threads failure!\n");
		exit(EXIT_FAILURE);
	}
	printf("create threads success!\n");

	//启动两个线程
	pthread_join(producer, NULL );
	pthread_join(consumer, NULL );

	printf("main thread exit!\n");
	exit(EXIT_SUCCESS);
}

//生产者线程生产产品
void * produce(void *ptr) {
	item production;
	while (1) {
		//在等待缓冲区可用之前提前生产好产品
		production.id = pro_number++;
		while (counter == BUFFER_SIZE) {
		}

		//缓冲区可用了
		buffer[in] = production;
		in = (in + 1) % BUFFER_SIZE;
		counter++;
		printf("生产产品：%d----当前产品数：%d\n", production.id, counter);

	}

	return NULL ;
}

//消费者线程消费产品
void * consume(void * ptr) {
	item production;
	while (1) {
		while (counter == 0) {
		}

		//缓冲区有产品了
		production = buffer[out];
		buffer[out].id = 0;
		out = (out + 1) % BUFFER_SIZE;
		counter--;
		printf("消费产品：%d----当前产品数：%d\n", production.id, counter);

	}
	return NULL ;
}
