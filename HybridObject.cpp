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

//#include "Arduino.h"
#include "HybridObject.h"

#define BUFFERLENGTH 200
#define SERIALBUFFERLENGTH 400
#define FLOATSTRBUFFER 10
#define BAUDRATE 115200
#define SYSTEMDELAYFORDATA 15

void serialEventRun() {
    HybridObject::update();
}

bool HybridObject::clearState = false;
bool HybridObject::starter = false;
bool HybridObject::developerStatus = false;
bool HybridObject::runInit = true;
int HybridObject::caseSteper = 9999;
int HybridObject::arraySize = 0;
unsigned int  HybridObject::objectInt = 0;
char HybridObject::str[SERIALBUFFERLENGTH + 1];
char HybridObject::floatStr[FLOATSTRBUFFER + 1];
char *HybridObject::object = new char[BUFFERLENGTH + 1];
float HybridObject::tempFloatBuffer = 0.0;


float *HybridObject::floatObjectArray =
        (float *) malloc(sizeof(float) * arraySize);

float *HybridObject::floatObjectArrayOld =
        (float *) malloc(sizeof(float) * arraySize);

bool *HybridObject::plusObjectArray =
        (bool *) malloc(sizeof(bool) * arraySize);

bool *HybridObject::minusObjectArray =
        (bool *) malloc(sizeof(bool) * arraySize);

char **HybridObject::stringArray =
        (char **) malloc(sizeof(char *) * arraySize);

void HybridObject::update() {

    //  Serial.println("");

   // Serial.println("ss");
    for (int i = 0; i < arraySize; i++) {
        floatObjectArrayOld[i] = floatObjectArray[i];
    }

    // char  incomingByte;
    while (Serial1.available() > 0) {
        //if(Serial1.available()<20){

        // int bRead;
        // bRead = Serial.readBytesUntil(0x010,str,20);
        strcpy(str, Serial1.readStringUntil('\n').c_str());


        // Serial.read();
        //continue;
        //    }else{
        // while (Serial1.available() > 0) {
        //   Serial.read();
        // }
        // }
        //sprintf(str, "%s", Serial1.readStringUntil('\n').c_str());
        // Serial1.readBytesUntil('\n',str, Serial1BUFFERLENGTH);
        // strcpy(str, Serial1.readStringUntil("\n").c_str());
        // delay(30);

       Serial.println(">>serial>> ");
       Serial.println(str);


        if (strcmp(str, "okbird") == 0) {
            // Serial.println("ok");
            // starter = true;
            sendDeveloper();
            for (int i = 0; i < arraySize; i++) {
                Serial1.print("a\n");
                Serial1.print(stringArray[i]);
                Serial1.print("\n");
                Serial1.print(i);
                Serial1.print("\n");
                // this must be considered for later
                Serial1.print("default");
                Serial1.print("\n");
            }

            Serial1.print("c\n");
            Serial1.print(arraySize);
            Serial1.print("\n");

            caseSteper = 0;
        }

        switch (caseSteper) {
            case 0:
                if (strcmp(str, "f") == 0) {
                    caseSteper = 1;
                    objectInt = 0;
                }
                else if (strcmp(str, "d") == 0) {
                    caseSteper = 1;
                    objectInt = 0;
                }
                else if (strcmp(str, "p") == 0) {
                    caseSteper = 10;
                    objectInt = 0;
                    // using the float buffer temporary to communicate the mode.
                    //  Serial.print("one\n");
                }
                else if (strcmp(str, "n") == 0) {
                    caseSteper = 20;
                    objectInt = 0;
                    // temp mode.. buffer will be overwritten later anyway.
                    // Serial.print("two\n");
                }
                break;
            case 1:
                objectInt = atoi(str);
                if (objectInt < arraySize && objectInt >= 0) {
                    caseSteper = 2;
                } else { caseSteper = 0; }
                // Serial.println(atoi(str));
                break;
            case 10:
                objectInt = atoi(str);
                if (objectInt < arraySize && objectInt >= 0) {
                    caseSteper = 12;
                } else { caseSteper = 0; }
                // Serial.println(atoi(str));
                break;
            case 20:
                objectInt = atoi(str);
                if (objectInt < arraySize && objectInt >= 0) {
                    caseSteper = 22;
                } else { caseSteper = 0; }
                // Serial.println(atoi(str));
                break;
            case 2:
                tempFloatBuffer = atof(str);
                if (tempFloatBuffer > 1) tempFloatBuffer = 1;
                if (tempFloatBuffer < 0) tempFloatBuffer = 0;
                floatObjectArray[objectInt] = tempFloatBuffer;
                caseSteper = 0;
                break;
            case 12:
                plusObjectArray[objectInt] = true;
                minusObjectArray[objectInt] = false;
                tempFloatBuffer = atof(str);
                if (tempFloatBuffer > 1) tempFloatBuffer = 1;
                if (tempFloatBuffer < 0) tempFloatBuffer = 0;
                floatObjectArray[objectInt] = tempFloatBuffer;
                caseSteper = 0;
                break;
            case 22:
                plusObjectArray[objectInt] = false;
                minusObjectArray[objectInt] = true;
                tempFloatBuffer = atof(str);
                if (tempFloatBuffer > 1) tempFloatBuffer = 1;
                if (tempFloatBuffer < 0) tempFloatBuffer = 0;
                floatObjectArray[objectInt] = tempFloatBuffer;
                caseSteper = 0;
                break;
        };
    };

    // destress the Hybrid Object Server....
    // todo might be able to be be altered when the data is processed based on old value...

    /*
   for(int i = 0; i < arraySize; i++){
        if(floatObjectArrayOld[i] != floatObjectArray[i])
         {
        Serial.print(floatObjectArray[i]);
        Serial.print(" - ");
        Serial.println(floatObjectArrayOld[i]);
        }
    }
    */


}

