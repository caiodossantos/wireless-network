﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Extensions.Enums
{
    public class Enums
    {
        public enum ConnectorType
        {
            SwitchLOW,
            SwitchHI,
            PWMTTL,
            Dimmer,
            IOLogic,
        }



        public enum BaseType
        {
            ATMega128RFA1,
        }



        public enum OPCode : byte
        {
            DigitalWrite = 0x05,
            DigitalSwitch = 0x06,
            DigitalWriteTime = 0x07,
            DigitalSwitchTime = 0x08,
            DigitalRead = 0x09,
            DigitalReadResponse = 0x0A,

            AnalogWrite = 0x10,
            AnalogWriteTime = 0x11,
            AnalogRead = 0x12,
            AnalogReadResponse = 0x13,

            Reset = 0x00,
            RouteTableRead = 0x01,
            RouteTableReadResponse = 0x02,

            TimeWrite = 0x20,
            TimeRead = 0x21,
            TimeReponse = 0x22,

            Warning = 0x30,
            Error = 0x31,

            ColorWrite = 0x50,
            ColorWriteRandom = 0x51,
            ColorSecuenceWrite = 0x52,
            ColorSortedSecuenceWrite = 0x53,
            ColorRead = 0x54,
            ColorReadResponse = 0x55,

            PresenceRead = 0x57,
            PresenceReadResponse = 0x58,

            TemperatureRead = 0x5A,
            TemperatureReadResponse = 0x5B,
            HumidityRead = 0x5C,
            HumidityReadResponse = 0x5D,

            PowerRead = 0x60,
            PowerReadResponse = 0x61,

            LuminosityRead = 0x63,
            LuminosityReadResponse = 0x64,
        }

        public enum PlugState
        {
        }


        public enum ShieldType
        {
            Example,
        }


        public enum HomeDeviceType : byte
        {
            Buttom = 0x00,
            Switch = 0x01,
            WallPlug = 0x02,
            Light = 0x03,
            Dimmable = 0x04,

            PresenceSensor = 0x10,
            PowerSensor = 0x11,
            TemperatureSensor = 0x12,
            HumiditySensor = 0x13,
            LightSensor = 0x14,

            DoorLock = 0x20,
            RGBLight = 0x21,
        }

    }
}
