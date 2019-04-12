#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>
#include <functional>
#include <cstdlib>

const int WIDTH = 800;
const int HEIGHT = 600;

using namespace std;

class HelloTriangleApplication {
	public:
		void run() {
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}

	private:
		GLFWwindow* window;
		VkInstance instance;

		void initWindow(){
			glfwInit();

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		}

		void createInstance(){
			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hello Triangle";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;

			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;

			createInfo.enabledLayerCount = 0;
			
			if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
				throw std::runtime_error("failed to create instance!");
			}

			checkExtensionSupport();
		}

		void checkExtensionSupport(){
			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
			set<char const*> extensionNamesSet;

			//std::cout << "Show all available extensions:" << std::endl;
			for (const auto& extension : extensions) {
				std::cout << "\t" << extension.extensionName << std::endl;
				extensionNamesSet.insert(extension.extensionName);
			}

			uint32_t extensionCountGLFW = 0;
			const char** requiredExtensionsList = glfwGetRequiredInstanceExtensions(&extensionCountGLFW);

			vector<char const*> requiredExtensionsNotIncluded;

			//std::cout << "Show all required extensions:" << std::endl;
			for(char const **requiredExtension = requiredExtensionsList; *requiredExtension; ++requiredExtension){
				//std::cout << "\t" <<  *requiredExtension << std::endl;
				if(extensionNamesSet.find(*requiredExtension)!=extensionNamesSet.end()){
					requiredExtensionsNotIncluded.push_back(*requiredExtension);
				}
			}

			if(!requiredExtensionsNotIncluded.size()) {
				std::cout << "\nAll required extensions are included in the supported extensions list!!!\n" << std::endl;
			}
			else {
				std::cout << "\nMissing these required extensions:" << endl;
				for(auto requiredExtension : requiredExtensionsNotIncluded){
					std::cout << "\t" << requiredExtension << std::endl;
				}
			}

			delete requiredExtensionsList;
		}

		void initVulkan() {
			createInstance();
		}

		void mainLoop() {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
			}

		}

		void cleanup() {
			vkDestroyInstance(instance, nullptr);
			glfwDestroyWindow(window);
			glfwTerminate();
		}
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