void HybridObject::developer() {
    developerStatus = true;
    init();
}

void HybridObject::add(char *obj, char *pos, String plugin) {
    init();

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);

    /* Serial1.print("a\n");
     Serial1.print(object);
     Serial1.print("\n");
     Serial1.print(arraySize);
     Serial1.print("\n");
     Serial1.print(plugin);
     Serial1.print("\n");*/

    char *objectPointer;
    objectPointer = (char *) malloc(strlen(obj) + strlen(pos) + 2);
    strcpy(objectPointer, pos);
    strcat(objectPointer, "\t");
    strcat(objectPointer, obj);

    arraySize++;
    stringArray = (char **) realloc(stringArray, (sizeof(char *) * arraySize));
    stringArray[arraySize - 1] = objectPointer;

    floatObjectArray = (float *) realloc(floatObjectArray, (sizeof(float) * arraySize));
    floatObjectArray[arraySize - 1] = 0;

    floatObjectArrayOld = (float *) realloc(floatObjectArrayOld, (sizeof(float) * arraySize));
    floatObjectArrayOld[arraySize - 1] = 1;


    plusObjectArray = (bool *) realloc(plusObjectArray, (sizeof(bool) * arraySize));
    plusObjectArray[arraySize - 1] = 1;

    minusObjectArray = (bool *) realloc(minusObjectArray, (sizeof(bool) * arraySize));
    minusObjectArray[arraySize - 1] = 1;


}

int HybridObject::printObjects() {
    for (int i = 0; i < arraySize; i++) {
        Serial1.println(stringArray[i]);
    }
}

float HybridObject::read(char *obj, char *pos) {

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);
    // object = obj +pos;
    for (int i = 0; i < arraySize; i++) {
        if (strcmp(stringArray[i], object) == 0)
            // if(floatObjectArray[i]!= floatObjectArrayOld[i]){
            // Serial.print("in: ");
            //     dtostrf(floatObjectArray[i], 5, 4, floatStr);
            //Serial.println(floatStr);}
            return floatObjectArray[i];
    }
    return 0;
}

int HybridObject::stepAvailable(char *obj, char *pos) {
    return stepAvailable(obj, pos, 1);
}

int HybridObject::stepAvailable(char *obj, char *pos, int steps) {

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);
    // object = obj +pos;
    if (steps > 0)
        for (int i = 0; i < arraySize; i++) {

            if (strcmp(stringArray[i], object) == 0) {

                if (plusObjectArray[i] == true) {
                    plusObjectArray[i] = false;

                    return 1;
                }

                if (minusObjectArray[i] == true) {
                    minusObjectArray[i] = false;

                    return -1;
                }


               // tempFloatBuffer = 0.0;



                if (floatObjectArray[i] != floatObjectArrayOld[i]){
                  /*  Serial.print(floatObjectArray[i]);
                    Serial.print(" ");
                    Serial.println(floatObjectArrayOld[i]);*/

                   // for (int w = 0; w < steps; w++) {
                      //  tempFloatBuffer = tempFloatBuffer + (1.0 / (steps + 1));

                      /*  Serial.print("BBBB > ");
                        Serial.print(tempFloatBuffer);
                        Serial.print(" ");
                        Serial.print(floatObjectArray[i]);
                        Serial.print(" ");
                        Serial.println(floatObjectArrayOld[i]);*/

                        if (floatObjectArray[i] > floatObjectArrayOld[i]) {
                          // floatObjectArrayOld[i] = floatObjectArray[i];
                            //Serial.println("hoch-----------------");

                            return -1;
                        }

                        if (floatObjectArray[i] < floatObjectArrayOld[i]) {
                           // floatObjectArrayOld[i] = floatObjectArray[i];
                           // Serial.println("rinter-----------------");
                            return 1;
                        }

                        //todo here I need the reference from an older run
                  //  }
                    return 1;
                }
                return 0;
            }
        }
    return 0;


}

bool HybridObject::readDigital(char *obj, char *pos) {
    readDigital(obj, pos, 0.5);
}

bool HybridObject::readDigital(char *obj, char *pos, float threshold) {

    if (threshold > 1.0) threshold = 1.0;
    if (threshold < 0.0) threshold = 0.0;

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);
    // object = obj +pos;
    for (int i = 0; i < arraySize; i++) {
        if (strcmp(stringArray[i], object) == 0) {

            if (floatObjectArray[i] < threshold) {
                return false;
            } else return true;
        }
    }
    return false;
}


