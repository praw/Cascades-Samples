/* Copyright (c) 2012 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef _HELLOFOREIGNWINDOW_H_
#define _HELLOFOREIGNWINDOW_H_

#include <bb/cascades/Application>
#include <screen/screen.h>
#include <QThread>

using namespace bb::cascades;

using namespace bb::cascades;

namespace bb
{
    namespace cascades
    {
        class Page;
    }
}

/**
 * HelloForeignWindowApp
 *
 * This application shows you how to use the ForeignWindow Control to render
 * a custom pixel buffer in a separate window outside Cascades. A ForeignWindow
 * literally "punch a hole" in the Cascades buffer allowing you to show whatever
 * you like in that window.
 */
class HelloForeignWindowApp: public QThread
{
Q_OBJECT

public:
    HelloForeignWindowApp();
    ~ HelloForeignWindowApp();

    /**
     * Invokable function that can be called from QML to turn the rendering to window on and off.
     */
    Q_INVOKABLE
    void tvPower(bool on);

private:
    /**
     * Set up function for our Foreign window, sets up a window and a pixel buffer which we use
     * to simulate the noise on a TV.
     *
     * @param group Window group of the application
     * @param id Window id
     * @param x window position in x direction
     * @param y window position in y direction
     * @param width window width
     * @param height window height
     *
     * @return true if creation was successful otherwise false.
     */
    bool createForeignWindow(const QString &group, const QString id, int x, int y, int width,
            int height);

    /**
     * This function retrieves the size and position of the ForeignWIndow from QML and
     * then create the window that should be rendered in it via createForeignWindow.
     *
     */
    void initForeignWindow();

    /**
     * QThread run function, we run the custom window rendering in a separate thread to avoid lag
     * in the rest of the Cascades UI.
     */
    void run();

    /**
     * This function performs the rendering off the TV noise.
     *
     * @param noise if true a random noise pattern is rendered, otherwise only black is shown.
     */
    void doNoise(bool noise);

    // Boolean that controls if the TV power is on or off (show noise or not).
    bool mTvOn;

    // Boolean that is true if the tv window has been initialized.
    bool mTvInitialized;

    // Screen context handle.
    screen_context_t mScreenCtx;

    // Screen window handle.
    screen_window_t mScreenWindow;

    // The screen window buffer.
    screen_buffer_t mScreenBuf[1];

    // The pixel buffer.
    screen_buffer_t mScreenPixelBuffer;

    // The pixel buffer size.
    int mSize[2];

    // The window dimensions.
    int mRect[4];

    // Pixel buffer stride.
    int mStride;

    // The application page.
    Page *mAppPage;
};

#endif // ifndef _HELLOFOREIGNWINDOW_H_
