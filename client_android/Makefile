#$CC -fPIE -pie hello.c -o hello -landroid

CC = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-gcc 
#CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-g++
CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-clang++
CFLAGS = 
#CXXFLAGS = -static -std=c++11 -v 
CXXFLAGS = -fPIE -pie -std=c++11
TARGET = hello
OBJECTS = hello.o
#LINKFLAGS = -l
LINKFILES = libandroid.a

all : $(TARGET)

$(TARGET) : $(OBJECTS)
#	$(CXX) -o hello hello.cpp libandroid.a
#	$(CXX) $(CXXFLAGS)  -landroid libmycode.so -o $@ $^
	$(CXX) $(CXXFLAGS) -landroid -o $@ $^ libmycode.a
clean :
	rm *.o hello

