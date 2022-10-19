///
/// @file MapStorage.hpp
/// @author Andréas Leroux (andreas.leroux@epitech.eu)
/// @brief
/// @version 1.0.0
/// @date 2022-10-19
///
/// @copyright Copyright (c) ECSTASY 2022
///
///

#ifndef ECSTASY_STORAGE_MAPSTORAGE_HPP_
#define ECSTASY_STORAGE_MAPSTORAGE_HPP_

#include <unordered_map>

#include "ecstasy/resource/entity/Entity.hpp"

namespace ecstasy
{
    ///
    /// @brief Associative Map to store entity components
    ///
    /// @tparam Component
    ///
    /// @author Andréas Leroux (andreas.leroux@epitech.eu)
    /// @since 1.0.0 (2022-10-19)
    ///
    template <typename Component>
    class MapStorage {
      public:
        ///
        /// @brief Construct a new Map Storage for a given Component type.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        MapStorage() = default;

        ///
        /// @brief Copy constructor is deleted.
        ///
        /// @param[in] other Storage to copy.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        MapStorage(const MapStorage &other) = delete;

        ///
        /// @brief Emplace a new @b Component instance for a given entity.
        ///
        /// @note No check is done to see if the entity already has the component.
        ///
        /// @tparam Args Type of the arguments to forward to the component constructor.
        ///
        /// @param[in] index Entity index.
        /// @param[in] args Args to forward to the component constructor.
        ///
        /// @return Component& Newly created component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        template <typename... Args>
        Component &emplace(Entity::Index index, Args &&...args)
        {
            return _components.emplace(std::make_pair(index, Component(std::forward<Args>(args)...))).first->second;
        }

        ///
        /// @brief Erase the @b Component instance associated to the given entity.
        ///
        /// @note Does nothing if the index doesn't match with any component (ie if the entity doesn't have a component
        /// @b Component)
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        void erase(Entity::Index index)
        {
            _components.erase(index);
        }

        ///
        /// @brief Retrieve the @b Component instance associated to the given entity.
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return const Component& Const reference to the associated component.
        ///
        /// @throw std::out_of_range If the entity doesn't have the component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        const Component &operator[](Entity::Index index) const
        {
            return _components.at(index);
        }

        ///
        /// @brief Retrieve the @b Component instance associated to the given entity.
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return Component& Reference to the associated component.
        ///
        /// @throw std::out_of_range If the entity doesn't have the component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        Component &operator[](Entity::Index index)
        {
            return _components.at(index);
        }

        ///
        /// @brief Test if the entity index match a @b Component instance.
        ///
        /// @param[in] index
        /// @return bool
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        bool contains(Entity::Index index) const
        {
            return _components.find(index) != _components.end();
        }

      private:
        std::unordered_map<Entity::Index, Component> _components;
    };
} // namespace ecstasy

#endif /* !ECSTASY_STORAGE_MAPSTORAGE_HPP_ */
