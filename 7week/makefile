# Target: The name of your executable file
TARGET = runMe

# C++ compiler
CXX = g++

# C++ compiler flags (optimize for speed)
CXXFLAGS = -O2 -Wall

# Source files (cpp)
SRCS = ground.cpp position.cpp  uiDraw.cpp Lab07.cpp test.cpp uiInteract.cpp

# Object files (created from source files)
OBJS = $(SRCS:.cpp=.o)

# Header files (include for compilation)
HDRS = ground.h testGround.h testPosition.h uiInteract.h position.h test.h uiDraw.h

# Linker flags (link with OpenGL and GLFW libraries)
LDFLAGS = -lglut -lGL -lGLU -lGLEW

# Rule to compile a source file (.cpp) into an object file (.o)
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
