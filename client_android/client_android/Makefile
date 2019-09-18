#$CC -fPIE -pie hello.c -o hello -landroid

CC = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-gcc 
#CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-g++
CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-clang++
CFLAGS = 
#CXXFLAGS = -static -std=c++11 -v 
CXXFLAGS = -fPIE -pie 
TARGET = hello
OBJECTS = backup.o
#LINKFLAGS = -l
LINKFILES = libandroid.a

all : $(TARGET)

$(TARGET) : $(OBJECTS)
#	$(CXX) -o hello hello.cpp libandroid.a
#	$(CXX) $(CXXFLAGS)  -landroid libmycode.so -o $@ $^
	$(CXX) $(CXXFLAGS) -landroid -lcamera2ndk -o $@ $^
clean :
	rm *.o hello