float HybridObject::readFaster(int pos) {
    return floatObjectArray[pos];
}

void HybridObject::write(char *obj, char *pos, float data) {

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);

    for (int i = 0; i < arraySize; i++) {
        if (strcmp(stringArray[i], object) == 0) {

            if (floatObjectArray[i] != data) {
                //indicate that its a floating point value
                Serial1.print("f\n");
                Serial1.print(i);
                // Serial.println(i);
                Serial1.print("\n");

                // print normal value
                // Make sure that everything is within the scale
                if (data > 1) data = 1;
                if (data < 0) data = 0;

                dtostrf(data, 5, 4, floatStr);
                Serial1.print(floatStr);
                //  Serial.print("out: ");
                //  Serial.println(floatStr);
                // Serial.println(data);
                Serial1.print("\n");
                // Serial.println(tempFloatBuffer);

                floatObjectArray[i] = data;
            }

            // this is for keeping the system from crashing
            delay(SYSTEMDELAYFORDATA);
            break;

        }
    }
}

void HybridObject::writeStepUp(char *obj, char *pos) {
    writeStepUp(obj, pos, 1);
}

void HybridObject::writeStepDown(char *obj, char *pos) {
    writeStepDown(obj, pos, 1);
}

void HybridObject::writeStepUp(char *obj, char *pos, int steps) {
    writeStepSerial(obj, pos, steps, true);
}

void HybridObject::writeStepDown(char *obj, char *pos, int steps) {
    writeStepSerial(obj, pos, steps, false);
}

void HybridObject::writeStepSerial(char *obj, char *pos, int steps, bool direction) {

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);

    if (steps != 0)
        for (int i = 0; i < arraySize; i++) {
            if (strcmp(stringArray[i], object) == 0) {
                //indicate that its a floating point value
                if (direction) {
                    Serial1.print("p\n");
                   // Serial.println("p");
                    floatObjectArray[i] = floatObjectArray[i] + (1.0 / steps);
                    if (floatObjectArray[i] > 1.0) floatObjectArray[i] = 1.0;
                }
                else {
                    Serial1.print("n\n");
                  //  Serial.println("n");
                    floatObjectArray[i] = floatObjectArray[i] - (1.0 / steps);
                    if (floatObjectArray[i] < 0.0) floatObjectArray[i] = 0.0;
                }

                Serial1.print(i);
                // Serial.println(i);
                Serial1.print("\n");

                dtostrf(floatObjectArray[i], 5, 4, floatStr);
                Serial1.print(floatStr);
                // Serial.println(data);
                Serial1.print("\n");
                break;
            }
        }
}

void HybridObject::writeDigital(char *obj, char *pos, bool data) {

    strcpy(object, pos);
    strcat(object, "\t");
    strcat(object, obj);

    /*
    if(data>1.0) data = 1.0;
    if(data<0.0) data = 0.0;

    if(threshold>1.0) threshold = 1.0;
    if(threshold<0.0) threshold = 0.0;
     */


    if (data) tempFloatBuffer = 1.0;
    else tempFloatBuffer = 0.0;

    for (int i = 0; i < arraySize; i++) {
        if (strcmp(stringArray[i], object) == 0) {

            if (tempFloatBuffer != floatObjectArray[i]) {
                //indicate that its a floating point value
                Serial1.print("d\n");

                Serial1.print(i);
                // Serial.println(i);
                Serial1.print("\n");

                //print digital. optional change the sensitivity.
                Serial1.print(tempFloatBuffer);
                // Serial.println(tempFloatBuffer);
                // Serial.println(i);
                Serial1.print("\n");

                floatObjectArray[i] = tempFloatBuffer;
            }
            break;
        }
    }

}

void HybridObject::writeFaster(int pos, float data) {
    //indicate that its floating
    Serial1.print("f\n");
    Serial1.print(pos);
    Serial1.print("\n");

    Serial1.print(data);
    Serial1.print("\n");
    floatObjectArray[pos] = data;
}


float HybridObject::map(float x, float in_min, float in_max) {
    if (x > in_max) x = in_max;
    if (x < in_min) x = in_min;

    float out_min = 0;
    float out_max = 1;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void HybridObject::init() {
    if (runInit) {
        //     for(int i = 0; i <30; i++){

        Serial1.begin(BAUDRATE);

        while (!Serial1) { ; // wait for serial port to connect. Needed for Leonardo only
        }
        //delay(100);
        runInit = false;

        Serial1.print("okbird\n");
        //  Serial1.print("ok\n");

        for (int i = 0; i < arraySize; i++) {
            plusObjectArray[i] = false;
            minusObjectArray[i] = false;
        }


    }
}

void HybridObject::sendDeveloper() {
    Serial1.print("def\n");
    if (developerStatus) {
        Serial1.print("1\n");
    }
    else {
        Serial1.print("0\n");
    }
}