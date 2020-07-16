#pragma once
#include <cstdint>
#include <vector>
#include <tuple>

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	struct BaseECSComponent;
	typedef void* EntityHandle;
	typedef std::uint32_t(*ECSComponentCreateFunction)(std::vector<std::uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp);
	typedef void (*ECSComponentFreeFunction)(BaseECSComponent* comp);

	struct ENJOYENGINE_API BaseECSComponent {
	public:
		int stackLayer = 0;
		static std::uint32_t registerComponentType(ECSComponentCreateFunction createfn, ECSComponentFreeFunction freefn, size_t size) {
			if (componentTypes == nullptr) {
				componentTypes = new std::vector<std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>;
			}
			std::uint32_t componentTypeID = componentTypes->size();
			componentTypes->push_back(
				std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(
					createfn, freefn, size
					)
			);
			return componentTypeID;
		}
		EntityHandle entity = nullptr;

		inline static ECSComponentCreateFunction getTypeCreateFunction(std::uint32_t id) {
			return std::get<0>((*componentTypes)[id]);
		}
		inline static ECSComponentFreeFunction getTypeFreeFunction(std::uint32_t id) {
			return std::get<1>((*componentTypes)[id]);
		}
		inline static size_t getTypeSize(std::uint32_t id) {
			return std::get<2>((*componentTypes)[id]);
		}
		inline static bool isTypeValid(std::uint32_t id) {
			return id < componentTypes->size();
		}
	private:
		static std::vector<std::tuple< ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>* componentTypes;
	};

	template<typename Component>
	struct ECSComponent : public BaseECSComponent {
		static const ECSComponentCreateFunction CREATE_FUNCTION;
		static const ECSComponentFreeFunction FREE_FUNCTION;
		static const std::uint32_t ID;
		static const size_t size;
	};

	template<typename Component>
	std::uint32_t ECSComponentCreate(std::vector<std::uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp) {
		size_t index = memory.size();
		memory.resize(index + Component::size);
		Component* component = new(&memory[index]) Component(*(Component*)comp);
		component->entity = entity;
		return index;
	}

	template<typename Component>
	void ECSComponentFree(BaseECSComponent* comp) {
		Component* component = (Component*)comp;
		component->~Component();
	}

	template<typename Component>
	const std::uint32_t ECSComponent<Component>::ID(
		BaseECSComponent::registerComponentType(ECSComponentCreate<Component>, ECSComponentFree<Component>, sizeof(Component))
	);

	template<typename Component>
	const size_t ECSComponent<Component>::size(sizeof(Component));

	template<typename Component>
	const ECSComponentCreateFunction ECSComponent<Component>::CREATE_FUNCTION(ECSComponentCreate<Component>);

	template<typename Component>
	const ECSComponentFreeFunction ECSComponent<Component>::FREE_FUNCTION(ECSComponentFree<Component>);
}
