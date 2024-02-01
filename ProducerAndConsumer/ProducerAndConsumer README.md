{\rtf1\ansi\ansicpg1252\cocoartf2709
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica-Bold;\f1\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\b\fs24 \cf0 ProducerAndConsumer.c README
\f1\b0 \
\
This README details the instructions for compiling and running the `ProducerAndConsumer.c` program, which is a solution to the classic Producer-Consumer synchronization problem using POSIX threads (pthreads) in C.\
\

\f0\b Overview
\f1\b0 \
\
The program simulates the Producer-Consumer scenario, where multiple producer threads generate data and place it into a shared buffer, and consumer threads read and process this data from the buffer. The main challenge and focus of the solution are to ensure safe access to the shared buffer, preventing producers from overwriting data that has not been consumed and ensuring consumers wait for new data to be produced.\
\

\f0\b Prerequisites
\f1\b0 \
\
- A Unix-like operating system with a standard C compiler (such as `gcc`).\
- The POSIX threads library (`pthreads`), typically included by default in most Unix-like environments.\
\

\f0\b File Description
\f1\b0 \
\
- `ProducerAndConsumer.c`: Contains the source code implementing the Producer-Consumer problem solution with proper synchronization mechanisms.\
\

\f0\b Compilation Instructions
\f1\b0 \
\
To compile the `ProducerAndConsumer.c` file, use the following command in your terminal, making sure you are in the directory where the file is located:\
\
\
	gcc ProducerAndConsumer.c -o ProducerAndConsumer -pthread\
\
\
This command compiles the source code into an executable named `ProducerAndConsumer`, linking it with the pthreads library (specified by the `-pthread` flag) to enable multithreading support.\
\

\f0\b Running the Program
\f1\b0 \
\
Execute the compiled program by entering the following command:\
\
\
	./ProducerAndConsumer\
\
\
Upon execution, the program initiates producer and consumer threads that interact with the shared buffer. The producers will insert items into the buffer, and the consumers will remove and process these items.\
\

\f0\b Expected Behavior
\f1\b0 \
\
The program will continuously display messages indicating the actions of the producer and consumer threads, including item production, buffer insertion, item consumption, and buffer removal. This output demonstrates the synchronization between threads and the safe management of the shared buffer.\
\

\f0\b Termination
\f1\b0 \
\
The `ProducerAndConsumer` program is designed to run indefinitely and must be manually terminated when desired, by using the `Ctrl+C` command in the terminal.\
\

\f0\b Author
\f1\b0 \
\
Written by Hunter Jenkins and Jack Utzerath\
\
}
