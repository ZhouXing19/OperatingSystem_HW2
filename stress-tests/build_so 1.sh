# 编译定义spin的变量类型及其相关函数的c文件
gcc -c -fPIC -o spin.o spin.c
# 从.o文件构造.so文件
gcc -shared -o libspin.so spin.o # （*） 
# 在编译使用到了spinlock结构的c文件 (例：test.c), 编译并执行如下：
# 注意： 下面的 -l[], 括号中的部分和 (*) 中定义的 lib[].so 应相同。
# gcc -o test test.c -lspin -L.  
# ./test

gcc -c -fPIC -o counter.o counter.c
gcc -shared -o libcounter.so counter.o

gcc -c -fPIC -o list.o list.c
gcc -shared -o liblist.so list.o

gcc -c -fPIC -o hash.o hash.c
gcc -shared -o libhash.so hash.o