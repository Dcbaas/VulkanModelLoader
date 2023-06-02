#include "graphics.h"

#include <string>
#include <vector>

namespace baas::graphics
{
	constexpr std::string_view APP_NAME{"Model Loader"};
	constexpr std::string_view ENGINE_NAME{"Baas Engine"};

	GraphicsSystem init_graphics_system()
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Vulkan_LoadLibrary(nullptr);

		GraphicsSystem gs;

		SDL_Window* raw_window = SDL_CreateWindow(APP_NAME.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
		WindowDeleter win_deleter;
		gs.window = std::unique_ptr<SDL_Window, WindowDeleter>(raw_window, win_deleter);


		uint32_t ext_count;
		SDL_Vulkan_GetInstanceExtensions(raw_window, &ext_count, nullptr);
		std::vector<const char*> ext_names(ext_count); 
		SDL_Vulkan_GetInstanceExtensions(raw_window, &ext_count, ext_names.data());
		gs.context = std::make_unique<vkr::Context>();

		vk::ApplicationInfo app_info(APP_NAME.data(), 1, ENGINE_NAME.data(), 1, VK_API_VERSION_1_3);
		vk::InstanceCreateInfo create_info({}, &app_info);
		gs.instance = std::make_unique<vkr::Instance>(*gs.context, create_info);

		return gs;
	} 
}