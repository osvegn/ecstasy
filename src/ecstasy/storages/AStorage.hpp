///
/// @file IStorage.hpp
/// @author Andréas Leroux (andreas.leroux@epitech.eu)
/// @brief
/// @version 1.0.0
/// @date 2022-10-19
///
/// @copyright Copyright (c) ECSTASY 2022 - 2024
///
///

#ifndef ECSTASY_STORAGE_ASTORAGE_HPP_
#define ECSTASY_STORAGE_ASTORAGE_HPP_

#include <span>

#include "ecstasy/config.hpp"
#include "ecstasy/resources/entity/Entity.hpp"
#include "ecstasy/storages/IStorage.hpp"
#include "util/BitSet.hpp"

namespace ecstasy
{

    ///
    /// @brief Abstract class for all components storage.
    ///
    /// @tparam C Component type.
    ///
    /// @author Andréas Leroux (andreas.leroux@epitech.eu)
    /// @since 1.0.0 (2024-04-23)
    ///
    template <typename C>
    class AStorage : public IStorage {
      public:
        /// @brief IsStorage constraint
        using Component = C;

        /// @brief @ref ecstasy::query::QueryableObject constraint.
        using QueryData = C &;
        /// @brief @ref ecstasy::query::ConstQueryableObject constraint.
        using ConstQueryData = const C &;

        ///
        /// @brief Erase the @b Component instance associated to the given entity.
        ///
        /// @note Does nothing if the index doesn't match with any component (ie if the entity doesn't have a component
        /// @b Component)
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return bool True if the component was erased, false otherwise.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        virtual bool erase(Entity::Index index) = 0;

        ///
        /// @brief Erase multiple @b Component instances associated to the given @p entities.
        ///
        /// @note Does nothing for entity without attached component (ie if the entity doesn't have a component
        /// @b Component)
        ///
        /// @param[in] entities target entities.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-21)
        ///
        void erase(std::span<Entity> entities) override final
        {
            for (Entity entity : entities)
                erase(entity.getIndex());
        }

        /// @copydoc contains
        bool contains(Entity::Index index) const noexcept override final
        {
            return (index < getMask().size()) && getMask()[index];
        }

        ///
        /// @brief Retrieve the @b Component instance associated to the given entity and perform bound checking.
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return QueryData Reference to the associated component.
        ///
        /// @throw std::out_of_range If the entity doesn't have the component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2024-04-23)
        ///
        Component &at(Entity::Index index)
        {
            if (!contains(index))
                throw std::out_of_range("Entity doesn't have the component");
            return (*this)[index];
        }

        ///
        /// @brief Retrieve the @b Component instance associated to the given entity and perform bound checking.
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return QueryData Reference to the associated component.
        ///
        /// @throw std::out_of_range If the entity doesn't have the component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2024-04-23)
        ///
        const Component &at(Entity::Index index) const
        {
            if (!contains(index))
                throw std::out_of_range("Entity doesn't have the component");
            return (*this)[index];
        }

        ///
        /// @brief Retrieve the @b Component instance associated to the given entity.
        ///
        /// @warning This function may not perform bound checking. For @ref VectorStorage or @ref MarkerStorage it is
        /// noexcept but not for @ref MapStorage for example.
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return Component& Reference to the associated component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        virtual Component &operator[](Entity::Index index) = 0;

        /// @copydoc operator[](Entity::Index)
        ///
        /// @note @ref ecstasy::query::QueryableObject constraint.
        QueryData getQueryData(Entity::Index index)
        {
            return (*this)[index];
        };

        ///
        /// @brief Retrieve the const @b Component instance associated to the given entity.
        ///
        /// @warning This function may not perform bound checking. For @ref VectorStorage or @ref MarkerStorage it is
        /// noexcept but not for @ref MapStorage for example.
        ///
        /// @param[in] index Index of the entity.
        ///
        /// @return const Component& Const reference to the associated component.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        virtual const Component &operator[](Entity::Index index) const = 0;

        /// @copydoc operator[](Entity::Index)
        ///
        /// @note @ref ecstasy::query::ConstQueryableObject constraint.
        ConstQueryData getQueryData(Entity::Index index) const
        {
            return (*this)[index];
        };
    };

} // namespace ecstasy

#endif /* !ECSTASY_STORAGE_ASTORAGE_HPP_ */
