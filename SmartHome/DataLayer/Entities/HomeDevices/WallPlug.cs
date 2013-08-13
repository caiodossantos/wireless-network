﻿#region Using Statements
using DataLayer.Entities.Enums;
using System.ComponentModel.DataAnnotations.Schema;

#endregion

namespace DataLayer.Entities.HomeDevices
{
    public class WallPlug : Light
    {
        public enum WallPlugType
        {
            AirFreshener,
            LightPoint,
            Matamosquitos,
            Fan,
            Heater,
            Speaker,
            Other,
            None,
        }

        public WallPlugType Type { get; set; }

        [NotMapped]
        public bool? Connected { get; set; }

        public WallPlug()
            : base()
        {
            base.ConnectorCapable = ConnectorTypes.SwitchHI;
        }
    }
}