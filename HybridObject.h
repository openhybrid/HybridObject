/**
 * @preserve
 *
 *                                     .,,,;;,'''..
 *                                 .'','...     ..',,,.
 *                               .,,,,,,',,',;;:;,.  .,l,
 *                              .,',.     ...     ,;,   :l.
 *                             ':;.    .'.:do;;.    .c   ol;'.
 *      ';;'                   ;.;    ', .dkl';,    .c   :; .'.',::,,'''.
 *     ',,;;;,.                ; .,'     .'''.    .'.   .d;''.''''.
 *    .oxddl;::,,.             ',  .'''.   .... .'.   ,:;..
 *     .'cOX0OOkdoc.            .,'.   .. .....     'lc.
 *    .:;,,::co0XOko'              ....''..'.'''''''.
 *    .dxk0KKdc:cdOXKl............. .. ..,c....
 *     .',lxOOxl:'':xkl,',......'....    ,'.
 *          .';:oo:...                        .
 *               .cd,    ╔═╗┌─┐┬─┐┬  ┬┌─┐┬─┐   .
 *                 .l;   ╚═╗├┤ ├┬┘└┐┌┘├┤ ├┬┘   '
 *                   'l. ╚═╝└─┘┴└─ └┘ └─┘┴└─  '.
 *                    .o.                   ...
 *                     .''''','.;:''.........
 *                          .'  .l
 *                         .:.   l'
 *                        .:.    .l.
 *                       .x:      :k;,.
 *                       cxlc;    cdc,,;;.
 *                      'l :..   .c  ,
 *                      o.
 *                     .,
 *
 *             ╦ ╦┬ ┬┌┐ ┬─┐┬┌┬┐  ╔═╗┌┐  ┬┌─┐┌─┐┌┬┐┌─┐
 *             ╠═╣└┬┘├┴┐├┬┘│ ││  ║ ║├┴┐ │├┤ │   │ └─┐
 *             ╩ ╩ ┴ └─┘┴└─┴─┴┘  ╚═╝└─┘└┘└─┘└─┘ ┴ └─┘
 *
 * Created by Valentin on 10/22/14.
 *
 * Copyright (c) 2015 Valentin Heun
 *
 * All ascii characters above must be included in any redistribution.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef HybridObject_h
#define HybridObject_h

#include "Arduino.h"

class HybridObject {
 
    public:
        HybridObject() {};
        static void update();
        static void developer();
        static void add(char * obj, char * pos, String plugin = "default");
        static void write(char *  object, char * pos, float data);
        static void writeStepUp(char * obj, char * pos);
        static void writeStepDown(char * obj, char * pos);
        static void writeStepUp(char * obj, char * pos, int steps);
        static void writeStepDown(char * obj, char * pos, int steps);
        static void writeStepSerial(char * obj, char * pos, int steps, bool direction);
        static void writeDigital(char * obj, char * pos, bool data);
        static void writeFaster(int pos, float data);

        static float read(char * obj, char * pos);
        static int   stepAvailable(char * obj, char * pos);
        static int   stepAvailable(char *  obj, char *  pos, int steps);
        static bool  readDigital(char * obj, char * pos);
        static bool  readDigital(char *  obj, char *  pos, float threshold);

    static float readFaster(int pos);
        static int printObjects();
    
    static float map(float x, float in_min, float in_max);
        static float *floatObjectArray;
        static float *floatObjectArrayOld;
    
        static bool *plusObjectArray;
        static bool *minusObjectArray;

    private:
        static void init();
        static void sendDeveloper();

        static bool clearState;
        static bool starter;
        static bool developerStatus;
        static bool runInit;
        static int caseSteper;
        static int arraySize;
        static char * object;
        static unsigned int objectInt;
        static char str[];
        static char floatStr[];
        static char **stringArray;
        static float tempFloatBuffer;
};

#endif

