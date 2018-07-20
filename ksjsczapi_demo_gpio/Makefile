#############################################################################
# Makefile for building: AppName
#############################################################################

#将所有AppName替换成实际项目名称
KSJ_SO_NAME = ksjsczapi_demo_gpio

GENFILE_DIR   = LinuxGenFiles/


####### Compiler, tools and options

CC            = arm-linux-gnueabihf-gcc 
CXX           = arm-linux-gnueabihf-g++ 
DEFINES       = -D$(KSJ_SO_NAME)_LIBRARY -DQT_WIDGETS_LIB -DQT_DLL -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/include -I$(GENFILE_DIR)\
 -I../ksjsczapi_include
 
LINK          = arm-linux-gnueabihf-g++ 

#下面的这三项可以生成动态库
#CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
#CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
#LFLAGS        = -Wl,-O1 -Wl,-rpath,-soname,lib$(KSJ_SO_NAME).so

#下面的这三项可以生成app
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT  $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT  $(DEFINES)
LFLAGS        = -Wl,-O1 -Wl,-rpath,/opt/Qt4.8/lib

#下面的加载的动态库及库目录，可根据需要增删
LIBS          = $(SUBLIBS)  -L../ksjsczapi_lib \
 -L. -L/usr/local/lib -lpthread \
 -lksjscz -ldl \


AR            = arm-linux-gnueabihf-ar cqs
QMAKE         = /usr/local/bin/GenMakefile
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-linux-gnueabihf-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rm -rf
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
MOC          = /opt/Qt4.8/bin/moc
UIH          = /opt/Qt4.8/bin/uic

OPENCV_INCLUDE_FILES = /usr/local/include/opencv2/opencv.hpp /usr/local/include/opencv2/core.hpp \
/usr/local/include/opencv2/highgui.hpp \
/usr/local/include/opencv2/imgcodecs.hpp \
/usr/local/include/opencv2/ml.hpp \
/usr/local/include/opencv2/cvconfig.h \
/usr/local/include/opencv2/features2d.hpp \
/usr/local/include/opencv2/flann.hpp \
/usr/local/include/opencv2/imgproc.hpp \
/usr/local/include/opencv2/objdetect.hpp \
/usr/local/include/opencv2/opencv_modules.hpp \
/usr/local/include/opencv2/photo.hpp \
/usr/local/include/opencv2/shape.hpp \
/usr/local/include/opencv2/stitching.hpp \
/usr/local/include/opencv2/superres.hpp \
/usr/local/include/opencv2/video.hpp \
/usr/local/include/opencv2/videoio.hpp \
/usr/local/include/opencv2/videostab.hpp \
/usr/local/include/opencv2/calib3d.hpp \
/usr/local/include/tinyxml2.h

####### Output directory



####### Files

		
		
DIST_CONFS    = /opt/Qt4.8/mkspecs/common/unix.conf \
		/opt/Qt4.8/mkspecs/common/linux.conf \
		/opt/Qt4.8/mkspecs/common/gcc-base.conf \
		/opt/Qt4.8/mkspecs/common/gcc-base-unix.conf \
		/opt/Qt4.8/mkspecs/common/g++-base.conf \
		/opt/Qt4.8/mkspecs/common/g++-unix.conf \
		/opt/Qt4.8/mkspecs/common/qws.conf 

		
DIST_PRFS     =	/opt/Qt4.8/mkspecs/qconfig.pri \
		/opt/Qt4.8/mkspecs/features/qt_functions.prf \
		/opt/Qt4.8/mkspecs/features/qt_config.prf \
		/opt/Qt4.8/mkspecs/features/exclusive_builds.prf \
		/opt/Qt4.8/mkspecs/features/default_pre.prf \
		/opt/Qt4.8/mkspecs/features/release.prf \
		/opt/Qt4.8/mkspecs/features/default_post.prf \
		/opt/Qt4.8/mkspecs/features/warn_on.prf \
		/opt/Qt4.8/mkspecs/features/qt.prf \
		/opt/Qt4.8/mkspecs/features/unix/thread.prf \
		/opt/Qt4.8/mkspecs/features/moc.prf \
		/opt/Qt4.8/mkspecs/features/resources.prf \
		/opt/Qt4.8/mkspecs/features/uic.prf \
		/opt/Qt4.8/mkspecs/features/yacc.prf \
		/opt/Qt4.8/mkspecs/features/lex.prf 	
		
DIST_PRLS    = /opt/Qt4.8/lib/libQtGui.prl \
		/opt/Qt4.8/lib/libQtNetwork.prl \
		/opt/Qt4.8/lib/libQtCore.prl
		
DIST          = $(DIST_CONFS) $(DIST_PRFS)

OBJECTS_DIR   = obj/armlinux/
OBJECTS_PARENT_DIR   = $(shell dirname $(OBJECTS_DIR))
#在此处修改目标位置路径/文件名$(KSJ_SO_NAME)，如果最终结果app,则去掉TARGET前面的lib及后面的.so，并删除TARGETA的有关内容
QMAKE_TARGET  = $(KSJ_SO_NAME)
pes_parent_dir:=$(shell pwd)/$(lastword $(MAKEFILE_LIST))
pes_parent_dir:=$(shell dirname $(pes_parent_dir))
DESTPARENTDIR:=../ksjsczapi_demo_bin
DESTDIR       = $(DESTPARENTDIR)/

