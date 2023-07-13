NAME	=	arcade_vulkan.so

LDFLAGS = -std=c++17 -O2 -Wall -Wextra -Werror -shared -I../../Header

CXXFLAGS += -L../../Utils -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -fPIC \
	-I/usr/include/freetype2 -I/usr/include/libpng16

CC	=	g++

SRC	=	FreeType/Texter.cpp \
		Vulkan/CommandManager.cpp \
		Vulkan/DebugMessenger.cpp \
		Vulkan/Instance.cpp \
		Vulkan/LogicalDevice.cpp \
		Vulkan/Operator.cpp \
		Vulkan/PhysicalDevice.cpp \
		Vulkan/Pipeline.cpp \
		Vulkan/QueueFamilyIndices.cpp \
		Vulkan/Surface.cpp \
		Vulkan/SwapChain.cpp \
		Vulkan/Utils.cpp \
		Vulkan/Vertex.cpp \
		Vulkan/VertexBuffer.cpp \
		Vulkan/Window.cpp \
		Renderer.cpp

RM = rm -f

OBJ	= $(SRC:.cpp=.o)

SHADERS = vert.spv frag.spv

all: $(OBJ)
	$(CC) $(LDFLAGS) $(CXXFLAGS) $(OBJ) -o $(NAME)
	./compile.sh
	mkdir -p ../lib
	mv $(NAME) ../lib

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../lib/$(NAME)
	$(RM) $(SHADERS)

re: fclean all

.PHONY: all clean fclean re
