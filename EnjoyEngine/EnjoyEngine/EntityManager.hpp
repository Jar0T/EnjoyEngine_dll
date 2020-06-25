#pragma once
#include <queue>

#ifdef ENJOYENGINE_EXPORTS
#define ENJOYENGINE_API __declspec(dllexport)
#else
#define ENJOYENGINE_API __declspec(dllimport)
#endif

namespace EE {
	/// <summary>
	/// Class managing entities
	/// </summary>
	class ENJOYENGINE_API EntityManager {
	private:
		static EntityManager* _entityManager;

		std::queue<std::uint32_t> _freeIDs;

		EntityManager(std::uint32_t maxIDs);

		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;

	public:
		~EntityManager();

		/// <summary>
		/// Initializes entity manager
		/// </summary>
		/// <param name="maxIDs">Max number of entities thart can be active at the same time</param>
		static void init(std::uint32_t maxIDs);

		/// <summary>
		/// Used by entity to get it's ID. Shouldn't be used bu user
		/// </summary>
		/// <returns>New entitie's ID</returns>
		static std::uint32_t getID();

		/// <summary>
		/// Entity calls this method when it gets destroyed
		/// </summary>
		/// <param name="ID">Destroyed entitie's ID</param>
		static void entityDestroyed(std::uint32_t ID);

		/// <summary>
		/// Vector of active entitie's IDs
		/// </summary>
		std::vector<std::uint32_t> entities;

	};
}