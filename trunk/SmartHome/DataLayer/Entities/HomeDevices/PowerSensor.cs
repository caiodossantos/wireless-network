﻿#region Using Statements
using DataLayer.Entities.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks; 
#endregion

namespace DataLayer.Entities.HomeDevices
{
    public class PowerSensor : HomeDevice
    {
        public const int DEFAULT_SENSIBILITY = 29; //AQUI PONEMOS ALGUNA REGLA ¿800 kw/h blabalbalbla?

        public byte Sensibility { set; get; }
        public int Consumption { set; get; }

        public PowerSensor()
            : base()
        {
            base.ConnectorCapable = ConnectorTypes.Dimmer;
        }


        public override void RefreshState()
        {
            base.RefreshState();
        }
    }
}