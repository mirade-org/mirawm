// This file is part of "mirawm"
// Under the MIT License
// Copyright (c) mirade-org, Antonin Hérault

module;

#include <X11/Xlib.h>
#include <X11/Xutil.h>

export module handler;

import utils;

/**
 * Handle XEvents for the `WM` class
*/
export class Handler {
    private:
        Display *_display; // pointer on the `WM` member

    public:
        /**
         * "Lateinit" constructor
         * NOTE The real constructor must be called later, and before any member
         * usage, else you can make important errors
        */
        Handler() {}

        Handler(Display *display) {
            _display = display;
        }

        /**
         * Handle the X11 errors
         * Static because the function's address is passed to X11
         * 
         * @param display Needed to be an X11 handler 
        */
        static int on_XError(Display *display, XErrorEvent *event) {
            return todo(0);
        }

        /**
         * Determine if a window manager is already running on the system 
         * 
         * @param display Needed to be an X11 handler
        */
        static int on_wm_detected(Display *display, XErrorEvent *event) {
            return todo(0);
        }

        void on_create_notify(const XCreateWindowEvent &event) {}
        void on_destroy_notify(const XDestroyWindowEvent &event) {}
        void on_reparent_notify(const XReparentEvent &event) {}
        void on_configure_notify(const XConfigureEvent &event) {}
        void on_map_notify(const XMapEvent &event) {}

        template <class WM>
        void on_unmap_notify(WM *wm, const XUnmapEvent &event) {
            // Ignore reparented pre-existing window
            if (event.event == wm->_root) {
                return;
            }

            wm->unframe(event.window);
        }

        /**
         * Configure a window like requested
        */
        void on_configure_request(const XConfigureRequestEvent &event) {
            XWindowChanges changes;
            changes.x = event.x;
            changes.y = event.y;
            changes.width = event.width;
            changes.height = event.height;
            changes.border_width = event.border_width;
            changes.sibling = event.above;
            changes.stack_mode = event.detail;

            XConfigureWindow(
                _display, 
                event.window, 
                event.value_mask, 
                &changes
            );
        }

        template <class WM>
        void on_map_request(WM *wm, const XMapRequestEvent &event) {
            wm->frame(event.window, false);
            XMapWindow(_display, event.window);
        }

        void on_button_press(const XButtonPressedEvent &event) {}

	template <class WM>
        void on_button_release(WM *wm, const XButtonReleasedEvent &event) {
            const Window frame = wm->_clients[event.window];

            Window returned_root;
            int x = 0;
            int y = 0;
            u_int width = 0;
            u_int height = 0;
            u_int border_width = 0;
            u_int depth = 0;

            XGetGeometry(
                _display,
                frame,
                &returned_root,
                &x,
                &y,
                &width,
                &height,
                &border_width,
                &depth
            );

            XRaiseWindow(_display, frame); // place the window at the top
        }

        void on_key_press(const XKeyPressedEvent &event) {
            // Close a window when ALT + F4 pressed
            if (
                (event.state & Mod1Mask) &&
                (event.keycode == XKeysymToKeycode(_display, XK_F4))
            ) {
                // Agressive way to kill a window
                XKillClient(_display, event.window);
                return;
            }

            // Others...
        }

        void on_key_release(const XKeyReleasedEvent &event) {}
};
