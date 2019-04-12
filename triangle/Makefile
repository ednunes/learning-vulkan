VULKAN_SDK_PATH = /home/eduardonunes/Documentos/instalations/vulkan1.1.101.0/x86_64
CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

Triangle: main.cpp
	g++ $(CFLAGS) -o Triangle main.cpp $(LDFLAGS)

.PHONY: test clean

test: Triangle
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/explicit_layer.d ./Triangle

clean:
	rm -f Triangle 
