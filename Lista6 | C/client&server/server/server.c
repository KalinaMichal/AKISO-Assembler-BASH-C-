#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <time.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h> 
#include <fcntl.h>
#include <signal.h> 

#define MAX 1024 
#define PORT 6666
#define SA struct sockaddr 

char* password = "admin";
int sockfd;


void c_handler(int sig)
{
	printf("Closing server");
	close(sockfd);
	exit(0);
}

int modPow(int a, int b, int n)
{
    int res = 1;
    while(b > 0){
        res *= a;
        res %= n;
        b--;
    }
    return res;
}

int getKey(int fd)
{
    char buff[128];
    bzero(buff, sizeof(buff));
    read(fd, buff, sizeof(buff));
    int p = atoi(buff);
    bzero(buff, sizeof(buff));
    read(fd, buff, sizeof(buff));
    int g = atoi(buff);
    bzero(buff, sizeof(buff));
    read(fd, buff, sizeof(buff));
    int A = atoi(buff);
    int b = getRandom(10, p/2);
    sprintf(buff, "%d", modPow(g, b, p));
    write(fd, buff, sizeof(buff));
    return modPow(A, b, p);
}

int getRandom(int min, int max) {
    return rand() % (max - min) + min;
}

int file_exist (char *filename)
{
	struct stat   buffer;   
	return (stat (filename, &buffer) == 0);
}

void code(char* data, int size, int key){
    for(int i = 0; i < size; i++){
        data[0] = (char)((int)data[0] + key);
    }
}

void readFromClient(int sockfd, char* buff, int size, int key) {
    bzero(buff, size);
    read(sockfd, buff, size);
    code(buff, size, -key);
}

void writeToClient(int sockfd, char* buff, int size, int key){
    code(buff, size, key);
    write(sockfd, buff, size);
    bzero(buff, size);
}

