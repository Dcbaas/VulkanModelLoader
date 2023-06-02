#pragma once

#include <memory>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

namespace vkr = vk::raii;

namespace baas::graphics
{
	struct WindowDeleter
	{
		//WindowDeleter() {}
		//WindowDeleter(const WindowDeleter& d) {}
		//WindowDeleter(WindowDeleter&& d) {}
		void operator()(SDL_Window* window)
		{
			SDL_DestroyWindow(window);
		}
	};

	struct GraphicsSystem
	{
		std::unique_ptr<SDL_Window, WindowDeleter> window;
		std::unique_ptr<vkr::Context> context;
		std::unique_ptr<vkr::Instance> instance;

	};

	GraphicsSystem init_graphics_system();
}