#app
TARGET        = $(KSJ_SO_NAME)

#动态库
#TARGET        = lib$(KSJ_SO_NAME).so
#在此处修改静态库目标位置路径及名称
#TARGETA       = ../$(KSJ_SO_NAME).lib/armlinux/lib$(KSJ_SO_NAME).a
#TARGETD       = $(KSJ_SO_NAME).so




SOURCE =

OBJECTS =


first: all

####### Implicit rules



.SUFFIXES: .o .c .cpp .cc .cxx .C



.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"



.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"



.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"



.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"



.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"



####### Build rules

#在此处修改目标位置路径delautofile
all:   genuih genmoc gensource genobjNames genobj $(DESTDIR)/$(TARGET)

$(DESTDIR)/$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	-$(DEL_FILE) $(TARGET) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP) -Wl,--whole-archive $(STATIC_LIB_BUILD_SCZ)  -Wl,--no-whole-archive
	-$(DEL_FILE) $(DESTDIR)/$(TARGET)
	-$(MOVE) $(TARGET)  $(DESTDIR) 

delautofile:
	-$(DEL_FILE) $(GENFILE_DIR)/*
	

genTmpDir:
	@$(CHK_DIR_EXISTS) $(GENFILE_DIR) || $(MKDIR) $(GENFILE_DIR)
	@$(CHK_DIR_EXISTS) $(OBJECTS_PARENT_DIR) || $(MKDIR) $(OBJECTS_PARENT_DIR)
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR) || $(MKDIR) $(OBJECTS_DIR)
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR)$(GENFILE_DIR) || $(MKDIR) $(OBJECTS_DIR)$(GENFILE_DIR)
	@$(CHK_DIR_EXISTS) $(DESTPARENTDIR) || $(MKDIR) $(DESTPARENTDIR)
	@$(CHK_DIR_EXISTS) $(DESTDIR) || $(MKDIR)  $(DESTDIR)  
	



genuih:
#	-$(UIH) $(WINNAME1).ui -o $(GENFILE_DIR)ui_$(WINNAME1).h

genmoc:
#	-$(MOC) $(DEFINES) $(INCPATH) $(WINNAME1).h -o $(GENFILE_DIR)moc_$(WINNAME1).cpp
####### Compile



#depends:gensource
#	-$(DEL_FILE) depends.mak
#	 $(CXX)  $(CXXFLAGS) $(INCPATH) -M  $(SOURCE) > depends.mak

#在此处添加.cpp文件
gensource:genTmpDir genuih genmoc
SOURCE += $(wildcard *.cpp) 
SOURCE += $(wildcard $(GENFILE_DIR)*.cpp) 
#SOURCE += $(GENFILE_DIR)moc_$(WINNAME1).cpp
		
#在此处添加.o文件, 一般每个.cpp添加一个.o文件

genobjNames:
OBJSsub = $(patsubst %.cpp,%.o,$(SOURCE))
OBJECTS += $(foreach  fn, $(OBJSsub),  $(OBJECTS_DIR)$(fn))


genobj:
#	@$(CHK_DIR_EXISTS) depends.mak &&  include depends.mak
	$(foreach fn, $(SOURCE),	$(shell $(CXX) -c $(CXXFLAGS) $(INCPATH)  $(fn) -o $(OBJECTS_DIR)$(patsubst %.cpp,%.o,$(fn))))


staticlib: $(TARGETA)



$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)



#在此处修改目标位置路径，清理上次生成的结果

clean: cleanuih cleanmoc
	-$(DEL_FILE) $(DESTDIR)/$(TARGET)
	-$(DEL_FILE) $(OBJECTS_DIR)*.o
	-$(DEL_FILE) $(OBJECTS_DIR)*/*.o
	-$(DEL_FILE) $(OBJECTS_DIR)*/*/*.o
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries



#在此处修改目标位置路径，清理上次生成的结果

distclean: clean
	-$(DEL_FILE) $(DESTDIR)/$(TARGET) 
	-$(DEL_FILE) $(TARGETA)
	-$(DEL_FILE) Makefile





check: first





cleanuih:
#	-$(DEL_FILE) $(GENFILE_DIR)ui_$(WINNAME1).h

cleanmoc:	
#	-$(DEL_FILE) $(GENFILE_DIR)moc_$(WINNAME1).cpp

####### Install

#在此处动态库安装的源路径和目标路径,KSJ自已的库相机上放在/usr/lib，
#这个不太重要，我们一般直接拷贝动态库到最终目录而不是利用make install
install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/usr/lib/ || $(MKDIR) $(INSTALL_ROOT)/usr/lib/ 
	-$(INSTALL_PROGRAM) "$(DESTDIR)/$(TARGET)" "$(INSTALL_ROOT)/usr/lib/$(TARGET)"
	-$(STRIP) --strip-unneeded "$(INSTALL_ROOT)/usr/lib/$(TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/lib/$(TARGET)" 
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/lib/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

