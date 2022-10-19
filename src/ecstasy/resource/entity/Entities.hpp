///
/// @file Entities.hpp
/// @author Andréas Leroux (andreas.leroux@epitech.eu)
/// @brief
/// @version 1.0.0
/// @date 2022-10-18
///
/// @copyright Copyright (c) ECSTASY 2022
///
///

#ifndef ECSTASY_RESOURCE_ENTITY_ENTITIES_HPP_
#define ECSTASY_RESOURCE_ENTITY_ENTITIES_HPP_

#include <vector>

#include "Entity.hpp"
#include "ecstasy/resource/Resource.hpp"
#include "util/BitSet.hpp"

namespace ecstasy
{
    ///
    /// @brief Entities Resource.
    ///
    /// @author Andréas Leroux (andreas.leroux@epitech.eu)
    /// @since 1.0.0 (2022-10-18)
    ///
    class Entities : public Resource {
      public:
        ///
        /// @brief Entities builder to add multiple component to an entity on creation.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        class Builder {
          public:
            ///
            /// @brief Cannot copy a builder.
            ///
            /// @param[in] other builder to copy.
            ///
            /// @author Andréas Leroux (andreas.leroux@epitech.eu)
            /// @since 1.0.0 (2022-10-19)
            ///
            Builder(const Builder &other) = delete;

            ///
            /// @brief Add a component to the builder target entity.
            ///
            /// @tparam S Component storage type.
            /// @tparam Args Type of the Component constructor parameters
            ///
            /// @param[in] storage Component storage.
            /// @param[in] args Arguments to forward to the component constructor.
            ///
            /// @return Builder& @b this.
            ///
            /// @throw std::logic_error If the builder was already consumed or if the entity already has the
            /// component.
            ///
            /// @author Andréas Leroux (andreas.leroux@epitech.eu)
            /// @since 1.0.0 (2022-10-19)
            ///
            template <IsStorage S, typename... Args>
            Builder &with(S &storage, Args &&...args)
            {
                assertNotBuilt();
                _entity.add(storage, std::forward<Args>(args)...);
                return *this;
            }

            ///
            /// @brief Finalize the entity, making it alive.
            ///
            /// @return Entity Newly created entity.
            ///
            /// @throw std::logic_error If the builder was already consumed.
            ///
            /// @author Andréas Leroux (andreas.leroux@epitech.eu)
            /// @since 1.0.0 (2022-10-19)
            ///
            Entity build();

          private:
            Entities &_parent;
            Entity _entity;
            bool _built;

            ///
            /// @brief Construct a new Builder, this method can only be called by an @ref Entities.
            ///
            /// @param[in] parent Entities object creating this builder.
            /// @param[in] entity Entity target (modified by the builder).
            ///
            /// @author Andréas Leroux (andreas.leroux@epitech.eu)
            /// @since 1.0.0 (2022-10-19)
            ///
            Builder(Entities &parent, Entity entity);

            ///
            /// @brief Verify if the builder has not already been consumed.
            ///
            /// @throw std::logic_error if @b _built is true.
            ///
            /// @author Andréas Leroux (andreas.leroux@epitech.eu)
            /// @since 1.0.0 (2022-10-19)
            ///
            void assertNotBuilt() const;

            friend Entities;
        };

        ///
        /// @brief Construct a new Entities resource without any entity.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-18)
        ///
        Entities();

        ///
        /// @brief Create a new entity, alive or not.
        ///
        /// @param[in] alive Whether the entity must be created alive or not.
        ///
        /// @return Entity Newly created entity.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-18)
        ///
        Entity create(bool alive = true);

        ///
        /// @brief Create a new entity builder.
        ///
        /// @return Builder Newly created builder.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-19)
        ///
        [[nodiscard]] Builder builder();

        ///
        /// @brief Retrieve an entity from its identifier.
        ///
        /// @param[in] id Index of the entity.
        ///
        /// @return Entity
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-18)
        ///
        Entity get(Entity::Index id) const;

        ///
        /// @brief Killing the entity when called.
        ///
        /// @note Entity is considered kill if it was alive.
        ///
        /// @param[in] entity Entity to kill.
        ///
        /// @return bool Whether the entity was killed or not.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-18)
        ///
        bool kill(Entity entity);

        ///
        /// @brief Tests if an entity is alive.
        ///
        /// @param[in] entity entity to test.
        ///
        /// @return bool If the entity is alive.
        ///
        /// @author Andréas Leroux (andreas.leroux@epitech.eu)
        /// @since 1.0.0 (2022-10-18)
        ///
        bool isAlive(Entity entity) const;

      private:
        std::vector<Entity::Generation> _generations;
        util::BitSet _alive;
    };
} // namespace ecstasy

#endif /* !ECSTASY_RESOURCE_ENTITY_ENTITIES_HPP_ */