// Function designed for chat between client and server. 
void* communication(void* args) 
{ 
	int fd = *(int*) args;
	int key = getKey(fd);		//taking id
	char path[MAX];			//path
   	char buff[MAX]; 		//buffor
	printf("New client %d have joined\n",key);
	getcwd(path, sizeof(path));	//workind dir
   	int n; 
	for (;;) {	/*Demo Acess*/
        readFromClient(fd, buff, sizeof(buff), key);
		if (strncmp("exit", buff, 4) == 0) { 					//exit but in demo
		printf("Client %d have left the server\n",key);
           	printf("Server Closing\n"); 
            	close(fd);
		pthread_exit(NULL); 
        } 
		else if (strncmp("login", buff, 5) == 0) { 				//login
			if (strncmp(password, buff+6, strlen(password)) == 0){
				strcpy(buff, "Login successful");
				printf("Client %d have sucesfully loggined in\n",key);
                		writeToClient(fd, buff, sizeof(buff), key);
				break;
			} 
			else {
				strcpy(buff, "Login unsuccessful");
                		writeToClient(fd, buff, sizeof(buff), key);
			}
	       	}
		else {
			strcpy(buff, "You have to login use: login <password>");
            		writeToClient(fd, buff, sizeof(buff), key);
		}
	}
      for (;;) {	/*Full Acess*/
		readFromClient(fd, buff, sizeof(buff), key);
	if (strncmp("pwd", buff, 3) == 0) {
		writeToClient(fd, path, sizeof(buff), key);
	}	
        else if (strncmp("cd", buff, 2) == 0) { 				//cd
		char* end = strchr(buff, '\n');
		if(end > buff) *end = '\0';
		chdir(path);
		chdir(buff+3);
		getcwd(path, sizeof(path));
            	writeToClient(fd, path, sizeof(buff), key);
	}
	else if (strncmp("ls", buff, 2) == 0) {				//ls
		int pid;
		int pipes[2];
		pipe(pipes);
		if((pid = fork()) == 0)
		{
			chdir(path);
			dup2(pipes[1], 1);
			close(pipes[0]);
                	close(pipes[1]);
			execlp("ls", "ls", NULL);
		}
            	close(pipes[1]);
		read(pipes[0], buff, sizeof(path));
            	close(pipes[0]);
		wait(&pid);
		writeToClient(fd, buff, sizeof(buff), key);
	}
	else if (strncmp("put", buff, 3) == 0) {			//put 			
		FILE* fp = fopen( buff+4, "wb");
		if(fp != NULL){
			strcpy(buff, "OK");
                	writeToClient(fd, buff, sizeof(buff), key);
                	//readFromClient(fd, buff, sizeof(buff), key);
			/**TUTAJ**/		
			readFromClient(fd, buff, sizeof(buff), key);
			//printf("nr otrzymany: %s\n",buff);
			int i = atoi(buff);	
			printf("\n%d\n",i);
			//while( i != 0 ) {
			//**TU*//
                    	readFromClient(fd, buff, i, key);
			fwrite(buff, i, 1, fp);
			//i--;
			//}
				//printf("nr otrzymany: %s\n",buff);
			//fprintf(fp, "\0");
		        fclose(fp);
		} 
		else {
			strcpy(buff, "FAIL");
	                writeToClient(fd, buff, sizeof(buff), key);
			perror("File");
		}
		strcpy(buff, "File successfuly sent");
            	writeToClient(fd, buff, sizeof(buff), key);
		//printf("File successfuly download");
	} 
	else if (strncmp("get", buff, 3) == 0) { 			//get
		if( file_exist(buff+4) ) {
			int b;
			FILE *fp = fopen(buff+4, "rb");//rb -non txt file, r -txt file
			bzero(buff, sizeof(buff));
			strcpy(buff, "OK");
                	writeToClient(fd, buff, sizeof(buff), key);
			bzero(buff, sizeof(buff));
			while( (b = fread(buff, 1, sizeof(buff), fp)) > 0 ){//file read
				printf("%s\n", buff);
                    		writeToClient(fd, buff, sizeof(buff), key);
    				bzero(buff, sizeof(buff));
			}	
			fclose(fp);
			strcpy(buff, "EOF");//eof - end of file
                	writeToClient(fd, buff, sizeof(buff), key);
    			bzero(buff, sizeof(buff));
			printf("File has been successfuly send");
		} 
		else {
			strcpy(buff, "error");
               		writeToClient(fd, buff, sizeof(buff), key);
		}
			
	}
       	else if (strncmp("exit", buff, 4) == 0) { 				//exit
            	close(fd);
		pthread_exit(NULL); 
        	} 
		else {								//special exception - unknow command
			strcpy(buff, "Unknow command");
            		writeToClient(fd, buff, sizeof(buff), key);
		}		
	}		 	
} 
int main() 
{
	srand(time(0));
	signal(SIGINT, c_handler);
	int connfd, len; 
	struct sockaddr_in servaddr, cli; 
  
   	 // socket create and verification 
    	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    	if (sockfd == -1) { 
    	    printf("socket creation failed...\n"); 
    	    exit(0); 
    	} 
    	else
        printf("Socket successfully created..\n"); 
    	bzero(&servaddr, sizeof(servaddr)); 
  
    	// assign IP, PORT etc. 
    	servaddr.sin_family = AF_INET; 
    	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    	servaddr.sin_port = htons(PORT); 
  
    	// Binding newly created socket and verification 
    	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
    	    printf("socket bind failed...\n"); 
    	    exit(0); 
    	} 
    	else
    	    printf("Socket successfully binded\n"); 
  
    	// checking socket
    	if ((listen(sockfd, 5)) != 0) { 
    	    printf("Listen failed...\n"); 
    	    exit(0); 
    	} 
    	else
    	    printf("Server listening..\n"); 
    	len = sizeof(cli); 
  
    	// Accept the data packet from client and verification 
	while(1){
    		connfd = accept(sockfd, (SA*)&cli, &len); 
	    	pthread_t t; 
        	pthread_create(&t, NULL, communication, &connfd);
	}
  	close(sockfd);     
} 

