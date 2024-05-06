#变量类似C语言的#define常量宏
#定义变量
BIN=main
OBJ=main.o space.o server.o
CC=gcc

#制定编译规则1
#访问变量值语法:$(变量名)
$(BIN):$(OBJ)
	$(CC) -g -o $(BIN) $(OBJ) -lmysqlclient
#制定编译规则2
%.o:%.c
	$(CC) -c -o $@ $< -lmysqlclient

#伪目标:没有依赖的目标
#对应的命令得到执行语法:make 伪目标名
#例如:只有执行:make clean时才会执行对应的命令:rm ...
clean:
	rm $(BIN) $(OBJ)


