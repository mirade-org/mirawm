// This file is part of "mirawm"
// Under the MIT License
// Copyright (c) mirade-org, Antonin Hérault

module;

#include <X11/Xlib.h>
#include <memory>
#include "utils.hpp"

export module wm;

import handler;
import utils;

/**
 * Main structure for "mirawm"
 * Window manager
*/
export class WM {
    private:
        Display *_display;
        Window _root;
        Handler _handler;

    public:
        WM() {
            _display = XOpenDisplay(nullptr);
            if (_display == nullptr) {
                todo();
            }

            _root = DefaultRootWindow(_display);
            _handler = Handler(_display);
        }

        ~WM()  {
            XCloseDisplay(_display);
        }

        void run() {
            _check_wm();
            XSetErrorHandler(&Handler::on_XError);

            while (true) {
                XEvent event;
                XNextEvent(_display, &event);
                _call_handler(event);
            }
        }

    private:
        // Check if a window manager is already running on the system
        // Temporarily define the error handler as `Handler::on_wm_detected`
        void _check_wm()  {
            // Detect if a window manager is already defined
            XSetErrorHandler(&Handler::on_wm_detected); // temporary error handler
            XSelectInput(
                _display,
                _root,
                SubstructureRedirectMask | SubstructureNotifyMask
            );
            XSync(_display, false);
        }

        /**
         * Call the correct function (mainly from `Handler`)
        */
        void _call_handler(XEvent event) {
            match (event.type) {
                with (CreateNotify,
                    _handler.on_create_notify(event.xcreatewindow);
                );
                with (DestroyNotify,
                    _handler.on_destroy_notify(event.xdestroywindow);
                );
                with (ReparentNotify,
                    _handler.on_reparent_notify(event.xreparent);
                );
                default: break;
            }
        }
};
