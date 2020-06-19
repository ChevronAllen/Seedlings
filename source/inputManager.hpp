#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <malloc.h>

#include "3ds.h"
#include <m3dia.hpp>



class Input
{
private:

    bool _micInitialized;

    
    u32 _micbuf_size;
    u32 _micbuf_pos; 
    u8* _micbuf;

    u32 _micbuf_datasize;
    u32 _audiobuf_size;
    u32 _audiobuf_pos;
    u8* _audiobuf;


    static Input* _instance;
    static Input* getInstance()
    {
        if(_instance != NULL)
        {
            return _instance;
        }else{initialize();}
    }
    Input(){}
    ~Input(){}

public:
    /**
     *  Initialize the Input Manager creating a new instance. This should only be called once in the app
     */
    static void initialize();

    /**
     *  Updates the Input Manager, during update the manager reads peripherals and updates their status.
     *  performing checks on their status.
     *  Should be at the start of each update cycle, before any accesses to Input
     */
    static void update();

    /**
     *  @brief 
     *  @returns 
     */
    static bool btn( m3d::buttons::Button );
    
    /**
     *  @brief 
     *  @returns 
     */
    static bool btnPressed( m3d::buttons::Button );
    
    /**
     *  @brief 
     *  @returns 
     */
    static bool btnReleased( m3d::buttons::Button );

    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector2f* getCirclePad();

    /**
     *  @brief reads the volume slider level
     *  @returns volume level from 0 - 63
     */
    static unsigned short int getVolume();

    /**
     *  @brief tests for a touch, and returns the screen position
     *  @return if a touch is detected returns a vector2 with u=x,v=u. If no touch was detected both axis are < 0
     */
    static m3d::Vector2f* touch();

    /**
     *  @brief 
     *  @param
     *  @warning Thread
     */
    static void recordMic(m3d::Parameter);
    
    /**
     *  Reads the last addition to the micstream; the bytes inserted since the last frame
     *  @returns
     */
    static void readMic();


    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector2f* getGyroscope();

    /**
     *  @brief 
     *  @returns 
     */
    static m3d::Vector3f* getAccelerometer();

    


};