CXX = g++
CXXFLAGS = -g -Wall -static -fprofile-arcs -ftest-coverage -I./ -I$(CPPUTEST_HOME)/include
KERNELDIR = ./../../..
APPLDIR = ./..
CXXFLAGS += -I$(APPLDIR) \
			-I$(APPLDIR)/../common \
			-I$(APPLDIR)/../OBJ \
			-I$(KERNELDIR)/include \
			-I$(KERNELDIR)/target/ev3_gcc \
		   	-I$(KERNELDIR)/target/ev3_gcc/api/include \
			-I$(KERNELDIR)/arch \
			-I$(KERNELDIR)/arch/arm_gcc/am1808 \
			-I$(KERNELDIR)/arch/arm_gcc/common \
			-I$(KERNELDIR)/target/ev3_gcc/drivers/common/include \
		   	-I$(KERNELDIR)/target/ev3_gcc/TLSF-2.4.6/include \
		   	-I$(KERNELDIR)/target/ev3_gcc/platform/include \
		   	-I$(KERNELDIR)/target/ev3_gcc/pil/include

LDFLAGS = -L./ -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
CPPUTEST_HOME = ./
TARGET = ButtonTest
SRCS = SW_Buttontest.cpp ../SW_Button.c
OBJS = $(SRCS:.cpp=.o)
OBJS += $(SRCS:.c=.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	 $(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

$(OBJS): $(SRCS)
	$(CXX) -c $(CXXFLAGS) $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

%.o: %.c
	$(CXX) -c $(CXXFLAGS) $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) *.gcno *.gcov *~
	find . -name "*.gcda" | xargs -r rm
