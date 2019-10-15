#$CC -fPIE -pie hello.c -o hello -landroid

CC = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-gcc 
#CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-g++
CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-clang++
CFLAGS = 
#CXXFLAGS = -static -std=c++11 -v 
CXXFLAGS = -fPIE -pie -g
TARGET = client_android
OBJECTS = client_android.o
LIBS = -landroid -llog

all : $(TARGET)

$(TARGET) : $(OBJECTS)
#	$(CXX) -o hello hello.cpp libandroid.a
#	$(CXX) $(CXXFLAGS)  -landroid libmycode.so -o $@ $^
	$(CXX) $(CXXFLAGS) ${LIBS} -o $@ $^
clean :
	rm *.o client_android

