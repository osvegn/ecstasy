///
/// @file GamepadConnectedListener.hpp
/// @author Andréas Leroux (andreas.leroux@epitech.eu)
/// @brief
/// @version 1.0.0
/// @date 2022-11-18
///
/// @copyright Copyright (c) ECSTASY 2022
///
///

#ifndef ECSTASY_INTEGRATIONS_EVENT_LISTENERS_GAMEPADCONNECTEDLISTENER_HPP_
#define ECSTASY_INTEGRATIONS_EVENT_LISTENERS_GAMEPADCONNECTEDLISTENER_HPP_

#include "EventListeners.hpp"

namespace ecstasy::integration::event
{
    struct GamepadConnectedEvent;

    /// @brief @ref GamepadConnectedEvent listener.
    using GamepadConnectedListener = EventListener<GamepadConnectedEvent>;
} // namespace ecstasy::integration::event

#endif /* !ECSTASY_INTEGRATIONS_EVENT_LISTENERS_GAMEPADCONNECTEDLISTENER_HPP_ */
