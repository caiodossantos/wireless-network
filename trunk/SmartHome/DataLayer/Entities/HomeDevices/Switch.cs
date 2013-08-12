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
    public class Switch: HomeDevice
    {
        public bool Open { get; set; }

        public Switch() : base() 
        {
            base.Operations = new List<Operation>();
            base.ConnectorCapable = ConnectorTypes.LogicInput;
        }

        public override void RefreshState()
        {
            base.RefreshState();
        }
    }
}